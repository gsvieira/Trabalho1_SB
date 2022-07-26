#include "processor.h"


void process(char** argv)
{
	std::fstream file(argv[2]);
	std::string line;
	std::vector<TokensVector> vec;
	
	while (!file.eof())
	{
		getline(file, line);
		parseTokens(line, vec);

	}
	
}