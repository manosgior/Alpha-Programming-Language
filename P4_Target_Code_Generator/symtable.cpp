#include "symtable.h"
#include "error_handler.h"
#include <assert.h>
#include <iostream>
#include <iomanip>


SymbolInfo::SymbolInfo(SymTable_Entry_Type type, size_t line, size_t scope, size_t offset)
    : type(type), line(line), scope(scope), offset(offset), isActive(true), functionAddress(0), totalLocals(0){

}

SymbolInfo::SymbolInfo(SymTable_Entry_Type type, size_t line, size_t scope, size_t offset, size_t functionAddress)
    : type(type), line(line), scope(scope), offset(offset), isActive(true), functionAddress(functionAddress), totalLocals(0){
 
}

SymbolInfo SymbolInfo::ErrorSymbol(){
    SymbolInfo tmp(SymTable_Entry_Type::invalid_entry_type, 0, 0, 0);
    return tmp;
}

SymbolInfo *SymbolInfo::clone(){
    return new SymbolInfo(*this);
}

SymbolInfo::SymbolInfo(const SymbolInfo &other){
    this->type = other.type;
    this->line = other.line;
    this->scope = other.scope;
    this->offset = other.offset;
    this->isActive = other.isActive;
    this->functionAddress = other.functionAddress;
    this->totalLocals = other.totalLocals;
}

const SymTable_Entry_Type SymbolInfo::getType(){
    return type;
}

void SymbolInfo::setType(SymTable_Entry_Type type){
    this->type = type;
}

const size_t SymbolInfo::getLine(){
    return line;
}

const size_t SymbolInfo::getScope(){
    return scope;
}

void SymbolInfo::setScope(size_t scope){
    this->scope = scope;
}

const bool SymbolInfo::isCurrentlyActive(){
    return isActive;
}

void SymbolInfo::setActive(bool active){
    isActive = active;
}

const size_t SymbolInfo::getOffset(){
    return offset;
}

const size_t SymbolInfo::getFuncAddress(){
    return functionAddress;
}

void SymbolInfo::setFuncAddress(size_t addr){
    functionAddress = addr;
}
const size_t SymbolInfo::getTotalLocals(){
    return totalLocals;
}

void SymbolInfo::setTotalLocals(size_t total){
    totalLocals = total;
}

OffsetCounters::OffsetCounters(){
    this->formalArgOffset = this->localVarOffset = this->programVarOffset = 0;
}

OffsetCounters::OffsetCounters(size_t programVarOffset, size_t formalArgOffset, size_t localVarOffset){
    this->programVarOffset = programVarOffset;
    this->formalArgOffset = formalArgOffset;
    this->localVarOffset = localVarOffset;
}

size_t OffsetCounters::getProgVarOffset(){
    return programVarOffset;
}

size_t OffsetCounters::getFormalArgOffset(){
    return formalArgOffset;
}

size_t OffsetCounters::getLocalVarOffset(){
    return localVarOffset;
}

void OffsetCounters::incrementProgVarOffset(){
    programVarOffset++;
}

void OffsetCounters::incrementFormalArgOffset(){
    formalArgOffset++;
}

void OffsetCounters::incrementLocalVarOffset(){
    localVarOffset++;
}

ScopeToInfo::ScopeToInfo(Scope_Type scopeType){
    this->scopeType = scopeType;
    this->symbolsInScope = std::vector<NameToStorage>();
    scopeOffsets = OffsetCounters();
}

void ScopeToInfo::insertBindingInScope(NameToStorage b){
    symbolsInScope.push_back(b);
}

Scope_Type ScopeToInfo::getScopeType(){
    return this->scopeType;
}

size_t ScopeToInfo::getProgVarOffset(){
    return this->scopeOffsets.getProgVarOffset();
}

size_t ScopeToInfo::getFormalArgOffset(){
    return this->scopeOffsets.getFormalArgOffset();
}

size_t ScopeToInfo::getLocalVarOffset(){
    return this->scopeOffsets.getLocalVarOffset();
}

void ScopeToInfo::incrementProgVarOffset(){
    this->scopeOffsets.incrementProgVarOffset();
}

void ScopeToInfo::incrementLocalVarOffset(){
    this->scopeOffsets.incrementLocalVarOffset();
}

void ScopeToInfo::incrementFormalArgOffset(){
    this->scopeOffsets.incrementFormalArgOffset();
}

std::vector<NameToStorage> & ScopeToInfo::getSymbolsInScope(){
    return this->symbolsInScope;
}

NameToStorage::NameToStorage(std::string key, SymTable_InfoStorage *storage){
    this->key = key;
    this->storage = storage;
}

SymTable_InfoStorage * NameToStorage::getInfoStorage(){
    return this->storage;
}
    
SymTable::SymTable() {

}

SymTable::~SymTable() {
    for (std::map<std::string, SymTable_InfoStorage *>::iterator it = name2info_table.begin();
            it != name2info_table.end(); it++) {

        delete it->second;
    }
}

int SymTable::getOffsetCounter(SymTable_Entry_Type t) {
    int specialScopeDepth;
    switch(t) {
        case(SymTable_Entry_Type::global_variable):
            return scope2info_table[0].getProgVarOffset();
        case(SymTable_Entry_Type::formal_argument):
            return scope2info_table.back().getFormalArgOffset();
        case(SymTable_Entry_Type::local_variable):
            if ( (specialScopeDepth = inSpecialScope(function_scope)) > 0 ) 
                return scope2info_table[specialScopeDepth].getLocalVarOffset();
            else 
                return scope2info_table[0].getProgVarOffset();
        default:
            return -1;
    }
}

void SymTable::incOffsetCounter(SymTable_Entry_Type t) {
    int specialScopeDepth;
    switch(t) {
        case(SymTable_Entry_Type::global_variable):
            scope2info_table[0].incrementProgVarOffset();
            return;
        case(SymTable_Entry_Type::formal_argument):
            scope2info_table.back().incrementFormalArgOffset();
            return;
        case(SymTable_Entry_Type::local_variable):
            if ( (specialScopeDepth = inSpecialScope(function_scope)) > 0 ) 
                scope2info_table[specialScopeDepth].incrementLocalVarOffset();
            else 
                scope2info_table[0].incrementProgVarOffset();
            return;
        default:
            return;
    }
}

SymbolInfo SymTable::Insert(std::string key, SymTable_Entry_Type type, size_t line, size_t scope) {
    SymbolInfo info = SymbolInfo(type, line, scope, getOffsetCounter(type));
    incOffsetCounter(type);
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

    NameToStorage n2s(key, name2info_table[key]);

    scope2info_table[scope].insertBindingInScope(n2s);
    return info; 
}

void SymTable::addScopeType(Scope_Type st) {
	#ifdef DEBUG
	fprintf(stderr, "SymTable::addScopeType: Adding a new scope in the vector\n");
	#endif
    scope2info_table.push_back(ScopeToInfo(st));
}

Scope_Type SymTable::getScopeType() {
    return scope2info_table.back().getScopeType();
}

size_t SymTable::getMaxScope() {
	#ifdef DEBUG
	fprintf(stderr, "SymTable::getMaxScope: Max scope is %u\n", scope2info_table.size() - 1);
	#endif	
    return scope2info_table.size() - 1;
}

SymbolInfo SymTable::Lookup(std::string key, int scope) {
    SymbolInfo sym_error = SymbolInfo::ErrorSymbol();
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
        if (sym.getType() == SymTable_Entry_Type::invalid_entry_type) {
			#ifdef DEBUG
			fprintf(stderr, "SymTable::Lookup: Symbol found, but not active\n");
			#endif
            return sym_error;
        }
        return sym;
    } else {
        std::vector<SymbolInfo>& actVec = it->second->getActiveVector();
        for (unsigned int i = 0; i < actVec.size(); i++) {
            if (actVec[i].getScope() == (unsigned int) scope) {
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

void SymTable::setFunctionTotalLocals(std::string key, size_t totallocals) {
    std::map<std::string, SymTable_InfoStorage *>::iterator it = name2info_table.find(key);
    if (it == name2info_table.end()) {
        return;
    } else {
        std::vector<SymbolInfo>& actVec = it->second->getActiveVector();
        actVec.back().setTotalLocals(totallocals);
    }
}

void SymTable::setFunctionAddress(std::string key, size_t functionAddress) {
    std::map<std::string, SymTable_InfoStorage *>::iterator it = name2info_table.find(key);
    if (it == name2info_table.end()) {
        return;
    } else {
        std::vector<SymbolInfo>& actVec = it->second->getActiveVector();
        actVec.back().setFuncAddress(functionAddress);
    }
}

size_t SymTable::getFunctionLocalOffset() {
    return lastPoppedOffsets.getLocalVarOffset();
}

void SymTable::Hide() {
    size_t scope2hide = scope2info_table.size() - 1;
    for (NameToStorage n2s : scope2info_table.back().getSymbolsInScope()) {
#ifdef DEBUG
        fprintf(stderr, "SymTable::Hide: Hiding symbol %s\n", n2s.first.c_str());
#endif
        n2s.getInfoStorage()->HideActive(scope2hide);
    }
    lastPoppedOffsets = OffsetCounters(scope2info_table.back().getProgVarOffset(),
        scope2info_table.back().getFormalArgOffset(),    
            scope2info_table.back().getLocalVarOffset());
    scope2info_table.pop_back();
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
        if ((*it).getScopeType() == Scope_Type::function_scope && s == Scope_Type::loop_scope) {
            return -1;
        }
        if ( (*it).getScopeType() == s) {
#ifdef DEBUG
            fprintf(stderr, "SymTable::inSpecialScope: Special scope depth: %u\n", scope2info_table.size()-i-1);
#endif            
            return (int)scope2info_table.size()-i-1;
        }
        i++;
    }
    return -1;
}

void dumpSymbolInfo(std::string name, SymbolInfo info, std::stringstream &ss){
    
    ss << std::left << "\"" << std::setw(20) << name + "\"" << std::setw(20) 
            << "[" +  getStringFromEntryType(info.getType()) + "]" << std::setw(10)
            << "(line " + std::to_string(info.getLine()) + ")" << std::setw(10)
            << "(scope " +  std::to_string(info.getScope()) + ")" << std::setw(10)
            << ((info.getType() == user_function) ? ("(locals " + 
            std::to_string(info.getTotalLocals()) + ", address " + std::to_string(info.getFuncAddress()) + ") ") : "") << std::setw(10) <<
            ((info.getType() == local_variable || 
                info.getType() == member_variable || 
                    info.getType() == global_variable || info.getType() == formal_argument) ?
                         "(offset " + std::to_string(info.getOffset()) + ") " : "")
             << std::endl;
} 

void SymTable::PrintTable() {
    std::map<size_t, std::stringstream> to_print;
    for(auto it = this->name2info_table.begin(); it != this->name2info_table.end(); it++){
        for(auto sym : it->second->getActiveVector()){
            dumpSymbolInfo(it->first, sym, to_print[sym.getScope()]);
        }
        for(auto sym : it->second->getInactiveVector()){
            dumpSymbolInfo(it->first, sym, to_print[sym.getScope()]);
        }        
    }
    for(auto it = to_print.begin(); it != to_print.end(); it++){
        std::cout << "-------------------------   Scope #" << it->first << "   -------------------------" << std::endl;
        std::cout << it->second.str();
    }
}