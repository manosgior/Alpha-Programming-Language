#ifndef AVM_MEMCELL_H
#define AVM_MEMCELL_H

#include "VMarg.h"
#include <string>

extern unsigned VM_ERRNO;

enum AVM_MemCell_t {
    number_m = 0,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m,
    nonexistent_m
};

class AVM_Table;

class AVM_MemCell {
private:
    typedef std::string (AVM_MemCell::*Data_toString)() ;
    unsigned stackIndex;
    AVM_MemCell_t type;
    Data_toString toStringFuncs[8] = {
        &AVM_MemCell::number_toString,
        &AVM_MemCell::string_toString,
        &AVM_MemCell::bool_toString,
        &AVM_MemCell::table_toString,
        &AVM_MemCell::userfunc_toString,
        &AVM_MemCell::libfunc_toString,
        &AVM_MemCell::nil_toString,
        &AVM_MemCell::undef_toString
    };

    std::string number_toString();
    std::string string_toString();
    std::string bool_toString();
    std::string table_toString();
    std::string userfunc_toString();
    std::string libfunc_toString();
    std::string nil_toString();
    std::string undef_toString();
  

public:
	union {
        double      numVal;
        char*       strVal;
        bool        boolVal;
        AVM_Table*  tableVal;
        unsigned    funcVal;
        char*       libfuncVal;
    } data;    

    AVM_MemCell();
    AVM_MemCell(size_t);
    AVM_MemCell(AVM_MemCell_t);
    void assign(AVM_MemCell *other);
    std::string toString();
    std::string toStringTypeOf();
    void setType(AVM_MemCell_t);
    unsigned getStackIndex();
    AVM_MemCell_t getType();   
    void clear();
};
#endif
