#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

struct TokensVector
{
    std::string label;
    std::vector<std::string> tokens;
};

struct TabelaEQU 
{
    std::string label;
    std::string value;
};

void str_toupper(std::string&);
void readfile(std::fstream&, std::string);
std::string removeFormat(std::string);
void removeComment (std::string&);
void parseTokens (std::string&, std::vector<TokensVector>&);
void printVec (std::vector<TokensVector>&);
void removeEmptylines (std::vector<TokensVector>&);
void resolveEQU (std::vector<TokensVector>&);
void resolveIF (std::vector<TokensVector>&);
void preprocessor2file(std::vector<TokensVector>&, std::string);