%{
	#include <stdio.h>
	#include <string>
	#include <fstream>
	#include <assert.h>
	#include "function_actions.h"
	#include "symtable.h"
	#include "defines_header.h"
	#include "error_handler.h"
	#define yylex() lexer->alpha_yylex()
	#define BON "\e[1m"
	#define BOFF "\e[0m"
	int yyerror (char * yaccProvidedMessage);
	unsigned int getCurrentScope();
	void incrementScope();
	void decrementScope();
	unsigned int scope = 0;
	Scope_Type nextScope = Scope_Type::invalid_scope;
	SymTable symbol_table = SymTable();
	void init();	
%}

%defines 

%output = "alpha_parser.cpp"

%union {
	int    intValue;
	double doubleValue;
	char*  stringValue;
	int    sym_type;
}

%start program

%token <intValue>    INTCONST
%token <doubleValue> REALCONST
%token <stringValue> STRINGCONST
%token <stringValue> ID
%type  <sym_type>    lvalue
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
%left PLUS
%left MINUS
%left MULTIPLICATION
%left DIVISION
%left MODULO
%right NOT
%right PLUS_PLUS
%right MINUS_MINUS
%right UMINUS
%left DOT
%left DOT_DOT
%left LEFT_BRACKET RIGHT_BRACKET
%left LEFT_PAREN RIGHT_PAREN

%%
//introduced a stmts symbol to implement stmt*
program:		{init();} stmts 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"program -> stmt\" at line %d\n", yylineno); 
				#endif
				}
				;

stmts:			stmts stmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmts -> stmts stmt\" at line %d\n", yylineno); 
				#endif
				} 
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmts -> \" at line %d\n", yylineno); 
				#endif
				}
				; 

stmt:			expr SEMICOLON 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> expr SEMICOLON\" at line %d\n", yylineno); 
				#endif
				}
				| ifstmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> ifstmt\" at line %d\n", yylineno); 
				#endif
				}
				| whilestmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> whilestmt\" at line %d\n", yylineno); 
				#endif
				}
				| forstmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> forstmt\" at line %d\n", yylineno); 
				#endif
				}
				| returnstmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> returnstmt\" at line %d\n", yylineno); 
				#endif
				}
				| BREAK {Manage_stmt_BREAK();} SEMICOLON 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> BREAK SEMICOLON\" at line %d\n", yylineno); 
				#endif
				}
				| CONTINUE {Manage_stmt_CONTINUE();} SEMICOLON 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> CONTINUE SEMICOLON\" at line %d\n", yylineno); 
				#endif
				}
				| block 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> block\" at line %d\n", yylineno); 
				#endif
				}
				| funcdef 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> funcdef\" at line %d\n", yylineno); 
				#endif
				}
				| SEMICOLON 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"stmt -> SEMICOLON\" at line %d\n", yylineno); 
				#endif
				}
				| error SEMICOLON {yyerrok;}
				;

//converted all expr op expr into expr PLUS expr etc. to force priorities
expr:			assignexpr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> assignexpr\" at line %d\n", yylineno); 
				#endif
				}
				| expr PLUS expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr PLUS expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr MINUS expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr MINUS expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr MULTIPLICATION expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr MULTIPLICATION expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr DIVISION expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr DIVISION expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr MODULO expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr MODULO expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr GREATER_THAN expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr GREATER_THAN\" at line %d\n", yylineno); 
				#endif
				}
				| expr GREATER_OR_EQUAL expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr GREATER_OR_EQUAL\" at line %d\n", yylineno); 
				#endif
				}
				| expr LESS_THAN expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr LESS_THAN expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr LESS_OR_EQUAL expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr LESS_OR_EQUAL\" at line %d\n", yylineno); 
				#endif
				}
				| expr EQUAL expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr EQUAL expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr NOT_EQUAL expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr NOT_EQUAL expr\" at line %d\n", yylineno); 
				#endif
				}
				| expr AND expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr AND expr\" at line %d\n", yylineno);
				#endif
				}
				| expr OR expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> expr OR expr\" at line %d\n", yylineno); 
				#endif
				}
				| term 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"expr -> term\" at line %d\n", yylineno); 
				#endif
				}
				;

//forced priority of unary minus
term:			LEFT_PAREN expr RIGHT_PAREN 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> LEFT_PAREN expr RIGHT_PAREN\" at line %d\n", yylineno); 
				#endif
				}
				| MINUS expr %prec UMINUS 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> MINUS expr\" at line %d\n", yylineno); 
				#endif
				}
				| NOT expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> NOT expr\" at line %d\n", yylineno); 
				#endif
				}
				| PLUS_PLUS lvalue 
				{
				Manage_term_PLUS_PLUS_lvalue($2);
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> PLUS_PLUS lvalue\" at line %d\n", yylineno); 
				#endif
				}
				| lvalue PLUS_PLUS 
				{
				Manage_term_lvalue_PLUS_PLUS($1);
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> lvalue PLUS_PLUS\" at line %d\n", yylineno); 
				#endif
				}
				| MINUS_MINUS lvalue 
				{
				Manage_term_MINUS_MINUS_lvalue($2);
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> MINUS_MINUS lvalue\" at line %d\n", yylineno); 
				#endif
				}
				| lvalue MINUS_MINUS 
				{
				Manage_term_lvalue_MINUS_MINUS($1);
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> lvalue MINUS_MINUS\" at line %d\n", yylineno); 
				#endif
				}
				| primary 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized Rule: \"term -> primary\" at line %d\n", yylineno); 
				#endif
				}
				;

assignexpr:		lvalue ASSIGNMENT expr 
				{
				Manage_assignexpr_lvalue_ASSIGNMENT_expr($1);
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"assignexpr -> lvalue ASSIGNMENT expr\" on line %d\n", yylineno);
				#endif
				}
				;

primary:		lvalue 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"primary -> lvalue\" on line %d\n", yylineno); 
				#endif
				}
				| call
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"primary -> call\" on line %d\n", yylineno); 
				#endif
				}
				| objectdef
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"primary -> objectdef\" on line %d\n", yylineno);
				#endif
				}
				| LEFT_PAREN funcdef RIGHT_PAREN
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"primary -> LEFT_PAREN funcdef RIGHT_PAREN\" on line %d\n", yylineno); 
				#endif
				}
				| const
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"primary -> const\" on line %d\n", yylineno); 
				#endif
				}
				;

lvalue: 		ID 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"lvalue -> ID\" on line %d\n", yylineno); 
				#endif
				$$ = Manage_lvalue_ID($1);
				free($1);
				}
				| LOCAL ID 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"lvalue -> LOCAL ID\" on line %d\n", yylineno);
				#endif
				$$ = Manage_lvalue_LOCAL_ID($2);
				free($2);
				}
				| DOUBLE_COLON ID 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"lvalue -> DOUBLE_COLON ID\" on line %d\n", yylineno); 
				#endif
				$$ = Manage_lvalue_DOUBLE_COLON_ID($2);
				free($2);
				}
				| member
				{
				#ifdef P2_PRINTS 
				fprintf(stderr, "Recognized rule \"lvalue ->  member\" on line %d\n", yylineno); 
				#endif
				return SymTable_Entry_Type::member_variable;
				}
				;

member: 		lvalue DOT ID
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"member -> lvalue DOT ID\" on line %d\n", yylineno); 
				#endif
				$3;
				free($3);
				}
				| lvalue LEFT_BRACKET expr RIGHT_BRACKET
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"member -> lvalue LEFT_BRACKET expr RIGHT_BRACKET\" on line %d\n", yylineno); 
				#endif
				}
				| call DOT ID
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"member -> call DOT ID\" on line %d\n", yylineno); 
				#endif
				$3;
				free($3);
				}
				| call LEFT_BRACKET expr RIGHT_BRACKET
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"member -> call LEFT_BRACKET expr RIGHT_BRACKET\" on line %d\n", yylineno); 
				#endif
				}
				;

call:			call LEFT_PAREN elist RIGHT_PAREN
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"call -> call LEFT_PAREN elist RIGHT_PAREN\" on line %d\n", yylineno); 
				#endif
				}
				| lvalue callsuffix
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"call -> lvalue callsuffix\" on line %d\n", yylineno); 
				#endif
				}
				| LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"call -> LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN\" on line %d\n", yylineno); 
				#endif
				}
				;

callsuffix:		normcall
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"callsuffix -> normcall\" on line %d\n", yylineno); 
				#endif
				}
				| methodcall
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"callsuffix -> methodcall\" on line %d\n", yylineno); 
				#endif
				}
				;

normcall:		LEFT_PAREN elist RIGHT_PAREN
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"normcall -> LEFT_PAREN elist RIGHT_PAREN\" on line %d\n", yylineno); 
				#endif
				}
				;

methodcall:		DOT_DOT ID LEFT_PAREN elist RIGHT_PAREN
				{
				#ifdef P2_PRINTS 
					fprintf(stderr, "Recognized rule \"methodcall -> DOT_DOT ID LEFT_PAREN elist RIGHT_PAREN\" on line %d\n", yylineno); 
				#endif
				$2;
				free($2);
				}
				;

//introduced elistnotempty to implement "zero or more" repetitions
elist:			elistnotempty 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"elist -> elistnotempty\" at line %d\n",yylineno); 
				#endif
				}
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"elist -> \" at line %d\n",yylineno); 
				#endif
				}
				;

//commalist expands into 2nd, 3rd etc. arguments
elistnotempty:	expr commalist 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"elistnotempty -> expr commalist\" at line %d\n",yylineno); 
				#endif
				}
				;


commalist:		COMMA expr commalist 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"commalist ->  COMMA expr commalist \" at line %d\n",yylineno); 
				#endif
				} 
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"#ifdef P2_PRINTS Recognized rule "Recognized rule \"commalist ->  \" at line %d\n",yylineno); 
				#endif
				}
				;

//introduced objectdinner to implement potentially empty bracket content
objectdef:		LEFT_BRACKET objectdinner RIGHT_BRACKET 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"objectdef -> LEFT_BRACKET objectdinner RIGHT_BRACKET\" at line %d\n",yylineno); 
				#endif
				}
				;

//empty list produced via index, not needed via elist (resolves reduce-reduce)
objectdinner:	elistnotempty 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"objectdinner -> elistnotempty\" at line %d\n",yylineno); 
				#endif
				} 
				| indexed 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"objectdinner -> indexed\" at line %d\n",yylineno); 
				#endif
				}
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"objectdinner -> \" at line %d\n",yylineno); 
				#endif
				}
				;

//commaindexed produces 2nd, 3rd etc.arguments
indexed:		indexedelem commaindexed 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"indexed -> indexedelem commaindexed\" at line %d\n",yylineno); 
				#endif
				}
				;

commaindexed:	COMMA indexedelem commaindexed 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"commaindexed -> COMMA indexedelem commaindexed\" at line %d\n",yylineno); 
				#endif
				} 
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"commaindexed -> \" at line %d\n",yylineno); 
				#endif
				}
				;

indexedelem:	LEFT_BRACE expr COLON expr RIGHT_BRACE 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"indexedelem -> LEFT_BRACE expr COLON expr RIGHT_BRACE\" at line %d\n",yylineno); 
				#endif
				}
				;

block:			LEFT_BRACE { Manage_block_LEFT_BRACE();} stmts RIGHT_BRACE
				{Manage_stmts_RIGHT_BRACE(); 
				#ifdef P2_PRINTS  
					fprintf(stderr,"Recognized rule \"block -> LEFT_BRACE stmts RIGHT_BRACE\" at line %d\n",yylineno); 
				#endif
				}
				;

//introduced funcstart to implement optional function name
funcdef:		funcstart LEFT_PAREN idlist RIGHT_PAREN block 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"funcdef -> funcstart LEFT_PAREN idlist RIGHT_PAREN block\" at line %d\n",yylineno); 
				#endif
				}
				;

funcstart:		FUNCTION 
				{Manage_funcstart_FUNCTION(); 
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"funcstart -> FUNCTION\" at line %d\n",yylineno); 
				#endif
				}
				| FUNCTION ID 
				{Manage_funcstart_FUNCTION_ID($2); 
				#ifdef P2_PRINTS  
					fprintf(stderr,"Recognized rule \"funcstart -> FUNCTION ID\" at line %d\n",yylineno); 
				#endif
				free($2);
				}
				;

const:			INTCONST 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"const -> INTCONST\" at line %d\n",yylineno); 
				#endif
				}
				| REALCONST 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"const -> REALCONST\" at line %d\n",yylineno); 
				#endif
				} 
				| STRINGCONST 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"const -> STRINGCONST\" at line %d\n",yylineno); 
				#endif
				$1;
				free($1);
				}
				| NIL 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"const -> NIL\" at line %d\n",yylineno); 
				#endif
				}
				| TRUE 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"const -> TRUE\" at line %d\n",yylineno); 
				#endif
				}
				| FALSE 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"const -> FALSE\" at line %d\n",yylineno); 
				#endif
				}
				;

//introduced commaidlist to implement 2nd, 3rd etc. arguments
idlist:			ID commaidlist 
				{Manage_idlist($1); 
				#ifdef P2_PRINTS  
					fprintf(stderr,"Recognized rule \"idlist -> ID commaidlistat\" at line %d\n",yylineno); 
				#endif
				free($1);
				}
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"idlist -> \" at line %d\n",yylineno); 
				#endif
				}
				;

commaidlist:	COMMA ID commaidlist 
				{Manage_idlist($2); 
				#ifdef P2_PRINTS  
					fprintf(stderr,"Recognized rule \"commaidlist -> COMMA ID commaidlist\" at line %d\n",yylineno); 
				#endif
				free($2);
				}
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"commaidlist -> \" at line %d\n",yylineno); 
				#endif
				}
				;

ifstmt:			IF LEFT_PAREN expr RIGHT_PAREN stmt else 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"ifstmt ->  IF LEFT_PAREN expr RIGHT_PAREN stmt else\" at line %d\n",yylineno); 
				#endif
				}
				;

else:			ELSE stmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"else -> ELSE stmt\" at line %d\n",yylineno); 
				#endif
				} 
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"else -> \" at line %d\n",yylineno); 
				#endif
				}
				;

whilestmt:		WHILE LEFT_PAREN expr RIGHT_PAREN {Manage_whilestmt_WHILE_LEFT_PAREN_expr_RIGHT_PAREN_stmt();} stmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"whilestmt -> WHILE LEFT_PAREN expr RIGHT_PAREN\" at line %d\n",yylineno); 
				#endif
				}
				;

forstmt:		FOR LEFT_PAREN elist SEMICOLON expr SEMICOLON elist RIGHT_PAREN {Manage_forstmt_FOR_LEF_PAREN_elist_SEMICOLON_expr_SEMICOLON_elist_RIGHT_PAREN_stmt();} stmt 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"forstmt -> FOR LEFT_PAREN elist SEMICOLON expr SEMICOLON elist RIGHT_PAREN\" at line %d\n",yylineno); 
				#endif
				};

//introduced retex to implement empty return; statement
returnstmt:		RETURN {Manage_returnstmt_RETURN();} retex SEMICOLON 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"returnstmt -> RETURN\" at line %d\n",yylineno); 
				#endif
				};

retex:			expr 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"retex -> expr\" at line %d\n",yylineno); 
				#endif
				} 
				| 
				{
				#ifdef P2_PRINTS 
					fprintf(stderr,"Recognized rule \"retex -> \" at line %d\n",yylineno); 
				#endif
				};

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