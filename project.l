%{
#include <stdio.h>
#include "project.tab.h"
#include<string.h>
#include<math.h>
extern int yydebug;
extern FILE *yyin;
extern FILE *yyout;

int yyparse();	

%}

%%
"@import"[ ][a-z]+[.][h]    						 {return HEADER; }


"start"									 {return MAIN;}
":"									 {return START;}
";"                                      				 {return EOL;}
"end"									 {return END;}


"int"									 {return INTEGER_TYPE;}
"real" 									 {return REAL_TYPE;}
"string"								 {return STRING_TYPE;}


"+"									 {return PLUS;}
"-"									 {return MINUS;}
"*"									 {return MUL;}
"/"									 {return DIV;}
":="									 {return ASSIGN;}
"++"									 {return PPLUS;}
"--"									 {return MMINUS;}
"%"									 {return MOD;}
"**"									 {return EXPONENT;}


"=="									 {return EQUAL;}
"<>"									 {return NOT_EQUAL;}
"<"									 {return LT;}
">"									 {return GT;}
"<="									 {return LEQ;}
">="									 {return GEQ;}


"write"								 	 {return WRITE;}
"->"									 {return ARROW;}
"read"									 {return READ;}
"<-"									 {return RARROW;}


"^"									 {return XOR;}
"&"									 {return AND;}
"|"									 {return OR;}
"~"									 {return NOT;}


"SIN" 									 {return SIN;}
"COS" 									 {return COS;}
"TAN" 									 {return TAN;}
"SQRT" 									 {return SQRT;}
"LOG" 									 {return LOG;}
"LN"  									 {return LN;}
"!"									 {return FACTORIAL;}


"if"									 {return IF;}
"elseif"								 {return ELIF;}
"else"									 {return ELSE;}

"choice"								 {return SWITCH;}
"case"									 {return CASE;}
"def"									 {return DEFAULT;}


"repeat"								 {return REPEAT;}
"while"									 {return WHILE;}
"from"									 {return FROM;}
"-->"									 {return TO;}
"step"									 {return BY;}


"module"								 {return MODULE;}
"call"									 {return CALL;}
"ret"									 {return RET;}

"max("								 	 {return MAX;}
"min("								 	 {return MIN;}


[/][*][A-Za-z0-9. \n\t;',]*[*][/]					{
    										char* comment = yytext + 2;
    										int commentLength = yyleng - 4;
    										comment[commentLength] = '\0';
    										printf("This is a comment: %s\n\n", comment);
									}

[0-9]+  								{yylval.integer = atoi(yytext);return INTEGER;}
[0-9]*[.][0-9]+([eE][+-]?[0-9]+)?		 			{yylval.real=atof(yytext); return REAL;}

[A-Za-z0-9]+ 							 	{yylval.string = strdup(yytext);return VARIABLE;}
[A-Za-z0-9]+[#] 						 	{yylval.string = strdup(yytext); return ARRAY;}
\"(\\|[^"\\])*\"						 	{
										char* tmp = strdup(yytext);
										int n = strlen(tmp);
										yylval.string = malloc(n*sizeof(char));
  										memcpy(yylval.string,&tmp[1],n-2);
										yylval.string[n-2]='\0';
										return STRING;
									}
[,.(){}\]\[]	 						 	{return yytext[0];}
[ \t\n]									{}
.									{printf("\nUnknown character: %s\n", yytext);}
%%
int yywrap()
{
	return 1;
}
int yyerror(char *s){
	fprintf(stderr,"error: %s\n", s);
}
