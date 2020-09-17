/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "alpha_parser.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <string>
	#include <fstream>
	#include <assert.h>
	#include <list>
	#include <utility>
	#include "function_actions.h"
	#include "symtable.h"
	#include "expression.h"
	#include "defines_header.h"
	#include "error_handler.h"
	#include "quadtable.h"
	#include "instructiontable.h"
	#include "quads.h"
	#include "tempManagement.h"
	#define yylex() lexer->alpha_yylex()
	#define BON "\e[1m"
	#define BOFF "\e[0m"
	#define P3_DEBUG	
	int yyerror (char * yaccProvidedMessage);
	unsigned int getCurrentScope();
	void incrementScope();
	void decrementScope();
	void init();
	unsigned int scope = 0;
	Scope_Type nextScope = Scope_Type::invalid_scope;
	SymTable symbol_table = SymTable();
	QuadTable quad_table = QuadTable(); 
	InstructionTable instruction_table = InstructionTable();	

#line 98 "alpha_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "alpha_parser.hpp".  */
#ifndef YY_YY_ALPHA_PARSER_HPP_INCLUDED
# define YY_YY_ALPHA_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTCONST = 258,
    REALCONST = 259,
    STRINGCONST = 260,
    ID = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    AND = 270,
    NOT = 271,
    OR = 272,
    LOCAL = 273,
    TRUE = 274,
    FALSE = 275,
    NIL = 276,
    ASSIGNMENT = 277,
    PLUS = 278,
    MINUS = 279,
    MULTIPLICATION = 280,
    DIVISION = 281,
    MODULO = 282,
    EQUAL = 283,
    NOT_EQUAL = 284,
    PLUS_PLUS = 285,
    MINUS_MINUS = 286,
    GREATER_THAN = 287,
    LESS_THAN = 288,
    GREATER_OR_EQUAL = 289,
    LESS_OR_EQUAL = 290,
    LEFT_BRACE = 291,
    RIGHT_BRACE = 292,
    LEFT_BRACKET = 293,
    RIGHT_BRACKET = 294,
    LEFT_PAREN = 295,
    RIGHT_PAREN = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    DOUBLE_COLON = 300,
    DOT = 301,
    DOT_DOT = 302,
    COMMENT_TOKEN = 303,
    BAD_TOKEN = 304,
    UMINUS = 305
  };
#endif
/* Tokens.  */
#define INTCONST 258
#define REALCONST 259
#define STRINGCONST 260
#define ID 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define AND 270
#define NOT 271
#define OR 272
#define LOCAL 273
#define TRUE 274
#define FALSE 275
#define NIL 276
#define ASSIGNMENT 277
#define PLUS 278
#define MINUS 279
#define MULTIPLICATION 280
#define DIVISION 281
#define MODULO 282
#define EQUAL 283
#define NOT_EQUAL 284
#define PLUS_PLUS 285
#define MINUS_MINUS 286
#define GREATER_THAN 287
#define LESS_THAN 288
#define GREATER_OR_EQUAL 289
#define LESS_OR_EQUAL 290
#define LEFT_BRACE 291
#define RIGHT_BRACE 292
#define LEFT_BRACKET 293
#define RIGHT_BRACKET 294
#define LEFT_PAREN 295
#define RIGHT_PAREN 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define DOUBLE_COLON 300
#define DOT 301
#define DOT_DOT 302
#define COMMENT_TOKEN 303
#define BAD_TOKEN 304
#define UMINUS 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 37 "alpha_parser.y" /* yacc.c:355  */

	int    			  intValue;
	unsigned		  unsignedValue;
	double 			  doubleValue;
	char*  			  stringValue;
	expr*  			  exprValue;
    callInfo*         callInfoValue;
	std::list<expr*>* elistValue;
	indElem*		  indexedElement;
	indexedList* 	  indexedValue;
	objectInner*	  objectInnerValue;
	unsignedPair*  	  unsignedPairValue;
	stmtInfo*		  stmtInfoValue;

#line 253 "alpha_parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ALPHA_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 270 "alpha_parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   567

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   116,   116,   116,   118,   119,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   153,   155,   156,   157,
     158,   159,   160,   161,   164,   167,   171,   172,   173,   175,
     178,   183,   188,   193,   196,   200,   204,   205,   208,   210,
     212,   216,   218,   222,   226,   231,   232,   236,   239,   240,
     244,   251,   252,   253,   257,   260,   261,   264,   264,   270,
     270,   273,   275,   278,   281,   284,   288,   291,   292,   293,
     294,   295,   296,   300,   305,   307,   312,   314,   316,   317,
     317,   320,   322,   324,   326,   328,   335,   335,   343,   344
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTCONST", "REALCONST", "STRINGCONST",
  "ID", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL",
  "ASSIGNMENT", "PLUS", "MINUS", "MULTIPLICATION", "DIVISION", "MODULO",
  "EQUAL", "NOT_EQUAL", "PLUS_PLUS", "MINUS_MINUS", "GREATER_THAN",
  "LESS_THAN", "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "LEFT_BRACE",
  "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PAREN",
  "RIGHT_PAREN", "SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT",
  "DOT_DOT", "COMMENT_TOKEN", "BAD_TOKEN", "UMINUS", "$accept", "program",
  "$@1", "stmts", "stmt", "expr", "$@2", "$@3", "$@4", "$@5", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "elistnotempty", "commalist",
  "objectdef", "objectdinner", "indexed", "commaindexed", "indexedelem",
  "$@6", "block", "$@7", "N", "M", "funcdef", "funcprefix", "funcname",
  "const", "idlist", "commaidlist", "ifprefix", "ifstmt", "$@8",
  "elseprefix", "whilestart", "whilecond", "whilestmt", "forprefix",
  "forstmt", "$@9", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -112

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-112)))

#define YYTABLE_NINF -97

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-97)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -112,     6,  -112,  -112,   158,   -32,  -112,  -112,  -112,  -112,
     -28,  -112,   -21,    11,   -16,    -9,    75,    33,  -112,  -112,
    -112,    75,     3,     3,  -112,    18,    75,  -112,    44,  -112,
     289,  -112,  -112,  -112,    79,  -112,   -18,  -112,  -112,    49,
    -112,  -112,   244,  -112,    15,  -112,  -112,  -112,  -112,  -112,
      75,    30,  -112,   310,  -112,  -112,  -112,  -112,  -112,  -112,
       0,   -18,     0,  -112,  -112,    75,    38,  -112,    39,   352,
      41,  -112,  -112,  -112,    75,    75,    75,    75,    75,  -112,
    -112,    75,    75,    75,    75,  -112,    75,  -112,  -112,    75,
      43,    80,    81,  -112,  -112,  -112,    75,    43,    82,    84,
      45,    89,    75,   244,    43,   373,    50,  -112,  -112,    57,
     201,   268,  -112,    75,    59,  -112,    63,  -112,  -112,    -2,
      -2,  -112,  -112,  -112,    75,    75,   532,   532,   532,   532,
     478,   415,    66,  -112,    64,   436,    67,  -112,  -112,  -112,
     108,  -112,  -112,   394,  -112,  -112,  -112,  -112,    63,  -112,
    -112,   478,  -112,    43,    75,    75,   506,   506,  -112,  -112,
      43,  -112,  -112,    77,   110,   244,  -112,    83,    75,    78,
      86,   519,   493,    88,    85,    87,  -112,  -112,   331,    75,
    -112,  -112,  -112,  -112,   244,  -112,   457,  -112,  -112,  -112
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     5,     1,     0,     0,    87,    88,    89,    50,
       0,   102,     0,     0,     0,     0,     0,     0,    91,    92,
      90,     0,     0,     0,    79,    69,    81,    15,     0,     4,
       0,    35,    17,    43,    45,    53,    46,    47,    13,     0,
      14,    49,     0,     7,     0,     8,    81,     9,    10,    16,
       0,    69,   109,     0,    11,    12,    38,    51,    37,    81,
      39,     0,    41,     5,    71,     0,     0,    72,     0,     0,
       0,    52,    31,    33,     0,     0,     0,     0,     0,    27,
      29,     0,     0,     0,     0,     6,     0,    40,    42,     0,
      69,     0,     0,    59,    61,    62,     0,    69,     0,    86,
       0,    98,     0,     0,    69,     0,     0,    65,   108,     0,
       0,    67,    70,     0,    74,    36,    48,    82,    82,    18,
      19,    20,    21,    22,     0,     0,    23,    25,    24,    26,
      44,     0,     0,    54,     0,     0,     0,    56,    85,    84,
      94,   101,    99,     0,   104,   106,    97,    82,     0,    80,
      68,    77,    75,    69,     0,     0,    28,    30,    55,    63,
      69,    57,    58,     0,     0,     0,   103,     0,     0,     0,
       0,    32,    34,     0,     0,    93,   100,    81,     0,     0,
      60,    64,    83,    95,     0,   105,     0,    81,    78,   107
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -112,  -112,  -112,    60,   -37,   -13,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,    22,  -112,    36,  -112,  -112,  -112,   -86,
     106,  -112,  -112,  -112,  -112,  -112,  -112,  -112,   -42,  -112,
     -44,  -111,   -25,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     4,    29,    30,   124,   125,   117,   118,
      31,    32,    33,    34,    35,    36,    93,    94,    95,   106,
     107,    65,    37,    66,    67,    68,   114,   169,    38,    63,
      39,   154,    40,   100,   139,    41,   163,   164,    42,    43,
     165,   142,    44,   103,    45,    46,    47,   167,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    70,   104,    56,   132,   101,     3,   155,    58,     9,
      49,   136,    50,    69,     6,     7,     8,     9,   145,    51,
      96,    17,    97,    76,    77,    78,    54,    16,    98,    17,
      18,    19,    20,    55,   109,    21,   168,   105,    89,    57,
      90,    22,    23,    59,    60,    62,    91,    92,    28,    25,
      71,    26,   111,    52,   -76,   102,    28,   -73,    61,    61,
      99,   119,   120,   121,   122,   123,   144,   170,   126,   127,
     128,   129,   -66,   130,   173,   113,   131,   112,     6,     7,
       8,     9,   116,   135,   -66,   140,   133,   134,   137,   143,
     138,    16,   147,    17,    18,    19,    20,   141,   148,    21,
     151,    86,   152,   153,   160,    22,    23,   159,   162,    87,
      88,   156,   157,    25,   -96,    26,   175,    89,   174,    90,
      28,    24,   179,   110,   177,    91,    92,   180,   176,   181,
     183,    64,   182,   184,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   189,     0,     0,     0,   187,     0,     0,
       0,     0,     0,     0,     0,   178,     0,     0,    -3,     5,
       0,     6,     7,     8,     9,    10,   186,    11,    12,   -81,
      13,    14,    15,     0,    16,     0,    17,    18,    19,    20,
       0,     0,    21,     0,     0,     0,     0,     0,    22,    23,
       0,     0,     0,     0,    24,     0,    25,     0,    26,     0,
      27,     0,     5,    28,     6,     7,     8,     9,    10,     0,
      11,    12,   -81,    13,    14,    15,     0,    16,     0,    17,
      18,    19,    20,     0,     0,    21,     0,     0,     0,     0,
       0,    22,    23,     0,     0,     0,     0,    24,   149,    25,
       0,    26,     0,    27,     0,     5,    28,     6,     7,     8,
       9,    10,     0,    11,    12,   -81,    13,    14,    15,     0,
      16,     0,    17,    18,    19,    20,     0,     0,    21,     0,
       0,     0,     0,     0,    22,    23,     0,     0,     0,     0,
      24,     0,    25,    72,    26,    73,    27,     0,     0,    28,
       0,    74,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    72,     0,    73,     0,     0,     0,
       0,   150,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84,    72,     0,    73,     0,     0,
       0,    85,     0,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,    72,     0,    73,     0,
       0,     0,   108,     0,    74,    75,    76,    77,    78,    79,
      80,     0,     0,    81,    82,    83,    84,    72,     0,    73,
       0,     0,     0,   185,     0,    74,    75,    76,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,    72,     0,
      73,     0,     0,   115,     0,     0,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,    72,
       0,    73,     0,     0,   146,     0,     0,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
      72,     0,    73,     0,     0,   166,     0,     0,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,    72,     0,    73,   158,     0,     0,     0,     0,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,    72,     0,    73,   161,     0,     0,     0,     0,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,    72,   188,    73,     0,     0,     0,     0,
       0,    74,    75,    76,    77,    78,    79,    80,    72,     0,
      81,    82,    83,    84,     0,     0,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,    74,
      75,    76,    77,    78,   -97,   -97,     0,     0,    81,    82,
      83,    84,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84,    74,    75,    76,    77,    78,
       0,     0,     0,     0,   -97,   -97,   -97,   -97
};

static const yytype_int16 yycheck[] =
{
      13,    26,    46,    16,    90,    42,     0,   118,    21,     6,
      42,    97,    40,    26,     3,     4,     5,     6,   104,    40,
      38,    18,    40,    25,    26,    27,    42,    16,    46,    18,
      19,    20,    21,    42,    59,    24,   147,    50,    38,     6,
      40,    30,    31,    40,    22,    23,    46,    47,    45,    38,
       6,    40,    65,    42,    36,    40,    45,    39,    22,    23,
      11,    74,    75,    76,    77,    78,   103,   153,    81,    82,
      83,    84,    42,    86,   160,    36,    89,    39,     3,     4,
       5,     6,    41,    96,    41,    40,     6,     6,     6,   102,
       6,    16,    42,    18,    19,    20,    21,     8,    41,    24,
     113,    22,    43,    40,    40,    30,    31,    41,    41,    30,
      31,   124,   125,    38,     6,    40,     6,    38,    41,    40,
      45,    36,    44,    63,    41,    46,    47,    41,   165,    41,
      43,    25,   174,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   154,   155,   187,    -1,    -1,    -1,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   168,    -1,    -1,     0,     1,
      -1,     3,     4,     5,     6,     7,   179,     9,    10,    11,
      12,    13,    14,    -1,    16,    -1,    18,    19,    20,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    40,    -1,
      42,    -1,     1,    45,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    14,    -1,    16,    -1,    18,
      19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    36,    37,    38,
      -1,    40,    -1,    42,    -1,     1,    45,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    14,    -1,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,
      36,    -1,    38,    15,    40,    17,    42,    -1,    -1,    45,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,
      -1,    43,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    -1,    17,    -1,    -1,
      -1,    42,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    15,    -1,    17,    -1,
      -1,    -1,    42,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    15,    -1,    17,
      -1,    -1,    -1,    42,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    15,    -1,
      17,    -1,    -1,    41,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    15,
      -1,    17,    -1,    -1,    41,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      15,    -1,    17,    -1,    -1,    41,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    15,    -1,    17,    39,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    15,    -1,    17,    39,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    37,    17,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    15,    -1,
      32,    33,    34,    35,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    53,     0,    54,     1,     3,     4,     5,     6,
       7,     9,    10,    12,    13,    14,    16,    18,    19,    20,
      21,    24,    30,    31,    36,    38,    40,    42,    45,    55,
      56,    61,    62,    63,    64,    65,    66,    73,    79,    81,
      83,    86,    89,    90,    93,    95,    96,    97,    99,    42,
      40,    40,    42,    56,    42,    42,    56,     6,    56,    40,
      64,    66,    64,    80,    71,    72,    74,    75,    76,    56,
      83,     6,    15,    17,    23,    24,    25,    26,    27,    28,
      29,    32,    33,    34,    35,    42,    22,    30,    31,    38,
      40,    46,    47,    67,    68,    69,    38,    40,    46,    11,
      84,    55,    40,    94,    81,    56,    70,    71,    42,    83,
      54,    56,    39,    36,    77,    41,    41,    59,    60,    56,
      56,    56,    56,    56,    57,    58,    56,    56,    56,    56,
      56,    56,    70,     6,     6,    56,    70,     6,     6,    85,
      40,     8,    92,    56,    55,    70,    41,    42,    41,    37,
      43,    56,    43,    40,    82,    82,    56,    56,    39,    41,
      40,    39,    41,    87,    88,    91,    41,    98,    82,    78,
      70,    56,    56,    70,    41,     6,    55,    41,    56,    44,
      41,    41,    79,    43,    81,    42,    56,    55,    37,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    53,    52,    54,    54,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    57,    56,    58,
      56,    59,    56,    60,    56,    56,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    63,    63,    63,    63,    63,
      64,    64,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    67,    67,    68,    69,    70,    70,    71,    72,    72,
      73,    74,    74,    74,    75,    76,    76,    78,    77,    80,
      79,    81,    82,    83,    84,    85,    85,    86,    86,    86,
      86,    86,    86,    87,    87,    88,    88,    89,    90,    91,
      90,    92,    93,    94,    95,    96,    98,    97,    99,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     0,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     5,     0,     5,     1,     3,     2,     2,     2,
       2,     2,     2,     1,     3,     1,     1,     1,     3,     1,
       1,     2,     2,     1,     3,     4,     3,     4,     4,     2,
       6,     1,     1,     3,     5,     1,     0,     2,     3,     0,
       3,     1,     1,     0,     2,     3,     0,     0,     6,     0,
       4,     0,     0,     6,     2,     1,     0,     1,     1,     1,
       1,     1,     1,     2,     0,     3,     0,     4,     2,     0,
       5,     1,     1,     3,     3,     7,     0,     8,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 5: /* STRINGCONST  */
#line 98 "alpha_parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).stringValue)); }
#line 1311 "alpha_parser.cpp" /* yacc.c:1257  */
        break;

    case 6: /* ID  */
#line 99 "alpha_parser.y" /* yacc.c:1257  */
      { free(((*yyvaluep).stringValue)); }
#line 1317 "alpha_parser.cpp" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 116 "alpha_parser.y" /* yacc.c:1646  */
    {init();}
#line 1581 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 118 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmts_stmtsR_stmt((yyvsp[-1].stmtInfoValue), (yyvsp[0].stmtInfoValue)); }
#line 1587 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 119 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmts(); }
#line 1593 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 121 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_expr_SEMICOLON((yyvsp[-1].exprValue)); reset_tmp(); }
#line 1599 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 122 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_ifstmt((yyvsp[0].stmtInfoValue)); }
#line 1605 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 123 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_default(); }
#line 1611 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 124 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_default(); }
#line 1617 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 125 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_returnstmt((yyvsp[0].stmtInfoValue)); }
#line 1623 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_BREAK(); }
#line 1629 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_CONTINUE(); }
#line 1635 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_block((yyvsp[0].stmtInfoValue)); }
#line 1641 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 129 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_default(); }
#line 1647 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 130 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_default(); }
#line 1653 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 131 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmt_default(); yyerrok; }
#line 1659 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 135 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_assignexpr((yyvsp[0].exprValue)); }
#line 1665 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 136 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].exprValue),iopcode::add, (yyvsp[0].exprValue)); }
#line 1671 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 137 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::sub, (yyvsp[0].exprValue)); }
#line 1677 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 138 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::mul, (yyvsp[0].exprValue)); }
#line 1683 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::div_i, (yyvsp[0].exprValue)); }
#line 1689 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 140 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_ARITH_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::mod, (yyvsp[0].exprValue)); }
#line 1695 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 141 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::if_greater, (yyvsp[0].exprValue)); }
#line 1701 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 142 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::if_greatereq, (yyvsp[0].exprValue)); }
#line 1707 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 143 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::if_less, (yyvsp[0].exprValue)); }
#line 1713 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 144 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-2].exprValue), iopcode::if_lesseq, (yyvsp[0].exprValue)); }
#line 1719 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 145 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_expr_exprL_EQUAL(&((yyvsp[-1].exprValue))); }
#line 1725 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 145 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-3].exprValue), iopcode::if_eq, (yyvsp[0].exprValue)); }
#line 1731 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 146 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_expr_exprL_NOT_EQUAL(&((yyvsp[-1].exprValue))); }
#line 1737 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 146 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_REL_OPERATOR_exprR((yyvsp[-3].exprValue), iopcode::if_noteq, (yyvsp[0].exprValue)); }
#line 1743 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 147 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_expr_exprL_AND((yyvsp[-1].exprValue)); }
#line 1749 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 147 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_AND_M_exprR((yyvsp[-4].exprValue), (yyvsp[-1].unsignedValue), (yyvsp[0].exprValue)); }
#line 1755 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 148 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_expr_exprL_OR((yyvsp[-1].exprValue)); }
#line 1761 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 148 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_exprL_OR_M_exprR((yyvsp[-4].exprValue), (yyvsp[-1].unsignedValue), (yyvsp[0].exprValue)); }
#line 1767 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 149 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_expr_term((yyvsp[0].exprValue)); }
#line 1773 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 153 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].exprValue));}
#line 1779 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 155 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_MINUS_expr((yyvsp[0].exprValue)); }
#line 1785 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 156 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_NOT_expr((yyvsp[0].exprValue)); }
#line 1791 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 157 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_PLUS_PLUS_lvalue((yyvsp[0].exprValue)); }
#line 1797 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 158 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_lvalue_PLUS_PLUS((yyvsp[-1].exprValue)); }
#line 1803 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 159 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_MINUS_MINUS_lvalue((yyvsp[0].exprValue)); }
#line 1809 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 160 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_lvalue_MINUS_MINUS((yyvsp[-1].exprValue)); }
#line 1815 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 161 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_term_primary((yyvsp[0].exprValue));}
#line 1821 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 164 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_assignexpr_lvalue_ASSIGNMENT_expr((yyvsp[-2].exprValue),(yyvsp[0].exprValue)); }
#line 1827 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 168 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = Manage_primary_lvalue((yyvsp[0].exprValue));
				}
#line 1835 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 171 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_primary_call((yyvsp[0].exprValue)); }
#line 1841 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 172 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_primary_objectdef((yyvsp[0].exprValue)); }
#line 1847 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 174 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_primary_LEFT_PAREN_funcdef_RIGHT_PAREN((yyvsp[-1].exprValue)); }
#line 1853 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 175 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) =  Manage_primary_const((yyvsp[0].exprValue));}
#line 1859 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 179 "alpha_parser.y" /* yacc.c:1646  */
    {			
					(yyval.exprValue) = Manage_lvalue_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 1868 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 184 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = Manage_lvalue_LOCAL_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 1877 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 189 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = Manage_lvalue_DOUBLE_COLON_ID((yyvsp[0].stringValue));
					free((yyvsp[0].stringValue));
				}
#line 1886 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 193 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_lvalue_member((yyvsp[0].exprValue)); }
#line 1892 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 197 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = Manage_member_lvalue_DOT_ID((yyvsp[-2].exprValue), (yyvsp[0].stringValue));
				}
#line 1900 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 201 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = Manage_member_lvalue_LEFT_BRACKET_expr_RIGHT_BRACKET((yyvsp[-3].exprValue), (yyvsp[-1].exprValue));
				}
#line 1908 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 204 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_member_call_DOT_ID((yyvsp[-2].exprValue), (yyvsp[0].stringValue)); free((yyvsp[0].stringValue)); }
#line 1914 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 205 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_member_call_LEFT_BRACKET_expr_RIGHT_BRACKET((yyvsp[-3].exprValue), (yyvsp[-1].exprValue)); }
#line 1920 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 209 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_call_callRight_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-3].exprValue), (yyvsp[-1].elistValue)); }
#line 1926 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 211 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_call_lvalue_callsuffix((yyvsp[-1].exprValue), (yyvsp[0].callInfoValue)); }
#line 1932 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 213 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_LEFT_PAREN_funcdef_RIGHT_PAREN_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-4].exprValue), (yyvsp[-1].elistValue)); }
#line 1938 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 217 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.callInfoValue) = Manage_callsuffix_normcall((yyvsp[0].callInfoValue)); }
#line 1944 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 219 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.callInfoValue) = Manage_callsuffix_methodcall((yyvsp[0].callInfoValue)); }
#line 1950 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 223 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.callInfoValue) = Manage_normcall_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-1].elistValue)); }
#line 1956 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 227 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.callInfoValue) = Manage_methodcall_DOT_DOT_ID_LEFT_PAREN_elist_RIGHT_PAREN((yyvsp[-3].stringValue), (yyvsp[-1].elistValue)); }
#line 1962 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 231 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.elistValue) = Manage_elist_elistnotempty((yyvsp[0].elistValue)); }
#line 1968 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 232 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.elistValue) = Manage_elist(); }
#line 1974 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 236 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.elistValue) = Manage_elistnotempty_expr_commalist((yyvsp[-1].elistValue), (yyvsp[0].exprValue)); }
#line 1980 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 239 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.elistValue) = Manage_commalist_COMMA_expr_commalist((yyvsp[-2].elistValue), (yyvsp[-1].exprValue)); }
#line 1986 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 240 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.elistValue) = Manage_commalist(); }
#line 1992 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 245 "alpha_parser.y" /* yacc.c:1646  */
    { 
					(yyval.exprValue) = Manage_objectdef_LEFT_BRACKET_objectdinner_RIGHT_BRACKET((yyvsp[-1].objectInnerValue)); 
				}
#line 2000 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 251 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.objectInnerValue) = Manage_objectdinner_elistnotempty((yyvsp[0].elistValue)); }
#line 2006 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 252 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.objectInnerValue) = Manage_objectdinner_indexed((yyvsp[0].indexedValue)); }
#line 2012 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 253 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.objectInnerValue) = Manage_objectdinner(); }
#line 2018 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 257 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.indexedValue) = Manage_indexed_indexedelem_commaindexed((yyvsp[-1].indexedValue), (yyvsp[0].indexedElement)); }
#line 2024 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 260 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.indexedValue) = Manage_commaindexed_COMMA_indexedelem_commaindexed((yyvsp[-2].indexedValue), (yyvsp[-1].indexedElement)); }
#line 2030 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 261 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.indexedValue) = Manage_commaindexed(); }
#line 2036 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 264 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_indexedelem_LEFT_BRACE_expr(&((yyvsp[0].exprValue))); }
#line 2042 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 265 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.indexedElement) = Manage_indexedelem_LEFT_BRACE_expr_COLON_expr_RIGHT_BRACE((yyvsp[-4].exprValue), (yyvsp[-1].exprValue));
				}
#line 2050 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 270 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_block_LEFT_BRACE();}
#line 2056 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 270 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_stmts_RIGHT_BRACE((yyvsp[-1].stmtInfoValue)); }
#line 2062 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 273 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.unsignedValue) = Manage_N(); }
#line 2068 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 275 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.unsignedValue) = Manage_M(); }
#line 2074 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 278 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_funcdef_N_funcprefix_LEFT_PAREN_idlist_RIGHT_PAREN_block((yyvsp[-5].unsignedValue), (yyvsp[-4].stringValue), (yyvsp[0].stmtInfoValue)); }
#line 2080 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 281 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stringValue) = Manage_funcprefix_FUNCTION_funcname((yyvsp[0].stringValue)); }
#line 2086 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 285 "alpha_parser.y" /* yacc.c:1646  */
    { 
					(yyval.stringValue) = Manage_funcname_ID((yyvsp[0].stringValue));
				}
#line 2094 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 288 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stringValue) = Manage_funcname(); }
#line 2100 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 291 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_const_numerical_const((yyvsp[0].intValue));}
#line 2106 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 292 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_const_numerical_const((yyvsp[0].doubleValue));}
#line 2112 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 293 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_const_STRINGCONST((yyvsp[0].stringValue));}
#line 2118 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 294 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_const_NIL();}
#line 2124 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 295 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_boolconst(true);}
#line 2130 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 296 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.exprValue) = Manage_boolconst(false);}
#line 2136 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 301 "alpha_parser.y" /* yacc.c:1646  */
    {
					Manage_idlist((yyvsp[0].stringValue)); 
				  	free((yyvsp[0].stringValue));
				}
#line 2145 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 308 "alpha_parser.y" /* yacc.c:1646  */
    {
					Manage_idlist((yyvsp[-1].stringValue)); 
				  	free((yyvsp[-1].stringValue));
				}
#line 2154 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 314 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.unsignedValue) = Manage_ifprefix_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].exprValue)); }
#line 2160 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 316 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_ifstmt_ifprefix_stmt((yyvsp[-1].unsignedValue), (yyvsp[0].stmtInfoValue)); }
#line 2166 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 317 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_ifstmt_ifprefix_stmt_elseprefix((yyvsp[-1].stmtInfoValue)); }
#line 2172 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 317 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_ifstmt_ifprefix_stmt_elseprefix_stmt((yyvsp[-4].unsignedValue), (yyvsp[-2].unsignedValue), (yyvsp[-3].stmtInfoValue), (yyvsp[0].stmtInfoValue)); }
#line 2178 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 320 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.unsignedValue) = Manage_elseprefix_ELSE(); }
#line 2184 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 322 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.unsignedValue) = Manage_whilestart_WHILE(); }
#line 2190 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 324 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.unsignedValue) =  Manage_whilecond_LEFT_PAREN_expr_RIGHT_PAREN((yyvsp[-1].exprValue)); }
#line 2196 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 326 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_while_whilestart_whilecond_stmt((yyvsp[-2].unsignedValue), (yyvsp[-1].unsignedValue), (yyvsp[0].stmtInfoValue)); }
#line 2202 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 329 "alpha_parser.y" /* yacc.c:1646  */
    {
					(yyval.unsignedPairValue) = Manage_forprefix_FOR_LEFT_PAREN_elist_SEMICOLON_M_expr_SEMICOLON((yyvsp[-2].unsignedValue), (yyvsp[-1].exprValue));
					
				}
#line 2211 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 335 "alpha_parser.y" /* yacc.c:1646  */
    { Manage_forstmt_forprefix_N_elist(); }
#line 2217 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 336 "alpha_parser.y" /* yacc.c:1646  */
    { 
					 Manage_forstmt_forprefix_N_elist_RIGHT_PAREN_N_stmt_N((yyvsp[-7].unsignedPairValue), (yyvsp[-6].unsignedValue), (yyvsp[-2].unsignedValue), (yyvsp[-1].stmtInfoValue), (yyvsp[0].unsignedValue));
					 
				}
#line 2226 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 343 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_returnstmt_RETURN_expr_SEMICOLON((yyvsp[-1].exprValue)); }
#line 2232 "alpha_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 344 "alpha_parser.y" /* yacc.c:1646  */
    { (yyval.stmtInfoValue) = Manage_returnstmt_RETURN_SEMICOLON(); }
#line 2238 "alpha_parser.cpp" /* yacc.c:1646  */
    break;


#line 2242 "alpha_parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 347 "alpha_parser.y" /* yacc.c:1906  */


int yyerror(char * yaccProvidedMessage) {
 	error(ErrorType::Error, yylineno, "%s before token " BON "\'%s\'" BOFF "\n", yaccProvidedMessage, yytext);
	return 0;
}

unsigned int getCurrentScope() {
	return scope;
}

void incrementScope() {
	scope++;
}

void decrementScope() {
	assert(scope);
	scope--;
}

void init() {
	symbol_table.addScopeType(Scope_Type::global_scope);
	std::ifstream ifs;
	ifs.open("stdalpha.lib");
	if (!ifs.is_open()) {
		error(ErrorType::Warning, 0, "stdalpha.lib not found! Library functions won't be loaded\n");
	} else {
		std::string temp;
		while (!ifs.eof()) {
			ifs >> temp;
			symbol_table.Insert(temp, SymTable_Entry_Type::library_function, 0, 0);
		}
	}
}
