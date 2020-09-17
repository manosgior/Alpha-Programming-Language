#ifndef AVM_TABLE_H
#define AVM_TABLE_H

#include <string>
#include <map>
#include <vector>
#include "AVM_MemCell.h"

class AVM_Table {
private:
    std::map<double, AVM_MemCell> numberToValue;
    std::map<std::string, AVM_MemCell> stringToValue;
    std::map<bool, AVM_MemCell> boolToValue;
    std::map<AVM_Table *, AVM_MemCell> AVM_TableToValue;
    std::map<unsigned, AVM_MemCell> userFuncToValue;
    std::map<std::string, AVM_MemCell> libFuncToValue;
    std::string toString_Util(std::map<AVM_Table *, bool> visited);

    unsigned refCounter;
    static unsigned currSerialNo;
    unsigned serialNo;
    void clear();    
    
public:
    AVM_Table();
    AVM_MemCell getElem(AVM_MemCell*);
    void setElem(AVM_MemCell* key, AVM_MemCell* value);
    void incRefCounter();
    void decRefCounter();   
    unsigned getRefCounter();
    std::string toString(); 
    unsigned getSerialNo();
    unsigned int getTotalMembers();
    std::vector<AVM_MemCell> getKeys();
    std::vector<AVM_MemCell> getValues();
    ~AVM_Table();
};


#endif
