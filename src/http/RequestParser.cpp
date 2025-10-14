# include "Core.hpp"
# include "RequestParser.hpp"

bool	RequestParser::isCTL( unsigned char c ) {
	return (c <= 31) || (c == 127);
}

bool	RequestParser::isValidMethod( const std::string &method ) {
	return method == "GET" || method == "DELETE" || method == "POST";
}

bool	RequestParser::isValidVersion( const std::string &version ) {
	return version == "HTTP/1.1" || version == "HTTP/1.0";
}

bool	RequestParser::allDigits( const std::string &num ) {
	return num.find_first_not_of("0123456789") == std::string::npos;
}

std::string	RequestParser::toUpperInPlace( std::string token ) {
	for (size_t index = 0; index < token.size(); ++index)
		token[index] = std::toupper(token[index]);
	return token;
}

bool	RequestParser::isTspecials( unsigned char c ) {
	switch (c) {
		case '(': case ')': case '<': case '>': case '@':
		case ',': case ';': case ':': case '\\': case '\"':
		case '/': case '[': case ']': case '?': case '=':
		case '{': case '}': case ' ': case '\t':
			return true;
		default:
			return false;
	}
}

bool	RequestParser::percentDecode( const std::string &target ) {
	for (size_t index = 0; index < target.size(); ++index) {
		if (target[index] == '%') {
			if (index + 2 >= target.size()) return false;
			if (!std::isxdigit(target[index + 1]) || !std::isxdigit(target[index + 2]))
				return false;
			index += 2;
		}
	}
	return true;
}

bool	RequestParser::methodParser( std::string &method, int &code) {
	code = 400;

	if (method.empty()) return false;

	for (size_t index = 0; index < method.size(); ++index)
		if (isTspecials(method[index]) || isCTL(method[index]))
			return false;

	if (isValidMethod(method)) return true;
	if (isValidMethod(toUpperInPlace(method))) return false;

	return (code = 501, false);
}

bool	RequestParser::targetParser( std::string &target, std::string &query ) {
	if(target.empty() || target[0] != '/') return false;

	if (target.find('#') != std::string::npos) return false;

	for (size_t index = 0; index < target.size(); ++index) {
		if (isCTL(target[index]) || target[index] == ' '
				|| target[index] == '\t' || target[index] == '\\')
			return false;
	}

	if (percentDecode(target) == false) return false; 

	if (target.find("..") != std::string::npos) return false;

	size_t		pos;

	if((pos = target.find('?')) != std::string::npos) {
		query = target.substr(pos + 1);
		target.erase(pos);
	}

	return true;
}

bool	RequestParser::versionParser( std::string &version, int &code ) {
	code = 400;

	const std::string		prefix = "HTTP/";

	if (version.size() < prefix.size() + 3) return false;
	if (version.compare(0, prefix.size(), prefix) != 0) return false;

	size_t			dot = version.find('.', prefix.size());
	if (dot == std::string::npos) return false;

	std::string		major = version.substr(prefix.size(), dot - prefix.size());
	std::string		minor = version.substr(dot + 1);

	// if (!allDigits(major) || !allDigits(minor)) return false;
	if (major == "1" && (minor == "0" || minor == "1")) return true;

	return (code = 501, false);
}

State	RequestParser::requestLineParser( Request &request ) {	
	size_t				pos;
	std::string			CRLF("\r\n");

	if ((pos = request.recv.find(CRLF)) == std::string::npos) {
		if (request.recv.size() > MAX_REQUEST_LINE) return State(414, BAD);
		return State(0, REQUEST_LINE);
	}

	if (request.recv.size() > MAX_REQUEST_LINE) return State(414, BAD);

	std::string			line = request.recv.substr(0, pos);
	int					code;

	request.recv.erase(0, pos + CRLF.size());

	char				sp, space, extra;
	std::istringstream	streamLine(line);	

	streamLine >> std::noskipws >> request.method >> sp
		>> request.target >> space >> request.version;

	if (streamLine.fail()) return State(400, BAD);

	if (sp != ' ' || space != ' ') return State(400, BAD);

	if (methodParser(request.method, code) == false) return State(code, BAD);

	if (targetParser(request.target, request.query) == false) return State(400, BAD);

	if (versionParser(request.version, code) == false) return State(code, BAD);

	if (streamLine >> extra) return State(400, BAD);

	request.full_path = "." + request.server.getLocations().find("/")->second.getRoot()
			+ request.target; // Full Path Handler

	std::cout << "[ " << request.method <<  " ] " 
			<< "[ " << request.target <<  " ] " 
			<< "[ " << request.version <<  " ] " << std::endl;

	return State(0, READING_HEADERS);
}

State	RequestParser::headersParser( Request &request ) {
	std::string			DCRLF("\r\n");
	size_t				pos;

	if ((pos = request.recv.find(DCRLF)) == std::string::npos)
		return State(0, READING_HEADERS);

	std::stringstream	headersBlock;

	headersBlock << request.recv.substr(0, pos);
	request.recv.erase(0, pos + DCRLF.size());

	std::string			line;
	while (std::getline(headersBlock, line)) {
		if (line.empty()) continue ;

		std::string::size_type	colum = line.find(':');

		if (line[0] == ' ' || line[0] == '\t' || colum == std::string::npos)
			return State(400, BAD);

		std::string				name = line.substr(0, colum);
		std::string				value = line.substr(colum + 1);

		std::transform(name.begin(), name.end(), name.begin(),
			static_cast<int(*)(int)>(std::tolower));

		for (size_t index = 0; index < value.size() && (value[index] == ' '
				|| value[index] == '\t'); ++index)
			value.erase(0, index);

		for (size_t index = value.size(); index > 0 && (value[index - 1] == ' '
				|| value[index - 1] == '\r'); --index)
			value.erase(index - 1);

		if (name == "transfer-encoding") return State(400, BAD);

		std::cout << "[ " + name + " ]" << "[ " + value + " ]" << std::endl;

		request.headers[name] = value;
	}

	if (request.method == "POST") return State(0, READING_BODY);

	return State(0, READY_TO_WRITE);
}

State	RequestParser::bodyParser( Request &request ) {
	std::cout << request.recv << std::endl;
	return State(0, READY_TO_WRITE);
}
