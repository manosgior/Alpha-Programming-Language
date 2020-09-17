#ifndef QUADTABLE_H
#define QUADTABLE_H

#include "quads.h"
#include <vector>
#include <fstream>

class QuadTable {
private:
    std::vector<quad> quads;
    std::string opcode2string[26] = {
        "assign",         "add",            "sub",
        "mul",            "div",          "mod",
        "uminus",         "and_i",          "or_i",   
        "not_i",          "if_eq",          "if_noteq",
        "if_lesseq",      "if_greatereq",   "if_less",   
        "if_greater",     "call",           "param", 
        "return",            "getretval",      "funcstart",
        "funcend",        "tablecreate",    "jump", 
        "tablegetelem",   "tablesetelem"
    };
public:
    QuadTable();
    void emit(iopcode o, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line);
    unsigned nextQuadLabel();
    void patchLabel(unsigned quadNo, unsigned label);
    void printQuads(std::ostream& ofs);
    void altPrintQuads(std::ostream& ofs);
};

#endif