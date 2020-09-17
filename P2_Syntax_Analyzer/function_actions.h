#include "symtable.h"
#include "error_handler.h"
#include "defines_header.h"
//#define DEBUG

extern SymTable symbol_table;
extern unsigned int getCurrentScope();
extern void incrementScope();
extern void decrementScope();
extern int yyerror (char * yaccProvidedMessage);
int Manage_lvalue_DOUBLE_COLON_ID(char *id);
int Manage_lvalue_LOCAL_ID(char *id);
void Manage_idlist(char* id);
int Manage_lvalue_ID(char *id);
void Manage_funcstart_FUNCTION_ID(char *id);
void Manage_funcstart_FUNCTION();
void Manage_funcdef_funcstart_LEFT_PAREN_idlist_RIGHT_PAREN_block(char *id);
void Manage_block_LEFT_BRACE();
void Manage_stmts_RIGHT_BRACE();
void Manage_whilestmt_WHILE_LEFT_PAREN_expr_RIGHT_PAREN_stmt();
void Manage_forstmt_FOR_LEF_PAREN_elist_SEMICOLON_expr_SEMICOLON_elist_RIGHT_PAREN_stmt();
void Manage_returnstmt_RETURN();
void Manage_stmt_BREAK();
void Manage_stmt_CONTINUE();
void Manage_term_PLUS_PLUS_lvalue(int lvalueType);
void Manage_term_MINUS_MINUS_lvalue(int lvalueType);
void Manage_term_lvalue_PLUS_PLUS(int lvalueType);
void Manage_term_lvalue_MINUS_MINUS(int lvalueType);
void Manage_assignexpr_lvalue_ASSIGNMENT_expr(int lvalueType);