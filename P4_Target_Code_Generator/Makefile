 CPPFLAGS = -Wall -std=c++11 -g
 .PHONY: clean

all: alphac.out
	rm -f *.o

alphac.out: alpha_lexer.o alpha_parser.o alpha_yyFlexLexer.o ap.cpp symtable.o function_actions.o error_handler.o tempManagement.o quadtable.o expression.o instruction.o instructiontable.o VMarg.o instruction_generators.o
	g++ $(CPPFLAGS) alpha_lexer.o alpha_parser.o alpha_yyFlexLexer.o ap.cpp symtable.o infoStorage.o function_actions.o error_handler.o tempManagement.o quadtable.o expression.o instruction.o instructiontable.o VMarg.o instruction_generators.o -o alphac.out 

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

tempManagement.o: tempManagement.cpp
	g++ $(CPPFLAGS) -c tempManagement.cpp

quadtable.o: quadtable.cpp quads.h
	g++ $(CPPFLAGS) -c quadtable.cpp

expression.o: expression.cpp quads.h
	g++ $(CPPFLAGS) -c expression.cpp

instruction.o: instruction.cpp instruction.h
	g++ $(CPPFLAGS) -c instruction.cpp

instructiontable.o: instructiontable.cpp instructiontable.h 
	g++ $(CPPFLAGS) -c instructiontable.cpp

VMarg.o: VMarg.cpp VMarg.h 
	g++ $(CPPFLAGS) -c VMarg.cpp

instruction_generators.o: instruction_generators.cpp instruction_generators.h
	g++ $(CPPFLAGS) -c instruction_generators.cpp

clean:
	rm -f *.out *.o alpha_lexer.cpp alpha_parser.cpp alpha_parser.hpp