#include "AVM_Table.h"
#include <assert.h>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "error_handler.h"

extern unsigned __currentLine__;

unsigned AVM_Table::currSerialNo = 0;

void AVM_Table::clear()
{
	for (auto it = numberToValue.begin(); it != numberToValue.end(); it++)
	{
		it->second.clear();
	}
	for (auto it = stringToValue.begin(); it != stringToValue.end(); it++)
	{
		it->second.clear();
	}
	for (auto it = boolToValue.begin(); it != boolToValue.end(); it++)
	{
		it->second.clear();
	}
	for (auto it = AVM_TableToValue.begin(); it != AVM_TableToValue.end(); it++)
	{
		it->second.clear();
	}
	for (auto it = userFuncToValue.begin(); it != userFuncToValue.end(); it++)
	{
		it->second.clear();
	}
	for (auto it = libFuncToValue.begin(); it != libFuncToValue.end(); it++)
	{
		it->second.clear();
	}	
}

AVM_Table::AVM_Table()
{
	refCounter = 0;
	serialNo = currSerialNo++;
}

void AVM_Table::incRefCounter()
{
	refCounter++;
}

void AVM_Table::decRefCounter()
{
	assert(refCounter > 0);
	if (!--refCounter)
	{
		clear();
	}
}

unsigned AVM_Table::getRefCounter()
{
	return refCounter;
}

AVM_MemCell AVM_Table::getElem(AVM_MemCell *e)
{
	switch (e->getType())
	{
		case (number_m):
		{
			auto n2v = numberToValue.find(e->data.numVal);
			if (n2v == numberToValue.end())
				return AVM_MemCell(nil_m);
			return n2v->second;
		}
		case (string_m):
		{
			auto s2v = stringToValue.find(e->data.strVal);
			if (s2v == stringToValue.end())
				return AVM_MemCell(nil_m);
			return s2v->second;
		}
		case(bool_m):
		{
			auto s2v = boolToValue.find(e->data.boolVal);
			if (s2v == boolToValue.end())
				return AVM_MemCell(nil_m);
			return s2v->second;			
		}
		case(userfunc_m):
		{
			auto s2v = userFuncToValue.find(e->data.funcVal);
			if (s2v == userFuncToValue.end())
				return AVM_MemCell(nil_m);
			return s2v->second;				
		}
		case(libfunc_m):
		{
			auto s2v = libFuncToValue.find(e->data.libfuncVal);
			if (s2v == libFuncToValue.end())
				return AVM_MemCell(nil_m);
			return s2v->second;				
		}		
		case(table_m):
		{
			auto s2v = AVM_TableToValue.find(e->data.tableVal);
			if (s2v == AVM_TableToValue.end())
				return AVM_MemCell(nil_m);
			return s2v->second;				
		}
		default:
			error(Error, __currentLine__, "Unsupported table index type\n\n");
			return AVM_MemCell(nonexistent_m);
	}
}

void AVM_Table::setElem(AVM_MemCell *key, AVM_MemCell *value)
{
	switch (key->getType())
	{
	case (number_m):
	{
		auto n2v = numberToValue.find(key->data.numVal);
		if (n2v == numberToValue.end())
		{
			if (value->getType() != nil_m)
				numberToValue[key->data.numVal].assign(value);
		}
		else
		{
			if (value->getType() != nil_m)
			{
				n2v->second.clear();
				n2v->second.assign(value);
			}
			else
			{
				n2v->second.clear();
				numberToValue.erase(n2v);
			}
		}
		return;
	}
	case string_m:
	{
		auto s2v = stringToValue.find(key->data.strVal);
		if (s2v == stringToValue.end())
		{
			if (value->getType() != nil_m)
				stringToValue[key->data.strVal].assign(value);
		}
		else
		{
			if (value->getType() != nil_m)
			{
				s2v->second.clear();
				s2v->second.assign(value);
			}
			else
			{
				s2v->second.clear();
				stringToValue.erase(s2v);
			}
		}
		return;
	}
	case bool_m:
	{
		auto s2v = boolToValue.find(key->data.boolVal);
		if (s2v == boolToValue.end())
		{
			if (value->getType() != nil_m)
				boolToValue[key->data.boolVal].assign(value);
		}
		else
		{
			if (value->getType() != nil_m)
			{
				s2v->second.clear();
				s2v->second.assign(value);
			}
			else
			{
				s2v->second.clear();
				boolToValue.erase(s2v);
			}
		}
		return;
	}	
	case userfunc_m:
	{
		auto s2v = userFuncToValue.find(key->data.funcVal);
		if (s2v == userFuncToValue.end())
		{
			if (value->getType() != nil_m)
				userFuncToValue[key->data.funcVal].assign(value);
		}
		else
		{
			if (value->getType() != nil_m)
			{
				s2v->second.clear();
				s2v->second.assign(value);
			}
			else
			{
				s2v->second.clear();
				userFuncToValue.erase(s2v);
			}
		}
		return;
	}	
	case libfunc_m:
	{
		auto s2v = libFuncToValue.find(key->data.libfuncVal);
		if (s2v == libFuncToValue.end())
		{
			if (value->getType() != nil_m)
				libFuncToValue[key->data.libfuncVal].assign(value);
		}
		else
		{
			if (value->getType() != nil_m)
			{
				s2v->second.clear();
				s2v->second.assign(value);
			}
			else
			{
				s2v->second.clear();
				libFuncToValue.erase(s2v);
			}
		}
		return;
	}	
	case table_m:
	{
		auto s2v = AVM_TableToValue.find(key->data.tableVal);
		if (s2v == AVM_TableToValue.end())
		{
			if (value->getType() != nil_m)
				AVM_TableToValue[key->data.tableVal].assign(value);
		}
		else
		{
			if (value->getType() != nil_m)
			{
				s2v->second.clear();
				s2v->second.assign(value);
			}
			else
			{
				s2v->second.clear();
				AVM_TableToValue.erase(s2v);
			}
		}
		return;
	}		
	default:
		error(Error, __currentLine__, "Unsupported table index type %s\n");
	}
}

unsigned AVM_Table::getSerialNo() {
	return serialNo;
}

std::string AVM_Table::toString_Util(std::map<AVM_Table *, bool> visited) {
	std::string toReturn;
	std::ostringstream out;
    std::string tmp;
        
	toReturn = "[ ";

	visited[this] = true;

	for (std::map<double, AVM_MemCell>::iterator it = numberToValue.begin();
		 it != numberToValue.end(); it++)
	{    
		out << std::setprecision(3) << it->first;
		toReturn += "{ " + out.str() + " : ";
		if (it->second.getType() == table_m && visited.find(it->second.data.tableVal) != visited.end()) {
			toReturn += std::string("table #") + std::to_string(it->second.data.tableVal->serialNo) + " }, ";
		} else {
			tmp = it->second.getType() == table_m ? it->second.data.tableVal->toString_Util(visited) : it->second.toString();
	    	toReturn += (it->second.getType() == 
                                    string_m ? "\"" + tmp + "\"" : tmp) + " }, ";
		}
		out.str(std::string());
	}

	for (std::map<std::string, AVM_MemCell>::iterator it = stringToValue.begin();
		 it != stringToValue.end(); it++)
	{
		toReturn += "{ \"" + it->first + "\" : ";
		if (it->second.getType() == table_m && visited.find(it->second.data.tableVal) != visited.end()) {
			toReturn += std::string("table #") + std::to_string(it->second.data.tableVal->serialNo) + " }, ";
		} else {
        	tmp = it->second.getType() == table_m ? it->second.data.tableVal->toString_Util(visited) : it->second.toString();
			toReturn += (it->second.getType() 
                                   == string_m ? "\"" + tmp + "\"" : tmp) + " }, ";
		}
	}
        
        for (std::map<bool, AVM_MemCell>::iterator it = boolToValue.begin();
		 it != boolToValue.end(); it++)
	{
		toReturn += "{ " + (it->first ? std::string("true") : 
                    std::string("false")) + " : " ;
		if (it->second.getType() == table_m && visited.find(it->second.data.tableVal) != visited.end()) {
			toReturn += std::string("table #") + std::to_string(it->second.data.tableVal->serialNo) + " }, ";
		} else {
        	tmp = it->second.getType() == table_m ? it->second.data.tableVal->toString_Util(visited) : it->second.toString();
			toReturn += (it->second.getType() == 
                                    string_m ? "\"" + tmp + "\"" : tmp) + " }, ";
		}
	}
        
        for (std::map<AVM_Table *, AVM_MemCell>::iterator it = AVM_TableToValue.begin();
		 it != AVM_TableToValue.end(); it++)
	{
		toReturn += "{ " + it->first->toString() + " : ";
		if (it->second.getType() == table_m && visited.find(it->second.data.tableVal) != visited.end()) {
			toReturn += std::string("table #") + std::to_string(it->second.data.tableVal->serialNo) + " }, ";
		} else {
            tmp = it->second.getType() == table_m ? it->second.data.tableVal->toString_Util(visited) : it->second.toString();
			toReturn += (it->second.getType()
                                == string_m ? "\"" + tmp + "\"" : tmp) + " }, ";
		}
	}
        
        for (std::map<unsigned, AVM_MemCell>::iterator it = userFuncToValue.begin();
		 it != userFuncToValue.end(); it++)
	{
		toReturn += "{ " + std::string("user function ") + 
                        std::to_string(it->first) + " : ";
		if (it->second.getType() == table_m && visited.find(it->second.data.tableVal) != visited.end()) {
			toReturn += std::string("table #") + std::to_string(it->second.data.tableVal->serialNo) + " }, ";
		} else {
            tmp = it->second.getType() == table_m ? it->second.data.tableVal->toString_Util(visited) : it->second.toString();
			toReturn += (it->second.getType()
                                == string_m ? "\"" + tmp + "\"" : tmp) + " }, ";
		}
	}
        
        for (std::map<std::string, AVM_MemCell>::iterator it = libFuncToValue.begin();
		 it != libFuncToValue.end(); it++)
	{
		toReturn += "{ " + std::string("library function ") + it->first 
                        + " : ";
		if (it->second.getType() == table_m && visited.find(it->second.data.tableVal) != visited.end()) {
			toReturn += std::string("table #") + std::to_string(it->second.data.tableVal->serialNo) + " }, ";
		} else {
            tmp = it->second.getType() == table_m ? it->second.data.tableVal->toString_Util(visited) : it->second.toString();
			toReturn += (it->second.getType() == string_m ? "\"" + tmp
                                                            + "\"" : tmp) + " }, ";
		}
	}
        
    if(toReturn == "[ ") toReturn = " [ ] ";
	else if (toReturn[toReturn.length()-2] == ',') toReturn.replace(toReturn.length() - 2, 2, " ] ");

	return toReturn;
}

std::string AVM_Table::toString()
{
	std::map<AVM_Table *, bool> visited;
	return toString_Util(visited);
}

unsigned int AVM_Table::getTotalMembers()
{
	return numberToValue.size() + stringToValue.size() + boolToValue.size() +
		   AVM_TableToValue.size() + userFuncToValue.size() + libFuncToValue.size();
}

std::vector<AVM_MemCell> AVM_Table::getKeys(){
    std::vector<AVM_MemCell> toReturn;      
    
    AVM_MemCell cell;
    
    for(std::map<double, AVM_MemCell>::iterator it = numberToValue.begin(); it != numberToValue.end(); it++){
        cell.setType(number_m);
        cell.data.numVal = it->first;
        toReturn.push_back(cell);
    }
    
    for(std::map<std::string, AVM_MemCell>::iterator it = stringToValue.begin(); it != stringToValue.end(); it++){
        cell.setType(string_m);
        cell.data.strVal = strdup(it->first.c_str());
        toReturn.push_back(cell);
    }
    
    for(std::map<bool, AVM_MemCell>::iterator it = boolToValue.begin(); it != boolToValue.end(); it++){
        cell.setType(bool_m);
        cell.data.boolVal = it->first;
        toReturn.push_back(cell);
    }
    
    for(std::map<AVM_Table *, AVM_MemCell>::iterator it = AVM_TableToValue.begin(); it != AVM_TableToValue.end(); it++){
       cell.setType(table_m);
       cell.data.tableVal = it->first;
       toReturn.push_back(cell);
    }
    
    for(std::map<unsigned, AVM_MemCell>::iterator it = userFuncToValue.begin(); it != userFuncToValue.end(); it++){
        cell.setType(userfunc_m);
        cell.data.funcVal = it->first;
        toReturn.push_back(cell);
    }    
    
    for(std::map<std::string, AVM_MemCell>::iterator it = libFuncToValue.begin(); it != libFuncToValue.end(); it++){
        cell.setType(libfunc_m);
        cell.data.libfuncVal = strdup(it->first.c_str());
        toReturn.push_back(cell);
    } 
    
    return toReturn;
 }
  
std::vector<AVM_MemCell> AVM_Table::getValues(){
	std::vector<AVM_MemCell> toReturn;

	for(std::map<double, AVM_MemCell>::iterator it = numberToValue.begin(); it != numberToValue.end(); it++){        
		toReturn.push_back(it->second);
	}

	for(std::map<std::string, AVM_MemCell>::iterator it = stringToValue.begin(); it != stringToValue.end(); it++){
		toReturn.push_back(it->second);
	}

	for(std::map<bool, AVM_MemCell>::iterator it = boolToValue.begin(); it != boolToValue.end(); it++){
		toReturn.push_back(it->second);
	}

	for(std::map<AVM_Table *, AVM_MemCell>::iterator it = AVM_TableToValue.begin(); it != AVM_TableToValue.end(); it++){
		toReturn.push_back(it->second);
	}

	for(std::map<unsigned, AVM_MemCell>::iterator it = userFuncToValue.begin(); it != userFuncToValue.end(); it++){
		toReturn.push_back(it->second);
	}    

	for(std::map<std::string, AVM_MemCell>::iterator it = libFuncToValue.begin(); it != libFuncToValue.end(); it++){
		toReturn.push_back(it->second);
	} 

	return toReturn;      
}  



AVM_Table::~AVM_Table(){

}