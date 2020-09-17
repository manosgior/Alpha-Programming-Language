#include <string>
#include "symtable.h"

std::string new_tmp_name();
std::string get_curr_tmp_var();
void reset_tmp();
SymbolInfo new_tmp();
bool is_tmp_var(std::string var);
void createNewTmpVarSpace();
void backToPreviousTmpVarSpace();