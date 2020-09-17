 CPPFLAGS = -Wall -std=c++11
 .PHONY: clean

all: ap.out
	rm -f *.o

ap.out: alpha_lexer.o alpha_parser.o alpha_yyFlexLexer.o ap.cpp symtable.o function_actions.o error_handler.o
	g++ $(CPPFLAGS) alpha_lexer.o alpha_parser.o alpha_yyFlexLexer.o ap.cpp symtable.o infoStorage.o function_actions.o error_handler.o -o ap.out 

alpha_lexer.cpp: yyalpha.l alpha_parser.cpp alpha_parser.hpp 
	flex yyalpha.l 

alpha_parser.o: alpha_parser.cpp
	g++ $(CPPFLAGS) -c alpha_parser.cpp 

alpha_parser.cpp: alpha_parser.y symtable.h function_actions.h error_handler.h
	bison --yacc alpha_parser.y

alpha_yyFlexLexer.o: alpha_yyFlexLexer.cpp
	g++ $(CPPFLAGS) -c alpha_yyFlexLexer.cpp

alpha_lexer.o: alpha_lexer.cpp error_handler.h
	g++ $(CPPFLAGS) -c alpha_lexer.cpp

symtable.o: symtable.cpp infoStorage.cpp
	g++ $(CPPFLAGS) -c symtable.cpp infoStorage.cpp

function_actions.o: function_actions.cpp
	g++ $(CPPFLAGS) -c function_actions.cpp	

error_handler.o: error_handler.cpp
	g++ $(CPPFLAGS) -c error_handler.cpp

clean:
	rm -f *.out *.o alpha_lexer.cpp alpha_parser.cpp alpha_parser.hpp