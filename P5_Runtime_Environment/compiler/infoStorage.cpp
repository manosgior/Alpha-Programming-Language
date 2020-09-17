#include <assert.h>
#include "symtable.h"

SymTable_InfoStorage::SymTable_InfoStorage() {
    active = std::vector<SymbolInfo>();
    inactive = std::vector<SymbolInfo>();
}

void SymTable_InfoStorage::HideActive(int scope) {
    assert(active.back().getScope() == (unsigned int) scope);
    while (!active.empty() && active.back().getScope() == (unsigned int) scope) {
        active.back().setActive(false);
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
    fprintf(stderr, "INFO STORAGE: New active symbol with scope %u\n", newActive.getScope());
#endif
}

SymbolInfo SymTable_InfoStorage::getActive() {
    assert(active.empty() || active.back().getType() != invalid_entry_type);
    SymbolInfo sym_error = SymbolInfo::ErrorSymbol();
    if (active.empty()) {
        return sym_error;
    }
#ifdef DEBUG
    fprintf(stderr, "INFO STORAGE: Returning active token with scope %u\n", active.back().getScope());
#endif
    return active.back();
}

std::vector<SymbolInfo>& SymTable_InfoStorage::getActiveVector() {
    return active;
}

std::vector<SymbolInfo>& SymTable_InfoStorage::getInactiveVector() {
    return inactive;
}
