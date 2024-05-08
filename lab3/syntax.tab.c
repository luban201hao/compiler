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
#line 1 "./lex.y" /* yacc.c:339  */

    #include "node.h"
    #include "hash.h"
    #include "translate.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include "lex.yy.c"
    void yyerror(char* );
    void myError(char* );

#line 77 "./syntax.tab.c" /* yacc.c:339  */

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
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    ASSIGNOP = 258,
    OR = 259,
    AND = 260,
    RELOP = 261,
    PLUS = 262,
    MINUS = 263,
    STAR = 264,
    DIV = 265,
    NOT = 266,
    DOT = 267,
    MINUSINT = 268,
    LB = 269,
    RB = 270,
    LP = 271,
    RP = 272,
    THEN = 273,
    ELSE = 274,
    INT = 275,
    FLOAT = 276,
    TYPE = 277,
    STRUCT = 278,
    RETURN = 279,
    IF = 280,
    WHILE = 281,
    ID = 282,
    SEMI = 283,
    COMMA = 284,
    LC = 285,
    RC = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "./lex.y" /* yacc.c:355  */

    char *str;
    struct TreeNode *node;

#line 154 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 185 "./syntax.tab.c" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   467

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    48,    54,    59,    67,    74,    81,    85,
      89,    94,    98,   105,   110,   116,   121,   132,   139,   145,
     150,   157,   163,   174,   178,   191,   202,   208,   216,   222,
     228,   239,   245,   250,   257,   261,   265,   273,   284,   298,
     309,   313,   317,   321,   325,   329,   336,   341,   346,   354,
     358,   364,   368,   375,   380,   388,   396,   404,   412,   421,
     429,   437,   445,   453,   461,   468,   475,   488,   499,   510,
     520,   527,   534,   541,   545,   549,   553,   557,   561,   565,
     569,   573,   577,   581,   585,   589,   593,   599,   606
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASSIGNOP", "OR", "AND", "RELOP", "PLUS",
  "MINUS", "STAR", "DIV", "NOT", "DOT", "MINUSINT", "LB", "RB", "LP", "RP",
  "THEN", "ELSE", "INT", "FLOAT", "TYPE", "STRUCT", "RETURN", "IF",
  "WHILE", "ID", "SEMI", "COMMA", "LC", "RC", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     285,   286
};
# endif

#define YYPACT_NINF -58

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-58)))

#define YYTABLE_NINF -33

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     138,   -21,   -58,   -23,    25,   -58,   138,    20,   -58,   -58,
     -13,    19,   -58,   -58,   -58,     2,    36,   -58,    33,    17,
      23,     0,   -58,    54,   -58,    39,    12,    39,     0,   -58,
      14,    47,     0,    62,   -58,    39,    65,    52,   -58,   -58,
      71,    72,   -58,    43,    75,     5,    15,    63,   -58,   -58,
     -58,   105,   -58,     0,   -58,   -58,    93,   143,   157,   171,
     -58,   -58,   339,   118,   120,   125,   -58,   111,    43,    92,
     -58,   339,   -58,   -58,    39,   -58,   -58,   -58,   121,   -58,
      -2,   126,   391,   104,   185,   199,   129,   -58,   -58,   124,
     213,   227,   241,   255,   269,   283,   297,   311,   128,   325,
     -58,   436,   -58,   -58,   -58,   -58,   -58,   130,   406,   136,
     421,   140,   -58,   119,   145,   -58,   -58,   436,   -58,   362,
     -58,   445,   -58,   453,   -58,    48,   -58,    48,   -58,    -2,
     -58,    -2,   -58,   151,   378,    64,    64,    64,    64,   -58,
     339,   -58,   -58,   152,   -58,   150,   155,   -58,   -58,   -58,
     -58,    64,    64,   -58,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    19,     0,     2,     0,     0,    15,     8,
      20,     0,    17,     1,     3,     9,    21,     6,     0,     0,
       0,    47,    10,     0,     5,     0,     0,     0,    47,     7,
       0,     0,    47,     0,    25,     0,     0,    28,    21,    13,
       0,     0,    12,     0,     0,    53,     0,    51,    16,    46,
      26,    29,    24,     0,    23,    22,     0,     0,     0,     0,
      71,    72,     0,     0,     0,    70,    35,     0,     0,     0,
      49,     0,    50,    48,     0,    27,    40,    82,    64,    83,
      65,     0,     0,     0,     0,     0,     0,    30,    31,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    54,    52,    81,    63,    42,    36,     0,     0,     0,
       0,     0,    67,    88,     0,    34,    73,    55,    75,    57,
      74,    56,    76,    58,    77,    59,    78,    60,    79,    61,
      80,    62,    69,     0,     0,     0,     0,     0,     0,    84,
       0,    66,    85,     0,    68,    43,    37,    45,    39,    87,
      86,     0,     0,    44,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   165,   -58,    90,     3,   -58,   -58,   -58,   -24,
     -58,   122,   -58,   156,   112,   226,    -8,   -58,   107,   -58,
     -57,    45
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    30,     8,    11,    12,    19,
      20,    36,    37,    66,    67,    68,    31,    32,    46,    47,
      69,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    80,    82,     7,    10,    83,    45,     9,    71,     7,
      98,    51,    99,    40,   101,    44,    72,   -18,    25,    26,
      43,    15,     2,     3,    49,    13,    35,   108,   110,   113,
      22,    26,    41,   117,   119,   121,   123,   125,   127,   129,
     131,    38,   134,    73,    56,   -11,    27,    16,    17,    21,
      45,    57,    23,    28,    58,    33,    35,    96,    97,    59,
      98,    24,    99,    60,    61,    56,    38,    62,    63,    64,
      65,    34,    57,    28,   -32,    58,     2,     3,    48,    50,
      59,    53,    52,   113,    60,    61,    54,    55,    62,    63,
      64,    65,    74,    89,    28,    90,    91,    92,    93,    94,
      95,    96,    97,    70,    98,   105,    99,    90,    91,    92,
      93,    94,    95,    96,    97,    39,    98,    42,    99,    26,
     100,    76,    90,    91,    92,    93,    94,    95,    96,    97,
     111,    98,   106,    99,    84,    99,    85,    57,    -4,     1,
      58,    86,    87,   103,    77,    59,   112,   135,   140,    60,
      61,    57,   115,   137,    58,   132,    65,   139,    79,    59,
       2,     3,   141,    60,    61,    57,   142,   150,    58,   151,
      65,    14,    81,    59,   152,    75,    29,    60,    61,    57,
      88,   102,    58,     0,    65,   149,   107,    59,     0,     0,
       0,    60,    61,    57,     0,     0,    58,     0,    65,     0,
     109,    59,     0,     0,     0,    60,    61,    57,     0,     0,
      58,     0,    65,     0,   116,    59,     0,     0,     0,    60,
      61,    57,     0,     0,    58,     0,    65,     0,   118,    59,
       0,     0,     0,    60,    61,    57,     0,     0,    58,     0,
      65,     0,   120,    59,     0,     0,     0,    60,    61,    57,
       0,     0,    58,     0,    65,     0,   122,    59,     0,     0,
       0,    60,    61,    57,     0,     0,    58,     0,    65,     0,
     124,    59,     0,     0,     0,    60,    61,    57,     0,     0,
      58,     0,    65,     0,   126,    59,     0,     0,     0,    60,
      61,    57,     0,     0,    58,     0,    65,     0,   128,    59,
       0,     0,     0,    60,    61,    57,     0,     0,    58,     0,
      65,     0,   130,    59,     0,     0,     0,    60,    61,    57,
       0,     0,    58,     0,    65,     0,   133,    59,     0,     0,
       0,    60,    61,    57,     0,     0,    58,     0,    65,     0,
       0,    59,     0,     0,     0,    60,    61,    57,     0,     0,
      58,     0,    65,     0,     0,    59,     0,     0,     0,    60,
      61,   145,   146,   147,   148,     0,    65,    92,    93,    94,
      95,    96,    97,     0,    98,     0,    99,   153,   154,   143,
       0,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,     0,    99,   144,    90,    91,    92,    93,    94,    95,
      96,    97,     0,    98,     0,    99,     0,     0,   104,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,     0,     0,   136,    90,    91,    92,    93,    94,    95,
      96,    97,     0,    98,     0,    99,     0,     0,   138,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,    93,    94,    95,    96,    97,     0,    98,     0,    99,
      94,    95,    96,    97,     0,    98,     0,    99
};

static const yytype_int16 yycheck[] =
{
      57,    58,    59,     0,    27,    62,    30,    28,     3,     6,
      12,    35,    14,     1,    71,     1,     1,    30,     1,    14,
      28,     1,    22,    23,    32,     0,    23,    84,    85,    86,
      28,    14,    20,    90,    91,    92,    93,    94,    95,    96,
      97,    27,    99,    28,     1,    28,    29,    27,    28,    30,
      74,     8,    16,    30,    11,     1,    53,     9,    10,    16,
      12,    28,    14,    20,    21,     1,    27,    24,    25,    26,
      27,    17,     8,    30,    31,    11,    22,    23,    31,    17,
      16,    29,    17,   140,    20,    21,    15,    15,    24,    25,
      26,    27,    29,     1,    30,     3,     4,     5,     6,     7,
       8,     9,    10,    28,    12,     1,    14,     3,     4,     5,
       6,     7,     8,     9,    10,    25,    12,    27,    14,    14,
      28,    28,     3,     4,     5,     6,     7,     8,     9,    10,
       1,    12,    28,    14,    16,    14,    16,     8,     0,     1,
      11,    16,    31,    17,     1,    16,    17,    17,    29,    20,
      21,     8,    28,    17,    11,    27,    27,    17,     1,    16,
      22,    23,    17,    20,    21,     8,    15,    15,    11,    19,
      27,     6,     1,    16,    19,    53,    20,    20,    21,     8,
      68,    74,    11,    -1,    27,   140,     1,    16,    -1,    -1,
      -1,    20,    21,     8,    -1,    -1,    11,    -1,    27,    -1,
       1,    16,    -1,    -1,    -1,    20,    21,     8,    -1,    -1,
      11,    -1,    27,    -1,     1,    16,    -1,    -1,    -1,    20,
      21,     8,    -1,    -1,    11,    -1,    27,    -1,     1,    16,
      -1,    -1,    -1,    20,    21,     8,    -1,    -1,    11,    -1,
      27,    -1,     1,    16,    -1,    -1,    -1,    20,    21,     8,
      -1,    -1,    11,    -1,    27,    -1,     1,    16,    -1,    -1,
      -1,    20,    21,     8,    -1,    -1,    11,    -1,    27,    -1,
       1,    16,    -1,    -1,    -1,    20,    21,     8,    -1,    -1,
      11,    -1,    27,    -1,     1,    16,    -1,    -1,    -1,    20,
      21,     8,    -1,    -1,    11,    -1,    27,    -1,     1,    16,
      -1,    -1,    -1,    20,    21,     8,    -1,    -1,    11,    -1,
      27,    -1,     1,    16,    -1,    -1,    -1,    20,    21,     8,
      -1,    -1,    11,    -1,    27,    -1,     1,    16,    -1,    -1,
      -1,    20,    21,     8,    -1,    -1,    11,    -1,    27,    -1,
      -1,    16,    -1,    -1,    -1,    20,    21,     8,    -1,    -1,
      11,    -1,    27,    -1,    -1,    16,    -1,    -1,    -1,    20,
      21,   135,   136,   137,   138,    -1,    27,     5,     6,     7,
       8,     9,    10,    -1,    12,    -1,    14,   151,   152,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    -1,    14,    15,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    -1,    14,    -1,    -1,    17,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    12,    -1,
      14,    -1,    -1,    17,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    -1,    14,    -1,    -1,    17,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    12,    -1,
      14,     6,     7,     8,     9,    10,    -1,    12,    -1,    14,
       7,     8,     9,    10,    -1,    12,    -1,    14
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    22,    23,    33,    34,    35,    37,    38,    28,
      27,    39,    40,     0,    34,     1,    27,    28,    36,    41,
      42,    30,    28,    16,    28,     1,    14,    29,    30,    45,
      37,    48,    49,     1,    17,    37,    43,    44,    27,    36,
       1,    20,    36,    48,     1,    41,    50,    51,    31,    48,
      17,    41,    17,    29,    15,    15,     1,     8,    11,    16,
      20,    21,    24,    25,    26,    27,    45,    46,    47,    52,
      28,     3,     1,    28,    29,    43,    28,     1,    52,     1,
      52,     1,    52,    52,    16,    16,    16,    31,    46,     1,
       3,     4,     5,     6,     7,     8,     9,    10,    12,    14,
      28,    52,    50,    17,    17,     1,    28,     1,    52,     1,
      52,     1,    17,    52,    53,    28,     1,    52,     1,    52,
       1,    52,     1,    52,     1,    52,     1,    52,     1,    52,
       1,    52,    27,     1,    52,    17,    17,    17,    17,    17,
      29,    17,    15,     1,    15,    47,    47,    47,    47,    53,
      15,    19,    19,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    36,    36,    36,    37,    37,    38,    38,    39,    39,
      40,    41,    41,    41,    42,    42,    42,    43,    43,    44,
      45,    46,    46,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    48,    48,    49,    49,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     2,
       3,     1,     3,     3,     1,     1,     5,     2,     1,     0,
       1,     1,     4,     4,     4,     3,     4,     3,     1,     2,
       4,     2,     0,     2,     3,     1,     3,     5,     7,     5,
       2,     2,     3,     5,     7,     5,     2,     0,     3,     3,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     4,     4,     5,     3,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 44 "./lex.y" /* yacc.c:1646  */
    { root = (yyval.node) = newNode("Program", (yyloc).first_line);
                             add_child(root, (yyvsp[0].node));
                           }
#line 1523 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 48 "./lex.y" /* yacc.c:1646  */
    {
                                        //printf("ExtDecList: ExtDef ExtDefList\n"); 
                                        (yyval.node) = newNode("ExtDefList", (yyloc).first_line);
                                        add_child((yyval.node), (yyvsp[-1].node));
                                        add_child((yyval.node), (yyvsp[0].node));
                                   }
#line 1534 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 54 "./lex.y" /* yacc.c:1646  */
    { 
                                        (yyval.node) = newNode("ExtDefList", (yyloc).first_line);
                                        (yyval.node)->hasE=1;
                }
#line 1543 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 59 "./lex.y" /* yacc.c:1646  */
    {
                                        //printf("Specifier ExtDecList SEMI\n");
                                        (yyval.node) = newNode("ExtDef", (yyloc).first_line);
                                        add_child((yyval.node), (yyvsp[-2].node));
                                        add_child((yyval.node), (yyvsp[-1].node));
                                        struct TreeNode *n3 = newNode("SEMI", (yyloc).first_line);
                                        add_child((yyval.node), n3);
                                  }
#line 1556 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 67 "./lex.y" /* yacc.c:1646  */
    {
                            //printf("Specifier SEMI\n");
                            (yyval.node) = newNode("ExtDef", (yyloc).first_line);
                            add_child((yyval.node), (yyvsp[-1].node));
                            struct TreeNode *n2 = newNode("SEMI", (yyloc).first_line);
                            add_child((yyval.node), n2);
                        }
#line 1568 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 74 "./lex.y" /* yacc.c:1646  */
    {
                                    //printf("Specifier FunDec CompSt\n");
                                    (yyval.node) = newNode("ExtDef", (yyloc).first_line);
                                    add_child((yyval.node), (yyvsp[-2].node));
                                    add_child((yyval.node), (yyvsp[-1].node));
                                    add_child((yyval.node), (yyvsp[0].node));
                                }
#line 1580 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 81 "./lex.y" /* yacc.c:1646  */
    {
        myError("ExtDef: error SEMI");
        (yyval.node) = newNode("ExtDef", (yyloc).first_line); 
    }
#line 1589 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 85 "./lex.y" /* yacc.c:1646  */
    {
        myError("ExtDef: Specifier error");
        (yyval.node) = newNode("ExtDef", (yyloc).first_line); 
    }
#line 1598 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 89 "./lex.y" /* yacc.c:1646  */
    {
        myError("ExtDef: Specifier error SEMI");
        (yyval.node) = newNode("ExtDef", (yyloc).first_line); 
    }
#line 1607 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 94 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDecList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1616 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 98 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDecList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("COMMA", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1628 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 105 "./lex.y" /* yacc.c:1646  */
    {
        myError("VarDec error ExtDecList");
        (yyval.node) = newNode("ExtDecList", (yyloc).first_line); 
    }
#line 1637 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 110 "./lex.y" /* yacc.c:1646  */
    {
                    (yyval.node) = newNode("Specifier", (yyloc).first_line);
                    struct TreeNode *n1 = newNode("TYPE", (yyloc).first_line);
                    n1->info = strdup((yyvsp[0].str));
                    add_child((yyval.node), n1);
                }
#line 1648 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 116 "./lex.y" /* yacc.c:1646  */
    {
                                (yyval.node) = newNode("Specifier", (yyloc).first_line);
                                add_child((yyval.node), (yyvsp[0].node));
                            }
#line 1657 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 121 "./lex.y" /* yacc.c:1646  */
    {
                                                (yyval.node) = newNode("StructSpecifier", (yyloc).first_line);
                                                struct TreeNode *n1 = newNode("STRUCT", (yyloc).first_line);
                                                struct TreeNode *n3 = newNode("LC", (yyloc).first_line);
                                                struct TreeNode *n5 = newNode("RC", (yyloc).first_line);
                                                add_child((yyval.node), n1);
                                                add_child((yyval.node), (yyvsp[-3].node));
                                                add_child((yyval.node), n3);
                                                add_child((yyval.node), (yyvsp[-1].node));
                                                add_child((yyval.node), n5);
                                             }
#line 1673 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 132 "./lex.y" /* yacc.c:1646  */
    {
                                (yyval.node) = newNode("StructSpecifier", (yyloc).first_line);
                                struct TreeNode *n1 = newNode("STRUCT", (yyloc).first_line);
                                add_child((yyval.node), n1);
                                add_child((yyval.node), (yyvsp[0].node));
                             }
#line 1684 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 139 "./lex.y" /* yacc.c:1646  */
    {
            (yyval.node) = newNode("OptTag", (yyloc).first_line);
            struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
            n1->info = strdup((yyvsp[0].str));
            add_child((yyval.node), n1);
            }
#line 1695 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 145 "./lex.y" /* yacc.c:1646  */
    {
            (yyval.node) = newNode("OptTag", (yyloc).first_line);
            (yyval.node)->hasE=1;
        }
#line 1704 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 150 "./lex.y" /* yacc.c:1646  */
    {
            (yyval.node) = newNode("Tag", (yyloc).first_line);
            struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
            n1->info = strdup((yyvsp[0].str));
            add_child((yyval.node), n1);    
        }
#line 1715 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 157 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarDec", (yyloc).first_line);
        struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
        n1->info = strdup((yyvsp[0].str));
        add_child((yyval.node), n1);  
    }
#line 1726 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarDec", (yyloc).first_line);
        struct TreeNode *n2 = newNode("LB", (yyloc).first_line);
        struct TreeNode *n3 = newNode("INT", (yyloc).first_line);
        n3->info = strdup((yyvsp[-1].str));
        struct TreeNode *n4 = newNode("RB", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), n2);
        add_child((yyval.node), n3);
        add_child((yyval.node), n4);
    }
#line 1742 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 174 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarDec", (yyloc).first_line); 
    }
#line 1750 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 178 "./lex.y" /* yacc.c:1646  */
    {
        
        (yyval.node) = newNode("FunDec", (yyloc).first_line);
        struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
        n1->info = strdup((yyvsp[-3].str));
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RP", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n4);
        //printf("FunDec, %s\n", n1->info);
    }
#line 1768 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 191 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("FunDec", (yyloc).first_line);
        struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
        n1->info = strdup((yyvsp[-2].str));
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n3 = newNode("RP", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), n2);
        add_child((yyval.node), n3);        
    }
#line 1783 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 202 "./lex.y" /* yacc.c:1646  */
    {
        myError("ID LP error RP");
        (yyval.node) = newNode("FunDec", (yyloc).first_line); 
    }
#line 1792 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 208 "./lex.y" /* yacc.c:1646  */
    {
        //printf("VarList: ParamDec COMMA VarDec\n");
        (yyval.node) = newNode("VarList", (yyloc).first_line);
        struct TreeNode *n2 = newNode("COMMA", (yyloc).first_line);        
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1805 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 216 "./lex.y" /* yacc.c:1646  */
    {
        //printf("VarList: ParamDec\n");
        (yyval.node) = newNode("VarList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1815 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 222 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ParamDec", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1825 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 228 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("CompSt", (yyloc).first_line);
        struct TreeNode *n1 = newNode("LC", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RC", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n4);
    }
#line 1839 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 239 "./lex.y" /* yacc.c:1646  */
    {
        //printf("StmtList: Stmt StmtList\n");
        (yyval.node) = newNode("StmtList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1850 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 245 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("StmtList", (yyloc).first_line);
        (yyval.node)->hasE=1;
    }
#line 1859 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 250 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Stmt: Exp SEMI\n");
        (yyval.node) = newNode("Stmt", (yyloc).first_line);
        struct TreeNode *n2 = newNode("SEMI", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n2);
    }
#line 1871 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 257 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp error SEMI");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 1880 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 261 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1889 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 265 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line);
        struct TreeNode *n1 = newNode("RETURN", (yyloc).first_line);
        struct TreeNode *n3 = newNode("SEMI", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n3);
    }
#line 1902 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 273 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line);
        struct TreeNode *n1 = newNode("IF", (yyloc).first_line);
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RP", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), n4);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1918 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 284 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line);
        struct TreeNode *n1 = newNode("IF", (yyloc).first_line);
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RP", (yyloc).first_line);
        struct TreeNode *n6 = newNode("ELSE", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), n4);
        add_child((yyval.node), (yyvsp[-2].node));   
        add_child((yyval.node), n6);
        add_child((yyval.node), (yyvsp[0].node));     
    }
#line 1937 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 298 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line);
        struct TreeNode *n1 = newNode("WHILE", (yyloc).first_line);
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RP", (yyloc).first_line);  
        add_child((yyval.node), n1);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), n4);
        add_child((yyval.node), (yyvsp[0].node));              
    }
#line 1953 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 309 "./lex.y" /* yacc.c:1646  */
    {
        myError("Stmt: error SEMI");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 1962 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 313 "./lex.y" /* yacc.c:1646  */
    {
        myError("Stmt: Exp error");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 1971 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 317 "./lex.y" /* yacc.c:1646  */
    {
        myError("Stmt: RETURN Exp error");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 1980 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 321 "./lex.y" /* yacc.c:1646  */
    {
        myError("Stmt: IF LP error RP Stmt %prec THEN");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 1989 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 325 "./lex.y" /* yacc.c:1646  */
    {
        myError("Stmt: IF LP error RP Stmt ELSE Stmt");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 1998 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 329 "./lex.y" /* yacc.c:1646  */
    {
        myError("Stmt: WHILE LP error RP Stmt");
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
    }
#line 2007 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 336 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DefList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2017 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 341 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DefList", (yyloc).first_line);
        (yyval.node)->hasE=1;
    }
#line 2026 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 346 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Def: Specifier DecList SEMI\n");
        (yyval.node) = newNode("Def", (yyloc).first_line);
        struct TreeNode *n3 = newNode("SEMI", (yyloc).first_line); 
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n3);
    }
#line 2039 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 354 "./lex.y" /* yacc.c:1646  */
    {
        myError("Def: Specifier error SEMI");
        (yyval.node) = newNode("Def", (yyloc).first_line); 
    }
#line 2048 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 358 "./lex.y" /* yacc.c:1646  */
    {
        myError("Def: Specifier DecList error");
        (yyval.node) = newNode("Def", (yyloc).first_line); 
    }
#line 2057 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 364 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DecList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2066 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 368 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DecList", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("COMMA", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node)); 
    }
#line 2078 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 375 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Dec: VarDec\n");
        (yyval.node) = newNode("Dec", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2088 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 380 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Dec", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("ASSIGNOP", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));         
    }
#line 2100 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 388 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp ASSIGNOP Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("ASSIGNOP", (yyloc).first_line);
        add_child((yyval.node), n2); 
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2113 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 396 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp AND Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("AND", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2126 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 404 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp OR Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("OR", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2139 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 412 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp RELOP Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("RELOP", (yyloc).first_line);
        n2->info = strdup((yyvsp[-1].str));
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2153 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 421 "./lex.y" /* yacc.c:1646  */
    {
        ////printf("Exp PLUS Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("PLUS", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2166 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 429 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp MINUS Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("MINUS", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2179 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 437 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp STAR Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("STAR", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2192 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 445 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp DIV Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("DIV", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2205 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 453 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n3 = newNode("RP", (yyloc).first_line);
        add_child((yyval.node), n1);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n3);
    }
#line 2218 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 461 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp MINUS Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("MINUS", (yyloc).first_line);
        add_child((yyval.node), n1); 
        add_child((yyval.node), (yyvsp[0].node));        
    }
#line 2230 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 468 "./lex.y" /* yacc.c:1646  */
    {
        //printf("NOT Exp\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("NOT", (yyloc).first_line);
        add_child((yyval.node), n1); 
        add_child((yyval.node), (yyvsp[0].node)); 
    }
#line 2242 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 475 "./lex.y" /* yacc.c:1646  */
    {
        //printf("ID LP Args RP\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
        n1->info = strdup((yyvsp[-3].str));
        add_child((yyval.node), n1);   
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RP", (yyloc).first_line); 
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n4);

    }
#line 2260 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 488 "./lex.y" /* yacc.c:1646  */
    {
        //printf("ID LP RP\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
        n1->info = strdup((yyvsp[-2].str));
        struct TreeNode *n2 = newNode("LP", (yyloc).first_line);
        struct TreeNode *n3 = newNode("RP", (yyloc).first_line); 
        add_child((yyval.node), n1);
        add_child((yyval.node), n2);
        add_child((yyval.node), n3);        
    }
#line 2276 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 499 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp LB Exp RB\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n2 = newNode("LB", (yyloc).first_line);
        struct TreeNode *n4 = newNode("RB", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), n4);
    }
#line 2291 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 510 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp DOT ID\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("DOT", (yyloc).first_line);
        struct TreeNode *n3 = newNode("ID", (yyloc).first_line);
        n3->info = strdup((yyvsp[0].str));
        add_child((yyval.node), n2);
        add_child((yyval.node), n3);
    }
#line 2306 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 520 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp: ID, %s\n", $1);
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("ID", (yyloc).first_line);
        n1->info = strdup((yyvsp[0].str));
        add_child((yyval.node), n1);
    }
#line 2318 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 527 "./lex.y" /* yacc.c:1646  */
    {
        //printf("Exp: INT\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("INT", (yyloc).first_line);
        n1->info = strdup((yyvsp[0].str));
        add_child((yyval.node), n1);        
    }
#line 2330 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 534 "./lex.y" /* yacc.c:1646  */
    {
        //printf("FLOAT\n");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        struct TreeNode *n1 = newNode("FLOAT", (yyloc).first_line);
        n1->info = strdup((yyvsp[0].str));
        add_child((yyval.node), n1);
    }
#line 2342 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 541 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp ASSIGNOP error");
        (yyval.node) = newNode("Error", (yyloc).first_line); 
    }
#line 2351 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 545 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp AND error");
        (yyval.node) = newNode("Error", (yyloc).first_line); 
    }
#line 2360 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 549 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp OR error");
        (yyval.node) = newNode("Error", (yyloc).first_line); 
    }
#line 2369 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 553 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp RELOP error");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2378 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 557 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp PLUS error");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2387 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 561 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp MINUS error");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2396 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 565 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp STAR error");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2405 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 569 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp DIV error");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2414 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 573 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: LP error RP");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2423 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 577 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: MINUS error");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
    }
#line 2432 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 581 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: NOT error");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
    }
#line 2441 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 585 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: ID LP error RP");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
    }
#line 2450 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 589 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp LB error RB");
        (yyval.node) = newNode("Exp", (yyloc).first_line);
    }
#line 2459 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 593 "./lex.y" /* yacc.c:1646  */
    {
        myError("Exp: Exp LB Exp error RB");
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
    }
#line 2468 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 599 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Args", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[-2].node));
        struct TreeNode *n2 = newNode("COMMA", (yyloc).first_line);
        add_child((yyval.node), n2);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2480 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 606 "./lex.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Args", (yyloc).first_line);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2489 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2493 "./syntax.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 610 "./lex.y" /* yacc.c:1906  */


void yyerror(char* s)
{
    //fprintf(stderr, "in yyerror: %s, %d\n", s, yylineno);
    if(lexFlag==1) 
        printf("Error type B at Line %d: %s\n", yylineno, s);
    successFlag=0;
}

void myError(char* s)
{
    if(lexFlag==1)
    {
        printf("Error type B at Line %d: %s\n", yylineno, s);
    }
}

int main(int argc, char **argv)
{
    successFlag=1;  
    lexFlag=1; 
    if(argc<=1)
        return 1;
    FILE *f = fopen(argv[1], "r");
    if(!f)
    {
        perror(argv[1]);
        return 1;
    }
    
    yyrestart(f);
    yyparse();
    //print_tree(root, 0);
    sematic_check(root);
    
    if(semaSuccess == 0)
        return 0;

    FILE *out = fopen(argv[2],"w+");
    tra_Program(root);
    printIr(out);
    fclose(f);
    fclose(out);
    return 0;
}


