#include "function_actions.h"
#include "tempManagement.h"
#include "defines_header.h"
#include "expression.h"
#include "quadtable.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <list>
#include <utility>
#define BON "\e[1m"
#define BOFF "\e[0m"

unsigned int name_suffix = 0;
extern QuadTable quad_table;

void hideIfNotBlock(stmtInfo *stmt) {
    if (std::get<2>(*stmt) == false) {
        symbol_table.Hide();
        while (symbol_table.getMaxScope() < getCurrentScope())
            decrementScope();
    }
}

expr * evalIfBooleanSC(expr * e) {
    assert(e != nullptr);
    if (e->getType() == boolexpr_e) {
        expr * tmp_e = expr::newexpr(var_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        tmp_e->setSymbol(tmpsym);
        tmp_e->setName(get_curr_tmp_var());
        e->backpatch(true, quad_table.nextQuadLabel());
        quad_table.emit(iopcode::assign, expr::newexpr_constbool(true), nullptr, tmp_e, 0, yylineno);
        quad_table.emit(iopcode::jump, nullptr, nullptr, nullptr, quad_table.nextQuadLabel() + 2, yylineno);
        e->backpatch(false, quad_table.nextQuadLabel());
        quad_table.emit(iopcode::assign, expr::newexpr_constbool(false), nullptr, tmp_e, 0, yylineno);
        return tmp_e;
    }
    return e;
}

stmtInfo * Manage_stmt_expr_SEMICOLON(expr * e) {
    evalIfBooleanSC(e);
    return Manage_stmt_default();
}

stmtInfo* Manage_stmt_default() {
    stmtInfo* tmp = new stmtInfo();
    std::get<0>(*tmp) = new std::list<unsigned>();
    std::get<1>(*tmp) = new std::list<unsigned>();
    std::get<3>(*tmp) = new std::list<unsigned>();
    std::get<2>(*tmp) = false;
    return tmp;
}

expr * Manage_lvalue_DOUBLE_COLON_ID(char *id) {
    SymbolInfo info = symbol_table.Lookup(id, 0);
    if (info.getType() == SymTable_Entry_Type::invalid_entry_type) {
        error(ErrorType::Error, yylineno, "No global variable " BON "\'%s\'" BOFF " has been declared\n", id);
        //set these just so compilation can continue
        info.setActive(true);
        info.setScope(0);
        info.setType(global_variable);
    }
    SymbolInfo *tmpsym = info.clone();
    return expr::lvalue_expr(std::string(id), tmpsym);
}

expr * Manage_lvalue_ID(char *id) {
    SymbolInfo info = symbol_table.Lookup(id, -1);
    if (info.getType() == invalid_entry_type) {
#ifdef DEBUG
        fprintf(stderr, "Inserting a new %s id with value %s\n",
                ((getCurrentScope() == 0)) ? ("global") : ("local"), id);
#endif
        while (symbol_table.getMaxScope() > getCurrentScope()) incrementScope();
        info = symbol_table.Insert(std::string(id), (getCurrentScope() == 0) ? (SymTable_Entry_Type::global_variable) :
                (SymTable_Entry_Type::local_variable), yylineno, getCurrentScope());
    } else {
        if (info.getType() != SymTable_Entry_Type::user_function && !(info.getScope() == 0) && ((int)
            info.getScope() < symbol_table.inSpecialScope(Scope_Type::function_scope))) {
            error(ErrorType::Error, yylineno, "Cannot access variable " BON "\'%s\'" BOFF " from within a function\n", id);
        }
#ifdef DEBUG
        else {
            fprintf(stderr, "%s in scope %d refers to existing id defined in line %u\n", id,
                    getCurrentScope(), std::get<1>(info));
        }
#endif
    }
    SymbolInfo * tmpsym = info.clone();
    return expr::lvalue_expr(std::string(id), tmpsym);
}

expr * Manage_lvalue_LOCAL_ID(char *id) {
    SymbolInfo info = symbol_table.Lookup(id, getCurrentScope());
    SymbolInfo libf = symbol_table.Lookup(id, 0);
    if (libf.getType() == SymTable_Entry_Type::library_function && getCurrentScope() != 0) {
        error(ErrorType::Error, yylineno, "Shadowing of library function " BON "\'%s\'" BOFF " is not allowed\n", id);
        //again, cheat the compiler into thinking this is ok
        info = libf;
    } else if (info.getType() == SymTable_Entry_Type::user_function) {
        error(ErrorType::Warning, yylineno, BON "\'%s\'" BOFF " is redefined as user function\n", id);
    } else if (info.getType() == SymTable_Entry_Type::invalid_entry_type) {
        SymTable_Entry_Type type;
        if (getCurrentScope() == 0) {
#ifdef DEBUG
            fprintf(stderr, "Defining %s in line %d as a global variable\n", id, yylineno);
#endif
            type = SymTable_Entry_Type::global_variable;
        } else {
#ifdef DEBUG
            fprintf(stderr, "Defining %s in line %d as a local variable\n", id, yylineno);
#endif   
            type = SymTable_Entry_Type::local_variable;
        }
        while (symbol_table.getMaxScope() > getCurrentScope()) incrementScope();
        info = symbol_table.Insert(std::string(id), type, yylineno, getCurrentScope());
    }
    SymbolInfo * tmpsym = info.clone();
    return expr::lvalue_expr(std::string(id), tmpsym);
}

void Manage_idlist(char* id) {
    SymbolInfo info = symbol_table.Lookup(id, getCurrentScope() + 1);
    SymbolInfo libf = symbol_table.Lookup(id, 0);
    if (info.getType() == SymTable_Entry_Type::invalid_entry_type && libf.getType() != SymTable_Entry_Type::library_function) {
        symbol_table.Insert(std::string(id), SymTable_Entry_Type::formal_argument, yylineno, getCurrentScope() + 1);
    } else if (libf.getType() == SymTable_Entry_Type::library_function) {
        error(ErrorType::Error, yylineno, "Use of library function name " BON "\'%s\'" BOFF " as a formal argument is not allowed\n", id);
    } else if (info.getType() == SymTable_Entry_Type::formal_argument) {
        error(ErrorType::Error, yylineno, "Redeclaration of formal argument " BON "\'%s\'" BOFF "\n", id);
    }
}

char * Manage_funcname() {
    std::string func_name = "$f" + std::to_string(name_suffix);
    name_suffix++;
    char * toobad = strdup(func_name.c_str());
    return toobad;
}

char * Manage_funcname_ID(char *id) {
    return id;
}

char * Manage_funcprefix_FUNCTION_funcname(char *id) {
    SymbolInfo info = symbol_table.Lookup(id, getCurrentScope());

    if (info.getType() == SymTable_Entry_Type::library_function) {
        error(ErrorType::Error, yylineno, "Redeclaration of library function " BON "\'%s\'" BOFF " is not allowed\n", id);
    } else if (info.getType() == SymTable_Entry_Type::global_variable) {
        error(ErrorType::Error, yylineno, BON "\'%s\'" BOFF " is already declared as a global variable at line %d\n", id, info.getLine());
    } else if (info.getType() == SymTable_Entry_Type::user_function) {
        error(ErrorType::Error, yylineno, "Redeclaration of user function " BON "\'%s\'" BOFF " is not allowed. User function first declared at line %d\n", id, info.getLine());
    } else if (info.getType() == SymTable_Entry_Type::local_variable) {
        error(ErrorType::Error, yylineno, BON "\'%s\'" BOFF " is already declared as a local variable at line %d\n", id, info.getLine());
    } else if (info.getType() == SymTable_Entry_Type::formal_argument) {
        error(ErrorType::Error, yylineno, BON "\'%s\'" BOFF " is already declared as a formal argument at line %d\n", id, info.getLine());
    } else {
        while (symbol_table.getMaxScope() > getCurrentScope()) incrementScope();
        symbol_table.Insert(id, SymTable_Entry_Type::user_function, yylineno, getCurrentScope());
    }
    symbol_table.setFunctionAddress(id, quad_table.nextQuadLabel());
    SymbolInfo si = symbol_table.Lookup(std::string(id), -1);
    SymbolInfo * tmpsi = si.clone();
    quad_table.emit(funcstart, nullptr, nullptr, expr::lvalue_expr(std::string(id), tmpsi), 0, yylineno);
    symbol_table.addScopeType(Scope_Type::function_scope);
    return id;
}

expr * Manage_funcdef_N_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block(unsigned N, char * funcprefix, stmtInfo * block) {
    expr *toReturn = expr::newexpr(expr_t::programfunc_e);
    SymbolInfo sym = symbol_table.Lookup(std::string(funcprefix), -1);
    symbol_table.setFunctionTotalLocals(std::string(funcprefix), symbol_table.getFunctionLocalOffset());
    SymbolInfo * tmpsym = sym.clone();
    for (unsigned i : *std::get<3>(*block)) { //siga mi thimomaste ti kanei ayto
        quad_table.patchLabel(i, quad_table.nextQuadLabel());
    }
    quad_table.emit(funcend, nullptr, nullptr, expr::lvalue_expr(funcprefix, tmpsym), 0, yylineno);
    toReturn->setSymbol(tmpsym);
    toReturn->setName(funcprefix);
    quad_table.patchLabel(N, quad_table.nextQuadLabel());
    return toReturn;
}

void Manage_block_LEFT_BRACE() {
    if (symbol_table.getMaxScope() == getCurrentScope()) {
#ifdef DEBUG
        fprintf(stderr, "Block opened a new scope (%d)\n", getCurrentScope() + 1);
#endif
        symbol_table.addScopeType(Scope_Type::default_scope);
    }
#ifdef DEBUG
    else
        fprintf(stderr, "Block didn't open a new scope (immediately after function etc.)\n");
#endif
    incrementScope();
}

stmtInfo* Manage_stmts_RIGHT_BRACE(stmtInfo * stmts) {
    symbol_table.Hide();
    decrementScope();
    return stmts;
}

expr * Manage_term_PLUS_PLUS_lvalue(expr * lvalue) {
    expr * toReturn;

    SymTable_Entry_Type lvalueType = lvalue->getSymbol()->getType();
    if (lvalueType == SymTable_Entry_Type::user_function ||
            lvalueType == SymTable_Entry_Type::library_function) {
        error(ErrorType::Error, yylineno, "Lvalue required as increment operand\n");
        //again, these statements just to cheat the compiler that ++ was ok
        toReturn = expr::newexpr(arithexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
    } else {
        if (lvalue->getType() == tableitem_e) {
            toReturn = expr::emit_iftableitem(lvalue);
            quad_table.emit(iopcode::add, toReturn, expr::newexpr_constnum(1), toReturn, 0, yylineno);
            quad_table.emit(iopcode::tablesetelem, lvalue, lvalue->getIndex(), toReturn, 0, yylineno);
        } else {
            quad_table.emit(iopcode::add, lvalue, expr::newexpr_constnum(1), lvalue, 0, yylineno);
            toReturn = expr::newexpr(arithexpr_e);
            SymbolInfo * tmpsym = new_tmp().clone();
            toReturn->setSymbol(tmpsym);
            toReturn->setName(get_curr_tmp_var());

            quad_table.emit(iopcode::assign, lvalue, nullptr, toReturn, 0, yylineno);
        }
    }
    return toReturn;
}

expr * Manage_term_lvalue_PLUS_PLUS(expr * lvalue) {
    expr * toReturn;

    SymTable_Entry_Type lvalueType = lvalue->getSymbol()->getType();
    if (lvalueType == SymTable_Entry_Type::user_function ||
            lvalueType == SymTable_Entry_Type::library_function) {
        error(ErrorType::Error, yylineno, "Lvalue required as increment operand\n");
        //again, these statements just to cheat the compiler that ++ was ok
        toReturn = expr::newexpr(arithexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
    } else {
        toReturn = expr::newexpr(var_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());

        if (lvalue->getType() == tableitem_e) {
            expr * value = expr::emit_iftableitem(lvalue);
            quad_table.emit(iopcode::assign, value, nullptr, toReturn, 0, yylineno);
            quad_table.emit(iopcode::add, value, expr::newexpr_constnum(1), value, 0, yylineno);
            quad_table.emit(iopcode::tablesetelem, lvalue, lvalue->getIndex(), value, 0, yylineno);
        } else {
            quad_table.emit(iopcode::assign, lvalue, nullptr, toReturn, 0, yylineno);
            quad_table.emit(iopcode::add, lvalue, expr::newexpr_constnum(1), lvalue, 0, yylineno);
        }
    }

    return toReturn;
}

expr * Manage_term_MINUS_MINUS_lvalue(expr * lvalue) {
    expr * toReturn;

    SymTable_Entry_Type lvalueType = lvalue->getSymbol()->getType();
    if (lvalueType == SymTable_Entry_Type::user_function ||
            lvalueType == SymTable_Entry_Type::library_function) {
        error(ErrorType::Error, yylineno, "Lvalue required as decrement operand\n");
        //again, these statements just to cheat the compiler that -- was ok
        toReturn = expr::newexpr(arithexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
    } else {
        if (lvalue->getType() == tableitem_e) {
            toReturn = expr::emit_iftableitem(lvalue);
            quad_table.emit(iopcode::sub, toReturn, expr::newexpr_constnum(1), toReturn, 0, yylineno);
            quad_table.emit(iopcode::tablesetelem, lvalue, lvalue->getIndex(), toReturn, 0, yylineno);
        } else {
            quad_table.emit(iopcode::sub, lvalue, expr::newexpr_constnum(1), lvalue, 0, yylineno);
            toReturn = expr::newexpr(arithexpr_e);
            SymbolInfo * tmpsym = new_tmp().clone();
            toReturn->setSymbol(tmpsym);
            toReturn->setName(get_curr_tmp_var());

            quad_table.emit(iopcode::assign, lvalue, nullptr, toReturn, 0, yylineno);
        }
    }

    return toReturn;
}

expr * Manage_term_lvalue_MINUS_MINUS(expr * lvalue) {
    expr * toReturn;

    SymTable_Entry_Type lvalueType = lvalue->getSymbol()->getType();
    if (lvalueType == SymTable_Entry_Type::user_function ||
            lvalueType == SymTable_Entry_Type::library_function) {
        error(ErrorType::Error, yylineno, "Lvalue required as decrement operand\n");
        //again, these statements just to cheat the compiler that -- was ok
        toReturn = expr::newexpr(arithexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
    } else {
        toReturn = expr::newexpr(var_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());

        if (lvalue->getType() == tableitem_e) {
            expr * value = expr::emit_iftableitem(lvalue);
            quad_table.emit(iopcode::assign, value, nullptr, toReturn, 0, yylineno);
            quad_table.emit(iopcode::sub, value, expr::newexpr_constnum(1), value, 0, yylineno);
            quad_table.emit(iopcode::tablesetelem, lvalue, lvalue->getIndex(), value, 0, yylineno);
        } else {
            quad_table.emit(iopcode::assign, lvalue, nullptr, toReturn, 0, yylineno);
            quad_table.emit(iopcode::sub, lvalue, expr::newexpr_constnum(1), lvalue, 0, yylineno);
        }
    }

    return toReturn;
}

expr * Manage_assignexpr_lvalue_ASSIGNMENT_expr(expr * lvalue, expr * expression) {
    expr * toReturn;
    expr * tmp_e = evalIfBooleanSC(expression);
    if (lvalue->getType() == expr_t::programfunc_e || lvalue->getType() == expr_t::libraryfunc_e) {
        error(ErrorType::Error, yylineno, "Lvalue required as left operand of assignment\n");
        //again, these statements just to cheat the compiler that = was ok
        toReturn = expr::newexpr(arithexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
    }
    if (lvalue->getType() == expr_t::tableitem_e) {
        quad_table.emit(iopcode::tablesetelem, lvalue->getIndex(), tmp_e, lvalue, 0, yylineno);
        toReturn = expr::emit_iftableitem(lvalue);
        toReturn->setType(expr_t::assignexpr_e);
    } else {
        quad_table.emit(iopcode::assign, tmp_e, nullptr, lvalue, 0, yylineno);
        toReturn = expr::newexpr(expr_t::assignexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
        quad_table.emit(iopcode::assign, lvalue, nullptr, toReturn, 0, yylineno);
    }

    return toReturn;
}

expr *Manage_member_lvalue_DOT_ID(expr *lvalue, char *id) {
    return expr::member_item(lvalue, std::string(id));
}

expr *Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET(expr *lvalue, expr * e) {
    expr * tmp_e = evalIfBooleanSC(e);
    lvalue = expr::emit_iftableitem(lvalue);
    expr * table_item = expr::newexpr(tableitem_e);
    table_item->setSymbol(lvalue->getSymbol());
    table_item->setIndex(tmp_e);
    table_item->setName(lvalue->getName());
    return table_item;
}

expr *Manage_primary_lvalue(expr *lvalue) {
    return expr::emit_iftableitem(lvalue);
}

expr *Manage_const_numerical_const(double value) {
    return expr::newexpr_constnum(value);
}

expr *Manage_const_STRINGCONST(char *value) {
    return expr::newexpr_conststring(value);
}

expr *Manage_const_NIL() {
    return expr::newexpr_constnil();
}

expr *Manage_boolconst(bool value) {
    return expr::newexpr_constbool(value);
}

expr *Manage_primary_const(expr *value) {
    return value;
}

expr *Manage_term_primary(expr *value) {
    return value;
}

expr *Manage_expr_term(expr *term) {
    return term;
}

expr *Manage_term_NOT_expr(expr *term) {
    expr * toReturn = expr::newexpr(boolexpr_e);
    toReturn->setTrueList(term->getFalseList());
    toReturn->setFalseList(term->getTrueList());

    if (term->getType() != boolexpr_e && term->getType() != constbool_e) {
        toReturn->falseListInsert(quad_table.nextQuadLabel());
        quad_table.emit(if_eq, term, expr::newexpr_constbool(true), nullptr, 0, yylineno);
        toReturn->trueListInsert(quad_table.nextQuadLabel());
        quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    }

    toReturn->setSymbol(nullptr);
    toReturn->setName("John Valsamakis");

    return toReturn;
}

expr *Manage_term_MINUS_expr(expr *expression) {
    expr::checkuminus(expression);
    expr *term = expr::newexpr(arithexpr_e);

    if (expression->isTmpExpr()) {
        term->setSymbol(expression->getSymbol());
        term->setName(expression->getName());
    } else {
        SymbolInfo * tmpsym = new_tmp().clone();
        term->setSymbol(tmpsym);
        term->setName(get_curr_tmp_var());
    }

    quad_table.emit(uminus, expression, nullptr, term, 0, yylineno);
    return term;

}

expr *Manage_term_LEFT_PAREN_expr_RIGHT_PAREN(expr *expression) {
    return expression;
}

expr *Manage_expr_assignexpr(expr * e) {
    return e;
}

expr *Manage_expr_exprL_ARITH_OPERATOR_exprR(expr *exprL, iopcode op, expr *exprR) {
    if (!(exprL->isArithmExpr()) || !(exprR->isArithmExpr())) {
        error(ErrorType::Error, yylineno, "Invalid arithmetic operand\n");
        //again, these lines just to cheat the compiler that the operation was legal
        expr * toReturn = expr::newexpr(arithexpr_e);
        SymbolInfo * tmpsym = new_tmp().clone();
        toReturn->setSymbol(tmpsym);
        toReturn->setName(get_curr_tmp_var());
        return toReturn;
    } else {
        expr * toReturn = expr::newexpr(arithexpr_e);

        if (exprL->isTmpExpr()) {
            toReturn->setSymbol(exprL->getSymbol());
            toReturn->setName(exprL->getName());
        } else if (exprR->isTmpExpr()) {
            toReturn->setSymbol(exprR->getSymbol());
            toReturn->setName(exprR->getName());
        } else {
            SymbolInfo * tmpsym = new_tmp().clone();
            toReturn->setSymbol(tmpsym);
            toReturn->setName(get_curr_tmp_var());
        }

        quad_table.emit(op, exprL, exprR, toReturn, 0, yylineno);

        return toReturn;
    }
}

void Manage_expr_exprL_EQUAL(expr ** exprL) {
    *exprL = evalIfBooleanSC(*exprL);
}

void Manage_expr_exprL_NOT_EQUAL(expr ** exprL) {
    *exprL = evalIfBooleanSC(*exprL);
}

expr *Manage_expr_exprL_REL_OPERATOR_exprR(expr *exprL, iopcode op, expr *exprR) {
    expr * toReturn = expr::newexpr(boolexpr_e);
    switch(op) {
        case iopcode::if_greater:
        case iopcode::if_greatereq:
        case iopcode::if_less:
        case iopcode::if_lesseq:
            if (!(exprL->isArithmExpr()) || !(exprR->isArithmExpr())) {
                error(ErrorType::Error, yylineno, "Ordering allowed only between Numbers\n");
                //again, these lines just to cheat the compiler that the operation was legal
                expr * toReturn = expr::newexpr(arithexpr_e);
                SymbolInfo * tmpsym = new_tmp().clone();
                toReturn->setSymbol(tmpsym);
                toReturn->setName(get_curr_tmp_var());
                return toReturn;
            }
            break;
        case iopcode::if_eq:
        case iopcode::if_noteq:
            if (!exprL->hasSameType(exprR)) {
                error(ErrorType::Error, yylineno, "Equality check applies only to expressions of same type\n");
                //again, these lines just to cheat the compiler that the operation was legal
                expr * toReturn = expr::newexpr(arithexpr_e);
                SymbolInfo * tmpsym = new_tmp().clone();
                toReturn->setSymbol(tmpsym);
                toReturn->setName(get_curr_tmp_var());
                return toReturn;
            }
            break;
        default:
            assert(0);
    }
    expr * tmp_eL = evalIfBooleanSC(exprL);
    expr * tmp_eR = evalIfBooleanSC(exprR);
    toReturn->setSymbol(nullptr);
    toReturn->setName("ILLEGAL!!1!!11");

    toReturn->trueListInsert(quad_table.nextQuadLabel());
    toReturn->falseListInsert(quad_table.nextQuadLabel() + 1);

    quad_table.emit(op, tmp_eL, tmp_eR, nullptr, 0, yylineno);
    quad_table.emit(iopcode::jump, nullptr, nullptr, nullptr, 0, yylineno);

    return toReturn;
}

void Manage_expr_exprL_AND(expr * exprL) {
    if (exprL->getType() != boolexpr_e && exprL->getType() != constbool_e) {
        quad_table.emit(if_eq, exprL, expr::newexpr_constbool(true), nullptr, quad_table.nextQuadLabel() + 2, yylineno);
        exprL->falseListInsert(quad_table.nextQuadLabel());
        quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    }
}

void Manage_expr_exprL_OR(expr * exprL) {
    if (exprL->getType() != boolexpr_e && exprL->getType() != constbool_e) {
        exprL->trueListInsert(quad_table.nextQuadLabel());
        quad_table.emit(if_eq, exprL, expr::newexpr_constbool(true), nullptr, 0, yylineno);
        quad_table.emit(jump, nullptr, nullptr, nullptr, quad_table.nextQuadLabel() + 1, yylineno);
    }
}

expr *Manage_expr_exprL_AND_M_exprR(expr *exprL, unsigned M, expr *exprR) {
    expr * toReturn = expr::newexpr(boolexpr_e);
    std::vector<unsigned> E = std::vector<unsigned>();
    E.reserve(exprL->getFalseList().size() + exprR->getFalseList().size());
    E.insert(E.end(), exprL->getFalseList().begin(), exprL->getFalseList().end());
    E.insert(E.end(), exprR->getFalseList().begin(), exprR->getFalseList().end());
    toReturn->setFalseList(E);
    toReturn->setTrueList(exprR->getTrueList());
    exprL->backpatch(true, M);

    if (exprR->getType() != boolexpr_e && exprR->getType() != constbool_e) {
        toReturn->trueListInsert(quad_table.nextQuadLabel());
        quad_table.emit(if_eq, exprR, expr::newexpr_constbool(true), nullptr, 0, yylineno);
        toReturn->falseListInsert(quad_table.nextQuadLabel());
        quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    }
    
    toReturn->setSymbol(nullptr);
    toReturn->setName("WHAT NAME");

    return toReturn;
}

expr *Manage_expr_exprL_OR_M_exprR(expr *exprL, unsigned M, expr *exprR) {
    expr * toReturn = expr::newexpr(boolexpr_e);
    std::vector<unsigned> E = std::vector<unsigned>();
    E.reserve(exprL->getTrueList().size() + exprR->getTrueList().size());
    E.insert(E.end(), exprL->getTrueList().begin(), exprL->getTrueList().end());
    E.insert(E.end(), exprR->getTrueList().begin(), exprR->getTrueList().end());
    toReturn->setTrueList(E);
    toReturn->setFalseList(exprR->getFalseList());
    exprL->backpatch(false, M);
    
    if (exprR->getType() != boolexpr_e && exprR->getType() != constbool_e) {
        toReturn->trueListInsert(quad_table.nextQuadLabel());
        quad_table.emit(if_eq, exprR, expr::newexpr_constbool(true), nullptr, 0, yylineno);
        toReturn->falseListInsert(quad_table.nextQuadLabel());
        quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    }
    
    toReturn->setSymbol(nullptr);
    toReturn->setName("John Doe");

    return toReturn;
}

expr *Manage_lvalue_member(expr *member) {
    return member;
}

std::list<expr*>* Manage_commalist() {
    return new std::list<expr*>();
}

std::list<expr*>* Manage_commalist_COMMA_expr_commalist(std::list<expr*>* elist, expr * e) {
    expr * tmp_e = evalIfBooleanSC(e);
    elist->push_back(tmp_e);
    return elist;
}

std::list<expr*>* Manage_elistnotempty_expr_commalist(std::list<expr*>* elist, expr * e) {
    expr * tmp_e = evalIfBooleanSC(e);
    elist->push_back(tmp_e);
    return elist;
}

std::list<expr*>* Manage_elist() {
    return new std::list<expr*>();
}

std::list<expr*>* Manage_elist_elistnotempty(std::list<expr*>* elist) {
    return elist;
}

void Manage_indexedelem_LEFT_BRACE_expr(expr ** e) {
    *e = evalIfBooleanSC(*e);
}

indElem* Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE(expr * key, expr * value) {
    expr * tmp_evalue = evalIfBooleanSC(value);
    return new indElem(key, tmp_evalue);
}

indexedList* Manage_commaindexed() {
    return new indexedList();
}

indexedList* Manage_commaindexed_COMMA_indexedelem_commaindexed(indexedList* indexed, indElem* elem) {
    indexed->push_back(elem);
    return indexed;
}

indexedList* Manage_indexed_indexedelem_commaindexed(indexedList* indexed, indElem* elem) {
    indexed->push_back(elem);
    return indexed;
}

objectInner* Manage_objectdinner() {
    objectInner * res = new objectInner();
    res->first = nullptr;
    res->second = nullptr;
    return res;
}

objectInner* Manage_objectdinner_indexed(indexedList* indexed) {
    objectInner * res = new objectInner();
    res->second = indexed;
    res->first = nullptr;
    return res;
}

objectInner* Manage_objectdinner_elistnotempty(std::list<expr*>* elist) {
    objectInner * res = new objectInner();
    res->first = elist;
    res->second = nullptr;
    return res;
}

expr * Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET(objectInner * cont) {
    expr * t = expr::newexpr(newtable_e);

    SymbolInfo * tmpsym = new_tmp().clone();
    t->setSymbol(tmpsym);
    t->setName(get_curr_tmp_var());

    quad_table.emit(tablecreate, nullptr, nullptr, t, 0, yylineno);

    if (cont->first != nullptr) {
        int i = 0;
        for (expr * e : *(cont->first)) {
            quad_table.emit(tablesetelem, expr::newexpr_constnum(i++), e, t, 0, yylineno);
        }
    } else if (cont->second != nullptr) {
        for (indElem * ind : *(cont->second)) {
            quad_table.emit(tablesetelem, ind->first, ind->second, t, 0, yylineno);
        }
    }
    return t;
}

callInfo *Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN(char *id, std::list<expr*> *elist) {
    callInfo *toReturn = new callInfo();
    std::get<0>(*toReturn) = elist;
    std::get<1>(*toReturn) = true;
    std::get<2>(*toReturn) = id;
    return toReturn;
}

expr *Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN(expr *callRight, std::list<expr*> *elist) {
    return expr::make_call(callRight, elist);
}

expr *Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN(expr *funcdef, std::list<expr*> *elist) {
    expr *func = expr::newexpr(programfunc_e);
    func->setSymbol(funcdef->getSymbol());
    func->setName(funcdef->getName());
    return expr::make_call(func, elist);
}

expr *Manage_call_lvalue_callsuffix(expr *lvalue, callInfo *callsuffix) {
    if (std::get<1>(*callsuffix) == true) {//calling a method
        expr *self = lvalue;
        expr * temp = expr::member_item(self, std::get<2>(*callsuffix));
        lvalue = expr::emit_iftableitem(temp);
        std::get<0>(*callsuffix)->push_front(temp);
    }
    return expr::make_call(lvalue, std::get<0>(*callsuffix));
}

callInfo *Manage_callsuffix_normcall(callInfo *normcall) {
    return normcall;
}

callInfo *Manage_callsuffix_methodcall(callInfo *methodcall) {
    return methodcall;
}

callInfo *Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN(std::list<expr*> *elist) {
    callInfo *toReturn = new callInfo();
    std::get<0>(*toReturn) = elist;
    std::get<1>(*toReturn) = false;
    std::get<2>(*toReturn) = std::string();
    return toReturn;
}

expr *Manage_primary_call(expr * e) {
    return e;
}

expr *Manage_primary_objectdef(expr * e) {
    return e;
}

expr *Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN(expr *funcdef) {
    expr *toReturn = expr::newexpr(programfunc_e);
    toReturn->setSymbol(funcdef->getSymbol());
    toReturn->setName(funcdef->getName());
    return toReturn;
}

unsigned Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN(expr * e) {
    expr * tmp_e = evalIfBooleanSC(e);
    quad_table.emit(if_eq, tmp_e, expr::newexpr_constbool(true), nullptr, quad_table.nextQuadLabel() + 2, yylineno);
    unsigned temp = quad_table.nextQuadLabel();
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    symbol_table.addScopeType(Scope_Type::default_scope);
    return temp;
}

void Manage_ifstmt_ifprefix_stmt_elseprefix(stmtInfo *ifstmt) {
    hideIfNotBlock(ifstmt);
    symbol_table.addScopeType(Scope_Type::default_scope);
}

stmtInfo* Manage_ifstmt_ifprefix_stmt(unsigned ifprefix, stmtInfo* stmt) {
    quad_table.patchLabel(ifprefix, quad_table.nextQuadLabel());
    hideIfNotBlock(stmt);
    return stmt;
}

unsigned Manage_elseprefix_ELSE() {
    unsigned temp = quad_table.nextQuadLabel();
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    return temp;
}

stmtInfo* Manage_ifstmt_ifprefix_stmt_elseprefix_stmt(unsigned ifprefix, unsigned elseprefix, stmtInfo* stmt1, stmtInfo* stmt2) {
    quad_table.patchLabel(ifprefix, elseprefix + 1);
    quad_table.patchLabel(elseprefix, quad_table.nextQuadLabel());
    std::get<0>(*stmt1)->splice(std::get<0>(*stmt1)->end(), *std::get<0>(*stmt2));
    std::get<1>(*stmt1)->splice(std::get<1>(*stmt1)->end(), *std::get<1>(*stmt2));
    std::get<3>(*stmt1)->splice(std::get<3>(*stmt1)->end(), *std::get<3>(*stmt2));
    hideIfNotBlock(stmt2);
    delete stmt2;
    return stmt1;
}

unsigned Manage_N() {
    unsigned temp = quad_table.nextQuadLabel();
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    return temp;
}

unsigned Manage_M() {
    return quad_table.nextQuadLabel();
}

unsigned int Manage_whilestart_WHILE() {
    return quad_table.nextQuadLabel();
}

unsigned int Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN(expr * expression) {
    unsigned int toReturn;
    expr * tmp_e = evalIfBooleanSC(expression);
    quad_table.emit(iopcode::if_eq, tmp_e, expr::newexpr_constbool(true), nullptr, quad_table.nextQuadLabel() + 2, yylineno);
    toReturn = quad_table.nextQuadLabel();
    quad_table.emit(iopcode::jump, nullptr, nullptr, nullptr, 0, yylineno);

    symbol_table.addScopeType(Scope_Type::loop_scope);

    return toReturn;
}

void Manage_while_whilestart_whilecond_stmt(unsigned int label, unsigned int toPatch, stmtInfo* stmt) {
    quad_table.emit(iopcode::jump, nullptr, nullptr, nullptr, label, yylineno);
    quad_table.patchLabel(toPatch, quad_table.nextQuadLabel());
    for (unsigned i : *std::get<0>(*stmt)) {
        quad_table.patchLabel(i, quad_table.nextQuadLabel());
    }
    for (unsigned i : *std::get<1>(*stmt)) {
        quad_table.patchLabel(i, label);
    }
    hideIfNotBlock(stmt);
}

unsignedPair* Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_M_expr_SEMICOLON(unsigned M, expr * e) {
    expr * tmp_e = evalIfBooleanSC(e);
    unsignedPair * tmp = new unsignedPair();
    std::get<0>(*tmp) = M;
    std::get<1>(*tmp) = quad_table.nextQuadLabel();
    quad_table.emit(if_eq, tmp_e, expr::newexpr_constbool(true), nullptr, 0, yylineno);
    return tmp;
}

void Manage_forstmt_forprefix_N_elist() {
    symbol_table.addScopeType(Scope_Type::loop_scope);
}

void Manage_forstmt_forprefix_N_elist_RIGHT_PAREN_N_stmt_N(unsignedPair* forprefix, unsigned N1, unsigned N2, stmtInfo* stmt, unsigned N3) {
    quad_table.patchLabel(std::get<1>(*forprefix), N2 + 1);
    quad_table.patchLabel(N1, quad_table.nextQuadLabel());
    quad_table.patchLabel(N2, std::get<0>(*forprefix));
    quad_table.patchLabel(N3, N1 + 1);
    for (unsigned i : *std::get<0>(*stmt)) {
        quad_table.patchLabel(i, quad_table.nextQuadLabel());
    }
    for (unsigned i : *std::get<1>(*stmt)) {
        quad_table.patchLabel(i, N1 + 1);
    }
    hideIfNotBlock(stmt);
}

stmtInfo* Manage_stmts() {
    stmtInfo* tmp = new stmtInfo();
    std::get<0>(*tmp) = new std::list<unsigned>();
    std::get<1>(*tmp) = new std::list<unsigned>();
    std::get<3>(*tmp) = new std::list<unsigned>();
    return tmp;
}

stmtInfo* Manage_stmts_stmtsR_stmt(stmtInfo* stmtsR, stmtInfo* stmt) {
    if (stmt == nullptr) return stmtsR;
    std::get<0>(*stmtsR)->splice(std::get<0>(*stmtsR)->end(), *std::get<0>(*stmt));
    std::get<1>(*stmtsR)->splice(std::get<1>(*stmtsR)->end(), *std::get<1>(*stmt));
    std::get<3>(*stmtsR)->splice(std::get<3>(*stmtsR)->end(), *std::get<3>(*stmt));
    delete stmt;
    return stmtsR;
}

stmtInfo* Manage_stmt_BREAK() {
    int scope = symbol_table.inSpecialScope(Scope_Type::loop_scope);
    if (scope < 0) {
        error(ErrorType::Error, yylineno, BON "break" BOFF " statement not within a loop\n");
    }
    unsigned tmp = quad_table.nextQuadLabel();
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    stmtInfo * ll = new stmtInfo();
    std::get<0>(*ll) = new std::list<unsigned>();
    std::get<1>(*ll) = new std::list<unsigned>();
    std::get<3>(*ll) = new std::list<unsigned>();
    std::get<0>(*ll)->push_back(tmp);
    std::get<2>(*ll) = false;
    return ll;
}

stmtInfo* Manage_stmt_block(stmtInfo* blockLists) {
    std::get<2>(*blockLists) = true;
    return blockLists;
}

stmtInfo* Manage_stmt_ifstmt(stmtInfo* ifstmtLists) {
    std::get<2>(*ifstmtLists) = false;
    return ifstmtLists;
}

stmtInfo* Manage_stmt_CONTINUE() {
    int scope = symbol_table.inSpecialScope(Scope_Type::loop_scope);
    if (scope < 0) {
        error(ErrorType::Error, yylineno, BON "continue" BOFF " statement not within a loop\n");
    }
    unsigned tmp = quad_table.nextQuadLabel();
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    stmtInfo * ll = new stmtInfo();
    std::get<0>(*ll) = new std::list<unsigned>();
    std::get<1>(*ll) = new std::list<unsigned>();
    std::get<3>(*ll) = new std::list<unsigned>();
    std::get<1>(*ll)->push_back(tmp);
    std::get<2>(*ll) = false;
    std::get<3>(*ll) = new std::list<unsigned>();
    return ll;
}

stmtInfo* Manage_stmt_returnstmt(stmtInfo* returnstmt) {
    return returnstmt;
}

stmtInfo* Manage_returnstmt_RETURN_expr_SEMICOLON(expr * e) {
	expr * tmp_e = evalIfBooleanSC(e);
    int scope = symbol_table.inSpecialScope(Scope_Type::function_scope);
    if (scope < 0) {
        error(ErrorType::Error, yylineno, BON "return" BOFF " statement not within a function\n");
    }
    quad_table.emit(ret, nullptr, nullptr, tmp_e, 0, yylineno);
    stmtInfo * ll = new stmtInfo();
    std::get<0>(*ll) = new std::list<unsigned>();
    std::get<1>(*ll) = new std::list<unsigned>();
    std::get<2>(*ll) = false;
    std::get<3>(*ll) = new std::list<unsigned>();
    std::get<3>(*ll)->push_back(quad_table.nextQuadLabel());
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    return ll;
}

stmtInfo* Manage_returnstmt_RETURN_SEMICOLON() {
    int scope = symbol_table.inSpecialScope(Scope_Type::function_scope);
    if (scope < 0) {
        error(ErrorType::Error, yylineno, BON "return" BOFF " statement not within a function\n");
    }
    quad_table.emit(ret, nullptr, nullptr, nullptr, 0, yylineno);
    stmtInfo * ll = new stmtInfo();
    std::get<0>(*ll) = new std::list<unsigned>();
    std::get<1>(*ll) = new std::list<unsigned>();
    std::get<2>(*ll) = false;
    std::get<3>(*ll) = new std::list<unsigned>();
    std::get<3>(*ll)->push_back(quad_table.nextQuadLabel());
    quad_table.emit(jump, nullptr, nullptr, nullptr, 0, yylineno);
    return ll;
}

expr *Manage_member_call_DOT_ID(expr *call, char *id) {
    return expr::member_item(call, id);
}

expr *Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET(expr *call, expr *expression) {
    bool isRboolexpr = expression->getType() == boolexpr_e;
    expr * tmp_e = expr::newexpr(var_e);
    if (isRboolexpr) {
        SymbolInfo * tmpsym = new_tmp().clone();
        tmp_e->setSymbol(tmpsym);
        tmp_e->setName(get_curr_tmp_var());
        expression->backpatch(true, quad_table.nextQuadLabel());
        quad_table.emit(iopcode::assign, expr::newexpr_constbool(true), nullptr, tmp_e, 0, yylineno);
        quad_table.emit(iopcode::jump, nullptr, nullptr, nullptr, quad_table.nextQuadLabel() + 2, yylineno);
        expression->backpatch(false, quad_table.nextQuadLabel());
        quad_table.emit(iopcode::assign, expr::newexpr_constbool(false), nullptr, tmp_e, 0, yylineno);
    }
    call = expr::emit_iftableitem(call);
    expr * table_item = expr::newexpr(tableitem_e);
    table_item->setSymbol(call->getSymbol());
    table_item->setIndex(isRboolexpr ? tmp_e : expression);
    table_item->setName(call->getName());

    return table_item;
}