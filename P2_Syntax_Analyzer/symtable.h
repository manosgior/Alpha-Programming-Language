#ifndef SYMTABLE_H
#define SYMTABLE_H
#include <stdlib.h>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <map>
//#define DEBUG

enum SymTable_Entry_Type {
	invalid_entry_type=0, library_function, user_function, global_variable, formal_argument, local_variable, member_variable
};

enum Scope_Type {
	invalid_scope=0, default_scope, function_scope, loop_scope, global_scope
};

typedef std::tuple<SymTable_Entry_Type, size_t, size_t, bool> SymbolInfo;

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
	void printSymbolInfo();
};

typedef std::pair<std::string, SymTable_InfoStorage*> name2storage;
typedef std::pair<Scope_Type, std::vector<name2storage>> scope2info_entry;

std::string getStringFromEntryType(SymTable_Entry_Type type);

class SymTable {
private:
	std::map<std::string, SymTable_InfoStorage *> name2info_table;
	std::vector<scope2info_entry> scope2info_table;
public:
	SymTable();
	~SymTable();
	void Insert(std::string key, SymTable_Entry_Type type, size_t line, size_t scope);
	SymbolInfo Lookup(std::string key, int scope);
	void Hide();
	void addScopeType(Scope_Type st);
	Scope_Type getScopeType();
	size_t getMaxScope();
	int inSpecialScope(Scope_Type s);
	void PrintTable();;
};

#endif
