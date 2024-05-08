%{
    #include "node.h"
    #include "hash.h"
    #include "translate.h"
    #include "obj.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include "lex.yy.c"
    void yyerror(char* );
    void myError(char* );
%}

%union {
    char *str;
    struct TreeNode *node;
}



%right <str> ASSIGNOP
%left <str> OR
%left <str> AND
%left <str> RELOP
%left <str> PLUS MINUS
%left <str> STAR DIV
%right <str> NOT
%left <str> DOT
%nonassoc MINUSINT
%left <str> LB RB
%left <str> LP RP 
%nonassoc THEN
%nonassoc ELSE
%token <str> INT FLOAT TYPE STRUCT RETURN IF WHILE ID SEMI COMMA LC RC



%type <node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier
%type <node> OptTag Tag VarDec FunDec VarList ParamDec CompSt 
%type <node> StmtList Stmt DefList Def Dec DecList Exp Args



%%

Program:        ExtDefList { root = $$ = newNode("Program", @$.first_line);
                             add_child(root, $1);
                           }

ExtDefList:     ExtDef ExtDefList  {
                                        //printf("ExtDecList: ExtDef ExtDefList\n"); 
                                        $$ = newNode("ExtDefList", @$.first_line);
                                        add_child($$, $1);
                                        add_child($$, $2);
                                   }
                | /* e */          { 
                                        $$ = newNode("ExtDefList", @$.first_line);
                                        $$->hasE=1;
                }

ExtDef: Specifier ExtDecList SEMI {
                                        //printf("Specifier ExtDecList SEMI\n");
                                        $$ = newNode("ExtDef", @$.first_line);
                                        add_child($$, $1);
                                        add_child($$, $2);
                                        struct TreeNode *n3 = newNode("SEMI", @$.first_line);
                                        add_child($$, n3);
                                  }
    |   Specifier SEMI  {
                            //printf("Specifier SEMI\n");
                            $$ = newNode("ExtDef", @$.first_line);
                            add_child($$, $1);
                            struct TreeNode *n2 = newNode("SEMI", @$.first_line);
                            add_child($$, n2);
                        }
    |   Specifier FunDec CompSt {
                                    //printf("Specifier FunDec CompSt\n");
                                    $$ = newNode("ExtDef", @$.first_line);
                                    add_child($$, $1);
                                    add_child($$, $2);
                                    add_child($$, $3);
                                }
    | error SEMI {
        myError("ExtDef: error SEMI");
        $$ = newNode("ExtDef", @$.first_line); 
    }
    | Specifier error {
        myError("ExtDef: Specifier error");
        $$ = newNode("ExtDef", @$.first_line); 
    }
    | Specifier error SEMI {
        myError("ExtDef: Specifier error SEMI");
        $$ = newNode("ExtDef", @$.first_line); 
    }

ExtDecList: VarDec {
        $$ = newNode("ExtDecList", @$.first_line);
        add_child($$, $1);
    }
    | VarDec COMMA ExtDecList {
        $$ = newNode("ExtDecList", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("COMMA", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | VarDec error ExtDecList {
        myError("VarDec error ExtDecList");
        $$ = newNode("ExtDecList", @$.first_line); 
    }

Specifier: TYPE {
                    $$ = newNode("Specifier", @$.first_line);
                    struct TreeNode *n1 = newNode("TYPE", @$.first_line);
                    n1->info = strdup($1);
                    add_child($$, n1);
                }
        |   StructSpecifier {
                                $$ = newNode("Specifier", @$.first_line);
                                add_child($$, $1);
                            }

StructSpecifier: STRUCT OptTag LC DefList RC {
                                                $$ = newNode("StructSpecifier", @$.first_line);
                                                struct TreeNode *n1 = newNode("STRUCT", @$.first_line);
                                                struct TreeNode *n3 = newNode("LC", @$.first_line);
                                                struct TreeNode *n5 = newNode("RC", @$.first_line);
                                                add_child($$, n1);
                                                add_child($$, $2);
                                                add_child($$, n3);
                                                add_child($$, $4);
                                                add_child($$, n5);
                                             }
                | STRUCT Tag {
                                $$ = newNode("StructSpecifier", @$.first_line);
                                struct TreeNode *n1 = newNode("STRUCT", @$.first_line);
                                add_child($$, n1);
                                add_child($$, $2);
                             }

OptTag: ID {
            $$ = newNode("OptTag", @$.first_line);
            struct TreeNode *n1 = newNode("ID", @$.first_line);
            n1->info = strdup($1);
            add_child($$, n1);
            }
        | /* e */ {
            $$ = newNode("OptTag", @$.first_line);
            $$->hasE=1;
        }

Tag: ID {
            $$ = newNode("Tag", @$.first_line);
            struct TreeNode *n1 = newNode("ID", @$.first_line);
            n1->info = strdup($1);
            add_child($$, n1);    
        }

VarDec: ID {
        $$ = newNode("VarDec", @$.first_line);
        struct TreeNode *n1 = newNode("ID", @$.first_line);
        n1->info = strdup($1);
        add_child($$, n1);  
    }
    | VarDec LB INT RB {
        $$ = newNode("VarDec", @$.first_line);
        struct TreeNode *n2 = newNode("LB", @$.first_line);
        struct TreeNode *n3 = newNode("INT", @$.first_line);
        n3->info = strdup($3);
        struct TreeNode *n4 = newNode("RB", @$.first_line);
        add_child($$, $1);
        add_child($$, n2);
        add_child($$, n3);
        add_child($$, n4);
    } 
    | VarDec LB error RB {
        $$ = newNode("VarDec", @$.first_line); 
    }

FunDec: ID LP VarList RP {
        
        $$ = newNode("FunDec", @$.first_line);
        struct TreeNode *n1 = newNode("ID", @$.first_line);
        n1->info = strdup($1);
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n4 = newNode("RP", @$.first_line);
        add_child($$, n1);
        add_child($$, n2);
        add_child($$, $3);
        add_child($$, n4);
        //printf("FunDec, %s\n", n1->info);
    }
    |  ID LP RP {
        $$ = newNode("FunDec", @$.first_line);
        struct TreeNode *n1 = newNode("ID", @$.first_line);
        n1->info = strdup($1);
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n3 = newNode("RP", @$.first_line);
        add_child($$, n1);
        add_child($$, n2);
        add_child($$, n3);        
    }

    | ID LP error RP {
        myError("ID LP error RP");
        $$ = newNode("FunDec", @$.first_line); 
    }


VarList: ParamDec COMMA VarList {
        //printf("VarList: ParamDec COMMA VarDec\n");
        $$ = newNode("VarList", @$.first_line);
        struct TreeNode *n2 = newNode("COMMA", @$.first_line);        
        add_child($$, $1);
        add_child($$, n2);
        add_child($$, $3);
    }
    | ParamDec {
        //printf("VarList: ParamDec\n");
        $$ = newNode("VarList", @$.first_line);
        add_child($$, $1);
    }

ParamDec: Specifier VarDec {
        $$ = newNode("ParamDec", @$.first_line);
        add_child($$, $1);
        add_child($$, $2);
    }

CompSt: LC DefList StmtList RC {
        $$ = newNode("CompSt", @$.first_line);
        struct TreeNode *n1 = newNode("LC", @$.first_line);
        struct TreeNode *n4 = newNode("RC", @$.first_line);
        add_child($$, n1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, n4);
    }


StmtList: Stmt StmtList {
        //printf("StmtList: Stmt StmtList\n");
        $$ = newNode("StmtList", @$.first_line);
        add_child($$, $1);
        add_child($$, $2);
    }
    | /* e */ {
        $$ = newNode("StmtList", @$.first_line);
        $$->hasE=1;
    }

Stmt: Exp SEMI {
        //printf("Stmt: Exp SEMI\n");
        $$ = newNode("Stmt", @$.first_line);
        struct TreeNode *n2 = newNode("SEMI", @$.first_line);
        add_child($$, $1);
        add_child($$, n2);
    }
    | Exp error SEMI {
        myError("Exp error SEMI");
        $$ = newNode("Stmt", @$.first_line); 
    }
    | CompSt {
        $$ = newNode("Stmt", @$.first_line);
        add_child($$, $1);
    }
    | RETURN Exp SEMI {
        $$ = newNode("Stmt", @$.first_line);
        struct TreeNode *n1 = newNode("RETURN", @$.first_line);
        struct TreeNode *n3 = newNode("SEMI", @$.first_line);
        add_child($$, n1);
        add_child($$, $2);
        add_child($$, n3);
    }
    | IF LP Exp RP Stmt %prec THEN {
        $$ = newNode("Stmt", @$.first_line);
        struct TreeNode *n1 = newNode("IF", @$.first_line);
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n4 = newNode("RP", @$.first_line);
        add_child($$, n1);
        add_child($$, n2);
        add_child($$, $3);
        add_child($$, n4);
        add_child($$, $5);
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        $$ = newNode("Stmt", @$.first_line);
        struct TreeNode *n1 = newNode("IF", @$.first_line);
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n4 = newNode("RP", @$.first_line);
        struct TreeNode *n6 = newNode("ELSE", @$.first_line);
        add_child($$, n1);
        add_child($$, n2);
        add_child($$, $3);
        add_child($$, n4);
        add_child($$, $5);   
        add_child($$, n6);
        add_child($$, $7);     
    }
    | WHILE LP Exp RP Stmt {
        $$ = newNode("Stmt", @$.first_line);
        struct TreeNode *n1 = newNode("WHILE", @$.first_line);
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n4 = newNode("RP", @$.first_line);  
        add_child($$, n1);
        add_child($$, n2);
        add_child($$, $3);
        add_child($$, n4);
        add_child($$, $5);              
    }
    | error SEMI {
        myError("Stmt: error SEMI");
        $$ = newNode("Stmt", @$.first_line); 
    }
    | Exp error {
        myError("Stmt: Exp error");
        $$ = newNode("Stmt", @$.first_line); 
    }
    | RETURN Exp error {
        myError("Stmt: RETURN Exp error");
        $$ = newNode("Stmt", @$.first_line); 
    }
    | IF LP error RP Stmt %prec THEN {
        myError("Stmt: IF LP error RP Stmt %prec THEN");
        $$ = newNode("Stmt", @$.first_line); 
    }
    | IF LP error RP Stmt ELSE Stmt {
        myError("Stmt: IF LP error RP Stmt ELSE Stmt");
        $$ = newNode("Stmt", @$.first_line); 
    }
    | WHILE LP error RP Stmt {
        myError("Stmt: WHILE LP error RP Stmt");
        $$ = newNode("Stmt", @$.first_line); 
    }



DefList: Def DefList {
        $$ = newNode("DefList", @$.first_line);
        add_child($$, $1);
        add_child($$, $2);
    }
    | /* e */ {
        $$ = newNode("DefList", @$.first_line);
        $$->hasE=1;
    }

Def: Specifier DecList SEMI {
        //printf("Def: Specifier DecList SEMI\n");
        $$ = newNode("Def", @$.first_line);
        struct TreeNode *n3 = newNode("SEMI", @$.first_line); 
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, n3);
    }
    | Specifier error SEMI {
        myError("Def: Specifier error SEMI");
        $$ = newNode("Def", @$.first_line); 
    }
    | Specifier DecList error {
        myError("Def: Specifier DecList error");
        $$ = newNode("Def", @$.first_line); 
    }
    

DecList: Dec {
        $$ = newNode("DecList", @$.first_line);
        add_child($$, $1);
    }
    | Dec COMMA DecList {
        $$ = newNode("DecList", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("COMMA", @$.first_line);
        add_child($$, n2);
        add_child($$, $3); 
    }
Dec: VarDec {
        //printf("Dec: VarDec\n");
        $$ = newNode("Dec", @$.first_line);
        add_child($$, $1);
    }
    | VarDec ASSIGNOP Exp {
        $$ = newNode("Dec", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("ASSIGNOP", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);         
    }

Exp: Exp ASSIGNOP Exp {
        //printf("Exp ASSIGNOP Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("ASSIGNOP", @$.first_line);
        add_child($$, n2); 
        add_child($$, $3);
    }
    | Exp AND Exp {
        //printf("Exp AND Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("AND", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp OR Exp {
        //printf("Exp OR Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("OR", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp RELOP Exp {
        //printf("Exp RELOP Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("RELOP", @$.first_line);
        n2->info = strdup($2);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp PLUS Exp {
        ////printf("Exp PLUS Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("PLUS", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp MINUS Exp {
        //printf("Exp MINUS Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("MINUS", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp STAR Exp {
        //printf("Exp STAR Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("STAR", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp DIV Exp {
        //printf("Exp DIV Exp\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("DIV", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | LP Exp RP {
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("LP", @$.first_line);
        struct TreeNode *n3 = newNode("RP", @$.first_line);
        add_child($$, n1);
        add_child($$, $2);
        add_child($$, n3);
    }
    | MINUS Exp %prec MINUSINT {
        //printf("Exp MINUS Exp\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("MINUS", @$.first_line);
        add_child($$, n1); 
        add_child($$, $2);        
    }
    | NOT Exp {
        //printf("NOT Exp\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("NOT", @$.first_line);
        add_child($$, n1); 
        add_child($$, $2); 
    }
    | ID LP Args RP {
        //printf("ID LP Args RP\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("ID", @$.first_line);
        n1->info = strdup($1);
        add_child($$, n1);   
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n4 = newNode("RP", @$.first_line); 
        add_child($$, n2);
        add_child($$, $3);
        add_child($$, n4);

    }
    | ID LP RP {
        //printf("ID LP RP\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("ID", @$.first_line);
        n1->info = strdup($1);
        struct TreeNode *n2 = newNode("LP", @$.first_line);
        struct TreeNode *n3 = newNode("RP", @$.first_line); 
        add_child($$, n1);
        add_child($$, n2);
        add_child($$, n3);        
    }
    | Exp LB Exp RB {
        //printf("Exp LB Exp RB\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n2 = newNode("LB", @$.first_line);
        struct TreeNode *n4 = newNode("RB", @$.first_line);
        add_child($$, $1);
        add_child($$, n2);
        add_child($$, $3);
        add_child($$, n4);
    }

    | Exp DOT ID {
        //printf("Exp DOT ID\n");
        $$ = newNode("Exp", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("DOT", @$.first_line);
        struct TreeNode *n3 = newNode("ID", @$.first_line);
        n3->info = strdup($3);
        add_child($$, n2);
        add_child($$, n3);
    }
    | ID {
        //printf("Exp: ID, %s\n", $1);
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("ID", @$.first_line);
        n1->info = strdup($1);
        add_child($$, n1);
    }
    | INT {
        //printf("Exp: INT\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("INT", @$.first_line);
        n1->info = strdup($1);
        add_child($$, n1);        
    }
    | FLOAT {
        //printf("FLOAT\n");
        $$ = newNode("Exp", @$.first_line);
        struct TreeNode *n1 = newNode("FLOAT", @$.first_line);
        n1->info = strdup($1);
        add_child($$, n1);
    }
    | Exp ASSIGNOP error {
        myError("Exp: Exp ASSIGNOP error");
        $$ = newNode("Error", @$.first_line); 
    }
    | Exp AND error {
        myError("Exp: Exp AND error");
        $$ = newNode("Error", @$.first_line); 
    }
    | Exp OR error {
        myError("Exp: Exp OR error");
        $$ = newNode("Error", @$.first_line); 
    }
    | Exp RELOP error {
        myError("Exp: Exp RELOP error");
        $$ = newNode("Exp", @$.first_line); 
    }
    | Exp PLUS error {
        myError("Exp: Exp PLUS error");
        $$ = newNode("Exp", @$.first_line); 
    }
    | Exp MINUS error {
        myError("Exp: Exp MINUS error");
        $$ = newNode("Exp", @$.first_line); 
    }
    | Exp STAR error {
        myError("Exp: Exp STAR error");
        $$ = newNode("Exp", @$.first_line); 
    }
    | Exp DIV error {
        myError("Exp: Exp DIV error");
        $$ = newNode("Exp", @$.first_line); 
    }
    | LP error RP {
        myError("Exp: LP error RP");
        $$ = newNode("Exp", @$.first_line); 
    }
    | MINUS error {
        myError("Exp: MINUS error");
        $$ = newNode("Exp", @$.first_line);
    }
    | NOT error {
        myError("Exp: NOT error");
        $$ = newNode("Exp", @$.first_line);
    }
    | ID LP error RP {
        myError("Exp: ID LP error RP");
        $$ = newNode("Exp", @$.first_line);
    }
    | Exp LB error RB {
        myError("Exp: Exp LB error RB");
        $$ = newNode("Exp", @$.first_line);
    }
    | Exp LB Exp error RB {
        myError("Exp: Exp LB Exp error RB");
        $$ = newNode("Exp", @$.first_line); 
    }

    
Args: Exp COMMA Args {
        $$ = newNode("Args", @$.first_line);
        add_child($$, $1);
        struct TreeNode *n2 = newNode("COMMA", @$.first_line);
        add_child($$, n2);
        add_child($$, $3);
    }
    | Exp {
        $$ = newNode("Args", @$.first_line);
        add_child($$, $1);
    }
%%

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

    FILE *out = fopen(argv[2], "w+");
    
    tra_Program(root);

    FILE *tmp = fopen(argv[3], "w+");
    printIr(tmp);
    fclose(tmp);
    
    gen_obj(out);   
    fclose(f);
    fclose(out);
    
    return 0;
}


