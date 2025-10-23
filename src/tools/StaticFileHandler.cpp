# include "Core.hpp"
# include "MimeResolver.hpp"
# include "StaticFileHandler.hpp"

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

std::string StaticFileHandler::readFile(const std::string& path) const {
    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

bool    StaticFileHandler::deleteFile(const std::string& path) const {
    return (std::remove(path.c_str()) == 0);
}

std::vector<std::string>    StaticFileHandler::listDirectory(const std::string& path) const {
    std::vector<std::string> entries;

    DIR* dir = opendir(path.c_str());
    if (dir == NULL) {
        return entries;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;

        // Skip . and ..
        if (name == "." || name == "..") {
            continue;
        }

        // Add "/" to directories
        std::string full_path = path + "/" + name;
        if (isDirectory(full_path)) {
            name += "/";
        }

        entries.push_back(name);
    }

    closedir(dir);

    std::sort(entries.begin(), entries.end());

    return entries;
}

std::string StaticFileHandler::getContentType(const std::string& path) const {
    MimeResolver resolver;
    size_t dot_pos = path.find_last_of('.');

    if (dot_pos == std::string::npos)
        return resolver.getMimeType("bin");

    std::string extension = path.substr(dot_pos + 1);
    return resolver.getMimeType(extension);
}

bool StaticFileHandler::isPathSafe(const std::string& path) const {
    // Check for directory traversal attempts
    if (path.find("..") != std::string::npos) {
        return false;
    }

    // Check for null bytes
    if (path.find('\0') != std::string::npos) {
        return false;
    }

    return true;
}
