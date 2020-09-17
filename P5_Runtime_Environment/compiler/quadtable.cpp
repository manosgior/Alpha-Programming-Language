#include "quadtable.h"
#include "TCodeDispatcher.h"
#include <assert.h>
#include <iomanip>

QuadTable::QuadTable() {
    cpq = 0;
    quads = std::vector<quad>();
}

void QuadTable::emit(iopcode o, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line){
    quad q = {o, result, arg1, arg2, label, line};
    quads.push_back(q);
}

unsigned QuadTable::nextQuadLabel() {
    return quads.size() + 1;
}

void QuadTable::patchLabel(unsigned quadNo, unsigned label) {
    assert(quadNo < quads.size()+1);
    quads[quadNo-1].label = label;
}

void QuadTable::printQuads(std::ostream& ofs) {
    ofs << "\n\n" <<
    std::left << std::setw(8) << "Quad#" << std::setw(15) << "opcode" << std::setw(10) << "result" << std::setw(10) << "arg1"<< std::setw(10) <<  "arg2" << std::endl;
    for (unsigned int i = 0; i < quads.size(); i++) {
        ofs << std::left << std::setw(8) << std::to_string(i + 1) + ":" << std::setw(15) << opcode2string[quads[i].op] << std::setw(10) << (quads[i].label > 0 ? std::to_string(quads[i].label) : (quads[i].result != nullptr) ? quads[i].result->toString() : "") << 
           std::setw(10) << ((quads[i].arg1 != nullptr) ? quads[i].arg1->toString() : "") << std::setw(10) << ((quads[i].arg2 != nullptr) ? quads[i].arg2->toString() : "") << std::endl;      
    }
}

void QuadTable::altPrintQuads(std::ostream& ofs){
    ofs << "\n\n";
    
    for (unsigned int i = 0; i < quads.size(); i++) {
        ofs << std::to_string(i + 1) + ": " << opcode2string[quads[i].op] << " " << ((quads[i].result != nullptr) ? quads[i].result->toString() + " " : "") << 
          ((quads[i].arg1 != nullptr) ? quads[i].arg1->toString() + " " : "") << ((quads[i].arg2 != nullptr) ? quads[i].arg2->toString() + " " : "")  << (quads[i].label > 0 ? std::to_string(quads[i].label) + " " : "") << "[line " + std::to_string(quads[i].line) + "]" << std::endl;      
    }
   
}

quad QuadTable::getQuad(unsigned index){
    assert(index > 0 && index <= quads.size());
    return quads[index - 1];
}

size_t QuadTable::size() {
    return quads.size();
}

void QuadTable::convertToTargetCode() {
    for (size_t i = 0; i < quads.size(); i++) {
        cpq++;
        (*generators[quads[i].op])(quads[i]);
    }
}

unsigned QuadTable::currProcessedQuad() {
    return cpq;
}