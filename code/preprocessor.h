#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<algorithm>
#include<regex>

struct preprocessor
{
    
};
void str_toupper(std::string&);
void readfile(std::fstream&);
std::string removeFormat(std::string);
void removeComment (std::string&);