#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

std::string removeComments(const std::string& code);
std::string normalizeCode(const std::string& code);
std::vector<std::string> tokenize(const std::string& code);
std::vector<std::string> processFile(const std::string& filename);

#endif
