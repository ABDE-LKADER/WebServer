#include "CgiHandler.hpp"
#include <string>
#include <unistd.h>

CgiHandler::CgiHandler(const Request& req, const Location& loc)
    : request(req), location(loc), script_path(""), cgi_executable("") {
}

CgiHandler::~CgiHandler() {
}

std::string CgiHandler::getFileExtension(const std::string& path) const {
	size_t dot_pos = path.find_last_of('.');
    if (dot_pos == std::string::npos) {
        return "";
    }
    return path.substr(dot_pos);
}

std::string CgiHandler::getCgiExecutable(const std::string& file_path) const{
	std::string extension = getFileExtension(file_path);
    const std::map<std::string, std::string>& cgi_map = location.getCgi();

    std::map<std::string, std::string>::const_iterator it = cgi_map.find(extension);
    if (it != cgi_map.end()) {
        return it->second;
    }
    return "";
}

Response CgiHandler::execute() {
	Response response;

	getFileExtension(request.path);
    // Set script path and CGI executable
    script_path = request.path;
    cgi_executable = getCgiExecutable(script_path);
    
    // Check if script exists and is executable
	std::cout << "Script to check: " << script_path.c_str() << std::endl;
    if (access(script_path.c_str(), F_OK) != 0) {
        response.generateErrorPage(request.server, 404);
        return response;
    }
    
    if (access(script_path.c_str(), X_OK) != 0) {
        response.generateErrorPage(request.server, 403);
        return response;
    }

    // Create pipes for communication
    // For POST, use file instead of pipe for input
    // Build environment variables and arguments
    // Fork and execute CGI

response.setStatusCode(999);
response.writeStringToBuffer("<body>handle CGI block</doby>");
return response;
}


