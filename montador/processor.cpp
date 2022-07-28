#include "processor.h"

std::vector<TokensVector> tu;
std::vector<DefTable> td;
bool load = false;
int data = -1;
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
	copyTStoTD(ts);
	linecounter = 1;
	locationcounter = 0;

	// printTS(ts);
	// printVec(vec);
	verifySections(vec);
	secondpass(vec, outvec, ti, ts, linecounter, locationcounter);

	std::fstream outputfile(ofile, std::ios_base::out);
	// print to file
	montador2file(outvec, outputfile);
}

void firstpass(std::vector<TokensVector> &vec, const std::vector<InstructionsTable> &ti, std::vector<SymbolTable> &ts, int &linecounter, int &locationcounter)
{
	if (!vec.back().label.empty()) // se tem rotulo procura na tabela de simbolos
	{
		valToken(vec.back().label.substr(0, vec.back().label.find(":")), linecounter);
		if (!ts.empty()) // se a tabela tem membros faz a busca
		{
			for (int i = 0; i < ts.size(); i++)
			{
				if (vec.back().label.substr(0, vec.back().label.find(":")) == ts[i].token)
				{
					std::cout << "Erro: Semantico - Símbolo Redefinido: " << vec.back().label << " - Linha: " << linecounter << std::endl;
					exit(0);
				}
			}
			if (vec.back().tokens[0] == "EXTERN")
			{
				ts.emplace_back(vec.back().label.erase(vec.back().label.find(":")), 0, true); // acrescenta com flag extern caso seja uma variável externa
			}
			else
			{
				ts.emplace_back(vec.back().label.erase(vec.back().label.find(":")), locationcounter); // acrescenta após não encontrar o valor na tabela
			}
		}
		else // adiciona simbolo na tabela de simbolos
		{
			if (vec.back().tokens[0] == "EXTERN")
			{
				ts.emplace_back(vec.back().label.erase(vec.back().label.find(":")), 0, true); // acrescenta com flag extern caso seja uma variável externa
			}
			else
			{
				ts.emplace_back(vec.back().label.erase(vec.back().label.find(":")), locationcounter); // acrescenta se a tabela for vazia
			}
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
	if (vec.back().tokens[0] == "PUBLIC")
	{
		td.emplace_back(vec.back().tokens[1]);
	}

	linecounter++;
}

void printTS(std::vector<SymbolTable> &ts)
{
	for (auto &&line : ts)
	{
		std::cout << line.token << " " << line.value << " " << line.externSymbol << std::endl;
	}
}

void secondpass(std::vector<TokensVector> &vec, std::vector<std::string> &outvec, const std::vector<InstructionsTable> &ti, std::vector<SymbolTable> &ts, int &linecounter, int &locationcounter)
{
	for (auto &&line : vec)
	{
		if (line.tokens.size() == 2 && !isdirective(line.tokens[0]))
		{
			valToken(line.tokens[1], linecounter);
			addtoTU(line.tokens[1], linecounter, ts);
			if (searchTS(line.tokens[1], ts) < 0)
			{
				std::cout << "Erro: Semantico - Simbolo indefinido: " << line.tokens[1] << " - Linha: " << linecounter << std::endl;
				exit(0);
			}
		}
		else if (line.tokens.size() == 3)
		{
			valToken(line.tokens[1].substr(0, line.tokens[1].find(",")), linecounter);
			addtoTU(line.tokens[1].substr(0, line.tokens[1].find(",")), linecounter, ts);
			if (searchTS(line.tokens[1].substr(0, line.tokens[1].find(",")), ts) < 0)
			{
				std::cout << "Erro: Semantico - Simbolo indefinido: " << line.tokens[1] << " - Linha: " << linecounter << std::endl;
				exit(0);
			}
			valToken(line.tokens[2], linecounter);
			addtoTU(line.tokens[2], linecounter, ts); // adiciona na tabela de uso
			if (searchTS(line.tokens[2], ts) < 0)
			{
				std::cout << "Erro: Semantico - Simbolo indefinido: " << line.tokens[2] << " - Linha: " << linecounter << std::endl;
				exit(0);
			}
		}
		// procura na tabela de instruções
		bool find = false;
		for (auto &&inst : ti)
		{
			if (line.tokens[0] == inst.token) // se a instrução da linha for a mesma da linha da tabela de instrução
			{
				locationcounter += inst.size;
				find = true;
				if (line.tokens.size() == inst.size)
				{
					outvec.push_back(inst.opcode); // passando opcode para output vector
					if (line.tokens.size() == 2)
					{
						outvec.push_back(std::to_string(searchTS(line.tokens[1], ts))); // passando primeiro operando, caso exista, para output vector
					}
					if (line.tokens.size() == 3)
					{
						outvec.push_back(std::to_string(searchTS(line.tokens[1].substr(0, line.tokens[1].find(",")), ts))); // passando primeiro operando, caso exista, para output vector
						outvec.push_back(std::to_string(searchTS(line.tokens[2], ts)));										// passando segundo operando, caso exista, para output vector
					}
					linecounter++; // incrementar o contador de linhas
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
					linecounter++; // incrementar o contador de linhas
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
					linecounter++; // incrementar o contador de linhas
					continue;
				}
				else
				{
					std::cout << "Erro: Sintático - Operando invalido - Linha: " << linecounter << std::endl;
					exit(0);
				}
			}
			// SECAO
			if (line.tokens[0] == "SECAO")
			{
				linecounter++;
				continue;
			}

			// BEGIN
			if (line.tokens[0] == "BEGIN")
			{
				load = true;
				continue;
			}

			// END
			if (line.tokens[0] == "END")
			{
				continue;
			}
			// EXTERN
			if (line.tokens[0] == "EXTERN")
			{
				continue;
			}
			// PUBLIC
			if (line.tokens[0] == "PUBLIC")
			{
				continue;
			}
		}
		if (find == false)
		{
			std::cout << "Erro: Semantico - Operação não identificada - Linha: " << linecounter << std::endl;
			exit(0);
		}
	}
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

void codetofile(std::vector<std::string> &outvec, std::fstream &file)
{
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

void verifySections(const std::vector<TokensVector> &vec)
{
	int text = -1;
	data = -1;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].tokens[0] != "SECAO")
		{
			if (vec[i].tokens[0] != "SPACE" && vec[i].tokens[0] != "CONST" && vec[i].tokens[0] != "END") // se não é diretiva que fica na seção de dados
			{
				if (data != -1 && i > data) // intrução está na seção de dados
				{
					std::cout << " Erro: Semantico - instruções ou diretivas nas seções erradas - Linha: " << i + 1 << std::endl;
					exit(0);
				}
			}
			else
			{
				if (data == -1) // data não foi definido no arquivo
				{
					std::cout << "Erro: Semantico - instruções ou diretivas nas seções erradas - Linha: " << i + 1 << std::endl;
					exit(0);
				}
			}
		}
		else if (vec[i].tokens[0] == "SECAO")
		{
			if (vec[i].tokens[1] == "TEXTO")
			{
				text = i;
			}
			else if (vec[i].tokens[1] == "DADOS")
			{
				data = i;
			}
		}
	}
	if (text == -1)
	{
		std::cout << "Erro: Semantico - falta de seção de texto" << std::endl;
	}
}

bool isdirective(std::string token)
{
	if (token == "CONST" || token == "SPACE" || token == "BEGIN" || token == "END" || token == "EXTERN" || token == "PUBLIC" || token == "SECAO")
	{
		return true;
	}
	return false;
}

void copyTStoTD(std::vector<SymbolTable> &ts)
{
	for (auto &&linetd : td)
	{
		int tdvalue = searchTS(linetd.label, ts);
		if (tdvalue != -1)
		{
			linetd.value = std::to_string(tdvalue);
		}
	}
}

void addtoTU(std::string token, int &locationcounter, std::vector<SymbolTable> &ts)
{
	if (load == true)
	{
		int pos;
		for (pos = 0; pos < ts.size(); pos++)
		{
			if (ts[pos].token == token)
			{
				break;
			}
		}
		if (pos != ts.size())
		{
			if (ts[pos].externSymbol == true)
			{
				if (tu.empty())
				{
					tu.emplace_back();
					tu.back().label = token;
					tu.back().tokens.emplace_back(std::to_string(locationcounter));
				}
				else
				{
					for (auto &&linetu : tu)
					{
						int tuPos = searchTU(token, tu);

						if (tuPos != -1)
						{
							tu[tuPos].tokens.emplace_back(std::to_string(locationcounter));
						}
					}
				}
			}
		}
	}
}

int searchTU(std::string token, std::vector<TokensVector> &tu)
{
	for (int i = 0; i < tu.size(); i++)
	{
		if (tu[i].label == token)
		{
			return i;
		}
	}
	return -1;
}

void TD2file(std::vector<DefTable> &vec, std::fstream &file)
{
	file << std::endl
		 << "TABELA DEF" << std::endl;
	for (int j = 0; j < vec.size(); j++)
	{
		if (!vec[j].label.empty())
		{
			file << vec[j].label << " ";
		}
		if (!vec[j].value.empty())
		{
			file << vec[j].value << std::endl;
		}
	}
	file << std::endl;
}

void montador2file(std::vector<std::string> &outvec, std::fstream &outputfile)
{
	if (load == true)
	{
		outputfile << data << std::endl;
		outputfile << "TABELA USO" << std::endl;
		preprocessor2file(tu, outputfile);
		outputfile << std::endl;
		TD2file(td, outputfile);
		codetofile(outvec, outputfile);
	}
	else
	{
		codetofile(outvec, outputfile);
	}
}

void valToken(std::string token, int &linecounter)
{
	if (token.size() > 99 || !isvalidtype(token))
	{
		std::cout << "Erro: Léxico - Token Inválido: " << token << " - Linha: " << linecounter << std::endl;
		exit(0);
	}
}

bool isvalidtype(std::string token)
{
	if (iswalpha(token[0]) || token[0] == '_')
	{
		for (int i = 1; i < token.size(); i++)
		{
			if (!iswalnum(token[i]) && token[0] == '_')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}