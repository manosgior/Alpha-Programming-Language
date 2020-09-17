#include "instructiontable.h"
#include "quadtable.h"

extern QuadTable quad_table;

InstructionTable::InstructionTable() {
    
}

void InstructionTable::emit(Instruction newInstruction){
    instructions.push_back(newInstruction);
}

void InstructionTable::exportByteCode(std::ofstream& os){
    std::string buffer;
    unsigned int magic_number = 340200501;
    size_t tmp = constStrings.size();
    os.write((char *) &magic_number, sizeof(unsigned int));
    os.write((char *) &tmp, sizeof(size_t));
    for (std::string s : constStrings) {
        os.write(s.c_str(), s.size()+1);
    }
    tmp = constNums.size();
    os.write((char *) &tmp, sizeof(size_t));
    for (double i : constNums) {
        os.write((char *)&i, sizeof(double));
    }
    tmp = userFuncs.size();
    os.write((char *) &tmp, sizeof(size_t));
    for (userFuncInfo i : userFuncs) {
        os.write((char *)&(i.address), sizeof(unsigned));
        os.write((char *)&(i.localsize), sizeof(unsigned));
        os.write((char *)i.id.c_str(), i.id.size()+1);
    }
    tmp = libFuncNames.size();
    os.write((char *) &tmp, sizeof(size_t));
    for (std::string l : libFuncNames) {
        os.write((char *)l.c_str(), l.size()+1);
    }
    tmp = instructions.size();
    os.write((char *) &tmp, sizeof(size_t));
    for(auto it = instructions.begin(); it != instructions.end(); it++){
        (*it).exportByteCode(os);
    }
}

unsigned int InstructionTable::newNumConst(double constNum){
    for(size_t i = 0; i < constNums.size(); i++){
        if(constNums[i] == constNum) return i;
    }
    constNums.push_back(constNum);
    return constNums.size()-1;
}

unsigned int InstructionTable::newStringConst(std::string constString){
    for(size_t i = 0; i < constStrings.size(); i++){
        if(constStrings[i] == constString) return i;
    }
    constStrings.push_back(constString);
    return constStrings.size()-1;
}

unsigned int InstructionTable::newLibFunc(std::string libFuncName){
    for(size_t i = 0; i < libFuncNames.size(); i++){
        if(libFuncNames[i] == libFuncName) return i;
    }
    libFuncNames.push_back(libFuncName);
    return libFuncNames.size()-1;
}

void InstructionTable::addIncompleteJump(unsigned tCodeINum, unsigned iCodeJAddr) {
    incompleteJumps.push_back(std::pair<unsigned, unsigned>(tCodeINum, iCodeJAddr));
}

void InstructionTable::patchIncompleteJumps() { 
    for (auto x : incompleteJumps) {
        if (x.second == quad_table.size()+1) {
            instructions[x.first-1].patchLabel(instructions.size()+1);
        } else {
            instructions[x.first-1].patchLabel(quad_table.getQuad(x.second).TCodeAddress);
        }
    }
}

size_t InstructionTable::size() {
    return instructions.size();
}

size_t InstructionTable::nextInstructionLabel() {
    return instructions.size() + 1;
}

void InstructionTable::addUserFunc(unsigned address, unsigned localsize, std::string id) {
    userFuncInfo tmp = {address, localsize, id};
    userFuncs.push_back(tmp);
}

void InstructionTable::printTable(std::ostream& ofs){
	ofs << "------------------------- Library Function names -------------------------" << std::endl;
	
	for(size_t i  = 0; i < libFuncNames.size(); i++){
		ofs << " \"" + libFuncNames[i] + "\" at index " + std::to_string(i) << std::endl;
	}
	ofs << std::endl;
	
	ofs << "------------------------- String constants -------------------------" << std::endl;
	
	for(size_t i  = 0; i < constStrings.size(); i++){
		ofs << " \"" + constStrings[i] + "\" at index " + std::to_string(i) << std::endl;
	}
	ofs << std::endl;
	
	ofs << "------------------------- Number constants -------------------------" << std::endl;
	
	for(size_t i  = 0; i < constNums.size(); i++){
		ofs << " \"" + std::to_string(constNums[i]) + "\" at index " + std::to_string(i) << std::endl;
	}
	ofs << std::endl;
	
	ofs << "------------------------- Target code -------------------------" << std::endl;
	
	ofs << std::left << std::setw(15) << "Instruction#" << std::setw(15) << "opcode" << 
	std::setw(15) << "result" << std::setw(15) << "arg1"<< std::setw(15) <<  "arg2"  << std::setw(15) << "line" << std::endl;
	
    for (size_t i = 0; i < instructions.size(); i++) {
        ofs << std::left << std::setw(15) << std::to_string(i + 1) + ":" << std::setw(15) << opcode2string[instructions[i].getOpcode()] <<
         std::setw(15) << instructions[i].getResult().toString() << std::setw(15) << instructions[i].getArg1().toString() << 
         std::setw(15) << std::setw(15) << instructions[i].getArg2().toString() << std::setw(15) << instructions[i].getLine() << std::endl;      
    }
}

