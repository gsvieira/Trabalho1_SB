#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

struct TokensVector
{
    std::string label;
    std::vector<std::string> tokens;
};

void parseTokens (std::string&, std::vector<TokensVector>&);
void printVec (std::vector<TokensVector>&);