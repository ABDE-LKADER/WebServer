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

bool	Request::isValidHeaders( void ) {
	return true;
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

State	Request::startProssessing( void ) {
	const map_location				&locations = server.getLocations();
	std::string						longestM = longestPrefixMatch();
	map_location::const_iterator	hit = locations.find(longestM);

	if (hit != locations.end()) location = hit->second;
	else return State(404, BAD);

	if (!isMethodAllowed()) return State(405, BAD);

	path = target.substr(longestM.size());
	path = joinPath(location.getRoot(), path);

	std::cout << path << std::endl;
	return State(0, READING_HEADERS);
}

State	Request::streamBodies( void ) {
	std::ofstream		outfile(path.c_str());

	if (!outfile.is_open()) return State(500, BAD);

	if (recv.length() >= content_length) {
		outfile << recv;
		content_length -= recv.length();
	}
	else if (!content_length) {
		outfile << recv.substr(0, content_length);
		content_length = 0;
		return State(0, READY_TO_WRITE);
	}

	return State(0, READING_BODY);
}
