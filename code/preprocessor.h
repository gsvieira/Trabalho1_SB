#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "auxfunctions.h"

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
void removeEmptylines (std::vector<TokensVector>&);
void resolveEQU (std::vector<TokensVector>&);
void resolveIF (std::vector<TokensVector>&);
void preprocessor2file(std::vector<TokensVector>&, std::string);