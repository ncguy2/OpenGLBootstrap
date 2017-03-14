//
// Created by Guy on 14/03/2017.
//

#ifndef OPENGLBOOTSTRAP_STRINGUTILS_H
#define OPENGLBOOTSTRAP_STRINGUTILS_H

#include <string>
#include <vector>

using namespace std;

namespace utils {
    vector<string> Split(const string& text, char delim);
    bool StartsWith(const string& text, const string& token);

    string &LTrim(string& str);
    string &RTrim(string& str);
    string &Trim(string& str);

    string Dirname(const string &str);
    void Peekline(ifstream& in, string& str);
}

#endif //OPENGLBOOTSTRAP_STRINGUTILS_H
