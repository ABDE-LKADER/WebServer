#include "CgiHandler.hpp"

CgiHandler::CgiHandler(const Request& req, const Location& loc)
    : request(req), location(loc) {
}

CgiHandler::~CgiHandler() {
}

Response CgiHandler::execute() {
// NOTE: test response
Response response;
response.setStatusCode(999);
response.writeStringToBuffer("<body>handle CGI block</doby>");
return response;
}


