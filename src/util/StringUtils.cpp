//
// Created by Guy on 14/03/2017.
//

#include <algorithm>
#include "../../include/util/StringUtils.h"

std::vector<std::string> utils::Split(const std::string& text, char delim) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(delim, start)) != std::string::npos) {
        if (end != start)
            tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    if (end != start)
        tokens.push_back(text.substr(start));
    return tokens;
}

bool utils::StartsWith(const std::string &text, const std::string &token) {
    if(text.length() < token.length())
        return false;
    return (text.compare(0, token.length(), token) == 0);
}

string& utils::LTrim(string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return str;
}

string& utils::RTrim(string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    return str;
}

string& utils::Trim(string &str) {
    return LTrim(RTrim(str));
}

string utils::Dirname(const string &str) {
    size_t found;
    found = str.find_last_of("/\\");
    return str.substr(0, found);
}
