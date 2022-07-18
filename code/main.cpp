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
        if (argv[1] == "-p")
        {
            //preprocess
        }
        
        if (argv[1] == "-o")
        {
            //process
        }
    } else {
        std::cout << "Não foi possivel abrir o arquivo" << std::endl;

    }
    
}