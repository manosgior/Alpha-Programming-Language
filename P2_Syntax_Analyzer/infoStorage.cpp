#include <assert.h>
#include "symtable.h"

SymTable_InfoStorage::SymTable_InfoStorage() {
    active = std::vector<SymbolInfo>();
    inactive = std::vector<SymbolInfo>();
}

void SymTable_InfoStorage::HideActive(int scope) {
    assert(std::get<2>(active.back()) == (unsigned int) scope);
    while (!active.empty() && std::get<2>(active.back()) == (unsigned int) scope) {
        std::get<3>(active.back()) = false;
        inactive.push_back(active.back());
        active.pop_back();
#ifdef DEBUG
        fprintf(stderr, "INFO STORAGE: Hiding a symbol with scope %d\n", scope);
#endif
    }
}

void SymTable_InfoStorage::addNewActive(SymbolInfo newActive) {
    active.push_back(newActive);
#ifdef DEBUG
    fprintf(stderr, "INFO STORAGE: New active symbol with scope %u\n", std::get<2>(newActive));
#endif
}

SymbolInfo SymTable_InfoStorage::getActive() {
    assert(active.empty() || std::get<0>(active.back()) != invalid_entry_type);
    SymbolInfo sym_error;
    std::get<0>(sym_error) = SymTable_Entry_Type::invalid_entry_type;
    std::get<1>(sym_error) = 0;
    std::get<2>(sym_error) = 0;
    std::get<3>(sym_error) = false;
    if (active.empty()) {
        return sym_error;
    }
#ifdef DEBUG
    fprintf(stderr, "INFO STORAGE: Returning active token with scope %u\n", std::get<2>(active.back()));
#endif
    return active.back();
}

std::vector<SymbolInfo>& SymTable_InfoStorage::getActiveVector() {
    return active;
}

std::vector<SymbolInfo>& SymTable_InfoStorage::getInactiveVector() {
    return inactive;
}
