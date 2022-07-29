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
    std::vector<DefinitionTable> deftable1, deftable2, tabelaglobaldef;
    std::vector<int> code1, code2, finalcode;
    if (file1.is_open() && file2.is_open())
    {
        readfile(file1, usetable1, deftable1, initdados1, code1);
        readfile(file2, usetable2, deftable2, initdados2, code2);

        corretionFactor2 = code2.size();
        gentdg(tabelaglobaldef, deftable1, deftable2);
        updateTU(usetable2, corretionFactor2);

        // identify();
    }
    else
    {
        std::cout << "Não foi possivel abrir os arquivos" << std::endl;
    }
}

void readfile(std::fstream &file, std::vector<TokensVector> &usetable, std::vector<DefinitionTable> &deftable, int &dados, std::vector<int> &vec)
{
    std::string line;
    getline(file, line); // 12

    dados = std::stoi(line);

    while (true)
    {
        getline(file, line);

        if (line == "TABELA USO")
        {
            continue;
        }
        if (line == "")
        {
            break;
        }

        // std::cout<< "tabela de uso:" << line << std::endl;
        parseTokens(line, usetable);
    }
    while (true)
    {
        getline(file, line);
        if (line == "TABELA DEF")
        {
            continue;
        }
        if (line == "")
        {
            break;
        }
        // std::cout<< "tabela de def:" << line << std::endl;
        extractTD(line, deftable);
    }

    while (!file.eof())
    {
        getline(file, line, ' ');
        if (line == "")
        {
            continue;
        }
        // std::cout << line << std::endl;
        vec.push_back(std::stoi(line));
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
        // std::cout << line.substr((pos + 1)) << std::endl;
        // vec.back().value = std::stoi(line.substr((pos + 1)));
    }
}

void gentdg(std::vector<DefinitionTable> &tdg, std::vector<DefinitionTable> &td1, std::vector<DefinitionTable> &td2)
{
    tdg = td1;
    for (auto &&line : td2)
    {
        std::string valuepluscorrection = std::to_string((std::stoi(line.value)) + corretionFactor2);
        tdg.emplace_back(line.label, valuepluscorrection);
    }
}

void updateTU(std::vector<TokensVector> &usetable, int corrf)
{
    for (auto &&line : usetable)
    {
        for (auto &&addr : line.tokens)
        {
            addr = std::to_string(std::stoi(addr) + corrf);
        }
    }
}
void setupfinalcode(std::vector<int> &code1, std::vector<int> &code2, std::vector<int> &finalcode)
{
    finalcode = code1;
    finalcode.reserve(code1.size() + code2.size());
    finalcode.insert(std::end(finalcode), std::begin(code2), std::end(code2));
    aux.assign(code1.size(), true);
    std::fill(aux.begin() + initdados1, aux.end(), false); // TODO: test print
    relativeaddrs = aux;
    aux2.assign(code2.size(), true);
    std::fill(aux2.begin() + initdados2, aux2.end(), false); // TODO: test print
    // relativeaddrs.insert(relativeaddrs.end(), aux2.begin(), aux2.end());
}
void identify(std::vector<int> &code)
{
    int pos = 0;
    while (true)
    {
        for (auto &&lineti : ti)
        {
            if (code[pos] == std::stoi(lineti.opcode))
            {
            }
        }

        code[pos]
    }
}
