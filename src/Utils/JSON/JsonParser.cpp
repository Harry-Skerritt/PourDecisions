#include "JsonParser.h"

JsonParser::JsonParser() {}

JsonParser::JsonParser(const std::string& filename) {
    loadJson(filename);
}

bool JsonParser::loadJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        trim(line);
        if (line.empty() || line[0] == '{' || line[0] == '}') {
            continue;  // Skip empty lines and braces
        }

        size_t separatorPos = line.find(':');
        if (separatorPos == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, separatorPos);
        std::string value = line.substr(separatorPos + 1);

        trim(key);
        trim(value);

        if (isNumber(value)) {
            jsonData[key] = std::stoi(value);  // Store as int
        }
        else if (isBool(value)) {
            jsonData[key] = (value == "true");  // Store as bool
        }
        else if (value.find('.') != std::string::npos) {
            jsonData[key] = std::stof(value);  // Store as float
        }
        else {
            jsonData[key] = value;  // Store as string
        }
    }

    file.close();
    return true;
}

bool JsonParser::saveJson(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << "{\n";
    for (const auto& [key, value] : jsonData) {
        file << "  \"" << key << "\": ";

        if (value.type() == typeid(int)) {
            file << std::any_cast<int>(value);
        }
        else if (value.type() == typeid(bool)) {
            file << (std::any_cast<bool>(value) ? "true" : "false");
        }
        else if (value.type() == typeid(float)) {
            file << std::any_cast<float>(value);
        }
        else if (value.type() == typeid(std::string)) {
            file << "\"" << std::any_cast<std::string>(value) << "\"";
        }

        file << ",\n";
    }

    file << "}\n";
    file.close();
    return true;
}

template <typename T>
T JsonParser::get(const std::string& key) const {
    auto it = jsonData.find(key);
    if (it == jsonData.end()) {
        throw std::runtime_error("Key not found in the JSON data: " + key);
    }
    try {
        return std::any_cast<T>(it->second);
    }
    catch (const std::bad_any_cast& e) {
        throw std::runtime_error("Bad any_cast for key: " + key);
    }
}

template <typename T>
void JsonParser::set(const std::string& key, const T& value) {
    jsonData[key] = value;
}

void JsonParser::trim(std::string& str) const {
    const std::string whitespace = " \t\n\r";
    size_t first = str.find_first_not_of(whitespace);
    size_t last = str.find_last_not_of(whitespace);
    if (first == std::string::npos || last == std::string::npos) {
        str.clear();
    }
    else {
        str = str.substr(first, last - first + 1);
    }
}

bool JsonParser::isNumber(const std::string& str) const {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

bool JsonParser::isBool(const std::string& str) const {
    return str == "true" || str == "false";
}
