#include <stdlib.h>
#include <fstream>
#include "alpha_yyFlexLexer.h"



int main(int argc, char** argv) {
    int i;
    alpha_yyFlexLexer* lexer = NULL;
    std::ifstream ifs;
    std::ofstream ofs;
    if (argc > 1) {
        ifs.open(argv[1],  std::ios::in);
        if (!ifs.is_open()) {
            fprintf(stderr, RED "ERROR" CR ":Unable to open input file\n");
            return 1;
        }
        if (argc > 2) {
            ofs.open(argv[2], std::ios::out);
            if (!ofs.is_open()) {
                fprintf(stderr, RED "ERROR" CR ":Unable to open output file\n");
                return 2;
            }
            lexer = new alpha_yyFlexLexer(&ifs, &ofs);
        } else {
            lexer = new alpha_yyFlexLexer(&ifs);
        }
    } else {
        lexer = new alpha_yyFlexLexer();
    }
	alpha_token_t currentToken;
    while ((i = lexer->alpha_yylex(&currentToken)) != 0){
        if (i == -2) fprintf(stderr, RED "INVALID TOKEN" CR ":%s\n", tokenToString(currentToken).c_str());
		else fprintf(stderr, GREEN "READ TOKEN" CR ":%s", tokenToString(currentToken).c_str());
	}
    lexer->printer();/*cumulatively prints all tokens*/
    return 0;
}