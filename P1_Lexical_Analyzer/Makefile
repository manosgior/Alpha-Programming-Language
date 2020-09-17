 CPPFLAGS = -Wall -std=c++11
 .PHONY: clean

all: al.out
	rm -f *.o

al.out: alpha_lexer.o alpha_yyFlexLexer.o al.cpp
	g++ $(CPPFLAGS) alpha_lexer.o alpha_yyFlexLexer.o al.cpp -o al.out

alpha_lexer.o: alpha_lexer.cpp
	g++ $(CPPFLAGS) -c alpha_lexer.cpp

alpha_yyFlexLexer.o: alpha_yyFlexLexer.cpp
	g++ $(CPPFLAGS) -c alpha_yyFlexLexer.cpp

alpha_lexer.cpp: yyalpha.l
	flex yyalpha.l

clean:
	rm -f *.out *.o alpha_lexer.cpp