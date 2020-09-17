#include "instruction.h"

Instruction::Instruction(TCodeOpcode opc, VMarg res, VMarg a1, VMarg a2, unsigned l) : op(opc), result(res), arg1(a1), arg2(a2), line(l){
    
}

void Instruction::exportByteCode(std::ofstream& os) {
    uint8_t tmp = op;
    os.write((char *)&tmp, sizeof(uint8_t));
    tmp = result.getType();
    os.write((char *)&tmp, sizeof(uint8_t));
    unsigned value_tmp = result.getValue();
    os.write((char *)&value_tmp, sizeof(unsigned));
    tmp = arg1.getType();
    os.write((char *)&tmp, sizeof(uint8_t));
    value_tmp = arg1.getValue();
    os.write((char *)&value_tmp, sizeof(unsigned));
    tmp = arg2.getType();
    os.write((char *)&tmp, sizeof(uint8_t));
    value_tmp = arg2.getValue();
    os.write((char *)&value_tmp, sizeof(unsigned));
    os.write((char *)&line, sizeof(unsigned));
}

void Instruction::patchLabel(unsigned int new_res) {
    result.setJumpValue(new_res);
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