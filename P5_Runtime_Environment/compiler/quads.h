#ifndef QUADS_H
#define QUADS_H

#include "expression.h"

#define NUM_OF_OP_CODES 26

enum iopcode {
    assign,         add,            sub,
    mul,            div_i,          mod,
    uminus,         if_eq,          if_noteq,
    if_lesseq,      if_greatereq,   if_less,   
    if_greater,     call,           param, 
    ret,            getretval,      funcstart,
    funcend,        tablecreate,    jump, 
    tablegetelem,   tablesetelem,   and_i,
    or_i,           not_i
};

typedef struct quad {
    iopcode     op;
    expr*       result;
    expr*       arg1;
    expr*       arg2;
    unsigned    label;
    unsigned    line;    
    unsigned    TCodeAddress;
} quad;

#endif