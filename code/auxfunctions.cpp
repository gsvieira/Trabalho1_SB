#include "auxfunctions.h"

void printVec(std::vector<TokensVector> &vec)
{
    for (auto line : vec)
    {
        if (!line.label.empty())
        {
            std::cout << line.label << " ";
        }
        if (!line.tokens.empty())
        {
            for (int i = 0; i < line.tokens.size(); i++)
            {
                if (i == 0)
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

void parseTokens(std::string &line, std::vector<TokensVector> &vec)
{
    std::string word;
    std::istringstream iss(line);
    size_t pos;
    int test;

    vec.emplace_back();

    while (iss >> word)
    {
        pos = word.find(':');
        if (pos != std::string::npos)
        {
            if (vec.back().label == "")
            {
                vec.back().label = word;
            }
            else
            {
                std::cout << "Erro: Mais de um rotulo na mesma linha" << std::endl;
                std::exit(0);
            }
        }
        else
        {
            vec.back().tokens.emplace_back(word);
        }
    }
}

void parseTokens(std::string &line, std::vector<TokensVector> &vec, int &linecounter)
{
    std::string word;
    std::istringstream iss(line);
    size_t pos;
    int test;

    vec.emplace_back();

    while (iss >> word)
    {
        pos = word.find(':');
        if (pos != std::string::npos)
        {
            if (vec.back().label == "")
            {
                vec.back().label = word; // adiciona no label da struct
            }
            else
            {
                std::cout << "Erro: Sintático - Mais de um rotulo na mesma linha - Linha: "<< linecounter << std::endl;
                std::exit(0);
            }
        }
        else
        {
            vec.back().tokens.emplace_back(word);
        }
    }
    linecounter++;
}
