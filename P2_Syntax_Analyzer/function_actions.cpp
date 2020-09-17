#include "function_actions.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define BON "\e[1m"
#define BOFF "\e[0m"

unsigned int name_suffix = 1;

int Manage_lvalue_DOUBLE_COLON_ID(char *id){
 	SymbolInfo info = symbol_table.Lookup(id, 0);
	if(std::get<0>(info) == SymTable_Entry_Type::invalid_entry_type){
		error(ErrorType::Error, yylineno, "No global variable " BON "\'%s\'" BOFF " has been declared\n", id);
	}
	
	return (int)std::get<0>(info);
}

int Manage_lvalue_ID(char *id){
 	SymbolInfo info = symbol_table.Lookup(id, -1);
 	if(std::get<0>(info) == invalid_entry_type){
 		#ifdef DEBUG
 		fprintf(stderr, "Inserting a new %s id with value %s\n", 
 					((getCurrentScope() == 0))?("global"):("local"), id);
 		#endif
 		symbol_table.Insert(std::string(id), (getCurrentScope() == 0)?(SymTable_Entry_Type::global_variable):
 				(SymTable_Entry_Type::local_variable), yylineno, getCurrentScope());
 	} else {
		if ( std::get<0>(info) != SymTable_Entry_Type::user_function && !(std::get<2>(info) == 0) && ( (int)
			std::get<2>(info) < symbol_table.inSpecialScope(Scope_Type::function_scope))){
			error(ErrorType::Error, yylineno, "Cannot access variable " BON "\'%s\'" BOFF " from within a function\n", id);
		} 		
 		#ifdef DEBUG
 		else{
 			fprintf(stderr, "%s in scope %d refers to existing id defined in line %u\n", id, 
 				getCurrentScope(), std::get<1>(info));
 		}
 		#endif
 	}
	
	return  (int)std::get<0>(info);
}

int Manage_lvalue_LOCAL_ID(char *id){
	SymbolInfo info = symbol_table.Lookup(id, getCurrentScope());	
        SymbolInfo libf = symbol_table.Lookup(id, 0);
	if(std::get<0>(libf) == SymTable_Entry_Type::library_function && getCurrentScope() != 0){
		error(ErrorType::Error, yylineno, "Shadowing of library function " BON "\'%s\'" BOFF " is not allowed\n", id);
	}
	else if(std::get<0>(info) == SymTable_Entry_Type::invalid_entry_type){
		SymTable_Entry_Type type;
		if (getCurrentScope() == 0) {
			#ifdef DEBUG
			fprintf(stderr, "Defining %s in line %d as a global variable\n", id,yylineno);
			#endif
			type = SymTable_Entry_Type::global_variable;
		} else {
			#ifdef DEBUG
			fprintf(stderr, "Defining %s in line %d as a local variable\n", id,yylineno);
			#endif			
			type = SymTable_Entry_Type::local_variable;
		}
		symbol_table.Insert(std::string(id), type, yylineno, getCurrentScope());		
	}
	
	return  (int)std::get<0>(info);
}

void Manage_idlist(char* id) {
	SymbolInfo info = symbol_table.Lookup(id, getCurrentScope()+1);
	SymbolInfo libf = symbol_table.Lookup(id, 0);
	
	if (std::get<0>(info) == SymTable_Entry_Type::invalid_entry_type && std::get<0>(libf) != SymTable_Entry_Type::library_function) {
		symbol_table.Insert(std::string(id), SymTable_Entry_Type::formal_argument, yylineno, getCurrentScope()+1);
	} else if (std::get<0>(libf) == SymTable_Entry_Type::library_function) {
		error(ErrorType::Error, yylineno, "Use of library function name " BON "\'%s\'" BOFF " as a formal argument is not allowed\n", id);
	} else if (std::get<0>(info) == SymTable_Entry_Type::formal_argument) {
		error(ErrorType::Error, yylineno, "Redeclaration of formal argument " BON "\'%s\'" BOFF "\n", id);
	}
}

void Manage_funcstart_FUNCTION() {
	std::string func_name = "$f" + std::to_string(name_suffix);
	name_suffix++;
	symbol_table.addScopeType(Scope_Type::function_scope);
	
	symbol_table.Insert(func_name, SymTable_Entry_Type::user_function, yylineno, getCurrentScope());	
}

void Manage_funcstart_FUNCTION_ID(char *id) {
	SymbolInfo info = symbol_table.Lookup(id, getCurrentScope());
	
	symbol_table.addScopeType(Scope_Type::function_scope);
	
	if(std::get<0>(info) == SymTable_Entry_Type::library_function){  
		error(ErrorType::Error, yylineno, "Redeclaration of library function " BON "\'%s\'" BOFF " is not allowed\n",id);		
	}
	else if(std::get<0>(info) == SymTable_Entry_Type::global_variable){		
		error(ErrorType::Error, yylineno, BON "\'%s\'" BOFF " is already declared as a global variable at line %d\n",id, std::get<1>(info));			
	}
	else if(std::get<0>(info) == SymTable_Entry_Type::user_function){
		error(ErrorType::Error, yylineno, "Redeclaration of user function " BON "\'%s\'" BOFF " is not allowed. User function first declared at line %d\n", id, std::get<1>(info));	
	}
	else if(std::get<0>(info) == SymTable_Entry_Type::local_variable){
		error(ErrorType::Error, yylineno, BON "\'%s\'" BOFF " is already declared as a local variable at line %d\n", id, std::get<1>(info));			
	}
	else if(std::get<0>(info) == SymTable_Entry_Type::formal_argument){
		error(ErrorType::Error, yylineno, BON "\'%s\'" BOFF " is already declared as a formal argument at line %d\n", id, std::get<1>(info));		
	}
	else{		
		symbol_table.Insert(id, SymTable_Entry_Type::user_function, yylineno, getCurrentScope());		
	}	
}

void Manage_block_LEFT_BRACE() {
	if (symbol_table.getMaxScope() == getCurrentScope()) {
		#ifdef DEBUG
		fprintf(stderr, "Block opened a new scope (%d)\n", getCurrentScope()+1);
		#endif
		symbol_table.addScopeType(Scope_Type::default_scope);
	}
	#ifdef DEBUG
	else
		fprintf(stderr, "Block didn't open a new scope (immediately after function etc.)\n");
	#endif
	incrementScope();
}

void Manage_stmts_RIGHT_BRACE() {
	symbol_table.Hide();
	decrementScope();
}

void Manage_whilestmt_WHILE_LEFT_PAREN_expr_RIGHT_PAREN_stmt(){
	symbol_table.addScopeType(Scope_Type::loop_scope);
}

void Manage_forstmt_FOR_LEF_PAREN_elist_SEMICOLON_expr_SEMICOLON_elist_RIGHT_PAREN_stmt(){
	symbol_table.addScopeType(Scope_Type::loop_scope);
}

void Manage_returnstmt_RETURN(){
	Scope_Type type = symbol_table.getScopeType();
	
	if(type != Scope_Type::function_scope) {
		error(ErrorType::Error, yylineno, BON "return" BOFF " statement not within a function\n");
	}
}

void Manage_stmt_BREAK(){
	Scope_Type type = symbol_table.getScopeType();
	
	if(type != Scope_Type::loop_scope) {		
		error(ErrorType::Error, yylineno, BON "break" BOFF " statement not within a loop\n");
	}
}

void Manage_stmt_CONTINUE(){
	Scope_Type type = symbol_table.getScopeType();
	
	if(type != Scope_Type::loop_scope) {		
		error(ErrorType::Error, yylineno, BON "continue" BOFF " statement not within a loop\n");
	}
}

void Manage_term_PLUS_PLUS_lvalue(int lvalueType){
	if((SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::user_function || 
		(SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::library_function){
		error(ErrorType::Error, yylineno, "Lvalue required as increment operand\n");
	}
}

void Manage_term_lvalue_PLUS_PLUS(int lvalueType){
	if((SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::user_function || 
		(SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::library_function){
		error(ErrorType::Error, yylineno, "Lvalue required as increment operand\n");
	}
}

void Manage_term_MINUS_MINUS_lvalue(int lvalueType){
	if((SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::user_function || 
		(SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::library_function){
		error(ErrorType::Error, yylineno, "Lvalue required as decrement operand\n");
	}
}

void Manage_term_lvalue_MINUS_MINUS(int lvalueType){
	if((SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::user_function || 
		(SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::library_function){
		error(ErrorType::Error, yylineno, "Lvalue required as decrement operand\n");
	}	
}

void Manage_assignexpr_lvalue_ASSIGNMENT_expr(int lvalueType){
	if((SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::user_function || 
		(SymTable_Entry_Type) lvalueType == SymTable_Entry_Type::library_function){
		error(ErrorType::Error, yylineno, "Lvalue required as left operand of assignment\n");
	}	
}