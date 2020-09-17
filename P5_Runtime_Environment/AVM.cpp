#include "AVM.h"
#include "error_handler.h"
#include "VMarg.h"
#include "instruction.h"
#include <cmath>
#include <assert.h>
#include <fstream>
#include <string.h>


unsigned VM_ERRNO = 0;
unsigned __currentLine__ = 0;

int readString(std::ifstream& ifs, char ** buffer) {
    size_t tmp;
    if (!ifs.read((char *) &tmp, sizeof(size_t))){
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return 0;
    }
    if (!(*buffer != nullptr && tmp <= strlen(*buffer)+1)) {
        if (*buffer != nullptr) delete[] *buffer;
        *buffer = new char[tmp];
    }
    if (!ifs.read(*buffer, tmp)) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return 0;
    }
    return 1;
}

AVM::AVM(std::ifstream& ifs) {
    totalActuals = 0;
    unsigned int magic_number;
    ifs.read((char *) &magic_number, sizeof(unsigned int));
    if (magic_number != 340200501) {
        error(ErrorType::Error, 0, "Input is not a valid Alpha Executable\n");
        return;
    }
    size_t num;
    if (!ifs.read((char *) &num, sizeof(size_t))) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return;
    }
    char * buffer = nullptr;
    for (size_t i = 0; i < num; i++) {
        if (!readString(ifs, &buffer)) return;
        CONSTSTRINGS.push_back(buffer);
    }
    if (!ifs.read((char *)&num, sizeof(size_t))) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return;
    }
    double tmp_d;
    for (size_t i = 0; i < num; i++) {
        if (!ifs.read((char*)&tmp_d, sizeof(double))) {
            error(ErrorType::Error, 0, "Bad Input File Format");
            return;
        }
        CONSTNUMS.push_back(tmp_d);
    }
    if (!ifs.read((char*)&num, sizeof(size_t))) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return;
    }
    unsigned tmp_adr, tmp_lsize, tmp_formals;
    for (size_t i = 0; i < num; i++) {
        if(!ifs.read((char*)&tmp_adr, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return; 
        }
        //number of locals
        if (!ifs.read((char*)&tmp_lsize, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }
        //number of formals
        if (!ifs.read((char*)&tmp_formals, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }        
        if (!readString(ifs, &buffer)) return;
        addressToFuncInfo[tmp_adr] = {tmp_adr, tmp_lsize, tmp_formals, std::string(buffer)};
    }
    if (!ifs.read((char*)&num, sizeof(size_t))) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return;
    }
    for (size_t i = 0; i < num; i++) {
        if (!readString(ifs, &buffer)) return;
        LIBFUNCNAMES.push_back(buffer);
    }
    if (!ifs.read((char*)&num, sizeof(size_t))) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return;
    }
    uint8_t tmp_optype, tmp_restype, tmp_arg1type, tmp_arg2type;
    unsigned tmp_resvalue, tmp_arg1value, tmp_arg2value, tmp_line;
    size_t globalCounter = 0;
    if (!ifs.read((char*)&globalCounter, sizeof(size_t))) {
        error(ErrorType::Error, 0, "Bad Input File Format\n");
        return;
    }    
    CODE.push_back( Instruction(nop_tc, VMarg(), VMarg(), VMarg(), 0) );

    for (size_t i = 0; i < num; i++) {
        if (!ifs.read((char*)&tmp_optype, sizeof(uint8_t))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }
        if (!ifs.read((char*)&tmp_restype, sizeof(uint8_t))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }
        if (!ifs.read((char*)&tmp_resvalue, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }

        if (!ifs.read((char*)&tmp_arg1type, sizeof(uint8_t))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }
        if (!ifs.read((char*)&tmp_arg1value, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }

        if (!ifs.read((char*)&tmp_arg2type, sizeof(uint8_t))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }
        if (!ifs.read((char*)&tmp_arg2value, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }

        if (!ifs.read((char*)&tmp_line, sizeof(unsigned))) {
            error(ErrorType::Error, 0, "Bad Input File Format\n");
            return;
        }  
        CODE.push_back(
            Instruction((TCodeOpcode)tmp_optype, 
                VMarg((VMarg_Type) tmp_restype, tmp_resvalue), 
                VMarg((VMarg_Type) tmp_arg1type, tmp_arg1value),
                VMarg((VMarg_Type) tmp_arg2type, tmp_arg2value),
                tmp_line
            )
        );
    }
    PC = 1;
    for (size_t i = 0; i < AVM_STACK_SIZE; i++) {
        STACK.push_back(AVM_MemCell(i));
    }
    TOPSP = 0; 
    TOP = globalCounter;
    VM_ERRNO = 0;
    registerLibfunc("print", &AVM::libfuncPrint);
    registerLibfunc("typeof", &AVM::libfuncTypeOf);
    registerLibfunc("argument", &AVM::libfuncArgument);
    registerLibfunc("totalarguments", &AVM::libfuncTotalArguments);
    registerLibfunc("strtonum", &AVM::libfuncStrToNum);
    registerLibfunc("sqrt", &AVM::libfuncSqrt);
    registerLibfunc("cos", &AVM::libfuncCos);
    registerLibfunc("sin", &AVM::libfuncSin);
    registerLibfunc("input", &AVM::libfuncInput);
    registerLibfunc("objecttotalmembers", &AVM::libfuncObjectTotalMembers);
    registerLibfunc("objectmemberkeys", &AVM::libfuncObjectMemberKeys);
    registerLibfunc("objectcopy", &AVM::libfuncObjectCopy);
    __currentLine__ = 1;
    delete[] buffer;
}


bool AVM::AVM_toBool(AVM_MemCell* cell){
	assert(cell);
	
	assert(cell->getType() >= 0 && cell->getType() < AVM_MemCell_t::undef_m);
	
	return (this->*toBoolDispatcher[cell->getType()])(cell);
}

bool AVM::numberToBool(AVM_MemCell* cell){	
	return (cell->data.numVal != 0);
}

bool AVM::stringToBool(AVM_MemCell* cell){	
	assert(cell->data.strVal);
	
	return (cell->data.strVal[0] != 0);
}

bool AVM::boolToBool(AVM_MemCell* cell){	
	return cell->data.boolVal;
}

bool AVM::tableToBool(AVM_MemCell* cell){	
	return true;
}

bool AVM::userfuncToBool(AVM_MemCell* cell){
	return true;
}

bool AVM::libfuncToBool(AVM_MemCell* cell){
	return true;
}

bool AVM::nilToBool(AVM_MemCell* cell){
	return false;
}

bool AVM::undefToBool(AVM_MemCell* cell){
	assert(false);
	
	return false;
}


void AVM::callLibfunc(std::string fName){
	LibraryFunc_t f = getLibraryFunc(fName);
	
	if(!f){
        error(Error, __currentLine__, "Unsupported library function: %s\n", fName.c_str());
	}
	else{
		TOPSP = TOP;
		totalActuals = 0;
		
		(this->*f)();
		
		if(!errorExists){
			executeFuncexit((Instruction *) nullptr);
		}
	}
}

void AVM::callLibfunc(unsigned index){
	assert(index < LIBFUNCNAMES.size());
	
	LibraryFunc_t f = libfuncNameToCode[LIBFUNCNAMES[index]];
	
	TOPSP = TOP;
	totalActuals = 0;
	
	(this->*f)();
	
	if(!errorExists){
		executeFuncexit((Instruction *) nullptr);
	}	
}

userFuncInfo AVM::getFuncInfo(unsigned address){
	return addressToFuncInfo[address];
}

AVM::LibraryFunc_t AVM::getLibraryFunc(std::string id){
	return libfuncNameToCode[id];
}

double AVM::addImpl(double x, double y) {
    return x+y;
}

double AVM::subImpl(double x, double y) {
    return x-y;
}

double AVM::mulImpl(double x, double y) {
    return x*y;
}

double AVM::divImpl(double x, double y) {
    if (y == 0) {
        error(Error, __currentLine__, "Division with 0\n");
        errorExists = true;
        return -1;
    }
    return x/y;
}

double AVM::modImpl(double x, double y) {
    if (x < 0 || y <= 0 || floor(x) != x || floor(y) != y) {
        error(Error, __currentLine__, "Mod operation with modulus 0\n");
        errorExists = true;
        return -1;
    }
    return ((unsigned)x)%((unsigned)y);
}

unsigned AVM::getEnvValue(unsigned i) {
    assert(STACK[i].getType() == number_m);
    unsigned val = (unsigned) STACK[i].data.numVal;
    assert(STACK[i].data.numVal == ((double) val));
    return val;
}

unsigned AVM::getTotalActuals() {
    return getEnvValue(TOPSP - AVM_NUMACTUALS_OFFSET);
}

AVM_MemCell& AVM::getActual(unsigned i) {
    assert(i < getTotalActuals());
    return STACK[TOPSP - AVM_STACKENV_SIZE - 1 - i];
}

void AVM::registerLibfunc(std::string id, LibraryFunc_t implementation) {
    libfuncNameToCode[id] = implementation;
}

AVM_MemCell* AVM::translateOperand(VMarg* arg, AVM_MemCell* reg){
    switch(arg->getType()){
        case global_a:
            return &STACK[arg->getValue()];
        case local_a:
            return &STACK[arg->getValue() + TOPSP];
        case formal_a:
            return &STACK[TOPSP - AVM_STACKENV_SIZE - 1 - arg->getValue()];
        case retval_a:
            return &RETVAL;
        case number_a:
            reg->clear();
            reg->setType(number_m);
            reg->data.numVal = CONSTNUMS[ arg->getValue() ];
            return reg;
        case string_a:
            reg->clear();
            reg->setType(string_m);
            reg->data.strVal = strdup(CONSTSTRINGS[ arg->getValue() ].c_str());
            return reg;        
        case bool_a:
            reg->clear();
            reg->setType(bool_m);
            reg->data.boolVal = arg->getValue();
            return reg;
        case nil_a:
            reg->clear();
            reg->setType(nil_m);
            return reg;
        case userfunc_a:
            reg->clear();
            reg->setType(userfunc_m);
            reg->data.funcVal = arg->getValue();//function address stored in VMarg
            return reg;
        case libfunc_a:
            reg->clear();
            reg->setType(libfunc_m);
            reg->data.libfuncVal = strdup(LIBFUNCNAMES[ arg->getValue() ].c_str());
            return reg;
        default:
            assert(0);
    }
}

void AVM::incTop(void) {
    if (TOP >= AVM_STACK_SIZE) {
        error(Error, __currentLine__, "Stack overflow\n");
    } else {
        TOP++;
    }
}

void AVM::pushEnvValue(unsigned val) {
    STACK[TOP].setType(number_m);
    STACK[TOP].data.numVal = val;
    incTop();
}

void AVM::callSaveEnvironment() {
    pushEnvValue(totalActuals);
    pushEnvValue(PC+1);
    pushEnvValue(TOP-totalActuals-2);
    pushEnvValue(TOPSP);
}

void AVM::execute() {
    while (PC < CODE.size()) {
        if (errorExists) break;
        Instruction instr = CODE[PC];
        assert(instr.getOpcode() >= assign_tc && instr.getOpcode() <= nop_tc);
        unsigned oldPC = PC;
        __currentLine__ = instr.getLine();
        (this->*executeDispatcher[instr.getOpcode()])(&instr);
        if (PC == oldPC) ++PC;
    }
}

AVM::~AVM(){
    for(int i = 0; i < AVM_STACK_SIZE; i++){
        STACK[i].clear();
    }
    RETVAL.clear();
    AX.clear();
    BX.clear();
    CX.clear();
}
