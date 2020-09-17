#ifndef SYMTABLE_H
#define SYMTABLE_H
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <sstream>
#include <map>
//#define DEBUG

enum SymTable_Entry_Type {
	invalid_entry_type=0, library_function, user_function, global_variable, formal_argument, local_variable, member_variable
};

enum Scope_Type {
	invalid_scope=0, default_scope, function_scope, loop_scope, global_scope, 
};

enum Scopespace_Type {
	programvar, functionlocal, formalarg
};

class SymbolInfo{
    
private:
    SymTable_Entry_Type type;
    size_t line;
    size_t scope;
    size_t offset;
    bool isActive;
    size_t functionAddress;
    size_t totalLocals;
    size_t totalFormals;
    Scopespace_Type scopeType;
    
public:
    SymbolInfo(SymTable_Entry_Type type, size_t line, size_t scope, size_t offset);
    SymbolInfo(SymTable_Entry_Type type, size_t line, size_t scope, size_t offset, size_t functionAddress);
    SymbolInfo(const SymbolInfo &);
    static SymbolInfo ErrorSymbol();
    SymbolInfo *clone();
    const SymTable_Entry_Type getType();
    void setType(SymTable_Entry_Type);
    const size_t getLine();
    const size_t getScope();
    void setScope(size_t);
    const bool isCurrentlyActive();
    void setActive(bool);
    const size_t getOffset();
    const size_t getFuncAddress();
    void setFuncAddress(size_t);
    const size_t getTotalLocals();
    void setTotalLocals(size_t);
    size_t getTotalFormals();
    void setTotalFormals(size_t);
    void setScopespaceType(Scopespace_Type);
    Scopespace_Type getScopespaceType();
};

void printSymbolInfo(std::string name, SymbolInfo info, std::ostream& ofs);

class SymTable_InfoStorage {
private:
	std::vector<SymbolInfo> active;
	std::vector<SymbolInfo> inactive;
public:
	SymTable_InfoStorage();
	void HideActive(int scope);
	void addNewActive(SymbolInfo);
	SymbolInfo getActive();
	std::vector<SymbolInfo> &getActiveVector();
	std::vector<SymbolInfo> &getInactiveVector();
};

class OffsetCounters{
private:
    size_t programVarOffset;
    size_t formalArgOffset;
    size_t localVarOffset;
public:
    OffsetCounters();
    OffsetCounters(size_t programVarOffset, size_t formalArgOffset, size_t localVarOffset);
    size_t getProgVarOffset();
    size_t getFormalArgOffset();
    size_t getLocalVarOffset();
    void incrementProgVarOffset();
    void incrementFormalArgOffset();
    void incrementLocalVarOffset();
};

class NameToStorage{
private:
    std::string key;
    SymTable_InfoStorage *storage;
    
public:
    NameToStorage(std::string, SymTable_InfoStorage *);
    SymTable_InfoStorage *getInfoStorage();
};

class ScopeToInfo{
private:
    Scope_Type scopeType;
    std::vector<NameToStorage> symbolsInScope;
    OffsetCounters scopeOffsets; 
public:
    ScopeToInfo(Scope_Type);
    Scope_Type getScopeType();
    size_t getProgVarOffset();
    size_t getFormalArgOffset();
    size_t getLocalVarOffset();
    void incrementProgVarOffset();
    void incrementFormalArgOffset();
    void incrementLocalVarOffset();
    void insertBindingInScope(NameToStorage);
    std::vector<NameToStorage> &getSymbolsInScope();
};

void dumpSymbolInfo(std::string name, SymbolInfo info, std::stringstream &ss);

class SymTable {
private:
	std::map<std::string, SymTable_InfoStorage *> name2info_table;
        OffsetCounters lastPoppedOffsets;
	std::vector<ScopeToInfo> scope2info_table;
	int getOffsetCounter(SymTable_Entry_Type);
	void incOffsetCounter(SymTable_Entry_Type);
    size_t totalGlobals;

public:
	SymTable();
	~SymTable();
	SymbolInfo Insert(std::string key, SymTable_Entry_Type type, size_t line, size_t scope);
	SymbolInfo Lookup(std::string key, int scope);
	void Hide();
	void setFunctionTotalLocals(std::string key, size_t totallocals);
    void setFunctionTotalFormals(std::string key, size_t totalFormals);
	void setFunctionAddress(std::string key, size_t functionAddress);
	size_t getFunctionLocalOffset();
    size_t getFormalsOffset();
	void addScopeType(Scope_Type st);
	Scope_Type getScopeType();
	size_t getMaxScope();
	int inSpecialScope(Scope_Type s);
	void PrintTable();
    size_t getTotalGlobals();
};

#endif
