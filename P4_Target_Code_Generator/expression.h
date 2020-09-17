#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "symtable.h"
#include "error_handler.h"
#include <string>
#include <list>

enum expr_t {

    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e
};

class expr {
private:
    expr_t                type;
    std::string           name;
    SymbolInfo*           sym;
    expr*                 index;
    double                numConst;
    std::string           strConst;
    bool                  boolConst;
    std::vector<unsigned> trueList;
    std::vector<unsigned> falseList;
public:
    expr();
    static expr * lvalue_expr(std::string name, SymbolInfo * sym);
    static expr * member_item(expr * lvalue, std::string memberName);
    static expr * newexpr(expr_t t);
    static expr * newexpr_constnum(double i);
    static expr * newexpr_conststring(std::string s);
    static expr * newexpr_constnil();
    static expr * newexpr_constbool(bool value);
    static expr * emit_iftableitem(expr * e);
    static expr * make_call(expr * lvalue, std::list<expr *>* elist);
    static void checkuminus(expr * e);
    SymbolInfo * getSymbol();
    void setSymbol(SymbolInfo * s);
    expr_t getType();
    void setType(expr_t t);
    expr* getIndex();
    void setIndex(expr * i);
    std::string getName();
    std::string toString();
    bool getBoolConst();
    std::string getStringConst();
    double getNumConst();
    void setName(std::string n);
    bool isArithmExpr();
    bool hasSameType(expr * expression);
    bool isTmpExpr();
    std::vector<unsigned>& getTrueList();
    std::vector<unsigned>& getFalseList();
    void setTrueList(std::vector<unsigned> newList);
    void setFalseList(std::vector<unsigned> newList);
    void trueListInsert(unsigned elem);
    void falseListInsert(unsigned elem);
    void backpatch(bool whatList, unsigned jumpTo);
};

#endif