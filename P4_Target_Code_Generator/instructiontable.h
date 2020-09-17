#ifndef INSTRUCTIONTABLE_H
#define INSTRUCTIONTABLE_H

#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include "instruction.h"
#include <fstream>
#include <iomanip>

class InstructionTable {
private:
    typedef struct userFuncInfo {
        unsigned address;
        unsigned localsize;
        std::string id;
    } userFuncInfo;
    std::vector<std::string> constStrings;
    std::vector<std::string> libFuncNames;
    std::vector<userFuncInfo> userFuncs;
    std::vector<double> constNums;
    std::vector<Instruction> instructions;
    std::vector<std::pair<unsigned, unsigned>> incompleteJumps;
    std::string opcode2string[22] = {
        "assign",         "add",            "sub",
        "mul",            "div",            "mod", 
        "callfunc",       "enterfunc",      "exitfunc",
        "jump",           "jeq",            "jne",
        "jgt",            "jlt",            "jge",
        "jle",            "newtable",       "tablegetelem",
        "tablesetelem",   "pusharg",        "nop_tc"
    };
public:
    InstructionTable();
    void emit(Instruction newInstruction);
    void exportByteCode(std::ofstream& os);
    unsigned int newStringConst(std::string);
    unsigned int newNumConst(double);
    unsigned int newLibFunc(std::string);
    void patchIncompleteJumps();
    void addIncompleteJump(unsigned tCodeINum, unsigned iCodeJAddr);
    size_t size();
    size_t nextInstructionLabel();
    
    void printTable(std::ostream& ofs);
    void addUserFunc(unsigned address, unsigned localsize, std::string id);
};

#endif
