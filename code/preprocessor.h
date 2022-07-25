#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

struct TokensVector
{
    std::string label;
    std::vector<std::string> tokens;
};
void str_toupper(std::string&);
void readfile(std::fstream&);
std::string removeFormat(std::string);
void removeComment (std::string&);
void parseTokens (std::string&, std::vector<TokensVector>&);
void printVec (std::vector<TokensVector>&);
void removeEmptylines (std::vector<TokensVector>&);