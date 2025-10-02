#include "../includes/StaticFileHandler.hpp"

StaticFileHandler::StaticFileHandler() {
}

StaticFileHandler::~StaticFileHandler() {
}

bool StaticFileHandler::fileExists(const std::string& path) const {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

bool StaticFileHandler::isDirectory(const std::string& path) const {
    struct stat buffer;
    if (stat(path.c_str(), &buffer) != 0) {
        return false;
    }
    return S_ISDIR(buffer.st_mode);
}

bool StaticFileHandler::isReadable(const std::string& path) const {
    return (access(path.c_str(), R_OK) == 0);
}

