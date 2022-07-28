#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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

void readfile(std::fstream &, int &);