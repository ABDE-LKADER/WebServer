#ifndef STATICFILEHANDLER_HPP
#define STATICFILEHANDLER_HPP

#include <sys/stat.h>
#include <string>
#include <unistd.h>

class StaticFileHandler {
private:
    
public:
    StaticFileHandler();
    ~StaticFileHandler();
    
    bool fileExists(const std::string& path) const;
    bool isDirectory(const std::string& path) const;
    bool isReadable(const std::string& path) const;

};

#endif

