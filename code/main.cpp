#include "preprocessor.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc <= 3 || argc > 4)
    {
        std::cout << "Forma de utilizar o programa incorreta!" << std::endl << "Exemplo: ./montador -p myprogram.asm saida.obj";
    }

    std::fstream file(argv[2]);

    if (file.is_open())
    {
        if (argv[1] == std::string("-p"))
        {
            readfile(file, argv[3]);
        }
        
        if (argv[1] == std::string("-o"))
        {
            //process
        }
    } 
    else 
    {
        std::cout << "Não foi possivel abrir o arquivo" << std::endl;
    }
    
}