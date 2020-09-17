#include <stdlib.h>
#include <fstream>
#include "alpha_yyFlexLexer.h"
#include "symtable.h"
#include "expression.h"
#include "quadtable.h"
#include "instructiontable.h"
#include "function_actions.h"
#include "alpha_parser.hpp"
#include "error_handler.h"
#define BON "\e[1m"
#define BOFF "\e[0m"

#define PRINT_VALSAMAKIS

alpha_yyFlexLexer * lexer;
extern SymTable symbol_table;
extern QuadTable quad_table;
extern InstructionTable instruction_table;
extern bool errorExists;

int main(int argc, char** argv) {
    lexer = NULL;
    std::ifstream ifs;
    std::ofstream ofs; 
    std::string outname = "a.abc";
    if (argc > 1) {
        error_handler_init(argv[1]);
        ifs.open(argv[1],  std::ios::in);
        if (!ifs.is_open()) {
            //fprintf(stderr, "Unable to open input file \n");
            error(ErrorType::FatalError, 0, "Unable to open input file " BON "\'%s\'" BOFF "\n", argv[1]);
            return 1;
        }
        if (argc > 2) {
            outname = argv[2];  
        } 
        lexer = new alpha_yyFlexLexer(&ifs); 
    } else {
        const char * dfname = "stdin";
        error_handler_init(dfname);
        lexer = new alpha_yyFlexLexer();
    }
    yyparse();
    if (!errorExists) {
        symbol_table.PrintTable();
    }
    if(!errorExists)
#ifdef PRINT_VALSAMAKIS
        quad_table.altPrintQuads(std::cout);
#else
        quad_table.printQuads(std::cout);
#endif
    if (!errorExists) {
        quad_table.convertToTargetCode();
        instruction_table.patchIncompleteJumps();
	    instruction_table.printTable(std::cout);
    }  
	std::ofstream binout;
    binout.open(outname.c_str(), std::ios::out | std::ios::binary);
    if (!errorExists) instruction_table.exportByteCode(binout);
    error_handler_destroy();
    ifs.close();
    ofs.close();
    binout.close();
    return 0;
}
