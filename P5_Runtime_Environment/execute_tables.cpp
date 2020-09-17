#include "AVM.h"
#include "AVM_Table.h"

extern unsigned __currentLine__;

void AVM::executeNewtable(Instruction *inst){
	VMarg result = inst->getResult();
	
	AVM_MemCell *lv = translateOperand(&result, (AVM_MemCell *) 0);
	
	assert(lv && ((lv->getStackIndex() >= 0 && lv->getStackIndex()< TOP) || lv == &RETVAL));
	
	lv->clear();
	
	lv->setType(AVM_MemCell_t::table_m);
	lv->data.tableVal = new AVM_Table();
	lv->data.tableVal->incRefCounter();
}

void AVM::executeTablegetelem(Instruction *inst){
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	VMarg result = inst->getResult();
	
	AVM_MemCell *lv = translateOperand(&result, (AVM_MemCell *) 0);
	AVM_MemCell *t = translateOperand(&arg1, (AVM_MemCell *) 0);
	AVM_MemCell *i = translateOperand(&arg2, &AX);
	
	assert(lv && ((lv->getStackIndex() >= 0 && lv->getStackIndex()< TOP) || lv == &RETVAL));
	assert(t && (t->getStackIndex() >= 0 && t->getStackIndex()< TOP));
	assert(i);
	
	lv->clear();
	lv->setType(AVM_MemCell_t::nil_m);
	
	if(t->getType() != AVM_MemCell_t::table_m){
		error(ErrorType::Error, __currentLine__, "Indexing non-table variable\n");		
	}
	else{
		AVM_MemCell content = t->data.tableVal->getElem(i);
		
		if(content.getType() != nil_m) {
			lv->assign(&content);
		}
		else{
			error(Warning, __currentLine__, "Table index \"%s\" does not exist\n", i->toString().c_str());			
		}
		
	}
}

void AVM::executeTablesetelem(Instruction *inst){
	VMarg arg1 = inst->getArg1();
	VMarg arg2 = inst->getArg2();
	VMarg result = inst->getResult();
	
	AVM_MemCell *t = translateOperand(&result, (AVM_MemCell *) 0);
	AVM_MemCell *i = translateOperand(&arg1, &AX);
	AVM_MemCell *c = translateOperand(&arg2, &BX);
	
	assert(t && (t->getStackIndex() >= 0 && t->getStackIndex()< TOP));
	assert(i && c);
	
	if(t->getType() != AVM_MemCell_t::table_m){
		error(ErrorType::Error, __currentLine__, "Indexing non-table variable\n");		
	}
	else{
		t->data.tableVal->setElem(i, c);
	}
}
