
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "project.y"

    #include<stdio.h>
	#include<stdlib.h>
	#include<conio.h>
	#include<string.h>
	#include<math.h>
    #define YYDEBUG 1

    extern FILE *yyin;
    extern FILE *yyout;
	int yylex();
	int yyparse();
    int yyerror(char *s);

    // structure for variables
    typedef struct VAR
    {
        char *name;
        int type; // 0:int,1:double,2:char* 
        int *ival;
        double *dval;
        char** sval;
        int size;
        int isArray;
    }varptr;

    varptr *ptr;

    int varCount=0;
    int varTaken=0, conditionMatched[10], conPtr=0;

//  For Array
    int *tmpInteger;
    double *tmpDouble;
    int array_size=0;

    // Get the index of variable that is called
        int getIndex(char *varName)
        {
            for(int i = 0 ; i<varCount; i++)
            {
                if(strcmp(ptr[i].name,varName)==0){
                    return i;
                }
            }
            return -1;
        }

    int takeInput(char *varName, int id ){
        int index = getIndex(varName);
        if (index == -1)
        {
            printf("Error: Variable '%s' doesn't exist\n", varName);
        }
        else
        {
            printf("Value of %s is taken input\n",varName);
        }
    }

    //Insert
    void insert(char *vname,void* value,int type,int index,int size,int isArray)
    {
            ptr[index].name = vname;
            ptr[index].size = size;
            
            ptr[index].isArray = isArray;
            if(type==0){
                int *x = ((int*)value);
                ptr[index].ival = malloc(size*sizeof(int));
                for(int i=0;i<size;i++){
                    ptr[index].ival[i] = x[i];
                }
                ptr[index].type = 0;
                
            }
            else if(type==1){
                double* x = ((double*)value);
                ptr[index].dval = malloc(size*sizeof(double));
                for(int i=0;i<size;i++){
                    ptr[index].dval[i] = x[i];
                }
                ptr[index].type = 1;
                
            }
            else if(type==2){
                char **s =((char**)value);
                ptr[index].sval = malloc(size*sizeof(char**));
                for(int i=0;i<size;i++){
                    ptr[index].sval[i] = s[i];
                }
                ptr[index].type = 2;
            }
        }

        // Printing a variable
        void printVariable(char *varName)
        {
            int index = getIndex(varName);
            if (index == -1)
            {
                printf("Error: Variable '%s' doesn't exist\n",varName);
            }
            else
            {
                if (ptr[index].isArray)
                {
                    printf("ArrayName: %s\nSize: %d\nElements are: ",varName, ptr[index].size);
                    for (int i = 0; i < ptr[index].size; i++)
                    {
                        if (ptr[index].type == 0)
                            printf("%d ", ptr[index].ival[i]);
                        if (ptr[index].type == 1)
                            printf("%lf ", ptr[index].dval[i]);
                        if (ptr[index].type == 2)
                            printf("%s ", ptr[index].sval[i]);
                        if (i % 10 == 9)
                            printf("\n");
                    }
                    printf("\n");
                }
                else
                {
                    printf("Value of %s is:",varName);
                    if (ptr[index].type == 0)
                        printf("%d\n", ptr[index].ival[0]);
                    if (ptr[index].type == 1)
                        printf("%lf\n", ptr[index].dval[0]);
                    if (ptr[index].type == 2)
                        printf("%s\n", ptr[index].sval[0]);
                }
            }
        }

        // Printing an Array Index
        int printArrayIndex(char *varName, int position)
        {
            int index = getIndex(varName);
            if (index == -1)
            {
               printf("Error: Variable '%s' doesn't exist\n",varName);
            }
            else if (ptr[index].isArray == 0)
            {
                printf("%s is not an Array\n",varName);
            }
            else if (position >= ptr[index].size)
            {
                printf("Index out of range\n");
            }
            else
            {
                printf("%s[%d] = ", varName, position);
                if (ptr[index].type == 1)
                    printf("%lf\n", ptr[index].dval[position]);
                if (ptr[index].type == 0)
                    printf("%d\n", ptr[index].ival[position]);
                if (ptr[index].type == 2)
                    printf("%s\n", ptr[index].sval[position]);
            }
        }


/* Line 189 of yacc.c  */
#line 237 "project.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     HEADER = 258,
     MAIN = 259,
     END = 260,
     START = 261,
     VARIABLE = 262,
     ARRAY = 263,
     EOL = 264,
     ARROW = 265,
     RARROW = 266,
     INTEGER = 267,
     REAL = 268,
     STRING = 269,
     INTEGER_TYPE = 270,
     REAL_TYPE = 271,
     STRING_TYPE = 272,
     WRITE = 273,
     READ = 274,
     AND = 275,
     OR = 276,
     NOT = 277,
     XOR = 278,
     LOG = 279,
     LOG2 = 280,
     LN = 281,
     SIN = 282,
     COS = 283,
     TAN = 284,
     FACTORIAL = 285,
     SQRT = 286,
     IF = 287,
     ELIF = 288,
     ELSE = 289,
     OPTION = 290,
     ASSIGN = 291,
     FROM = 292,
     TO = 293,
     REPEAT = 294,
     WHILE = 295,
     BY = 296,
     AS = 297,
     MODULE = 298,
     RET = 299,
     CALL = 300,
     MAX = 301,
     MIN = 302,
     COMMENT = 303,
     MOD = 304,
     SWITCH = 305,
     CASE = 306,
     DEFAULT = 307,
     MMINUS = 308,
     PPLUS = 309,
     GEQ = 310,
     LEQ = 311,
     NOT_EQUAL = 312,
     EQUAL = 313,
     LT = 314,
     GT = 315,
     MINUS = 316,
     PLUS = 317,
     DIV = 318,
     MUL = 319,
     EXPONENT = 320
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 165 "project.y"

	int integer;
	double real;
	char* string;



/* Line 214 of yacc.c  */
#line 346 "project.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 358 "project.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   814

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNRULES -- Number of states.  */
#define YYNSTATES  295

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      72,    73,     2,     2,    67,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,     2,    69,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    10,    11,    14,    15,    18,    19,    22,
      24,    27,    30,    35,    40,    44,    46,    48,    51,    54,
      57,    60,    63,    66,    70,    72,    76,    78,    84,    88,
      90,    94,    96,   100,   102,   108,   112,   114,   118,   120,
     124,   126,   130,   134,   141,   145,   149,   156,   159,   161,
     163,   165,   170,   174,   181,   183,   188,   193,   197,   200,
     202,   207,   210,   212,   218,   226,   228,   229,   235,   240,
     252,   263,   274,   282,   293,   304,   305,   309,   313,   317,
     320,   321,   323,   328,   331,   333,   335,   337,   343,   344,
     346,   350,   354,   356,   358,   360,   362,   365,   368,   372,
     376,   380,   384,   388,   392,   396,   400,   404,   408,   412,
     416,   420,   424,   428,   431,   435,   440,   445,   450,   455,
     460,   465,   471,   477
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      75,     0,    -1,    76,    77,     4,     6,    78,     5,    -1,
      -1,    76,     3,    -1,    -1,    77,   102,    -1,    -1,    78,
      79,    -1,     9,    -1,    80,     9,    -1,    89,     9,    -1,
      18,    10,    90,     9,    -1,    19,    11,    91,     9,    -1,
      32,    92,    94,    -1,   101,    -1,    98,    -1,   108,     9,
      -1,     7,    54,    -1,     7,    53,    -1,    15,    81,    -1,
      16,    84,    -1,    17,    87,    -1,    81,    67,    82,    -1,
      82,    -1,     7,    36,   110,    -1,     7,    -1,     8,    36,
      68,    83,    69,    -1,    83,    67,   110,    -1,   110,    -1,
      84,    67,    85,    -1,    85,    -1,     7,    36,   110,    -1,
       7,    -1,     8,    36,    68,    86,    69,    -1,    86,    67,
     110,    -1,   110,    -1,    87,    67,    88,    -1,    88,    -1,
       7,    36,    14,    -1,     7,    -1,     7,    36,   110,    -1,
       7,    36,    14,    -1,     8,    70,    12,    71,    36,   110,
      -1,    90,    67,   110,    -1,    90,    67,     8,    -1,    90,
      67,     8,    70,    12,    71,    -1,    90,    14,    -1,   110,
      -1,    14,    -1,     8,    -1,     8,    70,   110,    71,    -1,
      91,    67,     7,    -1,    91,    67,     8,    70,    12,    71,
      -1,     7,    -1,     8,    70,    12,    71,    -1,    93,     6,
      79,     5,    -1,    72,   110,    73,    -1,    96,    95,    -1,
      95,    -1,    34,     6,    79,     5,    -1,    96,    97,    -1,
      97,    -1,    33,   110,     6,    79,     5,    -1,    99,    72,
       7,    73,     6,   100,     5,    -1,    50,    -1,    -1,   100,
      51,    12,     6,    79,    -1,   100,    52,     6,    79,    -1,
      37,    72,   110,    38,   110,    41,   110,    73,     6,    78,
       5,    -1,    40,    72,   110,    59,   110,    73,    39,     6,
      78,     5,    -1,    40,    72,   110,    60,   110,    73,    39,
       6,    78,     5,    -1,   104,    72,   105,    73,     6,    79,
       5,    -1,   104,    72,   105,    73,    10,    15,     6,    79,
     103,     5,    -1,   104,    72,   105,    73,    10,    16,     6,
      79,   103,     5,    -1,    -1,    44,     7,     9,    -1,    44,
      12,     9,    -1,    44,    13,     9,    -1,    43,     7,    -1,
      -1,   106,    -1,   106,    67,   107,     7,    -1,   107,     7,
      -1,    15,    -1,    16,    -1,    17,    -1,    45,     7,    72,
     109,    73,    -1,    -1,     7,    -1,   109,    67,     7,    -1,
     109,    67,    12,    -1,    12,    -1,    12,    -1,    13,    -1,
       7,    -1,    62,   110,    -1,    61,   110,    -1,   110,    62,
     110,    -1,   110,    61,   110,    -1,   110,    64,   110,    -1,
     110,    63,   110,    -1,   110,    66,   110,    -1,   110,    49,
     110,    -1,   110,    59,   110,    -1,   110,    60,   110,    -1,
     110,    56,   110,    -1,   110,    55,   110,    -1,   110,    58,
     110,    -1,   110,    57,   110,    -1,   110,    20,   110,    -1,
     110,    21,   110,    -1,   110,    23,   110,    -1,    22,   110,
      -1,    72,   110,    73,    -1,    27,    72,   110,    73,    -1,
      28,    72,   110,    73,    -1,    29,    72,   110,    73,    -1,
      24,    72,   110,    73,    -1,    26,    72,   110,    73,    -1,
      31,    72,   110,    73,    -1,    46,     7,    67,     7,    73,
      -1,    47,     7,    67,     7,    73,    -1,    72,   110,    73,
      30,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   199,   202,   207,   208,   210,   211,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   238,
     254,   255,   256,   259,   260,   264,   279,   294,   305,   311,
     320,   321,   325,   340,   355,   366,   372,   381,   382,   386,
     401,   419,   436,   445,   470,   478,   480,   482,   484,   492,
     494,   496,   502,   504,   506,   508,   513,   533,   535,   536,
     540,   557,   558,   560,   584,   589,   591,   592,   596,   602,
     611,   620,   634,   635,   639,   645,   646,   647,   648,   650,
     668,   669,   671,   675,   681,   682,   683,   686,   704,   705,
     717,   730,   734,   742,   744,   746,   756,   758,   760,   762,
     764,   766,   768,   770,   772,   774,   776,   778,   780,   782,
     784,   786,   788,   790,   792,   794,   796,   798,   800,   802,
     804,   806,   823,   842
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HEADER", "MAIN", "END", "START",
  "VARIABLE", "ARRAY", "EOL", "ARROW", "RARROW", "INTEGER", "REAL",
  "STRING", "INTEGER_TYPE", "REAL_TYPE", "STRING_TYPE", "WRITE", "READ",
  "AND", "OR", "NOT", "XOR", "LOG", "LOG2", "LN", "SIN", "COS", "TAN",
  "FACTORIAL", "SQRT", "IF", "ELIF", "ELSE", "OPTION", "ASSIGN", "FROM",
  "TO", "REPEAT", "WHILE", "BY", "AS", "MODULE", "RET", "CALL", "MAX",
  "MIN", "COMMENT", "MOD", "SWITCH", "CASE", "DEFAULT", "MMINUS", "PPLUS",
  "GEQ", "LEQ", "NOT_EQUAL", "EQUAL", "LT", "GT", "MINUS", "PLUS", "DIV",
  "MUL", "'^'", "EXPONENT", "','", "'{'", "'}'", "'['", "']'", "'('",
  "')'", "$accept", "startprog", "header", "func1", "statements",
  "statement", "declaration", "integer_variable", "integer_statements",
  "integer_values", "real_variable", "real_statements", "real_values",
  "string_variable", "string_statements", "assign", "print", "scan",
  "if_block", "ifexpr", "else_statement", "single_else", "elif_statement",
  "single_elif", "switch_block", "switch1", "cases", "loop_block",
  "module_declare", "ret1", "module", "module_type1", "module_type",
  "types", "module_call", "parameters", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,    94,   320,    44,   123,   125,
      91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      80,    80,    80,    81,    81,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    85,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    91,    92,    93,    94,    94,
      95,    96,    96,    97,    98,    99,   100,   100,   100,   101,
     101,   101,   102,   102,   102,   103,   103,   103,   103,   104,
     105,   105,   106,   106,   107,   107,   107,   108,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     0,     2,     0,     2,     0,     2,     1,
       2,     2,     4,     4,     3,     1,     1,     2,     2,     2,
       2,     2,     2,     3,     1,     3,     1,     5,     3,     1,
       3,     1,     3,     1,     5,     3,     1,     3,     1,     3,
       1,     3,     3,     6,     3,     3,     6,     2,     1,     1,
       1,     4,     3,     6,     1,     4,     4,     3,     2,     1,
       4,     2,     1,     5,     7,     1,     0,     5,     4,    11,
      10,    10,     7,    10,    10,     0,     3,     3,     3,     2,
       0,     1,     4,     2,     1,     1,     1,     5,     0,     1,
       3,     3,     1,     1,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     4,     4,     4,     4,     4,
       4,     5,     5,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     5,     1,     4,     0,     0,     0,     6,     0,
       7,    79,    80,     0,    84,    85,    86,     0,    81,     0,
       2,     0,     0,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     8,     0,     0,    16,     0,    15,
       0,     0,     0,    83,     0,    19,    18,     0,    26,     0,
      20,    24,    33,     0,    21,    31,    40,    22,    38,     0,
       0,     0,     0,     0,     0,     0,     0,    10,    11,     0,
      17,     0,     0,     0,    95,    93,    94,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    49,     0,    48,    54,     0,     0,     0,     0,     0,
      14,    59,     0,    62,     0,     0,     0,    88,     0,     0,
       0,     0,    82,   113,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,     0,    23,    32,     0,    30,    39,    37,     0,
      12,    47,     0,     0,    13,     0,    57,     0,     0,    58,
      61,     0,     0,     0,     0,    89,    92,     0,     0,    72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,   110,   111,   112,   103,   107,   106,   109,   108,   104,
     105,    99,    98,   101,   100,   102,     0,     0,    29,     0,
      36,     0,    45,    44,     0,    52,     0,     0,     0,    56,
       0,   104,   105,     0,    87,    66,    75,    75,   118,   119,
     115,   116,   117,   120,     0,     0,   123,    43,     0,    27,
       0,    34,    51,     0,    55,     0,     0,    60,     0,     0,
       0,    90,    91,     0,     0,     0,     0,   121,   122,    28,
      35,     0,     0,    63,     0,     0,     0,    64,     0,     0,
       0,     0,     0,    73,    74,    46,    53,     0,     7,     7,
       0,     0,    76,    77,    78,     7,     0,     0,     0,    68,
       0,    70,    71,    67,    69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    13,    34,    35,    50,    51,   207,
      54,    55,   209,    57,    58,    36,   102,   106,    62,    63,
     110,   111,   112,   113,    37,    38,   253,    39,     8,   255,
       9,    17,    18,    19,    40,   177,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -257
static const yytype_int16 yypact[] =
{
    -257,    13,    30,  -257,  -257,     1,    31,     9,  -257,   -23,
    -257,  -257,    49,   608,  -257,  -257,  -257,   -11,     8,    86,
    -257,   -27,    41,  -257,    92,    96,    94,    98,   112,    59,
      71,    72,   138,  -257,  -257,   139,   141,  -257,    75,  -257,
     142,     4,    49,  -257,   158,  -257,  -257,   146,   124,   125,
      97,  -257,   127,   137,   102,  -257,   152,   128,  -257,   106,
      99,   214,    88,   184,   214,   214,   122,  -257,  -257,   189,
    -257,   764,   123,   192,  -257,  -257,  -257,  -257,   214,   129,
     130,   131,   134,   136,   143,   193,   211,   214,   214,   214,
     524,   151,   214,   155,    92,   214,   156,    96,   215,    94,
     163,  -257,    10,   524,  -257,   164,     6,   232,   214,   219,
    -257,  -257,    88,  -257,   764,   477,   548,    29,   162,   223,
     231,   233,  -257,   573,   214,   214,   214,   214,   214,   214,
     177,   181,   -24,   -24,   251,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     213,   524,   214,  -257,   524,   214,  -257,  -257,  -257,   214,
    -257,  -257,   185,   238,  -257,   133,  -257,    -3,   764,  -257,
    -257,   246,   214,   214,   214,  -257,  -257,   -39,   248,  -257,
     764,   764,   281,   300,   330,   349,   379,   398,   249,   252,
     228,   573,   573,   573,   196,   113,   113,   113,   113,   113,
     113,   -24,   -24,   196,   196,  -257,   214,     7,   524,    27,
     524,   447,   194,   524,   195,  -257,   197,   764,   258,  -257,
     501,    63,    93,    38,  -257,  -257,   221,   221,  -257,  -257,
    -257,  -257,  -257,  -257,   200,   204,  -257,   524,   214,  -257,
     214,  -257,  -257,   256,  -257,   257,   265,  -257,   214,   239,
     240,  -257,  -257,    -4,    -1,   275,   277,  -257,  -257,   524,
     524,   212,   226,  -257,   428,   278,   279,  -257,   287,   297,
     307,   309,   310,  -257,  -257,  -257,  -257,   316,  -257,  -257,
     319,   764,  -257,  -257,  -257,  -257,   647,   686,   764,  -257,
     725,  -257,  -257,  -257,  -257
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -257,  -257,  -257,  -257,  -256,   -71,  -257,  -257,   234,  -257,
    -257,   229,  -257,  -257,   230,  -257,  -257,  -257,  -257,  -257,
    -257,   220,  -257,   222,  -257,  -257,  -257,  -257,  -257,   100,
    -257,  -257,  -257,   289,  -257,  -257,   -57
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     119,   267,   103,   217,   107,     6,   270,   115,   116,    44,
      71,   271,   272,     3,    72,   164,    11,   135,   136,   160,
     137,   123,   286,   287,   161,   138,    45,    46,   223,   290,
     132,   133,   134,     4,   224,   151,   175,    10,   154,   147,
     148,   176,   149,   171,     7,   251,   138,   268,   269,    12,
     252,   167,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,    41,   149,    14,    15,    16,   182,   183,   184,
     185,   186,   187,   165,   238,    42,   239,   162,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,    43,   240,   208,   241,   218,   210,    48,
      49,    56,   211,    52,    53,   213,   104,   105,    59,   226,
     227,    47,   138,    74,   100,   220,   221,   222,    75,    76,
     101,   108,   109,    60,   145,   146,   147,   148,    78,   149,
      79,    61,    80,    81,    82,    83,   249,    84,   120,   121,
     215,   216,   138,    64,    65,    66,   246,    69,    67,   237,
      68,    70,    85,    86,   145,   146,   147,   148,    91,   149,
      92,    93,   138,    95,    94,    74,   250,    87,    88,    97,
      75,    76,    77,    96,   145,   146,   147,   148,    89,   149,
      78,   259,    79,   260,    80,    81,    82,    83,    98,    84,
     114,   264,    74,   212,   117,    99,   118,    75,    76,   122,
     130,   124,   125,   126,    85,    86,   127,    78,   128,    79,
     289,    80,    81,    82,    83,   129,    84,   293,   131,    87,
      88,    74,   150,   152,   155,   168,    75,    76,   179,   157,
      89,    85,    86,   159,   163,   178,    78,   180,    79,   181,
      80,    81,    82,    83,   188,    84,    87,    88,   189,   206,
     214,   219,   135,   136,   225,   137,   234,    89,   236,   235,
      85,    86,   149,   247,   243,   254,   244,   245,   261,   262,
     263,   135,   136,   257,   137,    87,    88,   258,   265,   266,
     273,   138,   274,   275,   278,   279,    89,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   276,   149,   280,
     138,   135,   136,   281,   137,   166,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   282,   149,   283,   284,
     135,   136,   285,   137,   190,   288,   156,   256,   153,   158,
     138,    73,   169,     0,   170,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     0,   149,     0,   138,
     135,   136,     0,   137,   228,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,     0,   149,     0,     0,   135,
     136,     0,   137,   229,     0,     0,     0,     0,     0,   138,
       0,     0,     0,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,     0,   149,     0,   138,   135,
     136,     0,   137,   230,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,     0,   149,     0,     0,   135,   136,
       0,   137,   231,     0,     0,     0,     0,     0,   138,     0,
       0,     0,     0,     0,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,     0,   149,     0,   138,   135,   136,
       0,   137,   232,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     0,   149,     0,     0,   135,   136,     0,
     137,   233,     0,     0,     0,     0,     0,   138,     0,     0,
       0,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     0,   149,     0,   138,   135,   136,     0,
     137,   277,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,     0,   149,     0,   172,     0,     0,   242,     0,
       0,   135,   136,     0,   137,     0,   138,     0,     0,     0,
       0,     0,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   248,   149,   135,   136,     0,   137,     0,     0,
     138,     0,     0,     0,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     0,   149,   135,   136,
       0,   137,     0,   138,     0,     0,     0,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,     0,
     149,     0,     0,     0,     0,     0,     0,   138,     0,     0,
       0,     0,     0,   139,   140,   141,   142,   173,   174,   145,
     146,   147,   148,    20,   149,    21,    22,    23,     0,     0,
       0,     0,   138,    24,    25,    26,    27,    28,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,     0,   149,
      29,     0,     0,     0,     0,    30,     0,     0,    31,     0,
       0,     0,   291,    32,    21,    22,    23,     0,    33,     0,
       0,     0,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,    30,     0,     0,    31,     0,     0,
       0,   292,    32,    21,    22,    23,     0,    33,     0,     0,
       0,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,     0,     0,    30,     0,     0,    31,     0,     0,     0,
     294,    32,    21,    22,    23,     0,    33,     0,     0,     0,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     0,    30,     0,     0,    31,     0,     0,     0,     0,
      32,    21,    22,    23,     0,    33,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,     0,
       0,    30,     0,     0,    31,     0,     0,     0,     0,    32,
       0,     0,     0,     0,    33
};

static const yytype_int16 yycheck[] =
{
      71,     5,    59,     6,    61,     4,     7,    64,    65,    36,
       6,    12,    13,     0,    10,     9,     7,    20,    21,     9,
      23,    78,   278,   279,    14,    49,    53,    54,    67,   285,
      87,    88,    89,     3,    73,    92,     7,     6,    95,    63,
      64,    12,    66,   114,    43,     7,    49,    51,    52,    72,
      12,   108,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    73,    66,    15,    16,    17,   124,   125,   126,
     127,   128,   129,    67,    67,    67,    69,    67,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,     7,    67,   152,    69,   168,   155,     7,
       8,     7,   159,     7,     8,   162,     7,     8,    10,   180,
     181,    70,    49,     7,     8,   172,   173,   174,    12,    13,
      14,    33,    34,    11,    61,    62,    63,    64,    22,    66,
      24,    72,    26,    27,    28,    29,    73,    31,    15,    16,
       7,     8,    49,    72,    72,     7,   217,    72,     9,   206,
       9,     9,    46,    47,    61,    62,    63,    64,    12,    66,
      36,    36,    49,    36,    67,     7,    73,    61,    62,    67,
      12,    13,    14,    36,    61,    62,    63,    64,    72,    66,
      22,   238,    24,   240,    26,    27,    28,    29,    36,    31,
       6,   248,     7,     8,    72,    67,     7,    12,    13,     7,
       7,    72,    72,    72,    46,    47,    72,    22,    72,    24,
     281,    26,    27,    28,    29,    72,    31,   288,     7,    61,
      62,     7,    71,    68,    68,     6,    12,    13,     5,    14,
      72,    46,    47,    70,    70,    73,    22,     6,    24,     6,
      26,    27,    28,    29,    67,    31,    61,    62,    67,    36,
      12,     5,    20,    21,     6,    23,     7,    72,    30,     7,
      46,    47,    66,     5,    70,    44,    71,    70,    12,    12,
       5,    20,    21,    73,    23,    61,    62,    73,    39,    39,
       5,    49,     5,    71,     6,     6,    72,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    71,    66,    12,
      49,    20,    21,     6,    23,    73,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     9,    66,     9,     9,
      20,    21,     6,    23,    73,     6,    97,   227,    94,    99,
      49,    42,   112,    -1,   112,    -1,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    66,    -1,    49,
      20,    21,    -1,    23,    73,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    66,    -1,    -1,    20,
      21,    -1,    23,    73,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    66,    -1,    49,    20,
      21,    -1,    23,    73,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    20,    21,
      -1,    23,    73,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    66,    -1,    49,    20,    21,
      -1,    23,    73,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    66,    -1,    -1,    20,    21,    -1,
      23,    73,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    66,    -1,    49,    20,    21,    -1,
      23,    73,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    66,    -1,    38,    -1,    -1,    71,    -1,
      -1,    20,    21,    -1,    23,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    41,    66,    20,    21,    -1,    23,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    66,    20,    21,
      -1,    23,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     5,    66,     7,     8,     9,    -1,    -1,
      -1,    -1,    49,    15,    16,    17,    18,    19,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    66,
      32,    -1,    -1,    -1,    -1,    37,    -1,    -1,    40,    -1,
      -1,    -1,     5,    45,     7,     8,     9,    -1,    50,    -1,
      -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    -1,
      -1,     5,    45,     7,     8,     9,    -1,    50,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    -1,    -1,
       5,    45,     7,     8,     9,    -1,    50,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      45,     7,     8,     9,    -1,    50,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,    76,     0,     3,    77,     4,    43,   102,   104,
       6,     7,    72,    78,    15,    16,    17,   105,   106,   107,
       5,     7,     8,     9,    15,    16,    17,    18,    19,    32,
      37,    40,    45,    50,    79,    80,    89,    98,    99,   101,
     108,    73,    67,     7,    36,    53,    54,    70,     7,     8,
      81,    82,     7,     8,    84,    85,     7,    87,    88,    10,
      11,    72,    92,    93,    72,    72,     7,     9,     9,    72,
       9,     6,    10,   107,     7,    12,    13,    14,    22,    24,
      26,    27,    28,    29,    31,    46,    47,    61,    62,    72,
     110,    12,    36,    36,    67,    36,    36,    67,    36,    67,
       8,    14,    90,   110,     7,     8,    91,   110,    33,    34,
      94,    95,    96,    97,     6,   110,   110,    72,     7,    79,
      15,    16,     7,   110,    72,    72,    72,    72,    72,    72,
       7,     7,   110,   110,   110,    20,    21,    23,    49,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    66,
      71,   110,    68,    82,   110,    68,    85,    14,    88,    70,
       9,    14,    67,    70,     9,    67,    73,   110,     6,    95,
      97,    79,    38,    59,    60,     7,    12,   109,    73,     5,
       6,     6,   110,   110,   110,   110,   110,   110,    67,    67,
      73,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,    36,    83,   110,    86,
     110,   110,     8,   110,    12,     7,     8,     6,    79,     5,
     110,   110,   110,    67,    73,     6,    79,    79,    73,    73,
      73,    73,    73,    73,     7,     7,    30,   110,    67,    69,
      67,    69,    71,    70,    71,    70,    79,     5,    41,    73,
      73,     7,    12,   100,    44,   103,   103,    73,    73,   110,
     110,    12,    12,     5,   110,    39,    39,     5,    51,    52,
       7,    12,    13,     5,     5,    71,    71,    73,     6,     6,
      12,     6,     9,     9,     9,     6,    78,    78,     6,    79,
      78,     5,     5,    79,     5
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 193 "project.y"
    {
                    printf("\n\n     -------Program Started Successfully-------\n\n\n");
                    return 0;
                ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 199 "project.y"
    {   int val = 0;
            insert("qwertyuiop", &val, 0, varCount, 1, 0);
            varCount++;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 202 "project.y"
    {printf("A Header Library is Declared\n");
                            int val = 0;
                            insert("qwertyuiop", &val, 0, varCount, 1, 0);
                            varCount++;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 207 "project.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 208 "project.y"
    {;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 210 "project.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 211 "project.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 214 "project.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 215 "project.y"
    {;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 216 "project.y"
    {;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 217 "project.y"
    {;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 218 "project.y"
    {;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 219 "project.y"
    {;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 220 "project.y"
    {;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 221 "project.y"
    {;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 222 "project.y"
    {;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 224 "project.y"
    {
                        int id = getIndex((yyvsp[(1) - (2)].string));
                        if(id==-1) printf("Variable '%s' already exists",(yyvsp[(1) - (2)].string));
                        else if(ptr[id].type==2) printf("Not Possible for String");
                        else if(ptr[id].type==0){
                            ptr[id].ival[0]++;
                            (yyval.real) = ptr[id].ival[0];
                        }
                        else{
                            ptr[id].dval[0]+=1;
                            (yyval.real)=ptr[id].dval[0];
                        }
                    
                    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 239 "project.y"
    {
                        int id = getIndex((yyvsp[(1) - (2)].string));
                        if(id==-1) printf("Variable '%s' already exists",(yyvsp[(1) - (2)].string));
                        else if(ptr[id].type==2) printf("Not Possible for Strng");
                        else if(ptr[id].type==0){
                            ptr[id].ival[0]--;
                            (yyval.real) = ptr[id].ival[0];
                        }
                        else{
                            ptr[id].dval[0]-=1;
                            (yyval.real)=ptr[id].dval[0];
                        }
                    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 265 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (3)].string));
                            if(declared==-1)
                            {
                                int value = (yyvsp[(3) - (3)].real);
                                insert((yyvsp[(1) - (3)].string), &value, 0, varCount, 1, 0);
                                varCount++;
                                printf("Int type variable declared '%s'\n",(yyvsp[(1) - (3)].string));
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",(yyvsp[(1) - (3)].string));
                            }
                        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 280 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (1)].string));
                            if(declared==-1)
                            {
                                int value = 0;
                                insert((yyvsp[(1) - (1)].string), &value, 0, varCount, 1, 0);
                                varCount++;
                                printf("Int type variable declared '%s'\n",(yyvsp[(1) - (1)].string));
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",(yyvsp[(1) - (1)].string));
                            }
                        ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 295 "project.y"
    {
                            insert((yyvsp[(1) - (5)].string), tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpInteger);
                            printf("Int type array declared '%s'\n",(yyvsp[(1) - (5)].string));
                        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 306 "project.y"
    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = (yyvsp[(3) - (3)].real);
                    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 312 "project.y"
    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = (yyvsp[(1) - (1)].real);
                    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 326 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (3)].string));
                            if(declared==-1)
                            {
                                double value = (yyvsp[(3) - (3)].real);
                                insert((yyvsp[(1) - (3)].string), &value, 1, varCount, 1, 0);
                                varCount++;
                                printf("Real type variable declared '%s'\n",(yyvsp[(1) - (3)].string));
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",(yyvsp[(1) - (3)].string));
                            }
                        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 341 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (1)].string));
                            if(declared==-1)
                            {
                                double value = 0;
                                insert((yyvsp[(1) - (1)].string), &value, 1, varCount, 1, 0);
                                varCount++;
                                printf("Real type variable declared '%s'\n",(yyvsp[(1) - (1)].string));
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",(yyvsp[(1) - (1)].string));
                            }
                        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 356 "project.y"
    {
                            insert((yyvsp[(1) - (5)].string), tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpDouble);
                            printf("Real type array declared '%s'\n",(yyvsp[(1) - (5)].string));
                        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 367 "project.y"
    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (yyvsp[(3) - (3)].real);
                    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 373 "project.y"
    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (double)(yyvsp[(1) - (1)].real);
                    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 387 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (3)].string));
                            if(declared==-1)
                            {
                                char *value = (yyvsp[(3) - (3)].string);
                                insert((yyvsp[(1) - (3)].string), &value, 2, varCount, 1, 0);
                                varCount++;
                                printf("String type variable declared '%s'\n",(yyvsp[(1) - (3)].string));
                            }
                            else
                            {
                                printf("Variable '%s' already exists\n",(yyvsp[(1) - (3)].string));
                            }
                        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 402 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (1)].string));
                            if(declared==-1)
                            {
                                char *value;
                                insert((yyvsp[(1) - (1)].string), &value, 2, varCount, 1, 0);
                                varCount++;
                                printf("String type variable declared '%s'\n",(yyvsp[(1) - (1)].string));
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",(yyvsp[(1) - (1)].string));
                            }
                        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 420 "project.y"
    {
                    int index = getIndex((yyvsp[(1) - (3)].string));
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", (yyvsp[(1) - (3)].string));
                    }
                    else
                    {
                        {
                            if (ptr[index].type == 1)
                                ptr[index].dval[0] = (yyvsp[(3) - (3)].real);
                            if (ptr[index].type == 0)
                                ptr[index].ival[0] = (yyvsp[(3) - (3)].real);
                        }
                    }
                ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 437 "project.y"
    {
                    int index = getIndex((yyvsp[(1) - (3)].string));
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", (yyvsp[(1) - (3)].string));
                    }
                    strcpy(ptr[index].sval[0],(yyvsp[(3) - (3)].string) )
                ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 446 "project.y"
    {
                    int id = (yyvsp[(3) - (6)].integer);
                    int index = getIndex((yyvsp[(1) - (6)].string));
                    if (index == -1)
                    {
                         printf("there is no variable named %s.\n", (yyvsp[(1) - (6)].string));
                    }
                    else
                    {
                        if(id>=ptr[index].size){
                             printf("Given index out of range\n");
                        }
                        else
                        {
                            if (ptr[index].type == 1)
                                ptr[index].dval[id] = (yyvsp[(6) - (6)].real);
                            if (ptr[index].type == 0)
                                ptr[index].ival[id] =  (yyvsp[(6) - (6)].real);
                        }
                    }
                ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 471 "project.y"
    {
                if(floor((yyvsp[(3) - (3)].real))==ceil((yyvsp[(3) - (3)].real)))
                    printf("Printing Value: %d\n",(int)(yyvsp[(3) - (3)].real));
                else
                    printf("Printing Value: %lf\n",(yyvsp[(3) - (3)].real));
            ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 478 "project.y"
    {printVariable((yyvsp[(3) - (3)].string));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 480 "project.y"
    {printArrayIndex((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 482 "project.y"
    {printf("%s\n",(yyvsp[(2) - (2)].string));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 485 "project.y"
    {
                if(floor((yyvsp[(1) - (1)].real))==ceil((yyvsp[(1) - (1)].real)))
                printf("Printing Value: %d\n",(int)(yyvsp[(1) - (1)].real));
                else
                printf("Printing Value: %lf\n",(yyvsp[(1) - (1)].real));
            ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 492 "project.y"
    {printf("%s\n",(yyvsp[(1) - (1)].string));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 494 "project.y"
    {printVariable((yyvsp[(1) - (1)].string));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 496 "project.y"
    {printArrayIndex((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].real));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 502 "project.y"
    {takeInput((yyvsp[(3) - (3)].string),0);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 504 "project.y"
    {takeInput((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 506 "project.y"
    {takeInput((yyvsp[(1) - (1)].string),0);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 508 "project.y"
    {takeInput((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].integer));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 514 "project.y"
    {
                    conditionMatched[0]=1;
                    conPtr++;
                    conditionMatched[conPtr]=0;
                    
                        int isTrue = (fabs((yyvsp[(2) - (4)].integer))>1e-9);
                        if(isTrue)
                        {
                            printf("IF block %d: TRUE.\n\n",conPtr);
                            conditionMatched[conPtr] = 1;
                        }
                        else
                        {
                            printf("IF block %d: FALSE.\n\n",conPtr);
                        }
                    
                ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 533 "project.y"
    {printf("If condition started.\n");;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 541 "project.y"
    {       
                    if(conditionMatched[conPtr]==0)
                    {
                        printf("ELSE block %d: TRUE.\n\n",conPtr);
                        conditionMatched[conPtr] = 1;
                    }
                    else
                    {
                        printf("ELSE block %d: IGNORE.\n\n",conPtr);
                    }
                
                    conditionMatched[conPtr]=0;
                    conPtr--; 
                    printf("If condition finished.\n\n");           
                ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 561 "project.y"
    {
                    
                    if(conditionMatched[conPtr]==0)
                    {
                        int isTrue = (fabs((yyvsp[(2) - (5)].real))>1e-9);
                        if(isTrue)
                        {
                            printf("ELIF block %d: TRUE.\n\n",conPtr);
                            conditionMatched[conPtr] = 1;
                        }
                        else
                        {
                            printf("ELIF block %d: FALSE.\n\n",conPtr);
                        }
                    }
                    else
                    {
                        printf("ELIF block %d: IGNORE.\n\n",conPtr);
                    }
                    
                ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 585 "project.y"
    {
                    printf("Switch statement finished\n");
                ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 589 "project.y"
    {printf("Switch statement begin\n");;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 593 "project.y"
    {
            printf("Case statement finished\n");
        ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 597 "project.y"
    {
            printf("Default statement finished\n");
        ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 603 "project.y"
    {
                    printf("START OF FOR LOOP: \n");
                    for(double i=(yyvsp[(3) - (11)].real);i<(yyvsp[(5) - (11)].real);i=i+(yyvsp[(7) - (11)].real))
                    {
                        printf("FOR LOOP at Value %d\n",(int)i);
                    }
                    printf("End OF FOR LOOP. \n\n");
                ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 612 "project.y"
    {
                    printf("START OF WHILE LOOP: \n");
                    for(double i=(yyvsp[(3) - (10)].real);i<(yyvsp[(5) - (10)].real);i++ )
                    {
                        printf("WHILE LOOP at Value %d\n",(int)i);
                    }
                    printf("End OF WHILE LOOP. \n\n");
                ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 621 "project.y"
    {
                    printf("START OF WHILE LOOP: \n");
                    for(double i=(yyvsp[(3) - (10)].real);i<(yyvsp[(5) - (10)].real);i++ )
                    {
                        printf("WHILE LOOP at Value %d\n",(int)i);
                    }
                    printf("End OF WHILE LOOP. \n\n");
                ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 634 "project.y"
    {printf("Function declaration finished\n\n");;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 636 "project.y"
    {
                        printf("Function declaration finished with Int return type \n\n");
                    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 640 "project.y"
    {
                        printf("Function declaration finished with Real return type \n\n");
                    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 645 "project.y"
    {printf("Error: Nothing returned \n");;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 646 "project.y"
    {printf("Returned '%s'\n",(yyvsp[(2) - (3)].string));;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 647 "project.y"
    {printf("Returned '%d'\n",(yyvsp[(2) - (3)].integer));;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 648 "project.y"
    {printf("Returned '%lf'\n",(yyvsp[(2) - (3)].real));;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 651 "project.y"
    {
                        int id = getIndex((yyvsp[(2) - (2)].string));
                        int val=0;
                        if(id==-1)
                        {
                            printf("\nFunctions '%s' declared with ",(yyvsp[(2) - (2)].string));
                            insert((yyvsp[(2) - (2)].string), &val, 0, varCount, 1, 0);
                            varCount++;
                        }
                        else
                        {
                            printf("\nError: '%s' named function already exist\n",(yyvsp[(2) - (2)].string));
                            printf("New function declaration has: \n",(yyvsp[(2) - (2)].string));
                        }
                        
                    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 668 "project.y"
    {printf("No Parameter\n");;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 669 "project.y"
    {printf(" Parameter(s)\n");;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 672 "project.y"
    {
                        printf(",%s",(yyvsp[(4) - (4)].string));
                    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 676 "project.y"
    {
                        printf("%s",(yyvsp[(2) - (2)].string));
                    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 687 "project.y"
    {
                    printf("parameters used to call function '%s'\n",(yyvsp[(2) - (5)].string));
                    int id = getIndex((yyvsp[(2) - (5)].string));
                    int val=0;
                    if(id==-1)
                    {
                        printf("Error: '%s' named function has no declaration\n",(yyvsp[(2) - (5)].string));
                        //printf("\n'%s' ",ptr[1].name);
                    }
                    else
                    {
                        printf("Functions called\n");
                    }
                        
                ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 704 "project.y"
    {printf("No");;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 706 "project.y"
    {
                    int id = getIndex((yyvsp[(1) - (1)].string));
                    if(id==-1)
                        printf("Error: Variable '%s' doesn't exist\n",(yyvsp[(1) - (1)].string));
                    if(ptr[id].type==0)
                        printf("'%s' = %d, ",(yyvsp[(1) - (1)].string), ptr[id].ival[0]);
                    else if(ptr[id].type==1)
                        printf("'%s' = %lf, ",(yyvsp[(1) - (1)].string), ptr[id].dval[0]);
                    else
                        printf("'%s' = %s, ",(yyvsp[(1) - (1)].string), ptr[id].sval[0]);
                ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 718 "project.y"
    {
                    int id = getIndex((yyvsp[(3) - (3)].string));
                    if(id==-1)
                        printf("Error: Variable '%s' doesn't exist\n",(yyvsp[(3) - (3)].string));
                    if(ptr[id].type==0)
                        printf("'%s' = %d, ",(yyvsp[(3) - (3)].string), ptr[id].ival[0]);
                    else if(ptr[id].type==1)
                        printf("'%s' = %lf, ",(yyvsp[(3) - (3)].string), ptr[id].dval[0]);
                    else
                        printf("'%s' = %s, ",(yyvsp[(3) - (3)].string), ptr[id].sval[0]);
                ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 731 "project.y"
    {
                    printf("%d, ",(yyvsp[(3) - (3)].integer));
                ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 735 "project.y"
    {
                    printf("%d, ",(yyvsp[(1) - (1)].integer));
                ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 742 "project.y"
    {(yyval.real)=(yyvsp[(1) - (1)].integer);;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 744 "project.y"
    {(yyval.real)=(yyvsp[(1) - (1)].real);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 747 "project.y"
    {
                int id = getIndex((yyvsp[(1) - (1)].string));
                if(id==-1) printf("Error: Variable '%s' doesn't exist\n",(yyvsp[(1) - (1)].string));
                else if(ptr[id].type==2){
                    printf("String: %s\n",ptr[id].sval[0]);
                }
                else if(ptr[id].type==0) (yyval.real) = ptr[id].ival[0];
                else (yyval.real) = ptr[id].dval[0];
            ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 756 "project.y"
    {(yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 758 "project.y"
    {(yyval.real) = -(yyvsp[(2) - (2)].real);;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 760 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 762 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 764 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 766 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 768 "project.y"
    {(yyval.real) = pow((yyvsp[(1) - (3)].real),(yyvsp[(3) - (3)].real));;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 770 "project.y"
    {(yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 772 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 774 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 776 "project.y"
    {{(yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));};}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 778 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 780 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 782 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 784 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 786 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 788 "project.y"
    {(yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 790 "project.y"
    {(yyval.real) = !(yyvsp[(2) - (2)].real);;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 792 "project.y"
    {(yyval.real) = (yyvsp[(2) - (3)].real);}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 794 "project.y"
    {(yyval.real) = sin((yyvsp[(3) - (4)].real));;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 796 "project.y"
    {(yyval.real) = cos((yyvsp[(3) - (4)].real));;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 798 "project.y"
    {(yyval.real) = tan((yyvsp[(3) - (4)].real));;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 800 "project.y"
    {(yyval.real) = log10((yyvsp[(3) - (4)].real));;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 802 "project.y"
    {(yyval.real) = log((yyvsp[(3) - (4)].real));;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 804 "project.y"
    {(yyval.real) = sqrt((yyvsp[(3) - (4)].real));;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 807 "project.y"
    {
                        int id1 = getIndex((yyvsp[(2) - (5)].string));
                        int id2 = getIndex((yyvsp[(4) - (5)].string));
                        int max_value;
                        int var1_value = ptr[id1].ival[0];
                        int var2_value = ptr[id2].ival[0];

                        if (var1_value > var2_value) {
                            max_value = var1_value;
                        } else {
                            max_value = var2_value;
                        }

                        printf("Maximum value between %s and %s is: %d\n", (yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), max_value);
                        (yyval.real) = max_value;
                    ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 824 "project.y"
    {
                        int id1 = getIndex((yyvsp[(2) - (5)].string));
                        int id2 = getIndex((yyvsp[(4) - (5)].string));
                        int min_value;
                        int var1_value = ptr[id1].ival[0];
                        int var2_value = ptr[id2].ival[0];

                        if (var1_value < var2_value) {
                            min_value = var1_value;
                        } else {
                            min_value = var2_value;
                        }

                        printf("Minimum value between %s and %s is: %d\n", (yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), min_value);
                        (yyval.real) = min_value;
                    ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 843 "project.y"
    {
                int cl = ceil((yyvsp[(2) - (4)].real));int fl = floor((yyvsp[(2) - (4)].real));
                if(cl!=fl) printf("can't find FACTORIAL of real number\n");
                else {
                    long long x = 1;
                    for(long long i=1;i<=(yyvsp[(2) - (4)].real);i++) x*=i;
                    (yyval.real) = x;
                }
            ;}
    break;



/* Line 1455 of yacc.c  */
#line 3025 "project.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 856 "project.y"



int main(int argc, char **argv)
{
    free(ptr);
    ptr = realloc(ptr,10*sizeof(varptr));
    varTaken=100;
	yyin = freopen("input.txt","r",stdin);
	yyout = freopen("output.txt","w",stdout);
    
    printf("\n\n     -------Starting Program Execution-------\n\n\n");
	yyparse();
	return 0;
} 



