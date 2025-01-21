#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <any>

class JsonParser {
public:
    JsonParser();
    JsonParser(const std::string& filename);

    bool loadJson(const std::string& filename);
    bool saveJson(const std::string& filename);

    template <typename T>
    T get(const std::string& key) const;

    template <typename T>
    void set(const std::string& key, const T& value);

private:
    std::map<std::string, std::any> jsonData;

    // Helper functions to parse and write simple JSON-like data
    void trim(std::string& str) const;
    bool isNumber(const std::string& str) const;
    bool isBool(const std::string& str) const;
};

#endif // JSONPARSER_H
