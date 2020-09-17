%{
	#if defined(WIN32)
	#define YY_NO_UNISTD_H
	static int isatty(int i) { return 0;}
	#elif defined(_WIN32_WCE)
	#define YY_NO_UNISTD_H
	static int isatty(void *i) {return 0;}
	#endif
	
	#include <stdlib.h>
	#include <fstream>
	#include <stack>
	#include <sstream>
	#include "alpha_yyFlexLexer.h"

	#define CR "\x1b[0m"
  	#define RED "\x1b[31m"
  	#define YELLOW "\x1b[33m"
  	#define CYAN "\x1b[36m"
  	#define GREEN "\x1b[32m"
  	//#define DEBUG
  	//#define STRCAT
%}

%option c++
%option yyclass = "alpha_yyFlexLexer"
%option outfile = "alpha_lexer.cpp"
%option yylineno
%option noyywrap

id 				[a-zA-Z][a-zA-Z_0-9]*
integer 		((0[xX][0-9A-Fa-f]+)|([0-9]+))
real 			(([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+))((e|E)([-+]?)[0-9]+)?    
space 			[\r \t\v]
newline 		\n
line_comment	"//".*

%%

{space}

{newline}


{integer}				{
							addToken(yytext, INTCONST, NO_SUBTYPE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized integer with value: %ld\n", strtol(yytext, NULL, 0));
							#endif
							return 1;
						}
{real}					{
							addToken(yytext, REALCONST, NO_SUBTYPE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized real with value: %f\n", atof(yytext));
							#endif
							return 1;

						}
if 						{
							addToken(yytext, KEYWORD, IF);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
else 					{
							addToken(yytext, KEYWORD, ELSE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
while 					{
							addToken(yytext, KEYWORD, WHILE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
for 					{
							addToken(yytext, KEYWORD, FOR);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
function 				{
							addToken(yytext, KEYWORD, FUNCTION);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
return 					{
							addToken(yytext, KEYWORD, RETURN);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
break 					{
							addToken(yytext, KEYWORD, BREAK);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
continue 				{
							addToken(yytext, KEYWORD, CONTINUE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
and 					{
							addToken(yytext, KEYWORD, AND);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
not 					{
							addToken(yytext, KEYWORD, NOT);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
or 						{
							addToken(yytext, KEYWORD, OR);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
local 					{
							addToken(yytext, KEYWORD, LOCAL);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
true 					{
							addToken(yytext, KEYWORD, TRUE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
false 					{
							addToken(yytext, KEYWORD, FALSE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
nil 					{
							addToken(yytext, KEYWORD, NIL);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized keyword with value: %s\n", yytext);
							#endif
							return 1;

						}
						
"+"						{
							addToken(yytext,OPERATOR,PLUS);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"-"						{
							addToken(yytext,OPERATOR,MINUS);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"="						{
							addToken(yytext,OPERATOR,ASSIGNMENT);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"*"						{
							addToken(yytext,OPERATOR,MULTIPLICATION);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"/"						{
							addToken(yytext,OPERATOR,DIVISION);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"%"						{
							addToken(yytext,OPERATOR,MODULO);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"=="					{
							addToken(yytext,OPERATOR,EQUAL);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"!="					{
							addToken(yytext,OPERATOR,NOT_EQUAL);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"++"					{
							addToken(yytext,OPERATOR,PLUS_PLUS);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"--"					{
							addToken(yytext,OPERATOR,MINUS_MINUS);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
">"						{
							addToken(yytext,OPERATOR,GREATER_THAN);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"<"						{
							addToken(yytext,OPERATOR,LESS_THAN);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
">="					{
							addToken(yytext,OPERATOR,GREATER_OR_EQUAL);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"<="					{
							addToken(yytext,OPERATOR,LESS_OR_EQUAL);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized operator with value: %s\n", yytext);
							#endif
							return 1;

						}
"{"						{
							addToken(yytext,PUNCTUATION,LEFT_BRACE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
"}"						{
							addToken(yytext,PUNCTUATION,RIGHT_BRACE);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
"["						{
							addToken(yytext,PUNCTUATION,LEFT_BRACKET);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
"]"						{
							addToken(yytext,PUNCTUATION,RIGHT_BRACKET);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
"("						{
							addToken(yytext,PUNCTUATION,LEFT_PAREN);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
")"						{
							addToken(yytext,PUNCTUATION,RIGHT_PAREN);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
";"						{
							addToken(yytext,PUNCTUATION,SEMICOLON);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
","						{
							addToken(yytext,PUNCTUATION,COMMA);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
":"						{
							addToken(yytext,PUNCTUATION,COLON);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
"::"					{
							addToken(yytext,PUNCTUATION,DOUBLE_COLON);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
"."						{
							addToken(yytext,PUNCTUATION,DOT);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}
".."					{
							addToken(yytext,PUNCTUATION,DOT_DOT);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized punctuation with value: %s\n", yytext);
							#endif
							return 1;

						}

{line_comment}			{ 
							addToken("",COMMENT,LINE_COMMENT);
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized comment with value: %s\n", yytext);
							#endif
							return 1;

						}
{id} 					{	
							addToken(yytext, ID, NO_SUBTYPE);							
							#ifdef DEBUG
							fprintf(stderr, CYAN "DEBUG" CR ":Recognized id with value: %s\n", yytext);
							#endif
							return 1;

						}

"/*"					{
							std::string dacc = "/*";
							std::stack<int> s = std::stack<int>();
                    		s.push(yylineno);
                    		while (!s.empty()) {
                        		int c = yyinput();
                        		dacc += c;
                        		if (c == 0 || c == EOF) {
                            		while (!s.empty()) {
                            			fprintf(stderr, RED "ERROR" CR ": Unclosed comment, starting on line: %d\n", s.top());
                            			s.pop();
                            		}
                            		return -1;
                        		}
                        		else if (c == '*') {
                            		if ((c = yyinput()) == '/') {
                            			dacc += c;
                                		int startno = s.top();
                                		s.pop();
                                		std::stringstream os;
                                		os << startno << " - " << yylineno;
                                		addToken(os.str().c_str(), COMMENT, BLOCK_COMMENT, startno);
                            		} else {
                                		unput(c);
                            		}	
                        		}
                        		else if (c == '/') {
                            		if ((c = yyinput()) == '*') {
                            			dacc += c;
                                		s.push(yylineno);
                            		} else {
                                		unput(c);
                            		}
                        		}
                    		}
							#ifdef DEBUG
                    		fprintf(stderr, CYAN "DEBUG" CR ":Recognized block comment with value: %s\n", dacc.c_str());
							#endif
                    		return 1;

                    	}

\"						{
							std::vector<char> my_yytext; 
							int curr = 0, tmp = 0, flag = 1, prop_closed = 0, ignore_white_space = 0;
							
							int	init_line_no = yylineno;
							while ((curr = yyinput()) != 0 && curr != EOF) {						
								if (curr == '\"') {	
									ignore_white_space = 0;								
									std::string my_yytext_for_real;
									for (auto i : my_yytext) my_yytext_for_real += i;										
									if (flag) {
										addToken(my_yytext_for_real.c_str(), STRING, NO_SUBTYPE, init_line_no);
										#ifdef DEBUG
										fprintf(stderr, CYAN "DEBUG" CR ":Recognized string with value: %s\n", my_yytext_for_real.c_str());
										#endif
										return 1;
									}
									prop_closed = 1;	
									break;															
								}
								else if (curr == '\\') {
									ignore_white_space = 0;
									tmp = yyinput();
									switch(tmp) {
										case 'n':
											my_yytext.push_back('\n');
											break;
										case 'v':
											my_yytext.push_back('\v');
											break;
										case 'r':
											my_yytext.push_back('\r');
											break; 
										case 't':
											my_yytext.push_back('\t'); 
											break;
										case '\\':
											my_yytext.push_back('\\');
											break;
										case '\"':
											my_yytext.push_back('\"');
											break;
										default:
											fprintf(stderr, RED "ERROR" CR ":Invalid escape character at line %d\n", yylineno);
											flag = 0;
									}
								}
								#ifdef STRCAT
								else if (curr == '\n') {
									ignore_white_space = 1;
								}
								#endif 
							    else if (!ignore_white_space || (curr != ' ' && curr != '\t')) {
									ignore_white_space = 0;
									my_yytext.push_back(curr);
								}
							}
							if (!prop_closed) fprintf(stderr, RED "ERROR" CR ":String opened at line %d but was not closed at line %d\n", init_line_no, yylineno);
							return -1;
						}

.				{ 
					fprintf(stderr, RED "ERROR" CR ":Cannot match character '%s', at line %d, with any rule!\n", yytext, yylineno); 
					return -1;
				}

%%
