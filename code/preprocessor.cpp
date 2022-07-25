#include "preprocessor.h"




void readfile(std::fstream& file)
{
    std::string line, word;
    std::istringstream iss;
    size_t pos;
    int linecount;

    while(!file.eof())
    {
        std::vector<struct TokensVector> vec;
        int vecPos = 0;
        getline(file, line);
        str_toupper(line);
        removeComment(line);
        std::istringstream iss(line);
        std::cout << line << std::endl;
        while (iss >> word)
        {
            pos = word.find(':');
            if (pos != std::string::npos)
            {
                if (vec[vecPos].label == "")
                {
                    vec[vecPos].label = word;  //adiciona no label da struct
                }
                else
                {
                    std::cout << "Erro: Mais de um rotulo na mesma linha" << std::endl;
                }                                
            //se as palavras acabam, pega proxima linha e junta na com a anterior (resolve rotulo \n)
            
            }
            //procurar equ e if
            
        }
        
        
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