#include "processor.h"

void process(std::fstream &file, std::string ofile)
{
	std::string line;
	int linecounter = 1;
	int locationcounter = 0;
	std::vector<TokensVector> vec;
	std::vector<SymbolTable> ts;
	std::vector<std::string> outvec;

	while (!file.eof())
	{
		getline(file, line);
		parseTokens(line, vec);
		firstpass(vec, ti, ts, linecounter, locationcounter);
	}
	linecounter = 1;
	locationcounter = 0;
	//printTS(ts);
	secondpass(vec, outvec, ti, ts, linecounter, locationcounter);
	processtofile(outvec, ofile);
}

void firstpass(std::vector<TokensVector> &vec, const std::vector<InstructionsTable> &ti, std::vector<SymbolTable> &ts, int &linecounter, int &locationcounter)
{
	if (!vec.back().label.empty()) // se tem rotulo procura na tabela de simbolos
	{
		if (!ts.empty()) // se a tabela tem membros faz a busca
		{
			for (int i = 0; i < ts.size(); i++)
			{
				if (vec.back().label == ts[i].token)
				{
					std::cout << "Erro: Semantico - Símbolo Redefinido" << std::endl
							  << "Linha: " << linecounter << std::endl;
					exit(0);
				}
			}

			ts.emplace_back(vec.back().label.erase(vec.back().label.find(":")), locationcounter); // acrescenta após não encontrar o valor na tabela
		}
		else // adiciona simbolo na tabela de simbolos
		{
			ts.emplace_back(vec.back().label.erase(vec.back().label.find(":")), locationcounter); // acrescenta se tabela estiver vazia
		}
	}

	for (auto &&tl : ti) // procura na tabela de instruções a instrução da linha
	{
		if (vec.back().tokens[0] == tl.token)
		{
			locationcounter += tl.size;
			break;
		}
	}
	if (vec.back().tokens[0] == "CONST" || vec.back().tokens[0] == "SPACE")
	{
		locationcounter++; // acrescenta 1 no endereço no caso das diretivas SPACE e CONST
	}
	linecounter++;
}

void printTS(std::vector<SymbolTable> &ts)
{
	for (auto &&line : ts)
	{
		std::cout << line.token << " " << line.value << std::endl;
	}
}

void secondpass(std::vector<TokensVector> &vec, std::vector<std::string> &outvec, const std::vector<InstructionsTable> &ti, std::vector<SymbolTable> &ts, int &linecounter, int &locationcounter)
{
	for (auto &&line : vec)
	{
		if (line.tokens.size() >= 2 && line.tokens[0] != "CONST")
		{
			if (searchTS(line.tokens[1], ts) < 0)
			{
				std::cout << "Erro: Semantico - Simbolo indefinido - Linha: " << linecounter << std::endl;
				exit(0);
			}

			if (line.tokens.size() == 3)
			{
				if (searchTS(line.tokens[1], ts) < 0)
				{
					std::cout << "Erro: Semantico - Simbolo indefinido - Linha: " << linecounter << std::endl;
					exit(0);
				}
			}
		}
		// procura na tabela de instruções
		bool find = false;
		for (auto &&inst : ti)
		{
			if (line.tokens[0] == inst.token) // se a instrução da linha for a mesma da linha da tabela de instrução
			{

				// std::cout << "token: "<< line.tokens[0] << " == "<< inst.token << std::endl;
				locationcounter += inst.size;
				find = true;
				if (line.tokens.size() == inst.size)
				{
					outvec.push_back(inst.opcode); // passando opcode para output vector
					if (line.tokens.size() >= 2)
					{
						outvec.push_back(std::to_string(searchTS(line.tokens[1], ts))); // passando primeiro operando, caso exista, para output vector

						if (line.tokens.size() == 3)
						{
							outvec.push_back(std::to_string(searchTS(line.tokens[2], ts))); // passando segundo operando, caso exista, para output vector
						}
					}
					break;
				}
				else
				{
					std::cout << "Erro: Sintático - Operando invalido - Linha: " << linecounter << std::endl;
					exit(0);
				}
			}
		}
		// procura na tabela de diretivas, mas só se não achou na tabela de instruções (find == false)

		if (find == false)
		{
			// CONST
			if (line.tokens[0] == "CONST")
			{
				if (line.tokens.size() == 2)
				{
					outvec.push_back(line.tokens[1]);
					continue;
				}
				else
				{
					std::cout << "Erro: Sintático - Operando invalido - Linha: " << linecounter << std::endl;
					exit(0);
				}
			}

			// SPACE
			if (line.tokens[0] == "SPACE")
			{
				if (line.tokens.size() == 1)
				{
					outvec.push_back("0");
					continue;
				}
				else
				{
					std::cout << "Erro: Sintático - Operando invalido - Linha: " << linecounter << std::endl;
					exit(0);
				}
			}

			// BEGIN
			// END
			// EXTERN
			// PUBLIC
		}
		if (find == false)
		{
			std::cout << "Erro: Semantico - Operação não identificada - Linha: " << linecounter << std::endl;
			exit(0);
		}
	}
	linecounter++; // incrementar o contador de linhas
}

int searchTS(std::string token, std::vector<SymbolTable> ts)
{
	for (auto &&line : ts)
	{
		if (line.token == token)
		{
			return line.value;
		}
	}
	return -1;
}

void printvec(std::vector<std::string> &outvec)
{
	for (auto &&line : outvec)
	{
		std::cout << line << " ";
	}
	std::cout << std::endl;
}

void processtofile(std::vector<std::string> &outvec, std::string filename)
{
	std::fstream file(filename, std::ios_base::out);
	for (int i = 0; i < outvec.size(); i++)
	{
		if (i == 0)
		{
			file << outvec[i];
		}
		else
			file << " " << outvec[i];
	}
}