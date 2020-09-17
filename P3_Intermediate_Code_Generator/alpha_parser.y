%{
	#include <stdio.h>
	#include <string>
	#include <fstream>
	#include <assert.h>
	#include <list>
	#include <utility>
	#include "function_actions.h"
	#include "symtable.h"
	#include "expression.h"
	#include "defines_header.h"
	#include "error_handler.h"
	#include "quadtable.h"
	#include "quads.h"
	#include "tempManagement.h"
	#define yylex() lexer->alpha_yylex()
	#define BON "\e[1m"
	#define BOFF "\e[0m"
	#define P3_DEBUG	
	int yyerror (char * yaccProvidedMessage);
	unsigned int getCurrentScope();
	void incrementScope();
	void decrementScope();
	void init();
	unsigned int scope = 0;
	Scope_Type nextScope = Scope_Type::invalid_scope;
	SymTable symbol_table = SymTable();
	QuadTable quad_table = QuadTable(); 	
%}

%defines 

%output = "alpha_parser.cpp"

%union {
	int    			  intValue;
	unsigned		  unsignedValue;
	double 			  doubleValue;
	char*  			  stringValue;
	expr*  			  exprValue;
    callInfo*         callInfoValue;
	std::list<expr*>* elistValue;
	indElem*		  indexedElement;
	indexedList* 	  indexedValue;
	objectInner*	  objectInnerValue;
	unsignedPair*  	  unsignedPairValue;
	stmtInfo*		  stmtInfoValue;
}

%start program

%token <intValue>    	  	INTCONST
%token <doubleValue> 	  	REALCONST
%token <stringValue> 	  	STRINGCONST
%token <stringValue> 	  	ID
%type  <exprValue>   	  	expr
%type  <exprValue>   	  	lvalue
%type  <stringValue> 	  	funcname
%type  <stringValue> 	  	funcprefix
%type  <exprValue>	 	  	funcdef
%type  <exprValue>	 	  	member
%type  <exprValue>	 	  	primary
%type  <exprValue>	 	  	assignexpr
%type  <exprValue>        	const
%type  <exprValue>        	term
%type  <callInfoValue>    	methodcall
%type  <callInfoValue>    	callsuffix
%type  <callInfoValue>    	normcall
%type  <exprValue>        	call
%type  <exprValue> 	  	  	objectdef
%type  <objectInnerValue> 	objectdinner
%type  <indexedValue>     	commaindexed
%type  <indexedValue>     	indexed
%type  <indexedElement>   	indexedelem
%type  <elistValue>  	  	elist
%type  <elistValue>	 	  	elistnotempty
%type  <elistValue>	 	  	commalist
%type  <unsignedValue>	  	ifprefix
%type  <unsignedValue>	  	elseprefix
%type  <unsignedValue>	  	N
%type  <unsignedValue>    	M
%type  <unsignedPairValue>  forprefix
%type  <stmtInfoValue>		stmt
%type  <stmtInfoValue>	    stmts
%type  <stmtInfoValue>      block
%type  <stmtInfoValue>	    ifstmt
%type  <unsignedValue>      whilestart
%type  <unsignedValue>      whilecond
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL 
%token TRUE FALSE NIL ASSIGNMENT PLUS MINUS MULTIPLICATION DIVISION MODULO EQUAL NOT_EQUAL 
%token PLUS_PLUS MINUS_MINUS GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL 
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PAREN RIGHT_PAREN
%token SEMICOLON COMMA COLON DOUBLE_COLON DOT DOT_DOT COMMENT_TOKEN BAD_TOKEN

%destructor { free($$); } STRINGCONST
%destructor { free($$); } ID

%right ASSIGNMENT
%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL
%left PLUS MINUS
%left MULTIPLICATION DIVISION MODULO
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT DOT_DOT
%left LEFT_BRACKET RIGHT_BRACKET
%left LEFT_PAREN RIGHT_PAREN


%%
//introduced a stmts symbol to implement stmt*
program:		{init();} stmts ;

stmts:			stmts stmt { $$ = Manage_stmts_stmtsR_stmt($1, $2); }
				| { $$ = Manage_stmts(); }; 

stmt:			expr SEMICOLON { $$ = Manage_stmt_expr_SEMICOLON($1); reset_tmp(); }
				| ifstmt { $$ = Manage_stmt_ifstmt($1); }
				| whilestmt { $$ = Manage_stmt_default(); }
				| forstmt { $$ = Manage_stmt_default(); }
				| returnstmt { $$ = Manage_stmt_default(); }
				| BREAK SEMICOLON { $$ = Manage_stmt_BREAK(); }
				| CONTINUE SEMICOLON { $$ = Manage_stmt_CONTINUE(); }
				| block { $$ = Manage_stmt_block($1); }
				| funcdef { $$ = Manage_stmt_default(); }
				| SEMICOLON { $$ = Manage_stmt_default(); }
				| error SEMICOLON { $$ = Manage_stmt_default(); yyerrok; }
				;

//converted all expr op expr into expr PLUS expr etc. to force priorities
expr:			assignexpr { $$ = Manage_expr_assignexpr($1); }
				| expr PLUS expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1,iopcode::add, $3); }
				| expr MINUS expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, iopcode::sub, $3); }
				| expr MULTIPLICATION expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, iopcode::mul, $3); }
				| expr DIVISION expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, iopcode::div_i, $3); }
				| expr MODULO expr { $$ = Manage_expr_exprL_ARITH_OPERATOR_exprR($1, iopcode::mod, $3); }
				| expr GREATER_THAN expr  { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, iopcode::if_greater, $3); }
				| expr GREATER_OR_EQUAL expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, iopcode::if_greatereq, $3); }
				| expr LESS_THAN expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, iopcode::if_less, $3); }
				| expr LESS_OR_EQUAL expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, iopcode::if_lesseq, $3); }
				| expr EQUAL { Manage_expr_exprL_EQUAL(&($1)); } expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, iopcode::if_eq, $4); }
				| expr NOT_EQUAL { Manage_expr_exprL_NOT_EQUAL(&($1)); } expr { $$ = Manage_expr_exprL_REL_OPERATOR_exprR($1, iopcode::if_noteq, $4); }
				| expr AND { Manage_expr_exprL_AND($1); } M expr { $$ = Manage_expr_exprL_AND_M_exprR($1, $4, $5); }
				| expr OR { Manage_expr_exprL_OR($1); } M expr { $$ = Manage_expr_exprL_OR_M_exprR($1, $4, $5); }
				| term { $$ = Manage_expr_term($1); }
				;

//forced priority of unary minus
term:			LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_term_LEFT_PAREN_expr_RIGHT_PAREN($2);}

				| MINUS expr %prec UMINUS { $$ = Manage_term_MINUS_expr($2); }
				| NOT expr { $$ = Manage_term_NOT_expr($2); }
				| PLUS_PLUS lvalue { $$ = Manage_term_PLUS_PLUS_lvalue($2); }
				| lvalue PLUS_PLUS { $$ = Manage_term_lvalue_PLUS_PLUS($1); }
				| MINUS_MINUS lvalue { $$ = Manage_term_MINUS_MINUS_lvalue($2); }
				| lvalue MINUS_MINUS { $$ = Manage_term_lvalue_MINUS_MINUS($1); }
				| primary { $$ = Manage_term_primary($1);}
				;

assignexpr:		lvalue ASSIGNMENT expr { $$ = Manage_assignexpr_lvalue_ASSIGNMENT_expr($1,$3); }
				;

primary:		lvalue 
				{
					$$ = Manage_primary_lvalue($1);
				}
				| call { $$ = Manage_primary_call($1); }
				| objectdef { $$ = Manage_primary_objectdef($1); }
				| LEFT_PAREN funcdef RIGHT_PAREN
                                { $$ = Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN($2); }
				| const { $$ =  Manage_primary_const($1);}
				;

lvalue: 		ID 
				{			
					$$ = Manage_lvalue_ID($1);
					free($1);
				}
				| LOCAL ID 
				{
					$$ = Manage_lvalue_LOCAL_ID($2);
					free($2);
				}
				| DOUBLE_COLON ID 
				{
					$$ = Manage_lvalue_DOUBLE_COLON_ID($2);
					free($2);
				}
				| member { $$ = Manage_lvalue_member($1); }
				;

member: 		lvalue DOT ID 
				{
					$$ = Manage_member_lvalue_DOT_ID($1, $3);
				}
				| lvalue LEFT_BRACKET expr RIGHT_BRACKET
				{
					$$ = Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET($1, $3);
				}
				| call DOT ID { $$ = Manage_member_call_DOT_ID($1, $3); free($3); }
				| call LEFT_BRACKET expr RIGHT_BRACKET { $$ = Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET($1, $3); }
				;

call:			call LEFT_PAREN elist RIGHT_PAREN
                        { $$ = Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN($1, $3); }
				| lvalue callsuffix
                        { $$ = Manage_call_lvalue_callsuffix($1, $2); }
				| LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN
                        { $$ = Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN($2, $5); }
				;

callsuffix:		normcall
                        { $$ = Manage_callsuffix_normcall($1); }
				| methodcall
                        { $$ = Manage_callsuffix_methodcall($1); }            
				;

normcall:		LEFT_PAREN elist RIGHT_PAREN
                        { $$ = Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN($2); }
				;

methodcall:		DOT_DOT ID LEFT_PAREN elist RIGHT_PAREN 
                        { $$ = Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN($2, $4); }
				;

//introduced elistnotempty to implement "zero or more" repetitions
elist:			elistnotempty { $$ = Manage_elist_elistnotempty($1); }
				| { $$ = Manage_elist(); }
				;

//commalist expands into 2nd, 3rd etc. arguments
elistnotempty:	commalist expr { $$ = Manage_elistnotempty_expr_commalist($1, $2); }
				;

commalist:		commalist expr COMMA { $$ = Manage_commalist_COMMA_expr_commalist($1, $2); }
				| { $$ = Manage_commalist(); }
				;

//introduced objectdinner to implement potentially empty bracket content
objectdef:		LEFT_BRACKET objectdinner RIGHT_BRACKET 
				{ 
					$$ = Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET($2); 
				}
				;

//empty list produced via index, not needed via elist (resolves reduce-reduce)
objectdinner:	elistnotempty { $$ = Manage_objectdinner_elistnotempty($1); }
				| indexed { $$ = Manage_objectdinner_indexed($1); }
				| { $$ = Manage_objectdinner(); }
				;

//commaindexed produces 2nd, 3rd etc.arguments
indexed:		commaindexed indexedelem { $$ = Manage_indexed_indexedelem_commaindexed($1, $2); }
				;

commaindexed:	commaindexed indexedelem COMMA { $$ = Manage_commaindexed_COMMA_indexedelem_commaindexed($1, $2); }
				| { $$ = Manage_commaindexed(); }
				;

indexedelem:	LEFT_BRACE expr { Manage_indexedelem_LEFT_BRACE_expr(&($2)); } COLON expr RIGHT_BRACE 
				{
					$$ = Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE($2, $5);
				}
				;

block:			LEFT_BRACE { Manage_block_LEFT_BRACE();} stmts RIGHT_BRACE { $$ = Manage_stmts_RIGHT_BRACE($3); }
				;

//introduced funcname to implement optional function name
funcdef:		funcprefix LEFT_PAREN idlist RIGHT_PAREN block { $$ = Manage_funcdef_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block($1); }
				;

funcprefix:		FUNCTION funcname { $$ = Manage_funcprefix_FUNCTION_funcname($2); }
				;

funcname:		ID
				{ 
					$$ = Manage_funcname_ID($1);
				}
				| { $$ = Manage_funcname(); }
				;

const:			INTCONST { $$ = Manage_const_numerical_const($1);}
				| REALCONST { $$ = Manage_const_numerical_const($1);}
				| STRINGCONST { $$ = Manage_const_STRINGCONST($1);}
				| NIL { $$ = Manage_const_NIL();}
				| TRUE { $$ = Manage_boolconst(true);}
				| FALSE { $$ = Manage_boolconst(false);}
				;

//introduced commaidlist to implement 2nd, 3rd etc. arguments
idlist:			commaidlist ID 
				{
					Manage_idlist($2); 
				  	free($2);
				}
				|;

commaidlist:	commaidlist ID COMMA  
				{
					Manage_idlist($2); 
				  	free($2);
				}
				|;

ifprefix:		IF LEFT_PAREN expr RIGHT_PAREN { $$ = Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN($3); }; 

ifstmt:			ifprefix stmt { $$ = Manage_ifstmt_ifprefix_stmt($1, $2); }
				| ifprefix stmt elseprefix { Manage_ifstmt_ifprefix_stmt_elseprefix($2); } stmt { $$ = Manage_ifstmt_ifprefix_stmt_elseprefix_stmt($1, $3, $2, $5); }
			    ;

elseprefix:		ELSE { $$ = Manage_elseprefix_ELSE(); };

whilestart:		WHILE { $$ = Manage_whilestart_WHILE(); }

whilecond:      LEFT_PAREN expr RIGHT_PAREN  { $$ =  Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN($2); };

N:				{ $$ = Manage_N(); };

whilestmt:          whilestart whilecond stmt { Manage_while_whilestart_whilecond_stmt($1, $2, $3); };

M:				{ $$ = Manage_M(); };

forprefix:		FOR LEFT_PAREN elist SEMICOLON M expr SEMICOLON 
				{
					$$ = Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_M_expr_SEMICOLON($5, $6);
					
				}
				;

forstmt:		forprefix N elist { Manage_forstmt_forprefix_N_elist(); } RIGHT_PAREN N stmt N 
				{ 
					 Manage_forstmt_forprefix_N_elist_RIGHT_PAREN_N_stmt_N($1, $2, $6, $7, $8);
					 
				} 
				;

//introduced retex to implement empty return; statement
returnstmt:		RETURN expr SEMICOLON { Manage_returnstmt_RETURN_expr_SEMICOLON($2); }
				| RETURN SEMICOLON { Manage_returnstmt_RETURN_SEMICOLON(); }
				;

%%


int yyerror(char * yaccProvidedMessage) {
 	error(ErrorType::Error, yylineno, "%s before token " BON "\'%s\'" BOFF "\n", yaccProvidedMessage, yytext);
	return 0;
}

unsigned int getCurrentScope() {
	return scope;
}

void incrementScope() {
	scope++;
}

void decrementScope() {
	assert(scope);
	scope--;
}

void init() {
	symbol_table.addScopeType(Scope_Type::global_scope);
	std::ifstream ifs;
	ifs.open("stdalpha.lib");
	if (!ifs.is_open()) {
		error(ErrorType::Warning, 0, "stdalpha.lib not found! Library functions won't be loaded\n");
	} else {
		std::string temp;
		while (!ifs.eof()) {
			ifs >> temp;
			symbol_table.Insert(temp, SymTable_Entry_Type::library_function, 0, 0);
		}
	}
}
