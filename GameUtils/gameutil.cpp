#include "gameutil.h"

std::vector<std::string> splitString(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream ss(s);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    return tokens;
}