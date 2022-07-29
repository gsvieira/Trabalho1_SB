#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
// variaveis globais
size_t corretionFactor1 = 0;
size_t corretionFactor2;
std::vector<bool> aux, aux2, relativeaddrs;
int initdados1, initdados2;

struct TokensVector
{
    std::string label;
    std::vector<std::string> tokens;
};

struct InstructionsTable
{
    std::string token;
    std::string opcode;
    int size;
};

struct DefinitionTable
{
    std::string label;
    std::string value;

    DefinitionTable(std::string l, std::string v)
    {
        label = l;
        value = v;
    }
    DefinitionTable(std::string l)
    {
        label = l;
        value = "";
    }
    DefinitionTable()
    {
        label = "";
        value = "";
    }
};

const std::vector<InstructionsTable> ti = {{"ADD", "1", 2},
                                           {"SUB", "2", 2},
                                           {"MUL", "3", 2},
                                           {"DIV", "4", 2},
                                           {"JMP", "5", 2},
                                           {"JMPN", "6", 2},
                                           {"JMPP", "7", 2},
                                           {"JMPZ", "8", 2},
                                           {"COPY", "9", 3},
                                           {"LOAD", "10", 2},
                                           {"STORE", "11", 2},
                                           {"INPUT", "12", 2},
                                           {"OUTPUT", "13", 2},
                                           {"STOP", "14", 1}};

void readfile(std::fstream &, std::vector<TokensVector> &, std::vector<DefinitionTable> &, int &, std::vector<int> &);
void parseTokens(std::string &, std::vector<TokensVector> &);
void extractTD(std::string &, std::vector<DefinitionTable> &);
void gentdg(std::vector<DefinitionTable> &, std::vector<DefinitionTable> &, std::vector<DefinitionTable> &);
void updateTU(std::vector<TokensVector> &, int);
void load(std::vector<int> &, std::vector<TokensVector> &, std::vector<TokensVector> &, std::vector<DefinitionTable> &);
void setupfinalcode(std::vector<int> &, std::vector<int> &, std::vector<int> &);
void identify(std::vector<int> &, std::vector<bool> &, int);
void executeTU(std::vector<TokensVector> &, std::vector<TokensVector> &, std::vector<DefinitionTable> &, std::vector<int> &);
int searchTGD(std::vector<DefinitionTable> &, std::string);
void applycorrf(std::vector<int> &);
void codetofile(std::vector<int> &, std::ofstream &);
void printTD(std::vector<DefinitionTable>);
void printTU(std::vector<TokensVector> &);
void auxtofile(std::vector<bool> &);