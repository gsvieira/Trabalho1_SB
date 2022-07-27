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

void process(char **);
void firstpass(std::vector<TokensVector> &, const std::vector<InstructionsTable> &, std::vector<SymbolTable> &, int &, int &);
void secondpass(std::vector<TokensVector> &, std::vector<std::string> &, const std::vector<InstructionsTable> &, std::vector<SymbolTable> &, int &, int &);
void printTS(std::vector<SymbolTable> &);
int searchTS(std::string, std::vector<SymbolTable>);
void printvec(std::vector<std::string> &outvec);