%{
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
%}


%union{
	int integer;
	double real;
	char* string;
}


%token HEADER MAIN END START VARIABLE ARRAY EOL ARROW RARROW INTEGER REAL STRING INTEGER_TYPE REAL_TYPE STRING_TYPE 
%token WRITE READ AND OR NOT XOR LOG LOG2 LN SIN COS TAN FACTORIAL SQRT IF ELIF ELSE OPTION ASSIGN
%token FROM TO REPEAT WHILE BY AS MODULE RET CALL MAX MIN COMMENT MOD SWITCH CASE DEFAULT

%type <integer> INTEGER MAIN END START startprog 
%type <string> VARIABLE INTEGER_TYPE REAL_TYPE STRING_TYPE STRING ARRAY COMMENT types
%type <real> expr REAL statements statement 
%nonassoc ELIF 
%nonassoc ELSE

%left PPLUS MMINUS
%left AND OR XOR NOT
%left LOG LOG2 LN SQRT 
%left GT LT EQUAL NOT_EQUAL LEQ GEQ
%left  PLUS MINUS
%left  MUL DIV MOD
%right  '^' FACTORIAL
%left EXPONENT SIN COS TAN

%%
startprog:    header func1 MAIN START statements END
                {
                    printf("\n\n     -------Program Started Successfully-------\n\n\n");
                    return 0;
                }
;

header: {   int val = 0;
            insert("qwertyuiop", &val, 0, varCount, 1, 0);
            varCount++}
        | header HEADER {printf("A Header Library is Declared\n");
                            int val = 0;
                            insert("qwertyuiop", &val, 0, varCount, 1, 0);
                            varCount++}

func1:  {}
        |func1 module_declare   {}

statements:     {}
                |statements statement   {}
;

statement:      EOL     {}
                |declaration    EOL     {}                
                |assign EOL        {}
                |WRITE ARROW print EOL    {}
                |READ RARROW scan EOL   {}
                |IF if_block else_statement   {}
                |loop_block     {}
                |switch_block     {}
                |module_call EOL    {}  
                |VARIABLE PPLUS        
                    {
                        int id = getIndex($1);
                        if(id==-1) printf("Variable '%s' already exists",$1);
                        else if(ptr[id].type==2) printf("Not Possible for String");
                        else if(ptr[id].type==0){
                            ptr[id].ival[0]++;
                            $$ = ptr[id].ival[0];
                        }
                        else{
                            ptr[id].dval[0]+=1;
                            $$=ptr[id].dval[0];
                        }
                    
                    }
                |VARIABLE MMINUS       
                    {
                        int id = getIndex($1);
                        if(id==-1) printf("Variable '%s' already exists",$1);
                        else if(ptr[id].type==2) printf("Not Possible for Strng");
                        else if(ptr[id].type==0){
                            ptr[id].ival[0]--;
                            $$ = ptr[id].ival[0];
                        }
                        else{
                            ptr[id].dval[0]-=1;
                            $$=ptr[id].dval[0];
                        }
                    }       
;

declaration:    INTEGER_TYPE integer_variable
                |REAL_TYPE real_variable
                |STRING_TYPE string_variable
;

integer_variable:   integer_variable ',' integer_statements
                    |integer_statements
;


integer_statements:     VARIABLE ASSIGN expr
                        {
                            int declared = getIndex($1);
                            if(declared==-1)
                            {
                                int value = $3;
                                insert($1, &value, 0, varCount, 1, 0);
                                varCount++;
                                printf("Int type variable declared '%s'\n",$1);
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",$1);
                            }
                        }
                        |VARIABLE
                        {
                            int declared = getIndex($1);
                            if(declared==-1)
                            {
                                int value = 0;
                                insert($1, &value, 0, varCount, 1, 0);
                                varCount++;
                                printf("Int type variable declared '%s'\n",$1);
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",$1);
                            }
                        }
                        |ARRAY ASSIGN '{' integer_values '}'
                        {
                            insert($1, tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpInteger);
                            printf("Int type array declared '%s'\n",$1);
                        }

;

integer_values:     integer_values ',' expr
                    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = $3;
                    }
                    |expr
                    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = $1;
                    }
;


real_variable:      real_variable ',' real_statements
                    |real_statements
;


real_statements:        VARIABLE ASSIGN expr
                        {
                            int declared = getIndex($1);
                            if(declared==-1)
                            {
                                double value = $3;
                                insert($1, &value, 1, varCount, 1, 0);
                                varCount++;
                                printf("Real type variable declared '%s'\n",$1);
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",$1);
                            }
                        }
                        |VARIABLE
                        {
                            int declared = getIndex($1);
                            if(declared==-1)
                            {
                                double value = 0;
                                insert($1, &value, 1, varCount, 1, 0);
                                varCount++;
                                printf("Real type variable declared '%s'\n",$1);
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",$1);
                            }
                        }
                        |ARRAY ASSIGN '{' real_values '}'
                        {
                            insert($1, tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpDouble);
                            printf("Real type array declared '%s'\n",$1);
                        }

;

real_values:        real_values ',' expr
                    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = $3;
                    }
                    |expr
                    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (double)$1;
                    }
;


string_variable:    string_variable ',' string_statements
                    |string_statements
;


string_statements:      VARIABLE ASSIGN STRING
                        {
                            int declared = getIndex($1);
                            if(declared==-1)
                            {
                                char *value = $3;
                                insert($1, &value, 2, varCount, 1, 0);
                                varCount++;
                                printf("String type variable declared '%s'\n",$1);
                            }
                            else
                            {
                                printf("Variable '%s' already exists\n",$1);
                            }
                        }
                        |VARIABLE
                        {
                            int declared = getIndex($1);
                            if(declared==-1)
                            {
                                char *value;
                                insert($1, &value, 2, varCount, 1, 0);
                                varCount++;
                                printf("String type variable declared '%s'\n",$1);
                            }
                            else
                            {
                                printf("Error: Variable '%s' already exists\n",$1);
                            }
                        }

;

assign:         VARIABLE ASSIGN expr
                {
                    int index = getIndex($1);
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", $1);
                    }
                    else
                    {
                        {
                            if (ptr[index].type == 1)
                                ptr[index].dval[0] = $3;
                            if (ptr[index].type == 0)
                                ptr[index].ival[0] = $3;
                        }
                    }
                }
                |VARIABLE ASSIGN STRING
                {
                    int index = getIndex($1);
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", $1);
                    }
                    strcpy(ptr[index].sval[0],$3 )
                }
                |ARRAY '[' INTEGER ']' ASSIGN expr
                {
                    int id = $3;
                    int index = getIndex($1);
                    if (index == -1)
                    {
                         printf("there is no variable named %s.\n", $1);
                    }
                    else
                    {
                        if(id>=ptr[index].size){
                             printf("Given index out of range\n");
                        }
                        else
                        {
                            if (ptr[index].type == 1)
                                ptr[index].dval[id] = $6;
                            if (ptr[index].type == 0)
                                ptr[index].ival[id] =  $6;
                        }
                    }
                }
;

print:                  
            print ',' expr                      
            {
                if(floor($3)==ceil($3))
                    printf("Printing Value: %d\n",(int)$3);
                else
                    printf("Printing Value: %lf\n",$3);
            }    
            
            |print ',' ARRAY                    {printVariable($3);}        
                
            |print ',' ARRAY '[' INTEGER ']'    {printArrayIndex($3,$5);}

            |print STRING                       {printf("%s\n",$2);}
            
            |expr
            {
                if(floor($1)==ceil($1))
                printf("Printing Value: %d\n",(int)$1);
                else
                printf("Printing Value: %lf\n",$1);
            }

            |STRING                             {printf("%s\n",$1);}
            
            |ARRAY                              {printVariable($1);}
                
            |ARRAY'[' expr ']'                  {printArrayIndex($1,$3);}
            
            
                
;

scan:       scan ',' VARIABLE                   {takeInput($3,0);} 
                
            |scan ',' ARRAY '[' INTEGER ']'     {takeInput($3,$5);} 
                
            |VARIABLE                           {takeInput($1,0);}
                
            |ARRAY '[' INTEGER ']'              {takeInput($1,$3);} 
                
;


if_block:       ifexpr START statement END 
                {
                    conditionMatched[0]=1;
                    conPtr++;
                    conditionMatched[conPtr]=0;
                    
                        int isTrue = (fabs($2)>1e-9);
                        if(isTrue)
                        {
                            printf("IF block %d: TRUE.\n\n",conPtr);
                            conditionMatched[conPtr] = 1;
                        }
                        else
                        {
                            printf("IF block %d: FALSE.\n\n",conPtr);
                        }
                    
                }
;

ifexpr:         '(' expr ')'        {printf("If condition started.\n");}

else_statement: elif_statement   single_else
                |single_else
;


single_else: ELSE START statement END
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
                }
    ;
elif_statement: elif_statement  single_elif
                |single_elif 
    ;
single_elif:    ELIF expr START statement END
                {
                    
                    if(conditionMatched[conPtr]==0)
                    {
                        int isTrue = (fabs($2)>1e-9);
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
                    
                }
;

switch_block:   switch1 '(' VARIABLE ')' START cases END
                {
                    printf("Switch statement finished\n");
                };

switch1:    SWITCH  {printf("Switch statement begin\n");}

cases: /* empty */
        | cases CASE INTEGER START statement
        {
            printf("Case statement finished\n");
        }
        | cases DEFAULT START statement
        {
            printf("Default statement finished\n");
        }
;

loop_block:     FROM '(' expr TO expr BY expr ')' START statements END
                {
                    printf("START OF FOR LOOP: \n");
                    for(double i=$3;i<$5;i=i+$7)
                    {
                        printf("FOR LOOP at Value %d\n",(int)i);
                    }
                    printf("End OF FOR LOOP. \n\n");
                }
                |WHILE '(' expr LT expr ')' REPEAT START statements END
                {
                    printf("START OF WHILE LOOP: \n");
                    for(double i=$3;i<$5;i++ )
                    {
                        printf("WHILE LOOP at Value %d\n",(int)i);
                    }
                    printf("End OF WHILE LOOP. \n\n");
                }
                |WHILE '(' expr GT expr ')' REPEAT START statements END
                {
                    printf("START OF WHILE LOOP: \n");
                    for(double i=$3;i<$5;i++ )
                    {
                        printf("WHILE LOOP at Value %d\n",(int)i);
                    }
                    printf("End OF WHILE LOOP. \n\n");
                }
                
                
                
;

module_declare:   module '(' module_type1 ')' START statement END       {printf("Function declaration finished\n\n");}
                    | module '(' module_type1 ')' ARROW INTEGER_TYPE START statement ret1 END
                    {
                        printf("Function declaration finished with Int return type \n\n");
                    }   
                    | module '(' module_type1 ')' ARROW REAL_TYPE START statement ret1 END
                    {
                        printf("Function declaration finished with Real return type \n\n");
                    }   
;

ret1:               {printf("Error: Nothing returned \n");}
                    |RET VARIABLE EOL       {printf("Returned '%s'\n",$2);}
                    |RET INTEGER EOL        {printf("Returned '%d'\n",$2);}
                    |RET REAL EOL           {printf("Returned '%lf'\n",$2);}

module:             MODULE VARIABLE
                    {
                        int id = getIndex($2);
                        int val=0;
                        if(id==-1)
                        {
                            printf("\nFunctions '%s' declared with ",$2);
                            insert($2, &val, 0, varCount, 1, 0);
                            varCount++;
                        }
                        else
                        {
                            printf("\nError: '%s' named function already exist\n",$2);
                            printf("New function declaration has: \n",$2);
                        }
                        
                    }

module_type1:                       {printf("No Parameter\n");}
                    |module_type    {printf(" Parameter(s)\n");}

module_type:        module_type ',' types VARIABLE
                    {
                        printf(",%s",$4);
                    }
                    |types VARIABLE
                    {
                        printf("%s",$2);
                    }
;

types:      INTEGER_TYPE  
            |REAL_TYPE    
            |STRING_TYPE  
;
                
module_call:    CALL VARIABLE '(' parameters ')'
                {
                    printf("parameters used to call function '%s'\n",$2);
                    int id = getIndex($2);
                    int val=0;
                    if(id==-1)
                    {
                        printf("Error: '%s' named function has no declaration\n",$2);
                        //printf("\n'%s' ",ptr[1].name);
                    }
                    else
                    {
                        printf("Functions called\n");
                    }
                        
                }
;

parameters:             {printf("No");}
                |VARIABLE
                {
                    int id = getIndex($1);
                    if(id==-1)
                        printf("Error: Variable '%s' doesn't exist\n",$1);
                    if(ptr[id].type==0)
                        printf("'%s' = %d, ",$1, ptr[id].ival[0]);
                    else if(ptr[id].type==1)
                        printf("'%s' = %lf, ",$1, ptr[id].dval[0]);
                    else
                        printf("'%s' = %s, ",$1, ptr[id].sval[0]);
                }
                |parameters ',' VARIABLE
                {
                    int id = getIndex($3);
                    if(id==-1)
                        printf("Error: Variable '%s' doesn't exist\n",$3);
                    if(ptr[id].type==0)
                        printf("'%s' = %d, ",$3, ptr[id].ival[0]);
                    else if(ptr[id].type==1)
                        printf("'%s' = %lf, ",$3, ptr[id].dval[0]);
                    else
                        printf("'%s' = %s, ",$3, ptr[id].sval[0]);
                }
                
                |parameters ',' INTEGER
                {
                    printf("%d, ",$3);
                }
                |INTEGER
                {
                    printf("%d, ",$1);
                }
                

;

expr:       INTEGER {$$=$1;}                 
                                         
            |REAL {$$=$1;}       
               
            |VARIABLE             
            {
                int id = getIndex($1);
                if(id==-1) printf("Error: Variable '%s' doesn't exist\n",$1);
                else if(ptr[id].type==2){
                    printf("String: %s\n",ptr[id].sval[0]);
                }
                else if(ptr[id].type==0) $$ = ptr[id].ival[0];
                else $$ = ptr[id].dval[0];
            }
            |PLUS expr          {$$ = $2;}
             
            |MINUS expr         {$$ = -$2;}
            
            |expr PLUS expr     {$$ = $1 + $3;}         
                
            |expr MINUS expr    {$$ = $1 - $3;}      
                
            |expr MUL expr      {$$ = $1 * $3;}
                 
            |expr DIV expr      {$$ = $1 / $3;}        
                
            |expr EXPONENT expr    {$$ = pow($1,$3);}        
                
            |expr MOD expr      {$$ = (int)$1 % (int)$3;}         
                
            |expr LT expr     {$$ = ($1 < $3);}         
                
            |expr GT expr  {$$ = ($1 > $3);}        
                
            |expr LEQ expr      {{$$ = ($1 <= $3);}}        
                
            |expr GEQ expr      {$$ = ($1 >= $3);}       
                
            |expr EQUAL expr    {$$ = ($1 == $3);}       
                
            |expr NOT_EQUAL expr {$$ = ($1 != $3);}        
                
            |expr AND expr      {$$ = ($1 && $3);}       
                
            |expr OR expr       {$$ = ($1 || $3);}         
                
            |expr XOR expr      {$$ = ((int)$1 ^ (int)$3);}         
                
            |NOT expr           {$$ = !$2;}              
                
            |'(' expr ')'      {$$ = $2}       
              
            |SIN '(' expr ')'  {$$ = sin($3);}   
              
            |COS '(' expr ')'  {$$ = cos($3);}    
              
            |TAN '(' expr ')'  {$$ = tan($3);}      
              
            |LOG '(' expr ')'  {$$ = log10($3);}      
                
            |LN '(' expr ')'   {$$ = log($3);}       
              
            |SQRT '(' expr ')' {$$ = sqrt($3);}  

            |MAX VARIABLE ',' VARIABLE ')'
                    {
                        int id1 = getIndex($2);
                        int id2 = getIndex($4);
                        int max_value;
                        int var1_value = ptr[id1].ival[0];
                        int var2_value = ptr[id2].ival[0];

                        if (var1_value > var2_value) {
                            max_value = var1_value;
                        } else {
                            max_value = var2_value;
                        }

                        printf("Maximum value between %s and %s is: %d\n", $2, $4, max_value);
                        $$ = max_value;
                    } 
            |MIN VARIABLE ',' VARIABLE ')'
                    {
                        int id1 = getIndex($2);
                        int id2 = getIndex($4);
                        int min_value;
                        int var1_value = ptr[id1].ival[0];
                        int var2_value = ptr[id2].ival[0];

                        if (var1_value < var2_value) {
                            min_value = var1_value;
                        } else {
                            min_value = var2_value;
                        }

                        printf("Minimum value between %s and %s is: %d\n", $2, $4, min_value);
                        $$ = min_value;
                    } 
                     
                
            |'(' expr ')' FACTORIAL   
            {
                int cl = ceil($2);int fl = floor($2);
                if(cl!=fl) printf("can't find FACTORIAL of real number\n");
                else {
                    long long x = 1;
                    for(long long i=1;i<=$2;i++) x*=i;
                    $$ = x;
                }
            }
    ; 

                        

%%


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


