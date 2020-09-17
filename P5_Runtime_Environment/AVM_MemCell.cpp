
#include "AVM_MemCell.h"
#include "AVM_Table.h"
#include <string.h>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include "error_handler.h"

extern unsigned __currentLine__;

AVM_MemCell::AVM_MemCell(){
    type = undef_m;
}

AVM_MemCell::AVM_MemCell(size_t si) : stackIndex(si) {
    type = undef_m;
}

AVM_MemCell::AVM_MemCell(AVM_MemCell_t t) : type(t) {

}


void AVM_MemCell::assign(AVM_MemCell *other){
    if(this == other)
        return; //self assignment
    if(this->type == table_m && other->type == table_m && this->data.tableVal == other->data.tableVal)
        return; //pointing to same table already
    if(other->type == undef_m)
        error(Warning, __currentLine__, "Assigning from a variable of undefined type\n");

    //take care of previous dynamic memory
    if(this->type == string_m)
        free(this->data.strVal);
    else if(this->type == libfunc_m)
        free(this->data.libfuncVal);
    else if(this->type == table_m){
        (this->data.tableVal)->decRefCounter();
        if(this->data.tableVal->getRefCounter() == 0)
            delete this->data.tableVal;
    }
    
    this->type = other->type;
    this->data = other->data;

    if(this->type == string_m)
        this->data.strVal = strdup(other->data.strVal);
    if(this->type == libfunc_m)
        this->data.libfuncVal = strdup(other->data.libfuncVal);
    else if(this->type == table_m)
        (this->data.tableVal)->incRefCounter(); 
}

void AVM_MemCell::clear(){
    if(this->type == string_m){
        free(this->data.strVal);
        this->data.strVal = nullptr;
    }
    else if(this->type == libfunc_m){
        free(this->data.libfuncVal);
        this->data.libfuncVal = nullptr;
    }
    else if(this->type == table_m){
        (this->data.tableVal)->decRefCounter();
        if(this->data.tableVal->getRefCounter() == 0)
            delete this->data.tableVal;
        this->data.tableVal = nullptr;
    }

    this->type = undef_m;
}

std::string AVM_MemCell::number_toString(){
    std::ostringstream out;
     
    out << std::fixed << std::setprecision(3) << this->data.numVal;
    
    return out.str();   
}

std::string AVM_MemCell::string_toString(){
	return std::string(this->data.strVal);
}

std::string AVM_MemCell::bool_toString(){
	return (this->data.boolVal ? "true" : "false");
}

std::string AVM_MemCell::table_toString(){
	return this->data.tableVal->toString();
}

std::string AVM_MemCell::userfunc_toString(){
	return "user function " + std::to_string(this->data.funcVal);
}

std::string AVM_MemCell::libfunc_toString(){
	return "library function " + std::string(this->data.libfuncVal);
}

std::string AVM_MemCell::nil_toString(){
	return "nil";
}

std::string AVM_MemCell::undef_toString(){
	return "undefined object";
}

std::string AVM_MemCell::toString(){
    return (this->*toStringFuncs[type])();
}

void AVM_MemCell::setType(AVM_MemCell_t t){
    this->type = t;
}

AVM_MemCell_t AVM_MemCell::getType(){
    return type;
}

unsigned AVM_MemCell::getStackIndex() {
    return stackIndex;
}

std::string AVM_MemCell::toStringTypeOf(){
    
    switch(this->type){
        case number_m:
            return "number";
        case string_m:
            return "string";
        case bool_m:
            return "boolean";
        case table_m:
            return "table";
        case userfunc_m:
            return "userfunction";
        case libfunc_m:
            return "libraryfunction";
        case nil_m:
            return "nil";
        case undef_m:
            return "undefined object";
        default:
            assert(false);
    }
}
