%{
    #include "syntax.tab.h"  
    #include <stdlib.h>
    #include <stdio.h>

    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;  
%}

%option yylineno

INT 0|([1-9][0-9]*)
FLOAT ([0-9]+\.[0-9]+)|((([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+))[eE][+-]?[0-9]+)

%%
{INT}        { yylval.str = strdup(yytext); 
        //printf("INT:%s\n",yylval.str); 
        return INT; }
{FLOAT}     { yylval.str = strdup(yytext);
        //printf("FLOAT:%s\n", yylval.str);
        return FLOAT;}

int|float    { yylval.str=strdup(yytext); 
        //printf("TYPE: %s\n",yylval.str); 
        return TYPE;}
struct    { yylval.str=strdup(yytext); 
        //printf("STRUCT\n");
        return STRUCT;}
return    { yylval.str=strdup(yytext); 
        //printf("RETURN\n");
        return RETURN;}
if    { yylval.str=strdup(yytext); 
        //printf("IF\n");
        return IF;}
else    { yylval.str=strdup(yytext); 
        //printf("ELSE\n");
        return ELSE;}
while    { yylval.str=strdup(yytext); 
        //printf("WHILE\n");
        return WHILE;}
[a-zA-Z_][a-zA-Z_0-9]*    { yylval.str=strdup(yytext); 
        //printf("this is ID:%s\n", yylval.str);
        return ID;}
;    { yylval.str=strdup(yytext); 
        //printf("SEMI\n");
        return SEMI;}
","    { yylval.str=strdup(yytext); 
        //printf("COMMA\n");
        return COMMA;}
>=|<=|==|!=    { yylval.str=strdup(yytext); 
        //printf("RELOP:%s\n", yylval.str);
        return RELOP;}
>|<    { yylval.str=strdup(yytext); 
        //printf("RELOP:%s\n", yylval.str);
        return RELOP;}
=    { yylval.str=strdup(yytext); 
    //printf("=\n");
    return ASSIGNOP;}
"+"    { yylval.str=strdup(yytext); 
        //printf("+\n");
        return PLUS;}
-    { yylval.str=strdup(yytext); 
        //printf("MINUS\n");
        return MINUS;}

"*"    { yylval.str=strdup(yytext); 
        //printf("STAR\n");
        return STAR;}
"/"    { yylval.str=strdup(yytext); 
        //printf("DIV\n");
        return DIV;}
"&&"    { yylval.str=strdup(yytext); 
        //printf("AND\n");
        return AND;}
"||"    { yylval.str=strdup(yytext); 
        //printf("OR\n");
        return OR;}
"."    { yylval.str=strdup(yytext); 
        //printf("DOT\n");
        return DOT;}
"!"    { yylval.str=strdup(yytext); 
        //printf("NOT\n");
        return NOT;}
"("   { yylval.str=strdup(yytext); 
        //printf("LP\n");
        return LP;}    
")"    { yylval.str=strdup(yytext); 
        //printf("RP\n");
        return RP;}
"["    { yylval.str=strdup(yytext); 
        //printf("LB\n");
        return LB;}
"]"    { yylval.str=strdup(yytext); 
        //printf("RB\n");
        return RB;}
"{"    { yylval.str=strdup(yytext); 
        //printf("LC\n");
        return LC;}
"}"    { yylval.str=strdup(yytext); 
        //printf("RC\n");
        return RC;}
[\n]   { 
    ////printf("line end \n");
    yycolumn = 1;}
[ \t]   { 
    ////printf("space\n");
}
. { printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); 
    successFlag=0;
    lexFlag=0;
}
%%

int yywrap()
{
    return 1;
}