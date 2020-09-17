#include "AVM.h"
#include "AVM_MemCell.h"
#include "VMarg.h"
#include "error_handler.h"
#include <string>


void AVM::executeAssign(Instruction *i){
    VMarg res = i->getResult();
    VMarg arg1 = i->getArg1();
    AVM_MemCell *lValue = translateOperand(&res, nullptr);
    AVM_MemCell *rValue = translateOperand(&arg1, &AX);

    assert(lValue && ( (lValue->getStackIndex() >= 0 && lValue->getStackIndex() < TOP) || lValue == &RETVAL) );
    assert(rValue);

    lValue->assign(rValue);
    if(rValue == &RETVAL){
        RETVAL.clear();
        RETVAL.setType(nil_m);
    }
}