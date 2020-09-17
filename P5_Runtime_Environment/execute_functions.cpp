#include "AVM.h"
#include "AVM_MemCell.h"
#include "instruction.h"
#include "VMarg.h"
#include "AVM_Table.h"
#include <string.h>

#define AVM_SAVEDTOPSP_OFFSET 1
#define AVM_SAVED_TOP_OFFSET 2
#define AVM_SAVED_PC_OFFSET 3
#define AVM_NUM_ACTUALS_OFFSET 4

void AVM::executeFuncenter(Instruction *i){
    VMarg res = i->getResult();
    AVM_MemCell *func = translateOperand(&res, &AX);
    assert(func);
    assert(PC == func->data.funcVal);
    RETVAL.clear();
    //callee actions
    totalActuals = 0;
    userFuncInfo info = getFuncInfo(PC); // get the information for this function
    TOPSP = TOP;
    TOP = TOP + info.localsize;
}

void AVM::executeFuncexit(Instruction *i){
    unsigned oldTop = TOP;
    TOP = getEnvValue(TOPSP - AVM_SAVED_TOP_OFFSET);
    PC = getEnvValue(TOPSP - AVM_SAVED_PC_OFFSET);
    TOPSP = getEnvValue(TOPSP - AVM_SAVEDTOPSP_OFFSET);
    if(RETVAL.getType() == undef_m)
        RETVAL.setType(nil_m);
    while(--oldTop >= TOP){ //clear the stack
        STACK[oldTop].clear();
    }
}

void AVM::executeCall(Instruction * i) {
    VMarg arg1 = i->getArg1();
    AVM_MemCell* func = translateOperand(&arg1, &AX);
    assert(func);
    if(errorExists)
        return;

    switch (func->getType()) {
        case (userfunc_m):
            if(totalActuals < addressToFuncInfo[func->data.funcVal].numberOfFormals){
                std::vector<AVM_MemCell> tmpStack;
                error(Warning,  __currentLine__, 
                        "Function \"%s\" called with less actuals than formals; remaining arguments will be undef\n"
                                , addressToFuncInfo[func->data.funcVal].id.c_str());
                for(unsigned i = 0; i < totalActuals; i++){
                    tmpStack.push_back(STACK[--TOP]);
                }
                while(totalActuals < addressToFuncInfo[func->data.funcVal].numberOfFormals){    
                    STACK[TOP] = AVM_MemCell(TOP);
                    ++totalActuals;
                    incTop();
                }
                while( !tmpStack.empty() ){
                    STACK[TOP] = tmpStack.back();
                    tmpStack.pop_back();
                    incTop();
                }
            }
            if(errorExists)
                return;            
            callSaveEnvironment();
            PC = func->data.funcVal;
            assert(PC < CODE.size()+1);
            assert(CODE[PC].getOpcode() == enterfunc_tc);
            break;
        
        case (string_m):
            callSaveEnvironment();
            callLibfunc(func->data.strVal);
            break;
        case (libfunc_m):
            callSaveEnvironment();
            callLibfunc(func->data.libfuncVal);
            break;
        case (table_m):{
            AVM_MemCell paren = AVM_MemCell(string_m);
            paren.data.strVal = strdup("()");
            AVM_MemCell functor;
            while( (functor = (func->data.tableVal)->getElem(&paren)).getType() == table_m ){
                func->assign(&functor);
            }
            switch(functor.getType()){
                case(userfunc_m):
                    STACK[TOP].assign(func);
                    ++totalActuals;
                    incTop();
                    callSaveEnvironment();
                    PC = functor.data.funcVal;
                    assert(PC < CODE.size()+1);
                    assert(CODE[PC].getOpcode() == enterfunc_tc);
                    break;  
                case (string_m):
                    STACK[TOP].assign(func);
                    ++totalActuals;
                    incTop();                
                    callSaveEnvironment();
                    callLibfunc(functor.data.strVal);
                    break;                
                case(libfunc_m):   
                    STACK[TOP].assign(func);
                    ++totalActuals;
                    incTop();
                    callSaveEnvironment();  
                    callLibfunc(functor.data.libfuncVal);
                    break;
                default:
                    std::string s = func->toString();
                    error(ErrorType::Error, i->getLine(), "'%s': not a functor\n", s.c_str());                                         
            }
            free(paren.data.strVal);
            paren.data.strVal = nullptr;
            break;
        }
        default:
            std::string s = func->toString();
            error(ErrorType::Error, i->getLine(), "Cannot bind '%s' to function!\n", s.c_str());
    }
}

void AVM::executePusharg(Instruction * i) {
    VMarg arg1 = i->getArg1();
    AVM_MemCell * arg = translateOperand(&arg1, &AX);
    assert(arg);
    STACK[TOP].assign(arg);
    ++totalActuals;
    incTop();
}