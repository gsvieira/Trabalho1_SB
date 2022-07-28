#include "preprocessor.h"



void readfile(std::fstream& file, std::string ofile)
{
    std::string line;
    std::vector<TokensVector> vec;
    int linecounter = 0;

    while(!file.eof())
    {
        getline(file, line);
        str_toupper(line);
        removeComment(line);        
        parseTokens(line, vec, linecounter);
        //std::cout << line << std::endl;
        
    }
    removeEmptylines(vec);
    resolveEQU(vec);
    resolveIF(vec);
    printVec(vec);
    std::fstream outputfile(ofile, std::ios_base::out);
    preprocessor2file(vec, outputfile);
}

void str_toupper(std::string& s)
{
    std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){ return std::toupper(c);});
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


void removeEmptylines (std::vector<TokensVector>& vec)
{
    auto it = vec.begin();
    while (it != vec.end())
    {
        //std::cout << "valores: "<< !(*it).label.empty() << std::endl << (*it).tokens.empty() << std::endl;

        if (((*it).label.empty() && (*it).tokens.empty()))
        {
            it = vec.erase(it);
        } else if ((!(*it).label.empty()) && ((*it).tokens.empty()))
        {
            (*it).tokens.swap((*(it+1)).tokens); //= (*(it+1)).tokens; // vec[i].tokens = vec[i+1].tokens
            it++;
        }
        else
        {
            it++;
        }
        
        
    }
    
}

void resolveEQU (std::vector<TokensVector>& vec )
{
    std::vector<TabelaEQU> equ;
    std::string value, label;

    
    for (auto &&line:vec)
    {
        if (line.tokens[0] == "EQU")
        {
            label = line.label.substr(0,line.label.find(":"));
            value = line.tokens[1];
            equ.push_back({label, value});
            line.label = "";
            line.tokens.clear();
        }
        else if (line.tokens[0] == "IF" || line.tokens[0] == "CONST")
        {
            for (auto &&lt : equ)
            {
                if (line.tokens[1] == lt.label)
                {
                    line.tokens[1] = lt.value;
                }
                
            }
                
        }       
    }
    removeEmptylines(vec); //remove lines with EQU
}

void resolveIF (std::vector<TokensVector>& vec )
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (!vec[i].tokens.empty())
        {
            if (vec[i].tokens[0] == "IF")
            {
                
                vec[i].label = "";
                vec[i].tokens.clear();
                if (vec[i].tokens[1] == "0")
                {
                    vec[i+1].label = "";
                    vec[i+1].tokens.clear();
                }
            }            
        }    
    }
    removeEmptylines(vec);
}

