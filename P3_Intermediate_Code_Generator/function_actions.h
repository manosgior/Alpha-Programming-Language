#ifndef FUNCTION_ACTIONS_H
#define FUNCTION_ACTIONS_H

#include "symtable.h"
#include "quadtable.h"
#include "expression.h"
#include <list>
#include "error_handler.h"
#include <list>
#include <utility>
//#define DEBUG

typedef std::tuple<std::list<expr *>*, bool, std::string> callInfo;

extern SymTable symbol_table;
extern unsigned int getCurrentScope();
extern void incrementScope();
extern void decrementScope();
extern int yyerror (char * yaccProvidedMessage);

typedef std::pair<expr*, expr*>                                      indElem;
typedef std::list<indElem*>                                          indexedList;
typedef std::pair<std::list<expr*>*, indexedList*>                   objectInner;
typedef std::pair<unsigned, unsigned>                                unsignedPair;
typedef std::tuple<std::list<unsigned>*, std::list<unsigned>*, bool> stmtInfo;


stmtInfo * Manage_stmt_expr_SEMICOLON(expr * e);
expr * Manage_lvalue_DOUBLE_COLON_ID(char *id);
expr * Manage_lvalue_LOCAL_ID(char *id);
void Manage_idlist(char* id);
expr * Manage_lvalue_ID(char *id);
char * Manage_funcprefix_FUNCTION_funcname(char * id);
char * Manage_funcname_ID(char *id);
char * Manage_funcname();
expr * Manage_funcdef_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block(char * funcprefix);
void Manage_block_LEFT_BRACE();
stmtInfo* Manage_stmts_RIGHT_BRACE(stmtInfo * stmts);
void Manage_returnstmt_RETURN();
stmtInfo* Manage_stmt_BREAK();
stmtInfo* Manage_stmt_CONTINUE();
expr *Manage_term_PLUS_PLUS_lvalue(expr * lvalue);
expr *Manage_term_MINUS_MINUS_lvalue(expr * lvalue);
expr *Manage_term_lvalue_PLUS_PLUS(expr * lvalue);
expr *Manage_term_lvalue_MINUS_MINUS(expr * lvalue);
expr *Manage_assignexpr_lvalue_ASSIGNMENT_expr(expr * lvalue, expr * expression);
expr *Manage_member_lvalue_DOT_ID(expr *lvalue, char *id);
expr *Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET(expr *lvalue, expr *expr);
expr *Manage_primary_call(expr * e);
expr *Manage_primary_objectdef(expr * e);
expr *Manage_primary_lvalue(expr *lvalue);
expr *Manage_const_numerical_const(double value);
expr *Manage_const_STRINGCONST(char *value);
expr *Manage_const_NIL();
expr *Manage_boolconst(bool value);
expr *Manage_primary_const(expr *value);
expr *Manage_term_primary(expr *value);
expr *Manage_expr_assignexpr(expr * e);
expr *Manage_expr_term(expr *term);
expr *Manage_term_NOT_expr(expr *term);
expr *Manage_term_MINUS_expr(expr *expression);
expr *Manage_term_LEFT_PAREN_expr_RIGHT_PAREN(expr *expression);
expr *Manage_expr_exprL_ARITH_OPERATOR_exprR(expr *exprL, iopcode op, expr *exprR);
void Manage_expr_exprL_EQUAL(expr ** exprL);
void Manage_expr_exprL_NOT_EQUAL(expr ** exprL);
expr *Manage_expr_exprL_REL_OPERATOR_exprR(expr *exprL, iopcode op, expr *exprR);
void Manage_expr_exprL_AND(expr * exprL);
void Manage_expr_exprL_OR(expr * exprL);
expr *Manage_expr_exprL_AND_M_exprR(expr *exprL, unsigned M, expr *exprR);
expr *Manage_expr_exprL_OR_M_exprR(expr *exprL, unsigned M, expr *exprR);
expr *Manage_lvalue_member(expr *member);
callInfo *Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN(char *id, std::list<expr*> *elist);
expr *Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN(expr *callRight, std::list<expr*> *elist);
expr *Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN(expr *funcdef, std::list<expr*> *elist);
expr *Manage_call_lvalue_callsuffix(expr *lvalue, callInfo *callsuffix);
callInfo *Manage_callsuffix_normcall(callInfo *normcall);
callInfo *Manage_callsuffix_methodcall(callInfo *methodcall);
callInfo *Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN(std::list<expr*> *elist);
expr *Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN(expr *funcdef);
std::list<expr*>* Manage_commalist();
std::list<expr*>* Manage_commalist_COMMA_expr_commalist(std::list<expr*>* elist, expr * e);
std::list<expr*>* Manage_elistnotempty_expr_commalist(std::list<expr*>* elist, expr * e);
std::list<expr*>* Manage_elist();
std::list<expr*>* Manage_elist_elistnotempty(std::list<expr*>* elist);
void Manage_indexedelem_LEFT_BRACE_expr(expr ** e);
indElem* Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE(expr * key, expr * value);
indexedList* Manage_commaindexed();
indexedList* Manage_commaindexed_COMMA_indexedelem_commaindexed(indexedList* indexed, indElem* elem);
indexedList* Manage_indexed_indexedelem_commaindexed(indexedList* indexed, indElem* elem);
objectInner* Manage_objectdinner();
objectInner* Manage_objectdinner_indexed(indexedList* indexed);
objectInner* Manage_objectdinner_elistnotempty(std::list<expr*>* elist);
expr * Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET(objectInner * cont);
stmtInfo* Manage_ifstmt_ifprefix_stmt_elseprefix_stmt(unsigned ifprefix, unsigned elseprefix, stmtInfo* stmt1, stmtInfo* stmt2);
unsigned Manage_elseprefix_ELSE();
stmtInfo* Manage_ifstmt_ifprefix_stmt(unsigned ifprefix, stmtInfo* stmt);
unsigned Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN(expr * e);
void Manage_ifstmt_ifprefix_stmt_elseprefix(stmtInfo *ifstmt);
unsigned Manage_N();
unsigned Manage_M();
unsigned int Manage_whilestart_WHILE();
unsigned int Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN(expr * expression);
void Manage_while_whilestart_whilecond_stmt(unsigned int label, unsigned int toPatch, stmtInfo* stmt);
unsignedPair* Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_M_expr_SEMICOLON(unsigned M, expr * e);
void Manage_forstmt_forprefix_N_elist();
void Manage_forstmt_forprefix_N_elist_RIGHT_PAREN_N_stmt_N (unsignedPair* forprefix, unsigned N1, unsigned N2, stmtInfo* stmt, unsigned N3);
stmtInfo* Manage_stmts();
stmtInfo* Manage_stmt_default();
stmtInfo* Manage_stmt_block(stmtInfo* blockLists);
stmtInfo* Manage_stmt_ifstmt(stmtInfo* ifstmtLists);
stmtInfo* Manage_stmts_stmtsR_stmt(stmtInfo* stmtsR, stmtInfo* stmt);
void Manage_returnstmt_RETURN_expr_SEMICOLON(expr * e);
void Manage_returnstmt_RETURN_SEMICOLON();
expr *Manage_member_call_DOT_ID(expr *call, char *id);
expr *Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET(expr *call, expr *expression);

#endif