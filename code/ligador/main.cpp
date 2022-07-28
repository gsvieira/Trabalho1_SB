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
    int dados;
    if (file1.is_open() && file2.is_open())
    {
        readfile(file1, dados);
    }
    else
    {
        std::cout << "Não foi possivel abrir os arquivos" << std::endl;
    }
}

void readfile(std::fstream &file, int& dados)
{
    std::string line;
    getline(file, line);
    // dados = std::stoi(line);
    // getline(file, line);
    // while(line!="")
    if (line == "")
    {
        std::cout << 1 << std::endl;
    }
    
}