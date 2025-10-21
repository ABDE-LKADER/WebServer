# include "Request.hpp"

Request::Request( void ) { }

Request::Request( ServerConfig &serv ) : server(serv),
		has_conlen(false), content_length(0) { }

Request::~Request( void ) { }

bool	Request::isMethodAllowed( void ) {
	const std::vector<std::string>	&allowed = location.getMethods();

	if (allowed.empty()) return (method == "GET");

	for (size_t index = 0; index < allowed.size(); ++index)
		if (allowed[index] == method) return true;

	return false;
}

std::string	joinPath ( const std::string &root, const std::string &target ) {
	if (root.empty()) return target;
	if (target.empty()) return root;

	if (root[root.size() - 1] == '/' && target[0] == '/')
		return root + target.substr(1);

	if (root[root.size() - 1] != '/' && target[0] != '/')
		return root + "/" + target;

	return root + target;
}

std::string	Request::longestPrefixMatch( void ) {
	std::string						longest = "/";
	const map_location				&locations = server.getLocations();

	for (map_location::const_iterator curr = locations.begin();
			curr != locations.end(); curr++) {
		const std::string		&prefix = curr->first;

		if (prefix.size() <= longest.size()) continue ;
		if (target.size() < prefix.size()) continue ;
		if (target.rfind(prefix, 0)) continue ;

		if (target.size() != prefix.size() && target[prefix.size()] != '/'
				&& prefix[prefix.size() - 1] != '/') continue ;

		longest = prefix;
	}

	return longest;
}

void	Request::isValidHeaders( void ) {
	if (headers.find("transfer-encoding") != headers.end())
		throw State(400, BAD);

	if (method != "POST") return ;

	map_t::iterator		headerIter = headers.find("content-length");

	if (headerIter == headers.end()) throw State(400, BAD);

	std::string		value = headerIter->second;

	if (value.empty()) throw State(400, BAD);

	if (value.find_first_not_of("0123456789") != std::string::npos)
		throw State(400, BAD);

	std::stringstream		convert(value);

	has_conlen = true;
	convert >> content_length;
	if (convert.fail()) throw State(400, BAD);

	size_t	max_size = server.getMaxClientBodySize();
	if (content_length > max_size) throw State(413, BAD);

	headerIter = headers.find("content-type");
	if (headerIter != headers.end()) {
		;
	}
}

void	Request::startProssessing( void ) {
	const map_location				&locations = server.getLocations();
	std::string						longestM = longestPrefixMatch();
	map_location::const_iterator	hit = locations.find(longestM);

	if (hit != locations.end()) location = hit->second;
	else throw State(404, BAD);

	if (!isMethodAllowed()) throw State(405, BAD);

	std::cout << "startProssessing ..." << std::endl;
	if (method == "POST") {
		/* For Handling POST Requirement PATH UPLOAD*/
		path = joinPath(location.getUploadLocation(), target);
	}

	else {
		path = target.substr(longestM.size());
		path = joinPath(location.getRoot(), path);
	}

	std::cout << "[ " << longestM << " ]"
			  << "[ " << content_length << " ]"
				 "[ " << path << " ]" << std::endl;

	if (method != "POST") throw State(0, READY_TO_WRITE);
}

void	Request::streamBodies( void ) {
	std::ofstream		outfile(path.c_str());

	if (!outfile.is_open()) throw State(500, BAD);

	if (recv.length() > content_length) {
		outfile << recv;
		content_length -= recv.length();
		return ;
	}

	outfile << recv.substr(0, content_length);
	outfile.close();

	throw State(0, READY_TO_WRITE);
}
