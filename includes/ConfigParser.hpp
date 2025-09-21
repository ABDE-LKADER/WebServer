#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include "ServerConfig.hpp"
#include <string>
#include <vector>

class ConfigParser {
private:
    std::string filename;
    std::vector<std::string> tokens;

public:
    ConfigParser(const std::string& filename);
    ~ConfigParser();

    ServerConfig parseConfig();

private:
    bool readFile();
    void tokenize(const std::string& content);

    void trim(std::string& str);
    void throwParseError(const std::string& message);
};

#endif

