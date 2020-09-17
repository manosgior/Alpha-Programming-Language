#include "VMarg.h"
#include "expression.h"
#include "symtable.h"
#include "quadtable.h"
#include "instructiontable.h"
#include "expression.h"
#include <assert.h>

extern QuadTable quad_table;
extern InstructionTable instruction_table;

VMarg::VMarg(){
    this->type = invalid_a;
    this->value = 0;
}

VMarg::VMarg(VMarg_Type t, unsigned int v) : type(t), value(v) {
}

VMarg::VMarg(expr * e){
    assert(e);
    switch(e->getType()){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case assignexpr_e:
        case newtable_e: {
            assert(e->getSymbol());
            this->value = e->getSymbol()->getOffset();

            switch(e->getSymbol()->getScopespaceType()){
                case programvar:
                    this->type = global_a;
                    break;
                case functionlocal:
                    this->type = local_a;
                    break;
                case formalarg:
                    this->type = formal_a;
                    break;
                default:
                    assert(0);
            }
            break;
        }
    
        case constbool_e: {
            this->value = e->getBoolConst();
            this->type = bool_a;
            break;
        }

        case conststring_e: {
            this->value = instruction_table.newStringConst( e->getStringConst() );
            this->type = string_a;
            break;
        }

        case constnum_e: {
            this->value = instruction_table.newNumConst( e->getNumConst() );
            this->type = number_a;
            break;
        }

        case nil_e:{
            this->type = nil_a;
            break;
        }

        case programfunc_e:{
            this->type = userfunc_a;
            this->value = quad_table.getQuad( e->getSymbol()->getFuncAddress() ).TCodeAddress;
            break;
        }
        
        case libraryfunc_e: {
            this->type = libfunc_a;
            this->value = instruction_table.newLibFunc( e->getName() );
            break;
        }

        default:
            assert(0);
    }
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

std::string VMarg::toString(){
	
	return type2string[type] + " (" + std::to_string(value) + ")";
}
