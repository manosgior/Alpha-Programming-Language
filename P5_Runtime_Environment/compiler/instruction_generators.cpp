#include "instruction_generators.h"
#include "instruction.h"
#include "instructiontable.h"
#include <stack>
#include <vector>

extern InstructionTable instruction_table;
extern QuadTable quad_table;

void generate(TCodeOpcode op, quad& q) {
    Instruction t = Instruction(op, VMarg(q.result), (q.arg1 != nullptr ? VMarg(q.arg1) : VMarg()), (q.arg2 != nullptr ? VMarg(q.arg2) : VMarg()), q.line);
    q.TCodeAddress = instruction_table.nextInstructionLabel();
    instruction_table.emit(t);
}

void generate_ADD(quad& q) {
    generate(add_tc, q);
}

void generate_SUB(quad& q) {
    generate(sub_tc, q);
}

void generate_MUL(quad& q) {
    generate(mul_tc, q);
}

void generate_DIV(quad& q) {
    generate(div_tc, q);
}

void generate_MOD(quad& q) {
    generate(mod_tc, q);
}

void generate_UMINUS(quad& q) {
    q.op = mul;
    q.arg2 = expr::newexpr_constnum(-1);
    generate(mul_tc, q);
}

void generate_NEWTABLE(quad &q) {
    generate(TCodeOpcode::newtable_tc, q);
}

void generate_TABLEGETELEM(quad &q) {
    generate(TCodeOpcode::tablegetelem_tc, q);
}

void generate_TABLESETELEM(quad &q) {
    generate(TCodeOpcode::tablesetelem_tc, q);
}

void generate_ASSIGN(quad &q) {
    generate(TCodeOpcode::assign_tc, q);
}

void generate_NOP() {
    Instruction t(TCodeOpcode::nop_tc, VMarg(), VMarg(), VMarg(), 0);
    instruction_table.emit(t);
}

void generate_RELATIONAL(TCodeOpcode op, quad &q) {
    VMarg arg1 = ((op == jump_tc) ? VMarg() : VMarg(q.arg1));
    VMarg arg2 = ((op == jump_tc) ? VMarg() : VMarg(q.arg2));
    VMarg res = VMarg();

    if (q.label < quad_table.currProcessedQuad())
        res.setJumpValue(quad_table.getQuad(q.label).TCodeAddress);
    else
        instruction_table.addIncompleteJump(instruction_table.nextInstructionLabel(), q.label);
    Instruction t(op, res, arg1, arg2, q.line);
    q.TCodeAddress = instruction_table.nextInstructionLabel();

    instruction_table.emit(t);
}

void generate_JUMP(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jump_tc, q);
}

void generate_IF_EQ(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jeq_tc, q);
}

void generate_IF_NOTEQ(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jne_tc, q);
}

void generate_IF_GREATER(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jgt_tc, q);
}

void generate_IF_GREATEREQ(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jge_tc, q);
}

void generate_IF_LESS(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jlt_tc, q);
}

void generate_IF_LESSEQ(quad& q) {
    generate_RELATIONAL(TCodeOpcode::jle_tc, q);
}

void generate_PARAM(quad& q) {
    q.TCodeAddress = instruction_table.nextInstructionLabel();
    Instruction t(pusharg_tc, VMarg(), VMarg(q.arg1), VMarg(), q.line);
    instruction_table.emit(t);
}

void generate_RETURN(quad& q) {
    VMarg arg1 = (q.result) ? VMarg(q.result) : VMarg(nil_a, 0);
    VMarg res = VMarg();

    res.convertToRetValOperand();

    q.TCodeAddress = instruction_table.nextInstructionLabel();

    Instruction t(TCodeOpcode::assign_tc, res, arg1, VMarg(), q.line);

    instruction_table.emit(t);
}

void generate_CALL(quad& q) {
    q.TCodeAddress = instruction_table.nextInstructionLabel();
    Instruction t(callfunc_tc, VMarg(), VMarg(q.arg1), VMarg(), q.line);
    instruction_table.emit(t);
}

void generate_GETRETVAL(quad& q) {
    q.TCodeAddress = instruction_table.nextInstructionLabel();
    VMarg res = VMarg(q.result);
    VMarg arg1 = VMarg();
    arg1.convertToRetValOperand();
    Instruction t(assign_tc, res, arg1, VMarg(), q.line);
    instruction_table.emit(t);
}

void generate_FUNCSTART(quad& q) {
    q.TCodeAddress = instruction_table.nextInstructionLabel();
    VMarg res = VMarg(q.result);
    Instruction t(enterfunc_tc, res, VMarg(), VMarg(), q.line);
    instruction_table.emit(t);
    instruction_table.addUserFunc(q.result->getSymbol()->getFuncAddress(), q.result->getSymbol()->getTotalLocals(), 
                q.result->getSymbol()->getTotalFormals(), q.result->getName());
}

void generate_FUNCEND(quad& q) {
    VMarg res = VMarg(q.result);

    q.TCodeAddress = instruction_table.nextInstructionLabel();

    Instruction t(TCodeOpcode::exitfunc_tc, res, VMarg(), VMarg(), q.line);

    instruction_table.emit(t);
}

