#include "tokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

// Remove multi-line comments manually
string removeMultiLineComments(const string& code) {
    string result;
    bool inComment = false;

    for (size_t i = 0; i < code.length(); ++i) {
        if (!inComment && i + 1 < code.length() && code[i] == '/' && code[i + 1] == '*') {
            inComment = true;
            ++i; // skip '*'
        } else if (inComment && i + 1 < code.length() && code[i] == '*' && code[i + 1] == '/') {
            inComment = false;
            ++i; // skip '/'
        } else if (!inComment) {
            result += code[i];
        }
    }

    return result;
}

// Remove single-line and then multi-line comments
string removeComments(const string& code) {
    string noSingleLine = regex_replace(code, regex("//.*"), "");
    return removeMultiLineComments(noSingleLine);
}

// Normalize whitespace and remove newlines
string normalizeCode(const string& code) {
    string result = regex_replace(code, regex(R"([\n\r\t]+)"), " ");
    result = regex_replace(result, regex(R"( +)"), " ");
    return result;
}

// Tokenize based on basic C++ syntax
vector<string> tokenize(const string& code) {
    vector<string> tokens;
    regex word_regex(R"([\w#]+|==|!=|<=|>=|&&|\|\||[{}\(\);,+*/=<>-])");

    auto words_begin = sregex_iterator(code.begin(), code.end(), word_regex);
    auto words_end = sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        tokens.push_back(it->str());
    }
    return tokens;
}

// Read and process file
vector<string> processFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << filename << endl;
        return {};
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    string noComments = removeComments(content);
    string normalized = normalizeCode(noComments);
    return tokenize(normalized);
}
