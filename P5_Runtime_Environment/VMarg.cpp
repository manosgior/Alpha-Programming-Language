#include "VMarg.h"
#include <assert.h>

VMarg::VMarg(){
    this->type = invalid_a;
    this->value = 0;
}

VMarg::VMarg(VMarg_Type t, unsigned int v) : type(t), value(v) {
}

VMarg_Type VMarg::getType(){
    return type;
}

unsigned int VMarg::getValue(){
    return value;
}

void VMarg::setJumpValue(unsigned int jVal){
    this->type = label_a;
    this->value = jVal;
}

void VMarg::convertToRetValOperand(){
    this->type = retval_a;
}
