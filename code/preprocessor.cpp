#include "preprocessor.h"




void readfile(std::fstream& file)
{
    std::string line, word;
    std::istringstream iss;

    while(!file.eof())
    {
        getline(file, line);
        str_toupper(line);
        removeComment(line);
        std::istringstream iss(line);
        std::cout << line << std::endl;
        // while (iss >> word)
        // {
        //     std::cout<< '|' <<word.c_str()<< '|' <<std::endl;
        // }
        
    }
}



int main(int argc, char* argv[])
{
    std::fstream file(argv[2]);
    readfile(file);
}

void str_toupper(std::string& s)
{
    std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){ return std::toupper(c);});
}

std::string removeFormat(std::string inputstr)
{
    size_t comentpos;
    std::regex str_expr("\\s+");
    std::string result = std::regex_replace(inputstr,str_expr," ");
    std::regex str_expr1("^[\\s]+|[\\s]+$|;.*");
    result = std::regex_replace(result,str_expr1,"");
    return result;
}

void removeComment (std::string& line)
{
    size_t pos;
    pos = line.find(';');
    if(pos != std::string::npos)
    {
        line.erase(pos); //ignorar comentários apagando todos os char após o ';'
    }
}