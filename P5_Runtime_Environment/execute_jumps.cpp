#include "AVM.h"
#include "AVM_MemCell.h"
#include <cstring>

extern unsigned VM_ERRNO;

void AVM::executeJump(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	if(!errorExists){
		PC = inst->getResult().getValue();
	}
}

void AVM::executeJeq(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	bool result = false;
	
	if(rv1->getType() == AVM_MemCell_t::undef_m || rv2->getType() == AVM_MemCell_t::undef_m){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());			
	}
	else if(rv1->getType() == AVM_MemCell_t::bool_m || rv2->getType() == AVM_MemCell_t::bool_m){
		result = (AVM_toBool(rv1) == AVM_toBool(rv2));
	}
	else if(rv1->getType() == AVM_MemCell_t::nil_m || rv2->getType() == AVM_MemCell_t::nil_m){
		result = (rv1->getType() == AVM_MemCell_t::nil_m && rv2->getType() == AVM_MemCell_t::nil_m);
	}
	else if(rv1->getType() != rv2->getType()){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else{
		if(rv1->getType() == AVM_MemCell_t::number_m){
			result = (rv1->data.numVal == rv2->data.numVal);
		}
		else if(rv1->getType() == AVM_MemCell_t::string_m){
			result = (strcmp(rv1->data.strVal, rv2->data.strVal) == 0);
		}
		else if(rv1->getType() == AVM_MemCell_t::libfunc_m){
			result = (strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal) == 0);
		}
		else if(rv1->getType() == AVM_MemCell_t::table_m){
			result = (rv1->data.tableVal == rv2->data.tableVal);
		}
		else if(rv1->getType() == AVM_MemCell_t::userfunc_m){
			result = (rv1->data.funcVal == rv2->data.funcVal);
		}
	}
	
	if(!errorExists && result){
		PC = inst->getResult().getValue();
	}
}

void AVM::executeJne(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	bool result = false;
	
	if(rv1->getType() == AVM_MemCell_t::undef_m || rv2->getType() == AVM_MemCell_t::undef_m){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else if(rv1->getType() == AVM_MemCell_t::bool_m || rv2->getType() == AVM_MemCell_t::bool_m){
		result = (AVM_toBool(rv1) != AVM_toBool(rv2));
	}
	else if(rv1->getType() == AVM_MemCell_t::nil_m || rv2->getType() == AVM_MemCell_t::nil_m){
		result = !(rv1->getType() == AVM_MemCell_t::nil_m && rv2->getType() == AVM_MemCell_t::nil_m);
	}
	else if(rv1->getType() != rv2->getType()){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else{
		if(rv1->getType() == AVM_MemCell_t::number_m){
			result = (rv1->data.numVal != rv2->data.numVal);
		}
		else if(rv1->getType() == AVM_MemCell_t::string_m){
			result = (strcmp(rv1->data.strVal, rv2->data.strVal) != 0);
		}
		else if(rv1->getType() == AVM_MemCell_t::libfunc_m){
			result = (strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal) != 0);
		}
		else if(rv1->getType() == AVM_MemCell_t::table_m){
			result = (rv1->data.tableVal != rv2->data.tableVal);
		}
		else if(rv1->getType() == AVM_MemCell_t::userfunc_m){
			result = (rv1->data.funcVal != rv2->data.funcVal);
		}
	}
	
	if(!errorExists && result){
		PC = inst->getResult().getValue();
	}
}


void AVM::executeJle(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	bool result = false;
	
	if(rv1->getType() != AVM_MemCell_t::number_m || rv2->getType() != AVM_MemCell_t::number_m){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else{
		result = (rv1->data.numVal <= rv2->data.numVal);
	}
	
	
	if(!errorExists && result){
		PC = inst->getResult().getValue();
	}
}

void AVM::executeJge(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	bool result = false;
	
	if(rv1->getType() != AVM_MemCell_t::number_m || rv2->getType() != AVM_MemCell_t::number_m){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else{
		result = (rv1->data.numVal >= rv2->data.numVal);
	}
	
	
	if(!errorExists && result){
		PC = inst->getResult().getValue();
	}
}

void AVM::executeJlt(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	bool result = false;
	
	if(rv1->getType() != AVM_MemCell_t::number_m || rv2->getType() != AVM_MemCell_t::number_m){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else{
		result = (rv1->data.numVal < rv2->data.numVal);
	}
	
	
	if(!errorExists && result){
		PC = inst->getResult().getValue();
	}
}

void AVM::executeJgt(Instruction *inst){
	assert(inst->getResult().getType() == VMarg_Type::label_a);
	
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	
	AVM_MemCell *rv1 = translateOperand(&arg1, &AX);
	AVM_MemCell *rv2 = translateOperand(&arg2, &BX);
	
	bool result = false;
	
	if(rv1->getType() != AVM_MemCell_t::number_m || rv2->getType() != AVM_MemCell_t::number_m){
		error(ErrorType::Error, inst->getLine(), VM_ERROR[6].c_str());		
	}
	else{
		result = (rv1->data.numVal > rv2->data.numVal);
	}
	
	
	if(!errorExists && result){
		PC = inst->getResult().getValue();
	}
}

