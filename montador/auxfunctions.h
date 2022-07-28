#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cwctype>

struct TokensVector
{
    std::string label;
    std::vector<std::string> tokens;
};

void parseTokens(std::string &, std::vector<TokensVector> &);
void parseTokens(std::string &, std::vector<TokensVector> &, int &);
void printVec(std::vector<TokensVector> &);
void preprocessor2file(std::vector<TokensVector> &, std::fstream &);