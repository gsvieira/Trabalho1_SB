#include "auxfunctions.h"

void printVec (std::vector<TokensVector>& vec)
{
    for(auto line: vec)
    {
        if (!line.label.empty())
        {
            std::cout << line.label<< " ";
        }
        if (!line.tokens.empty())
        {
            for (int i = 0; i < line.tokens.size(); i++)
            {
                if (i==0)
                {
                    std::cout << line.tokens[i];
                }
                else
                    std::cout << " " << line.tokens[i]; 
                
            }        
            std::cout << std::endl;
        }
        else
            std::cout << std::endl;
        }
}

void parseTokens (std::string& line, std::vector<TokensVector>& vec)
{
    std::string word;
    std::istringstream iss(line);
    size_t pos;
    int test;

    vec.emplace_back();
    
    //std::cout << "emplaced, size: " << vec.size() << std::endl;
    
    
    while (iss >> word)
    {
        pos = word.find(':');
        //std::cout << pos << std::endl;
        if (pos != std::string::npos)
        {
            //std::cout << "vec size " << vec.size() << std::endl;
            if (vec.back().label == "")
            {
                //std::cout << "find label" << std::endl;
                vec.back().label = word;  //adiciona no label da struct

                // std::cout << "size of buf: " << iss.rdbuf()->in_avail() << std::endl;
                // if (iss.rdbuf()->in_avail() == 0)
                // {
                //     std::cout << "end of line" << std::endl;
                // }
                
            }
            else
            {
                std::cout << "Erro: Mais de um rotulo na mesma linha" << std::endl;
                std::exit(0);
            }           
        }
        else
        {
            //std::cout<< word << std::endl;
            vec.back().tokens.emplace_back(word);
        }
        
    
    }
}
