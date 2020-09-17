#include "AVM.h"
#include "AVM_Table.h"
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <regex>
#include <iostream>

extern unsigned __currentLine__;

void AVM::libfuncPrint() {
    unsigned n = getTotalActuals();
    for (unsigned i = 0; i < n; ++i) {		
        std::string s = getActual(i).toString();
        std::cout << s;
    }
	RETVAL.clear();
	RETVAL.setType(nil_m);
}

void AVM::libfuncTypeOf(){
	unsigned n = getTotalActuals();
	
	if(n != 1){
		error(Error, __currentLine__, "typeof: too many or too few arguments\n");		 
	}
	else{
		RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::string_m);
		RETVAL.data.strVal = strdup(getActual(0).toStringTypeOf().c_str());
	}
}

void AVM::libfuncTotalArguments(){
	unsigned prev_topSP = getEnvValue(TOPSP - AVM_SAVEDTOPSP_OFFSET);
    unsigned n = getTotalActuals();

	if(n != 0){
		error(Error, __currentLine__, "totalarguments: too many or too few arguments\n");		 
	}	
	if(prev_topSP == 0){
        error(Warning, __currentLine__, "totalarguments: called outside a function\n");
        RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::nil_m);
	}
	else {
		RETVAL.setType(AVM_MemCell_t::number_m);
		RETVAL.data.numVal = getEnvValue(prev_topSP - AVM_NUM_ACTUALS_OFFSET);
	}
}

void AVM::libfuncArgument(){
	unsigned prev_topSP = getEnvValue(TOPSP - AVM_SAVEDTOPSP_OFFSET);
	unsigned n = getTotalActuals();
	
	if(n != 1){
		error(Error, __currentLine__, "argument(): too many or too few arguments\n");		 
	}
	else if(prev_topSP == 0){
        RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::nil_m);
	}
	else{
		unsigned numOfArgs = getEnvValue(prev_topSP - AVM_NUM_ACTUALS_OFFSET);
		AVM_MemCell& arg = getActual(0);
		if(arg.getType() != number_m){
			error(Error, __currentLine__, "argument(): argument \"%s\" is not a number\n", arg.toString().c_str());
		}
		else if(arg.data.numVal >= numOfArgs){
			error(Error, __currentLine__, "argument(): argument index out of bounds\n");
		}
		else{
			//get the argument
			RETVAL.clear();
			RETVAL.assign(&STACK[ prev_topSP - AVM_STACKENV_SIZE - 1 - arg.data.numVal ]);
		}
	}
	
}

void AVM::libfuncStrToNum(){
	unsigned n = getTotalActuals();	
	AVM_MemCell& arg = getActual(0);
    std::string tmp;
    std::regex integer("(0[xX][0-9A-Fa-f]+)|([0-9]+)");
    std::regex real("(([0-9]+\\.[0-9]*)|([0-9]*\\.[0-9]+))((e|E)([-\\+]?)[0-9]+)?");        
    std::smatch m;
        
	if(n != 1){
		error(Error, __currentLine__, "strtonum: Too many arguments or too few arguments\n");	 
	}
	else if(arg.getType() != string_m){
		RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::nil_m);
	}
	else{
		RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::number_m);
        tmp = arg.data.strVal;
        
        if(std::regex_match(tmp,m,integer) || std::regex_match(tmp,m,real)){                    
            RETVAL.data.numVal = std::stod(arg.data.strVal);
        }
        else{
            RETVAL.clear();
            RETVAL.setType(AVM_MemCell_t::nil_m);
        }                
	}
}

void AVM::libfuncSqrt(){
	unsigned n = getTotalActuals();
	AVM_MemCell& arg = getActual(0);

	if(n != 1){
		error(Error, __currentLine__, "sqrt: Too many or too few arguments\n");	 
	}
	else if(arg.getType() != number_m){
		RETVAL.clear();
        RETVAL.setType(AVM_MemCell_t::nil_m);
	}
	else if(arg.data.numVal < 0){
		RETVAL.clear();
        RETVAL.setType(AVM_MemCell_t::nil_m);		
	}
	else{
		RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::number_m);
		RETVAL.data.numVal = sqrt(arg.data.numVal);
	}
}

#define PI 3.14159265

void AVM::libfuncCos(){
	unsigned n = getTotalActuals();
	AVM_MemCell& arg = getActual(0);
	
	if(n != 1){
		error(Error, __currentLine__, "cos: Too many or too few arguments\n");		 
	}
	else if(arg.getType() != number_m){
		RETVAL.clear();
        RETVAL.setType(AVM_MemCell_t::nil_m);
	}	
	else{
		RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::number_m);
		RETVAL.data.numVal = cos(arg.data.numVal * PI / 180.0);
	}
}

void AVM::libfuncSin(){
	unsigned n = getTotalActuals();
	AVM_MemCell& arg = getActual(0);
	
	if(n != 1){
		error(Error, __currentLine__, "sin: Too many or too few arguments\n");		 
	}
	else if(arg.getType() != number_m){
		RETVAL.clear();
        RETVAL.setType(AVM_MemCell_t::nil_m);
	}
	else{
		RETVAL.clear();
		RETVAL.setType(AVM_MemCell_t::number_m);
		RETVAL.data.numVal = sin(arg.data.numVal * PI / 180.0);
	}
}

void AVM::libfuncInput(){
	unsigned n = getTotalActuals();
	std::string str;        
	std::regex integer("(0[xX][0-9A-Fa-f]+)|([0-9]+)");
        std::regex real("(([0-9]+\\.[0-9]*)|([0-9]*\\.[0-9]+))((e|E)([-\\+]?)[0-9]+)?");   
        std::smatch m;
        
	if(n != 0){
		error(Error, __currentLine__, "input: Too many arguments\n");	
	}
	else{
		RETVAL.clear();
		
		std::getline(std::cin, str);
                
                if(std::regex_match(str,m,integer) || std::regex_match(str,m,real)){
                    RETVAL.setType(AVM_MemCell_t::number_m);
                    RETVAL.data.numVal = std::stod(str);
                }                
                else if(str == "true" || str == "false"){
                    RETVAL.setType(AVM_MemCell_t::bool_m);
                    RETVAL.data.boolVal = (str == "true") ? true : false;
                }
                else if(str == "nil"){
                    RETVAL.setType(AVM_MemCell_t::nil_m);
                }                
                else{                    
                    RETVAL.setType(AVM_MemCell_t::string_m);
                    if( str.length() > 2 && (str[0] == '\"' && str[str.length()-1] == '\"')){
                        str.erase(0,1);
                        str.erase(str.length()-1,1);
                    }                
                    RETVAL.data.strVal = strdup(str.c_str());                   
                }	
	}
}

void AVM::libfuncObjectTotalMembers(){
    unsigned n = getTotalActuals();
    AVM_MemCell& arg = getActual(0);
    
    if(n != 1){
        error(Error, __currentLine__, "objecttotalmembers: Too many or too few arguments\n");	
    }
    else if(arg.getType() != table_m){
        error(Error, __currentLine__, "objecttotalmembers: Argument is not a table\n");        
    }
    else{
        RETVAL.clear();
	    RETVAL.setType(AVM_MemCell_t::number_m);
        RETVAL.data.numVal = arg.data.tableVal->getTotalMembers();
    }

}

void AVM::libfuncObjectMemberKeys(){
    unsigned n = getTotalActuals();
    AVM_MemCell& arg = getActual(0);
    
    if(n != 1){
        error(Error, __currentLine__, "objectmemberkeys: Too many or too few arguments\n");	
    }
    else if(arg.getType() != table_m){
        error(Error, __currentLine__, "objectmemberkeys: Argument is not a table\n");        
    }
    else{
        RETVAL.clear();
	    RETVAL.setType(AVM_MemCell_t::table_m);
        RETVAL.data.tableVal = new AVM_Table();
        RETVAL.data.tableVal->incRefCounter();
        
        std::vector<AVM_MemCell> keys = arg.data.tableVal->getKeys();
        AVM_MemCell key;
        AVM_MemCell value;       
        
        for(unsigned int i = 0; i < arg.data.tableVal->getTotalMembers(); i++){
            key = AVM_MemCell();
            AVM_MemCell tmp = keys[i];
            key.setType(number_m);
            key.data.numVal = i;

            value.assign(&tmp);
            
            RETVAL.data.tableVal->setElem(&key, &value);

            if(keys[i].getType() == string_m || keys[i].getType() == libfunc_m)
                keys[i].clear();
            value.clear();
        }
    }
}

void AVM::libfuncObjectCopy(){
    unsigned n = getTotalActuals();
    AVM_MemCell& arg = getActual(0);
    
    if(n != 1){
        error(Error, __currentLine__, "objectcopy: Too many or too few arguments\n");	
    }
    else if(arg.getType() != table_m){
        error(Error, __currentLine__, "objectcopy: Argument is not a table\n");        
    }
    else{
        RETVAL.clear();
	    RETVAL.setType(AVM_MemCell_t::table_m);
        RETVAL.data.tableVal = new AVM_Table();
        RETVAL.data.tableVal->incRefCounter();
        
        std::vector<AVM_MemCell> keys = arg.data.tableVal->getKeys();
        std::vector<AVM_MemCell> values = arg.data.tableVal->getValues();
        AVM_MemCell key;
        AVM_MemCell value; 
        
        for(unsigned int i = 0; i < arg.data.tableVal->getTotalMembers(); i++){
            key = keys[i];
            value = values[i];
            
            RETVAL.data.tableVal->setElem(&key, &value);
            if(key.getType() == string_m || key.getType() == libfunc_m)
                key.clear();                           
        }
    }
}
