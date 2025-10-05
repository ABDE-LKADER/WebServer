#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include "ServerConfig.hpp"
#include <string>

class ErrorHandler {
private:
    const ServerConfig& server_config;

public:
    ErrorHandler(const ServerConfig& config);
    ~ErrorHandler();

};

#endif

