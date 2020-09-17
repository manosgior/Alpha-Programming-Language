#ifndef VMARG_H
#define VMARG_H

#include <string>

enum VMarg_Type {
    global_a, local_a, formal_a, bool_a, string_a, number_a, nil_a, userfunc_a, libfunc_a, label_a, invalid_a,
    retval_a
};

class VMarg {
private:
    VMarg_Type type;
    unsigned int value;

public:
    VMarg();
    VMarg(VMarg_Type t, unsigned int v);
    VMarg_Type getType();
    unsigned int getValue();
    void setJumpValue(unsigned int);
    void convertToRetValOperand();
};

#endif
