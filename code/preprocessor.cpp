#include "preprocessor.h"



void readfile(std::fstream& file)
{
    std::string line;
    int linecount;
    std::vector<TokensVector> vec;

    while(!file.eof())
    {
        getline(file, line);
        str_toupper(line);
        removeComment(line);        
        parseTokens(line, vec);
        //std::cout << line << std::endl;
        
    }
    removeEmptylines(vec);
    resolveEQU(vec);
    resolveIF(vec);
    printVec(vec);
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

void removeComment (std::string& line)
{
    size_t pos;
    pos = line.find(';');
    if(pos != std::string::npos)
    {
        line.erase(pos); //ignorar comentários apagando todos os char após o ';'
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