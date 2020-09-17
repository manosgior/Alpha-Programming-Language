#ifndef VMARG_H
#define VMARG_H

#include <string>
#include "expression.h"

enum VMarg_Type {
    global_a, local_a, formal_a, bool_a, string_a, number_a, nil_a, userfunc_a, libfunc_a, label_a, invalid_a,
    retval_a
};

class VMarg {
private:
    VMarg_Type type;
    unsigned int value;
    std::string type2string[12] = {
		"global",  "local",     "formal",
		"bool",    "string",    "number",
		"nil",     "userfunc",  "libfunc",
		"label",   "invalid",   "retval"
		
	};
public:
    VMarg();
    VMarg(expr * e);
    VMarg_Type getType();
    unsigned int getValue();
    void setJumpValue(unsigned int);
    void convertToRetValOperand();
    std::string toString();
};

#endif
