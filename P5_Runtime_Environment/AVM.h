#ifndef AVM_H
#define AVM_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <assert.h>
#include "instruction.h"
#include "error_handler.h"
#include "VMarg.h"
#include "AVM_MemCell.h"

extern bool errorExists;

extern unsigned VM_ERRNO; /* 1: Division with 0, 2: invalid modulo operand, 3: Assignment from variable of undef type */ 

#define AVM_STACKENV_SIZE 4
#define AVM_NUMACTUALS_OFFSET 4
#define AVM_STACK_SIZE 4096
#define AVM_SAVEDTOPSP_OFFSET 1
#define AVM_SAVED_TOP_OFFSET 2
#define AVM_SAVED_PC_OFFSET 3
#define AVM_NUM_ACTUALS_OFFSET 4

extern unsigned __currentLine__;

class AVM {
private:
    //Type Declarations
    typedef void (AVM::*LibraryFunc_t)(void);
    typedef void (AVM::*ExecuteFunc_t)(Instruction*);
    typedef double (AVM::*ArithmeticFunc_t)(double, double);
    typedef bool (AVM::*ToBoolFunc_t)(AVM_MemCell*);

    //Executioners
    //Assignment
    void                                 executeAssign(Instruction *);
    //Arithmetic    
    void 								 executeArithmetic(Instruction *);
    //Branches
    void                                 executeJump(Instruction *);
    void                                 executeJeq(Instruction *);
    void                                 executeJne(Instruction *);
    void                                 executeJle(Instruction *);
    void                                 executeJge(Instruction *);
    void                                 executeJlt(Instruction *);
    void                                 executeJgt(Instruction *);
    void								 executeBranch(Instruction *);
    //Functions
    void                                 executeCall(Instruction *);
    void                                 executePusharg(Instruction *);
    void                                 executeFuncenter(Instruction *);
    void                                 executeFuncexit(Instruction *);
    //Tables
    void                                 executeNewtable(Instruction *);
    void                                 executeTablegetelem(Instruction *);
    void                                 executeTablesetelem(Instruction *);
    //NOP
    void                                 executeNop(Instruction *);

    //Arithmetic Utilities
    double                               addImpl(double x, double y);
    double                               subImpl(double x, double y);
    double                               mulImpl(double x, double y);
    double                               divImpl(double x, double y);
    double                               modImpl(double x, double y);

    //Boolean Convertors
    bool                                 numberToBool(AVM_MemCell*);
    bool                                 stringToBool(AVM_MemCell*);
    bool                                 boolToBool(AVM_MemCell*);
    bool                                 tableToBool(AVM_MemCell*);
    bool                                 userfuncToBool(AVM_MemCell*);
    bool                                 libfuncToBool(AVM_MemCell*);
    bool                                 nilToBool(AVM_MemCell*);
    bool                                 undefToBool(AVM_MemCell*);

    //Fields
    unsigned                             PC;
    AVM_MemCell                          RETVAL;
    unsigned                             TOP;
    unsigned                             TOPSP;
    AVM_MemCell                          CALLMEM;
    AVM_MemCell                          DATAMEM;
    AVM_MemCell                          AX;
    AVM_MemCell                          BX;
    AVM_MemCell                          CX;
    std::vector<Instruction>             CODE;
    std::vector<AVM_MemCell>             STACK;
    std::vector<double>                  CONSTNUMS;
    std::vector<std::string>             CONSTSTRINGS;
    std::vector<std::string>             LIBFUNCNAMES;
    std::map<unsigned, userFuncInfo>     addressToFuncInfo;
    std::map<std::string, LibraryFunc_t> libfuncNameToCode;
    unsigned                             totalActuals;
    ExecuteFunc_t                        executeDispatcher[21] = {
        &AVM::executeAssign,
        &AVM::executeArithmetic,
        &AVM::executeArithmetic,
        &AVM::executeArithmetic,
        &AVM::executeArithmetic,
        &AVM::executeArithmetic,
        &AVM::executeCall,
        &AVM::executeFuncenter,
        &AVM::executeFuncexit,
        &AVM::executeJump,
        &AVM::executeJeq,
        &AVM::executeJne,
        &AVM::executeJgt,
        &AVM::executeJlt,
        &AVM::executeJge,
        &AVM::executeJle,
        &AVM::executeNewtable,
        &AVM::executeTablegetelem,
        &AVM::executeTablesetelem,
        &AVM::executePusharg,
        &AVM::executeNop
    };
    ArithmeticFunc_t                     arithmeticDispatcher[5] = {
        &AVM::addImpl,
        &AVM::subImpl,
        &AVM::mulImpl,
        &AVM::divImpl,
        &AVM::modImpl
    };
    ToBoolFunc_t                         toBoolDispatcher[8] = {
        &AVM::numberToBool,
        &AVM::stringToBool,
        &AVM::boolToBool,
        &AVM::tableToBool,
        &AVM::userfuncToBool,
        &AVM::libfuncToBool,
        &AVM::nilToBool,
        &AVM::undefToBool
    };
    std::string                          VM_ERROR[19] = {
        "Reserved",
        "Division With 0",
        "Invalid Modulo Operand (either operand not a natural number or second operand 0)",
        "Assignment from a variable of undefined type",
        "unsupported lib function  called",
        "Arithmetic operand applied to non numerical values",
        "Undefined involved in comparison",
        "Illegal type used as table",
        "Table index not found",
        "Stack Overflow",
        "Invalid Index Type",
        "lib function \"typeof\" expects 1 argument",
        "\"total arguments\" called outside a function",
        "lib function \"argument\" expects 1 argument",
        "\"argument\" called outside a function",
        "lib function \"strtonum\" expects 1 argument",
        "lib function \"sqrt\" expects 1 argument"
        "lib function \"cos\" expects 1 argument"
        "lib function \"sin\" expects 1 argument"
    };

    //Helpers
    AVM_MemCell*                         translateOperand(VMarg* arg, AVM_MemCell* reg);
    bool								 AVM_toBool(AVM_MemCell*);
    void                                 callLibfunc(std::string);
    void                                 callLibfunc(unsigned);
    void                                 callSaveEnvironment();
    void                                 incStack();
    void                                 pushEnvValue(unsigned);
    userFuncInfo                         getFuncInfo(unsigned address);
    unsigned                             getEnvValue(unsigned);
    LibraryFunc_t                        getLibraryFunc(std::string id);
    unsigned                             getTotalActuals();
    AVM_MemCell&                         getActual(unsigned);
    void                                 registerLibfunc(std::string id, LibraryFunc_t implementation);
    void                                 incTop(void);

    //Library Functions
    void                                 libfuncPrint();
    void                                 libfuncTypeOf();
    void                                 libfuncTotalArguments();
    void                                 libfuncArgument();
    void                                 libfuncStrToNum();
    void                                 libfuncSqrt();
    void                                 libfuncCos();
    void                                 libfuncSin();
    void                                 libfuncInput();
    void                                 libfuncObjectTotalMembers();
    void                                 libfuncObjectMemberKeys();
    void                                 libfuncObjectCopy();
public:
    AVM(std::ifstream&);
    ~AVM();
    void execute();
};

#endif
