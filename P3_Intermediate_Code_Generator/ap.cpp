#include <stdlib.h>
#include <fstream>
#include "alpha_yyFlexLexer.h"
#include "symtable.h"
#include "expression.h"
#include "quadtable.h"
#include "function_actions.h"
#include "alpha_parser.hpp"
#include "error_handler.h"
#define BON "\e[1m"
#define BOFF "\e[0m"

#define PRINT_VALSAMAKIS

alpha_yyFlexLexer * lexer;
extern SymTable symbol_table;
extern QuadTable quad_table;
extern bool errorExists;

int main(int argc, char** argv) {
    lexer = NULL;
    std::ifstream ifs;
    std::ofstream ofs; 
    if (argc > 1) {
        error_handler_init(argv[1]);
        ifs.open(argv[1],  std::ios::in);
        if (!ifs.is_open()) {
            //fprintf(stderr, "Unable to open input file \n");
            error(ErrorType::FatalError, 0, "Unable to open input file " BON "\'%s\'" BOFF "\n", argv[1]);
            return 1;
        }
        if (argc > 2) {
            ofs.open(argv[2], std::ios::out);
            if (!ofs.is_open()) {
                //fprintf(stderr, "Unable to open output file\n");
                error(ErrorType::FatalError, 0, "Unable to open output file " BON "\'%s\'" BOFF "\n", argv[2]);
                return 2;
            }
            lexer = new alpha_yyFlexLexer(&ifs, &ofs);
        } else { 
            lexer = new alpha_yyFlexLexer(&ifs); 
        }
    } else {
        const char * dfname = "stdin";
        error_handler_init(dfname);
        lexer = new alpha_yyFlexLexer();
    }
    yyparse();
    symbol_table.PrintTable();
    if(!errorExists)
#ifdef PRINT_VALSAMAKIS
        quad_table.altPrintQuads(std::cout);
#else
        quad_table.printQuads(std::cout);
#endif
    error_handler_destroy();
    ifs.close();
    ofs.close();
    return 0;
}