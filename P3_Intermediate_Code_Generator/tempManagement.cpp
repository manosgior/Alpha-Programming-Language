#include "tempManagement.h"
#include "defines_header.h"
#include <assert.h>

extern SymTable symbol_table;
extern unsigned int getCurrentScope();
unsigned int tmp_var_counter = 0;

std::string new_tmp_name(){    
    return "_t" + std::to_string(tmp_var_counter++);
}

std::string get_curr_tmp_var(){
    assert(tmp_var_counter > 0);
	return "_t" + std::to_string(tmp_var_counter-1); 
}

void reset_tmp(){
	tmp_var_counter = 0;
}

SymbolInfo new_tmp(){
	std::string new_tmp_var = new_tmp_name();
	SymbolInfo info = symbol_table.Lookup(new_tmp_var, getCurrentScope());
	
	if(info.getType() == SymTable_Entry_Type::invalid_entry_type){
		return symbol_table.Insert(new_tmp_var, (getCurrentScope() == 0)?(SymTable_Entry_Type::global_variable):
 				(SymTable_Entry_Type::local_variable), yylineno, getCurrentScope()); 				
	}	
	else return info;
}

bool is_tmp_var(std::string var){
	return (var[0] == '_');
}
