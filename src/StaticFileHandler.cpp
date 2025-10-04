#include "../includes/StaticFileHandler.hpp"

StaticFileHandler::StaticFileHandler() {
}

StaticFileHandler::~StaticFileHandler() {
}

std::string StaticFileHandler::getMimeType(const std::string& path) const {
    size_t dot_pos = path.find_last_of('.');
    if (dot_pos == std::string::npos) {
        return "application/octet-stream";
    }
    
    std::string extension = path.substr(dot_pos + 1);
    
    // Convert to lowercase
    for (std::string::iterator it = extension.begin(); it != extension.end(); ++it) {
        *it = std::tolower(static_cast<unsigned char>(*it));
    }
    
    if (extension == "txt")  return "text/plain";
    if (extension == "html") return "text/html";

    return "application/octet-stream";
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

std::string StaticFileHandler::getContentType(const std::string& path) const {
    return getMimeType(path);
}

