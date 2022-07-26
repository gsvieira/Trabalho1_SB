#include "processor.h"


int main(int argc, char* argv[])
{
	process(argv);
}


void process(char** argv)
{
	std::fstream file(argv[2]);
	std::string line;
	int linecounter = 1;
	int locationcounter = 0;
	std::vector<TokensVector> vec;
	std::vector<SymbolTable> ts;
	
	
	while (!file.eof())
	{
		getline(file, line);
		parseTokens(line, vec);
		firstpass(vec, ti, ts, linecounter, locationcounter);
	}
	//printVec(vec);
	//printTS(ts);
	
}

void firstpass(std::vector<TokensVector>& vec, const std::vector<InstructionsTable>& ti, std::vector<SymbolTable>& ts, int& linecounter, int& locationcounter)
{
	if (!vec.back().label.empty()) //se tem rotulo procura na tabela de simbolos
	{
		if (!ts.empty()) //se a tabela tem membros faz a busca
		{
			for (int i = 0; i < ts.size(); i++)
			{
				if (vec.back().label == ts[i].token)
				{
					std::cout << "Erro: Semantico - Símbolo Redefinido" << std::endl;
					exit(0);
				}
				
			}

			ts.emplace_back(vec.back().label, locationcounter); //acrescenta após não encontrar o valor na tabela
		} 
		else //adiciona simbolo na tabela de simbolos
		{
			ts.emplace_back(vec.back().label, locationcounter); //acrescenta se tabela estiver vazia
		}
	}

	for (auto &&tl : ti)//procura na tabela de instruções a instrução da linha
	{
		//std::cout << vec.back().tokens[0] << " == " << tl.token << std::endl;
		if (vec.back().tokens[0] == tl.token)
		{
			//std::cout << "here1" << std::endl;
			locationcounter += tl.size;
			break;		
		}
		
	}
	//std::cout << "locationcounter: " << locationcounter << std::endl;
	if (vec.back().tokens[0] == "CONST" || vec.back().tokens[0] == "SPACE")
	{
		locationcounter++; //acrescenta 1 no endereço no caso das diretivas SPACE e CONST
	}
	linecounter++;
	
}

void printTS(std::vector<SymbolTable>& ts)
{
	for (auto &&line : ts)
	{
		std::cout << line.token << " " << line.value << std::endl;
	}
	
}