/*flex-wc.l*/
%option noyywrap
%{
int chars = 0;
int words = 0;
int lines = 0;
%}
%%
[a-zA-z]+ { words++; chars += strlen(yytext); }
\n { lines++; chars++; }
. { chars++; }
%%
int main() {
    yylex();
    printf("%8d %8d %8d\n", lines, words, chars);
    return 0;
}
