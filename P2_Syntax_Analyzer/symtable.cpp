#include "symtable.h"
#include <assert.h>
#include <iostream>

SymTable::SymTable() {

}

SymTable::~SymTable() {
    for (std::map<std::string, SymTable_InfoStorage *>::iterator it = name2info_table.begin();
            it != name2info_table.end(); it++) {

        delete it->second;
    }
}

void SymTable::Insert(std::string key, SymTable_Entry_Type type, size_t line, size_t scope) {
    SymbolInfo info;
    std::get<0>(info) = type;
    std::get<1>(info) = line;
    std::get<2>(info) = scope;
    std::get<3>(info) = true;
    std::map<std::string, SymTable_InfoStorage *>::iterator it;
	#ifdef DEBUG
	fprintf(stderr, "SymTable::Insert: Attempting insertion of symbol %s, line %u, scope %u\n", 
			key.c_str(), line, scope);
	#endif
    it = name2info_table.find(key);
    if (it == name2info_table.end()) {
		#ifdef DEBUG
		fprintf(stderr, "SymTable::Insert: Symbol was not found, creating a new binding\n");
        #endif
        name2info_table[key] = new SymTable_InfoStorage();
    }

    name2info_table[key]->addNewActive(info);

    assert(scope < scope2info_table.size());

    name2storage n2s;
    n2s.first = key;
    n2s.second = name2info_table[key];

    scope2info_table[scope].second.push_back(n2s);
}

void SymTable::addScopeType(Scope_Type st) {
	#ifdef DEBUG
	fprintf(stderr, "SymTable::addScopeType: Adding a new scope in the vector\n");
	#endif
    scope2info_entry e;
    e.first = st;
    e.second = std::vector<name2storage>();
    scope2info_table.push_back(e);
}

Scope_Type SymTable::getScopeType() {
    return scope2info_table.back().first;
}

size_t SymTable::getMaxScope() {
	#ifdef DEBUG
	fprintf(stderr, "SymTable::getMaxScope: Max scope is %u\n", scope2info_table.size() - 1);
	#endif	
    return scope2info_table.size() - 1;
}

SymbolInfo SymTable::Lookup(std::string key, int scope) {
    SymbolInfo sym_error;
    std::get<0>(sym_error) = SymTable_Entry_Type::invalid_entry_type;
    std::get<1>(sym_error) = 0;
    std::get<2>(sym_error) = 0;
    std::get<3>(sym_error) = false;
    std::map<std::string, SymTable_InfoStorage *>::iterator it = name2info_table.find(key);
	#ifdef DEBUG
	fprintf(stderr, "SymTable::Lookup: Looking up symbol %s in scope %d\n", key.c_str(), scope);
	#endif		
    if (it == name2info_table.end()) {
		#ifdef DEBUG
		fprintf(stderr, "SymTable::Lookup: Symbol was not found\n");
		#endif
        return sym_error;
    } else if (scope < 0) {
        SymbolInfo sym = it->second->getActive();
        if (std::get<0>(sym) == SymTable_Entry_Type::invalid_entry_type) {
			#ifdef DEBUG
			fprintf(stderr, "SymTable::Lookup: Symbol found, but not active\n");
			#endif
            return sym_error;
        }
        return sym;
    } else {
        std::vector<SymbolInfo>& actVec = it->second->getActiveVector();
        for (unsigned int i = 0; i < actVec.size(); i++) {
            if (std::get<2>(actVec[i]) == (unsigned int) scope) {
                #ifdef DEBUG
                fprintf(stderr, "SymTable::Lookup: Returning active token with scope %u\n", std::get<2>(actVec[i]));
                #endif
                return actVec[i];
            }
        }
		#ifdef DEBUG
		fprintf(stderr, "SymTable::Lookup: Symbol found, but not active\n");
		#endif
        return sym_error;
    }
}

void SymTable::Hide() {
    size_t scope2hide = scope2info_table.size() - 1;
    for (name2storage n2s : scope2info_table.back().second) {
#ifdef DEBUG
        fprintf(stderr, "SymTable::Hide: Hiding symbol %s\n", n2s.first.c_str());
#endif
        n2s.second->HideActive(scope2hide);
    }
    scope2info_table.pop_back();
}

void SymTable_InfoStorage::printSymbolInfo() {
    std::string type;
    for (auto i : active) {
        switch (std::get<0>(i)) {
            case SymTable_Entry_Type::invalid_entry_type:
                type = "invalid_type";
            case SymTable_Entry_Type::library_function:
                type = "library_function";
            case SymTable_Entry_Type::user_function:
                type = "user_function";
            case SymTable_Entry_Type::global_variable:
                type = "global_variable";
            case SymTable_Entry_Type::formal_argument:
                type = "formal_argument";
            case SymTable_Entry_Type::local_variable:
                type = "local_variable";
            default:
                type = "Apoklietai na ine kati allo re";
        }
        std::cout << "Type = " << type << " Line = " << std::get<1>(i) << " Scope = "
                << std::get<2>(i) << " isActive = " << std::get<3>(i) << std::endl;
    }
}

std::string getStringFromEntryType(SymTable_Entry_Type type) {
    switch (type) {
        case SymTable_Entry_Type::invalid_entry_type:
            return "invalid_type";
        case SymTable_Entry_Type::library_function:
            return "library_function";
        case SymTable_Entry_Type::user_function:
            return "user_function";
        case SymTable_Entry_Type::global_variable:
            return "global_variable";
        case SymTable_Entry_Type::formal_argument:
            return "formal_argument";
        case SymTable_Entry_Type::local_variable:
            return "local_variable";
        default:
            return "ase re pou thes kai string";
    }
}

int SymTable::inSpecialScope(Scope_Type s) {
    int i = 0;
    for (auto it = scope2info_table.rbegin(); it != scope2info_table.rend(); it++) {
        if ((*it).first == s) {
#ifdef DEBUG
            fprintf(stderr, "SymTable::inSpecialScope: Special scope depth: %u\n", scope2info_table.size()-i-1);
#endif            
            return (int)scope2info_table.size()-i-1;
        }
        i++;
    }
    return -1;
}

void SymTable::PrintTable() {
    std::map<size_t, std::string> to_print;
    std::vector<SymbolInfo> actives_inactives;

    for (std::map<std::string, SymTable_InfoStorage *>::iterator it =
            name2info_table.begin(); it != name2info_table.end(); it++) {

        actives_inactives = it->second->getActiveVector();
        for (auto i : actives_inactives) {
            to_print[std::get<2>(i)] += " \"" + it->first + "\" [" +
                    getStringFromEntryType(std::get<0>(i)) + "]	(line " +
                    std::to_string(std::get<1>(i)) + ")	(scope " +
                    std::to_string(std::get<2>(i)) + ")\n";
        }

        actives_inactives = it->second->getInactiveVector();
        for (auto i : actives_inactives) {
            to_print[std::get<2>(i)] += " \"" + it->first + "\" [" +
                    getStringFromEntryType(std::get<0>(i)) + "]	(line " +
                    std::to_string(std::get<1>(i)) + ")	(scope " +
                    std::to_string(std::get<2>(i)) + ")\n";
        }
    }

    for (std::map<size_t, std::string>::iterator it = to_print.begin();
            it != to_print.end(); it++) {
        std::cout << "-----------   Scope #" << it->first << "  -----------" << std::endl;
        std::cout << it->second << std::endl;
    }
}