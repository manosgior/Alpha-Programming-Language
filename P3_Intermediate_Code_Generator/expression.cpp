#include "expression.h"
#include "tempManagement.h"
#include "quads.h"
#include "quadtable.h"
#include "defines_header.h"
#include <assert.h>

#define PRINT_VALSAMAKIS

extern QuadTable quad_table;

expr::expr() {
    sym = nullptr;
    index = nullptr;
}

expr * expr::lvalue_expr(std::string name, SymbolInfo * sym) {
    assert(sym);
    expr * e = new expr();
    e->sym = sym;
    switch(sym->getType()) {
        case (SymTable_Entry_Type::global_variable):
        case (SymTable_Entry_Type::formal_argument):
        case (SymTable_Entry_Type::local_variable):
            e->type = expr_t::var_e;
            break;
        case (SymTable_Entry_Type::user_function):
            e->type = expr_t::programfunc_e;
            break;
        case (SymTable_Entry_Type::library_function):
            e->type = expr_t::libraryfunc_e;
            break;
        default:
            assert(0);
    }
    e->name = name;
    return e;
}

SymbolInfo * expr::getSymbol() {
    return sym;
}

void expr::setSymbol(SymbolInfo * s) {
    sym = s;
}

expr_t expr::getType() {
    return type;
}

void expr::setType(expr_t t) {
    type = t;
}

expr* expr::getIndex() {
    return index;
}

void expr::setIndex(expr * i) {
    index = i;
}

std::string expr::getName() {
    return name;
}

void expr::setName(std::string n) {
    name = n;
}

expr * expr::member_item(expr * lvalue, std::string memberName) {
    lvalue = emit_iftableitem(lvalue);
    expr * item = newexpr(expr_t::tableitem_e);
    item->sym = lvalue->sym;
    item->name = lvalue->name;
    item->index = newexpr_conststring(memberName);
    return item;
}

expr * expr::newexpr(expr_t t) {
    expr * e = new expr();
    e->type = t;
    e->sym = nullptr;
    e->index = nullptr;    
    e->name = std::string();
    e->strConst = std::string();    
    return e;
}

expr * expr::newexpr_constnum(double i) {
    expr * e = newexpr(constnum_e);
    e->numConst = i;    
    e->sym = nullptr;
    e->index = nullptr;
    e->name = std::string();
    e->strConst = std::string();
    
    return e;
}

expr * expr::newexpr_conststring(std::string s){
    expr * e = newexpr(conststring_e);
    e->strConst = s;
    e->sym = nullptr;
    e->index = nullptr;
    e->name = std::string();
   
    return e;
}

expr * expr::newexpr_constnil(){
    expr * e = newexpr(nil_e);
    e->name = std::string();
    e->strConst = std::string();
    e->sym = nullptr;
    e->index = nullptr;
    
    return e;
}

expr * expr::newexpr_constbool(bool value){
    expr * e = newexpr(constbool_e);
    e->name = std::string();
    e->strConst = std::string();
    e->sym = nullptr;
    e->index = nullptr;
    e->boolConst = value;
    
    return e;
}

expr * expr::emit_iftableitem(expr * e){
    if(e->type != tableitem_e)
        return e;
    else{
        expr *result = newexpr(var_e);
        result->sym = new_tmp().clone();
        result->name = get_curr_tmp_var();
        quad_table.emit(tablegetelem, e, e->index, result, 0, yylineno);
        return result;
    }
}

expr * expr::make_call(expr * lvalue, std::list<expr *>* elist){
    expr *func = emit_iftableitem(lvalue);
    expr *result = newexpr(var_e);
    int flag = 1;
    
    
    for (auto it = elist->rbegin(); it != elist->rend(); it++) {
        quad_table.emit(param, *it, nullptr, nullptr, 0, yylineno);
        if( flag && (*it)->isTmpExpr()){
            result->sym = (*it)->getSymbol();
            result->name = (*it)->getName();
            flag = 0;
        }
    }
    quad_table.emit(call, func, nullptr, nullptr, 0, yylineno);
   
    if(flag){
        result->sym = new_tmp().clone();
        result->name = get_curr_tmp_var();
    }
    
    quad_table.emit(getretval, nullptr, nullptr, result, 0, yylineno);
    return result;
}

void expr::checkuminus(expr * e){
    if(e->type == constbool_e || e->type == conststring_e || e->type == nil_e
            || e->type == newtable_e || e->type == programfunc_e || e->type == libraryfunc_e|| e->type == boolexpr_e)
        error(ErrorType::Error, yylineno, "Illegal expression to unary -\n");
}

bool expr::isArithmExpr(){
    return (this->type == var_e || this->type == tableitem_e || this->type == arithexpr_e || this->type == constnum_e);
}

bool expr::hasSameType(expr * expression){
    expr_t otherType = expression->getType();
    
    if(this->type == boolexpr_e || this->type == constbool_e || otherType == boolexpr_e ||otherType == constbool_e){
        return true;
    }
    else if(this->type == otherType){
        return true;
    }
    else if(this->type == var_e || otherType == var_e || this->type == assignexpr_e || otherType == assignexpr_e){
        return true;
    }
    else if(this->type == tableitem_e || otherType == tableitem_e){
        return true;
    }
    else if((this->type == expr_t::arithexpr_e && otherType == expr_t::constnum_e) || 
        (otherType == expr_t::arithexpr_e && this->type == expr_t::constnum_e)) {
            return true;
    } 
    else if((this->type == expr_t::conststring_e && otherType == expr_t::var_e) ||
        (this->type == expr_t::var_e && otherType == expr_t::conststring_e)) {
            return true;
    }
    
    return false;
}

bool expr::isTmpExpr(){
    return (this->sym != nullptr && (this->type == var_e || this->type == arithexpr_e || this->type == boolexpr_e) && is_tmp_var(this->name));
}

std::string expr::toString(){
    std::string toReturn, tmp;    
    
    switch(this->type){
        case constnum_e:
#ifdef PRINT_VALSAMAKIS            
            if(this->numConst == (int) this->numConst)toReturn = std::to_string((int) this->numConst);            
            else toReturn = std::to_string(this->numConst);
            break;    
#endif
            toReturn = std::to_string(this->numConst);
            break;
        case conststring_e:
            toReturn = "\"" + this->strConst + "\"";
            break;
        case constbool_e: 
            tmp = (this->boolConst ? "true" : "false");
            toReturn = "\'" + tmp + "\'";
            break;       
        case tableitem_e:
        case var_e:
        case programfunc_e:
        case libraryfunc_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e:
        case assignexpr_e:
#ifdef PRINT_VALSAMAKIS
    if(this->name[0] == '_') {
        toReturn = this->name;
        toReturn.replace(0,2,"^");
    }
    else if(this->name[0] == '$'){
        toReturn = this->name;
        toReturn.replace(0,2,"$");
    }
    else  toReturn = this->name;  
    break;
#endif
            toReturn = this->name;
            break;
        case nil_e:
            toReturn = "nil";
            break;
        default:
            assert(0);     
    }
    
    return toReturn;
}

std::vector<unsigned>& expr::getTrueList() {
    return trueList;
}

std::vector<unsigned>& expr::getFalseList() {
    return falseList;
}

void expr::setTrueList(std::vector<unsigned> newList) {
    trueList = newList;
}

void expr::setFalseList(std::vector<unsigned> newList) {
    falseList = newList;
}

void expr::trueListInsert(unsigned elem) {
    trueList.push_back(elem);
}

void expr::falseListInsert(unsigned elem) {
    falseList.push_back(elem);
}

void expr::backpatch(bool whatList, unsigned jumpTo) {
    for (unsigned i : whatList ? trueList : falseList) {
        quad_table.patchLabel(i, jumpTo);
    }
}