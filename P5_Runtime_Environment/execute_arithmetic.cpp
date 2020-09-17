#include "AVM.h"
#include "AVM_MemCell.h"

extern unsigned VM_ERRNO;
extern unsigned __currentLine__;

void AVM::executeArithmetic(Instruction *inst){
	VMarg res = inst->getResult();
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *lv = translateOperand(&res, (AVM_MemCell *) nullptr);
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	assert(lv && ((lv->getStackIndex() >= 0 && lv->getStackIndex()< TOP) || lv == &RETVAL));
	assert(rv1 && rv2);
	
	if(rv1->getType() != number_m || rv2->getType() != number_m){
		error(ErrorType::Error, __currentLine__, "Arithmetic operand applied to non-numerical values\n");
	}
	else{
		AVM::ArithmeticFunc_t op = arithmeticDispatcher[inst->getOpcode() - add_tc];
		lv->clear();
		lv->setType(AVM_MemCell_t::number_m);
		lv->data.numVal = (this->*op)(rv1->data.numVal, rv2->data.numVal);
	}
}
