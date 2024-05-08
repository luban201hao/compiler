%token HEXADECIMAL INTEGER VARIABLE SIN COS TAN
%left '+' '-'
%left '*' '/'
%left '&'
%left '|'
%left '^'
%right '@' '~'
%left '!'

%{
    #include<stdio.h>
    #include<math.h>
    #define YYSTYPE double
    #define pi 3.1415926
    void yyerror(char*);
    int yylex(void);
    double sym[26];

    extern void yyrestart(FILE *);


%}



%%
program: 
    program statement '\n'
    |
    ;
statement:
    expr {printf("ans=%lf, line=%d\n", $1, @$.first_line);}
    | VARIABLE '=' expr {sym[(int)$1]=$3; }
    ;
expr:
    INTEGER
    | HEXADECIMAL 
    | VARIABLE {$$ = sym[(int)$1];}
    | expr '+' expr {$$ = $1 + $3;}
    | expr '-' expr    {$$ = $1 - $3;}
    | expr '*' expr    {$$ = $1 * $3;}
    | expr '/' expr    {$$ = $1 / $3;}
    | expr '&' expr    {$$ = (int)$1 & (int)$3;}
    | expr '|' expr    {$$ = (int)$1 | (int)$3;}
    | '~' expr         {$$ = ~(int)$2;}
    | '@' expr         {$$ = sqrt($2);}
    | expr '@' expr    {$$ = $1*sqrt($3);}
    | expr '!'         {int i=1,s=1;for(;i<=$2;i++)s*=i;$$=s;}
    | expr '^' expr    {$$=pow($1,$3);}
    | '('expr')'       {$$ = $2;}
    | SIN'('expr')'       {$$ = sin($3*pi/180.0);}
    | COS'('expr')'       {$$ = cos($3*pi/180.0);}
    | TAN'('expr')'       {$$ = tan($3*pi/180.0);}
    ;
	
%%

void yyerror(char* s)
{
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char **argv)
{
    printf("A simple calculator.\n可以用的运算符：+-*/&|~!^@ \n要注意的是三角函数使用时要加括号。 例：sin(60)\n");
    
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
    return 0;
}
