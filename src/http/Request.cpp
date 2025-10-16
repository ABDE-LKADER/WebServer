# include "Request.hpp"

Request::Request( void ) { }

Request::Request( ServerConfig &serv ) : server(serv),
		has_content_length(false), content_length(0) { }

Request::~Request( void ) { }

void	Request::start( void ) {
	;
}

bool	Request::longestPrefixMatch( void ) {
	// const std::map<std::string, Location>	locations = server.getLocations();

	// for (std::map<std::string, Location>::const_iterator curr = locations.begin();
	// 		curr != locations.end(); curr++) {
	// 			;
	// }

	location = server.getLocations().find("/")->second;
	return true;
}

void	Request::setLocationPath( void ) {
	longestPrefixMatch();

	std::cout << target << std::endl;
}
