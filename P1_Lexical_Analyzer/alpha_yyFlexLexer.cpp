#include "alpha_yyFlexLexer.h"
#include <sstream>
#include <string>
#include <iomanip>

std::string supertype_names[] = { "INVALID_TOKEN_TYPE", "KEYWORD", "OPERATOR", "INTCONST", "REALCONST", "STRING", "PUNCTUATION", "ID", "COMMENT" };
std::string subtype_names[] = {
	"NO_SUBTYPE",
	/*KEYWORDS*/
	"IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL",
	"TRUE", "FALSE", "NIL",
	/*OPERATORS*/
	"ASSIGNMENT", "PLUS", "MINUS", "MULTIPLICATION", "DIVISION", "MODULO", "EQUAL", "NOT_EQUAL",
	"PLUS_PLUS", "MINUS_MINUS", "GREATER_THAN", "LESS_THAN", "GREATER_OR_EQUAL",
	"LESS_OR_EQUAL",
	/*PUNCTUATIONS*/
	"LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PAREN", "RIGHT_PAREN",
	"SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOT_DOT",
	/*COMMENTS*/
	"BLOCK_COMMENT", "LINE_COMMENT"
};

std::string tokenToString(alpha_token_t t) {	
	std::stringstream os;
	std::string tmp1, tmp2, tmp3;
	tmp1 += std::to_string(std::get<0>(t));
	tmp1 += ":";
	tmp2 += "\"" + std::get<2>(t)  + "\"";
	os << std::left << std::setw(5) << tmp1 << "  " << "#" << std::setw(5) << std::get<1>(t) << "  " << std::setw(15) << tmp2 <<  std::setw(15) << supertype_names[std::get<3>(t)] << "  ";
	switch (std::get<3>(t)) {
		case(INTCONST):
			os <<  std::left << std::setw(15) << strtol(std::get<2>(t).c_str(), NULL, 0) << "<- integer" << std::endl;
			break;
		case(REALCONST):
			os << std::left << std::setw(15) << atof(std::get<2>(t).c_str()) << "<- double" << std::endl;
			break;
		case(STRING):			
			tmp3 += "\"" + std::get<2>(t) + "\"";
			os << std::left << std::setw(15) <<tmp3 << "<- std::string" << std::endl;
			break;
		case(ID):
			tmp3 += "\"" + std::get<2>(t) + "\"";
			os << std::left << std::setw(15) <<tmp3 << "<- std::string" << std::endl;
			break;
		default:
			os << std::left << std::setw(15) << subtype_names[std::get<4>(t)] << "<- enumerated" << std::endl;
	}
	return os.str();
}

#ifdef LATEST_AND_GREATEST
alpha_yyFlexLexer::alpha_yyFlexLexer(std::istream& is, std::ostream& os) : yyFlexLexer(is, os){
	tokens = std::vector<alpha_token_t>();
	numberOfTokens = 0;
}
#endif

alpha_yyFlexLexer::alpha_yyFlexLexer(std::istream * is, std:: ostream * os) : yyFlexLexer(is, os){
	tokens = std::vector<alpha_token_t>();
	numberOfTokens = 0;
}

int alpha_yyFlexLexer::alpha_yylex(void * yylval) {
	alpha_token_t * token = (alpha_token_t *) yylval; //memory provided by caller
	alpha_token_t temp; //used only to generate bad token 
	int i, prev = numberOfTokens; 
	if (token == NULL) return -1; //if user gave bad memory
	if (buffer.size() == 0) { //if buffer empty, produce some tokens
		if ((i = yylex()) == 0) return 0; //call yylex(), if input stream empty, return
		else if (i == -1) { //bad token
			std::get<0>(temp) = yylineno;
			std::get<1>(temp) = 0;
			std::get<2>(temp) = yytext;
			std::get<3>(temp) = INVALID_TOKEN_TYPE;
			std::get<4>(temp) = NO_SUBTYPE;
			buffer.push_back(temp);
		} else { //we read 1 or more tokens
			//starting from previous numberOfTokens, to the current, add to buffer
			for (i = numberOfTokens-1; i >= prev; i--) {
				buffer.push_back(tokens[i]);
			}
		}
	} //buffer operations completed
	//get the last element added and return it. 
	std::get<0>(*token) = std::get<0>(buffer[buffer.size()-1]);
	std::get<1>(*token) = std::get<1>(buffer[buffer.size()-1]);
	std::get<2>(*token) = std::get<2>(buffer[buffer.size()-1]);
	std::get<3>(*token) = std::get<3>(buffer[buffer.size()-1]);
	std::get<4>(*token) = std::get<4>(buffer[buffer.size()-1]);
	buffer.pop_back();
	return 1;
}

void alpha_yyFlexLexer::printer() {
	std::string acc = "";
	acc  += "Line#  Token#  Token	      Type	       Subtype	      C++ type\n";
	for (alpha_token_t t : tokens) {
		acc += tokenToString(t);
	}
	LexerOutput(acc.c_str(), acc.length());
}

void alpha_yyFlexLexer::addToken(const char * content, supertype_enum supertype, subtype_enum subtype, int lineno) {
	alpha_token_t temp = std::make_tuple(lineno == -1 ? yylineno : lineno, ++numberOfTokens, std::string(content), supertype, subtype);
	tokens.push_back(temp);
}
