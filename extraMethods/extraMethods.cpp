
#include "extraMethods.h"
#include <iterator>

std::vector<std::string> splitString(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream ss(s);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    return tokens;
}

std::vector<std::string> tokenize(const std::string& str, char delim) {
    std::vector<std::string> tokens;

    size_t start = 0;
    size_t end = str.find(delim);

    for (; end != std::string::npos; start = end + 1, end = str.find(delim, start)) {
        tokens.push_back(str.substr(start, end - start));
    }

    // Handle the last token after the last delimiter
    tokens.push_back(str.substr(start));

    return tokens;
}
