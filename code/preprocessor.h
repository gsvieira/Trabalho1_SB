#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include<algorithm>
#include<regex>

struct arrayOfTokens
{
    std::string Label;
    std::vector<std::string> tokens;
};
void str_toupper(std::string&);
void readfile(std::fstream&);
std::string removeFormat(std::string);
void removeComment (std::string&);