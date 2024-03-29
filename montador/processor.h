#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "auxfunctions.h"

struct InstructionsTable
{
    std::string token;
    std::string opcode;
    int size;
};

struct SymbolTable
{
    std::string token;
    int value;
    bool externSymbol;

    SymbolTable(std::string t, int v)
    {
        token = t;
        value = v;
        externSymbol = false;
    }
    SymbolTable(std::string t, int v, bool e)
    {
        token = t;
        value = v;
        externSymbol = e;
    }
};

struct DefTable
{
    std::string label;
    std::string value;

    DefTable(std::string l)
    {
        label = l;
        value = "";
    }
};

// Variaveis globais
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

void process(std::fstream &, std::string);
void firstpass(std::vector<TokensVector> &, const std::vector<InstructionsTable> &, std::vector<SymbolTable> &, int &, int &);
void secondpass(std::vector<TokensVector> &, std::vector<std::string> &, const std::vector<InstructionsTable> &, std::vector<SymbolTable> &, int &, int &);
void printTS(std::vector<SymbolTable> &);
int searchTS(std::string, std::vector<SymbolTable>);
int searchTSline(std::string, std::vector<SymbolTable> &);
void printvec(std::vector<std::string> &outvec);
void codetofile(std::vector<std::string> &, std::fstream &);
void verifySections(const std::vector<TokensVector> &vec);
bool isdirective(std::string);
void copyTStoTD(std::vector<SymbolTable> &);
void addtoTU(std::string, int, std::vector<SymbolTable> &);
int searchTU(std::string, std::vector<TokensVector> &);
void montador2file(std::vector<std::string> &, std::fstream &);
bool isvalidtype(std::string);
void valToken(std::string, int &);