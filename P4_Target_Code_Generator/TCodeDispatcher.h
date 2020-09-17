#ifndef TCODEDISPATCHER_H
#define TCODEDISPATCHER_H

#include "instruction_generators.h"

typedef void (*generator_func_t)(quad&);

generator_func_t generators[] = {
    generate_ASSIGN,         
    generate_ADD,
    generate_SUB,
    generate_MUL,            
    generate_DIV,          
    generate_MOD,
    generate_UMINUS,         
    generate_IF_EQ,          
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,      
    generate_IF_GREATEREQ,   
    generate_IF_LESS,   
    generate_IF_GREATER,     
    generate_CALL,           
    generate_PARAM, 
    generate_RETURN,            
    generate_GETRETVAL,      
    generate_FUNCSTART,
    generate_FUNCEND,        
    generate_NEWTABLE,    
    generate_JUMP, 
    generate_TABLEGETELEM,   
    generate_TABLESETELEM,
};

#endif