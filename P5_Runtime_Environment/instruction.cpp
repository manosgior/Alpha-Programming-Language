#include "instruction.h"

Instruction::Instruction(TCodeOpcode opc, VMarg res, VMarg a1, VMarg a2, unsigned l) : op(opc), result(res), arg1(a1), arg2(a2), line(l){
    
}

TCodeOpcode Instruction::getOpcode() {
    return op;
}

bool Instruction::isJump() {
    switch (op) {
        case(jump_tc):
        case(jeq_tc):
        case(jge_tc):
        case(jgt_tc):
        case(jle_tc):
        case(jlt_tc):
        case(jne_tc):
            return true;
        default:
            return false;
    }
}

VMarg Instruction::getResult() {
    return result;
}

VMarg Instruction::getArg1(){
	return arg1;
}

VMarg Instruction::getArg2(){
	return arg2;
}

unsigned Instruction::getLine() {
    return line;
}