#ifndef HTTPRESPONSEBUILDER_HPP
#define HTTPRESPONSEBUILDER_HPP

#include "HttpResponse.hpp"
#include "ServerConfig.hpp"
#include "StaticFileHandler.hpp"
#include "Client.hpp"
#include "ErrorHandler.hpp"

#include <iostream>

class HttpResponseBuilder {
private:
    const ServerConfig&         server_config;
    ErrorHandler                error_handler;
    StaticFileHandler           static_handler;


public:
    HttpResponseBuilder(const ServerConfig& config);
    ~HttpResponseBuilder();

    std::string     generateDirectoryListing(const std::string& path) const;

    bool            isMethodAllowed(const std::string& method, const Location& location) const;
    HttpResponse    handleAutoIndex(const std::string& path) const;
    HttpResponse    buildResponse(Client& client);

    HttpResponse    handleGet(const HttpRequest& request, const Location& location);
};

#endif

