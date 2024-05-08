%{
    int yywrap();
    #define YYSTYPE double
    void yyerror(char *);
    #include "a.tab.h"    

    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;

%}

%option yylineno

%%
[a-z] {
    yylval = *yytext - 'a';
    return VARIABLE;   
}
0x\.?[a-f0-9]+|0x[a-f0-9]+\.[a-f0-9]* {
    yylval=atof(yytext);
    return HEXADECIMAL;
}
\.?[0-9]+|[0-9]+\.[0-9]* {
    yylval=atof(yytext);
    return INTEGER;
}
[-+()=/*&|~^@] {
    return *yytext;
}
sin {return SIN;}
cos {return COS;}
tan {return TAN;}
\n { yycolumn = 1;
     return *yytext; }
[ \t] ;
. yyerror("invalid input\n");

%%
int yywrap()
{
    return 1;
}