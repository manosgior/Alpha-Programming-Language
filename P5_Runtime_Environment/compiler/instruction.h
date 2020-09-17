#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <fstream>
#include "VMarg.h"

enum TCodeOpcode {
    assign_tc, add_tc, sub_tc, mul_tc, div_tc, mod_tc, callfunc_tc, enterfunc_tc, exitfunc_tc, 
    jump_tc, jeq_tc, jne_tc, jgt_tc, jlt_tc, jge_tc, jle_tc, 
    newtable_tc, tablegetelem_tc, tablesetelem_tc,
    pusharg_tc, nop_tc
};

class Instruction {
private:
    TCodeOpcode op;
    VMarg result;
    VMarg arg1;
    VMarg arg2;
    unsigned line;
public:
    Instruction(TCodeOpcode opc, VMarg res, VMarg a1, VMarg a2, unsigned l);
    void exportByteCode(std::ofstream& os);
    void patchLabel(unsigned int new_res);
    TCodeOpcode getOpcode();
    bool isJump();
    VMarg getResult();
    VMarg getArg1();
    VMarg getArg2();
    unsigned getLine();
};

#endif
