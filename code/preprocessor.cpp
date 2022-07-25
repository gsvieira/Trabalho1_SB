#include "preprocessor.h"




void readfile(std::fstream& file)
{
    std::string line;
    int linecount;

    while(!file.eof())
    {
        std::vector<TokensVector> vec;
        getline(file, line);
        str_toupper(line);
        removeComment(line);        
        std::cout << line << std::endl;
        parseTokens(line, vec);
        
        
        
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
    int vecPos = 0;
    size_t pos;
    int test;
    if (vec.size() <= vecPos)
        {
            vec.emplace_back();
            std::cout << "emplaced, size: " << vec.size() << std::endl;
        }
        
        while (iss >> word)
        {
            //std::cout << "reading line" << std::endl;
            std::cout << test++ << std::endl;
            pos = word.find(':');
            std::cout << pos << std::endl;
            if (pos != std::string::npos)
            {
                std::cout << "vec size " << vec.size() << std::endl;
                if (vec[vecPos].label == "")
                {
                    //std::cout << "find label" << std::endl;
                    vec[vecPos].label = word;  //adiciona no label da struct
                    std::cout << "size of buf: " << iss.rdbuf()->in_avail() << std::endl;
                    if (iss.rdbuf()->in_avail() == 0)
                    {
                        std::cout << "end of line" << std::endl;
                    }
                    continue;
                }
                // else
                // {
                //     std::cout << "Erro: Mais de um rotulo na mesma linha" << std::endl;
                //     std::exit(0);
                // }           
            }
            else
            {
                //std::cout<< word << std::endl;
                vec[vecPos].tokens.emplace_back(word);
            }
            
            
            vecPos++;
        }
}

void printVec (std::vector<TokensVector>& vec)
{
    for(auto content: vec)
    {
        if (content.label != "")
        {
            std::cout << content.label<< " ";
        }
        for (int i = 0; i < sizeof(content.tokens); i++)
        {
            if (i == sizeof(content.tokens))
            {
                std::cout << content.tokens[i] << std::endl;
            }
            else
            {
            std::cout << content.tokens[i] << " ";
            }
        }        
    }
}