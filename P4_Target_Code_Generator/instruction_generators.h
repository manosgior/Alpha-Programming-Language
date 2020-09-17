#include "quadtable.h"
#include "instruction.h"
#include "instructiontable.h"

void generate(TCodeOpcode, quad&);

void generate_ADD(quad&);
void generate_SUB(quad&);
void generate_MUL(quad&);
void generate_DIV(quad&);
void generate_MOD(quad&);
void generate_UMINUS(quad&);

void generate_NEWTABLE(quad&);
void generate_TABLEGETELEM(quad&);
void generate_TABLESETELEM(quad&);
void generate_ASSIGN(quad&);
void generate_NOP(quad&);

void generate_RELATIONAL(TCodeOpcode, quad&);

void generate_JUMP(quad&);
void generate_IF_EQ(quad&);
void generate_IF_NOTEQ(quad&);
void generate_IF_GREATER(quad&);
void generate_IF_GREATEREQ(quad&);
void generate_IF_LESS(quad&);
void generate_IF_LESSEQ(quad&);

void generate_PARAM(quad&);
void generate_CALL(quad&);
void generate_GETRETVAL(quad&);
void generate_FUNCSTART(quad&);
void generate_RETURN(quad&);
void generate_FUNCEND(quad&);
