#include "ligador.h"

int main(int argc, char *argv[])
{
    if (argc <= 2 || argc > 3)
    {
        std::cout << "Forma de utilizar o programa incorreta!" << std::endl
                  << "Exemplo: ./ligador myfile.o myfile2.o";
    }

    std::fstream file1(argv[1]);
    std::fstream file2(argv[2]);
    std::vector<TokensVector> usetable1, usetable2;
    std::vector<DefinitionTable> deftable1, deftable2;
    std::vector<std::string> code1, code2;
    int initdados1, initdados2;
    if (file1.is_open() && file2.is_open())
    {
        readfile(file1, usetable1, deftable1, initdados1, code1);
    }
    else
    {
        std::cout << "Não foi possivel abrir os arquivos" << std::endl;
    }
}

void readfile(std::fstream &file, std::vector<TokensVector> &usetable, std::vector<DefinitionTable> &deftable, int &dados, std::vector<std::string>& vec)
{
    std::string line;
    getline(file, line);
    dados = std::stoi(line);
    getline(file, line);
    while (line != "")
    {
        parseTokens(line, usetable);
        getline(file, line);
    }
    getline(file, line);
    while (line != "")
    {
        extractTD(line, deftable);
        getline(file, line);
    }
    while (!file.eof())
    {
        getline(file, line, ' ');
        vec.push_back(line);
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
        }
        else
        {
            vec.back().tokens.emplace_back(word);
        }
    }
}

void extractTD(std::string &line, std::vector<DefinitionTable> &vec)
{
    size_t pos;

    vec.emplace_back();
    pos = line.find(' ');
    if (pos != std::string::npos)
    {
        vec.back().label = line.substr(0, pos);
        vec.back().value = std::stoi(line.substr(pos + 1));
    }
}