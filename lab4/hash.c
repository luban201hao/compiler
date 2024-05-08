#include "hash.h"
#include "node.h"
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
void ExtDefList(struct TreeNode *);
void ExtDef(struct TreeNode *);
void ExtDecList(struct TreeNode *, struct Type *);
struct Type *Specifier(struct TreeNode *);
struct Type* StructSpecifier(struct TreeNode *);
struct FieldList *VarDec(struct TreeNode *, struct Type *, int);
void connectFieldList(struct FieldList* , struct FieldList *);
struct Type* Exp(struct TreeNode *);
int CompSt(struct TreeNode *, struct Type*);
int StmtList(struct TreeNode *, struct Type*);
int Stmt(struct TreeNode *, struct Type*);
int fieldListSame(struct FieldList *, struct FieldList *);
struct FieldList *Arg(struct TreeNode *);
int compareType(struct Type *, struct Type *);

struct hashNode *symbolTable[HASHSIZE];
struct hashNode *structDefTable[HASHSIZE];

int semaSuccess = 0;

//#define MYDEBUG
#ifdef MYDEBUG
#define LOG(x, arg...) \
do \
{   \
    printf(x, ##arg); \
} while(0)
#else
#define LOG(x, arg...) 
#endif 

unsigned int hash_pjw(char *name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~0x3fff)
            val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}

void initTables()
{
    memset(symbolTable,0,sizeof(symbolTable));
    memset(structDefTable,0,sizeof(structDefTable));
}
struct Type* newType()
{
    struct Type* res= (struct Type *) malloc(sizeof(struct Type));
    memset(res,0,sizeof(struct Type));
    return res;
}

struct FieldList* newFieldList()
{
    struct FieldList* res= (struct FieldList* ) malloc(sizeof(struct FieldList));
    memset(res,0,sizeof(struct FieldList));
    return res;
}

struct hashNode *newHashNode()
{
    struct hashNode* res= (struct hashNode *) malloc(sizeof(struct hashNode));
    memset(res,0,sizeof(struct hashNode));
    res->varNo = -1;
    return res;    
}


void insertIntoTable(struct hashNode *node, int table){
    unsigned int hash=hash_pjw(node->name);
    struct hashNode **currTable=NULL;
    if(table==SYMTABLE)
        currTable=symbolTable;
    else
        currTable=structDefTable;
    if(currTable[hash]==NULL)
    {
        currTable[hash]=node;
    }
    else
    {
        struct hashNode *last=currTable[hash];
        while(last->next!=NULL)
        {
            last=last->next;
        }
        last->next=node;
    }
    node->next=NULL;
}

struct hashNode* getHashNode(char *name, int table) {
    struct hashNode *res=NULL;
    unsigned int hashValue = hash_pjw(name);
    if(strlen(name) == 0)
        return NULL;
    if(table == SYMTABLE)
    {
        struct hashNode *tmp = symbolTable[hashValue];
        while(tmp!=NULL)
        {
            if(strcmp(tmp->name, name)==0)
            {
                res = tmp;
                break;
            }
            tmp = tmp->next;
        }
    }
    else
    {
        struct hashNode *tmp = structDefTable[hashValue];
        while(tmp!=NULL)
        {
            if(strcmp(tmp->name, name)==0)
            {
                res = tmp;
                break;
            }
            tmp = tmp->next;   
        }     
    }
    return res;
}

struct Type *copyType(struct Type* type)
{
    struct Type* new=newType();
    new->kind = type->kind;
    if(new->kind == BASIC)
    {
        new->u.basicType = type->u.basicType;
    }
    else if(new->kind == ARRAY)
    {
        new->u.array.size = type->u.array.size;
        new->u.array.elem = type->u.array.elem;
    }
    else if(new->kind == STRUCTURE)
    {
        new->u.structure = type->u.structure;
    }
    else if(new->kind == FUNCTION)
    {
        new->u.function.paraNum = type->u.function.paraNum;
        new->u.function.para = type->u.function.para;
        new->u.function.returnType = type->u.function.returnType;
    }
    return new;
}

char *errorInfo[] = {
    "undefined variable",
    "undefined function",
    "variable defined more than once",
    "function defined more than once",
    "The expression types on both sides of the assignment do not match",
    "Only a rvalue-expression appears to the left of an assignment",
    "Operand types are mismatched or operand type and operator are mismatched",
    "Return type is mismatched",
    "Parameters are mismatched when calling the function",
    "Operate other types of operand as array",
    "Operate other types of operand as function",
    "Use float as an array index",
    "Operate other types of operand as structure",
    "Visit an unexist structure field",
    "Field is defined more than once or initialized",
    "The name of the structure duplicates the name of a defined structure or variable",
    "Structure is used but haven't been defined"
};
void printSemaError(int type, int fisrtLine)
{
    semaSuccess = 0;
    printf("Error type %d at Line %d: %s\n", type, fisrtLine, errorInfo[type-1]);
}



char * OptTag(struct TreeNode *root)
{
    LOG("in func OptTag\n");
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        return n0->info;
    }
    else
        return NULL;
}

char *Tag(struct TreeNode *root)
{
    LOG("in func Tag, %d\n", root->lineNumber);
    struct TreeNode *n0 = getChild(root, 0);
    return n0->info;  
}
// TODO
struct FieldList* Dec(struct TreeNode *root, struct Type *type, int isInStruct)
{
    LOG("in func Dec\n");
    // VarDec
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        //VarDec will new a FieldList
        struct FieldList *list = VarDec(n0, type, isInStruct);
        return list;
    } 
    // VarDec ASSIGNOP Exp
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        if(isInStruct)
        {
            printSemaError(15, n1->lineNumber);
        }
        struct FieldList *list = VarDec(n0, type, isInStruct);
        // error in VarDec
        if(list==NULL)
        {
            return NULL;
        }
        struct FieldList *tmp = list;
        while(tmp!=NULL && tmp->next!=NULL)
        {
            tmp = tmp->next;
        }
        struct Type *type = Exp(n2);
        if(compareType(type, tmp->type) == 0)
        {
            printSemaError(5, n1->lineNumber);
            return NULL;
        }
        return list;
    }       
}

struct FieldList* DecList(struct TreeNode *root, struct Type *type, int isInStruct)
{
    LOG("in func DecList\n");
    // Dec
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct FieldList *list = Dec(n0, type, isInStruct);
        return list;
    }
    // Dec COMMA DecList
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        struct FieldList *list = Dec(n0, type, isInStruct);
        struct FieldList *list2 = DecList(n2, type, isInStruct);
        connectFieldList(list, list2);
        return list;    
    }
}

struct FieldList* Def(struct TreeNode *root, int isInStruct)
{
    LOG("in func Def\n");
    // Specifier DecList SEMI
    struct TreeNode *n0 = getChild(root, 0);
    struct TreeNode *n1 = getChild(root, 1);
    //这里只能得到类型名称，不能得到具体的变量名称
    struct Type *type = Specifier(n0); 
    return DecList(n1, type, isInStruct);
}

void connectFieldList(struct FieldList* l1, struct FieldList *l2)
{
    LOG("in func connectFieldList\n");
    if(l1 == NULL && l2 == NULL)
        return;
    if(l1 == NULL && l2!=NULL)
    {
        l1 = l2;
        return;
    }
    if(l1 != NULL && l2==NULL)
    {
        return;
    }
    LOG("l1 = %s, l2 = %s\n", l1->name, l2->name);
    while(l1->next != NULL)
    {
        l1 = l1->next;
    }
    l1->next = l2;
}

//此处，函数内变量或者结构体内变量最终也会通过VarDec等函数，加入符号表
struct FieldList *DefList(struct TreeNode *root, int isInStruct)
{
  LOG("=========in func DefList, line=%d\n", root->lineNumber);
  //Def DefList
  if(root->idxMax == 2)
  {
    struct TreeNode *n0 = getChild(root, 0);
    struct TreeNode *n1 = getChild(root, 1);
    LOG("==========Def DefList, line=%d\n", n0->lineNumber);
    //此处List1, List2都可能含有多个项目
    struct FieldList *list = Def(n0, isInStruct);
    struct FieldList *list2 = DefList(n1, isInStruct);
    connectFieldList(list, list2);
    //printf("in connect List, List1->name = %s, List2->name = %s, list1->next->name=%s\n", list->name, list2->name, list->next->name);
    return list;
  } 
  else
  {
    LOG("==========DefList :e\n");
    return NULL;
  } 
}

struct Type* StructSpecifier(struct TreeNode *root)
{
    LOG("in func StructSpecifier\n");
    char *name = NULL;
    // STRUCT OptTag LC DefList RC
    if(root->idxMax == 5)
    {
        name = OptTag(getChild(root, 1));
        //定义了一种新的结构体名称，需要加入符号表，此处需要返回其Type
        //name为空时，同样需要进行如下操作，但是不用检查名字是不是重复
        if(name!=NULL)
        {
            struct hashNode *h1 = getHashNode(name, SYMTABLE);
            struct hashNode *h2 = getHashNode(name, STRUCTTABLE);
            if(h1!=NULL || h2!=NULL)
            {
                printSemaError(16, getChild(root,1)->lineNumber);
                return NULL;
            }
        }
        struct FieldList* list = DefList(getChild(root, 3), 1); 
        //应当检查域名是否有出现重复的
        char map[100][100];
        memset(map,0,sizeof(map));
        int idx=0;
        struct FieldList *tmp = list;
        while(tmp!=NULL)
        {
            if(tmp->name!=NULL)
            {
                for(int i=0;i<idx;++i)
                {
                    if(strcmp(map[i], tmp->name)==0)
                    {
                        printSemaError(15, tmp->lineNumber);
                    }
                }
                strcpy(map[idx], tmp->name);
                idx++;
            }
            tmp = tmp->next;
        }
        LOG("in func StructSpecifier, after DefList\n");
        // new structure type 
        struct Type *type = newType();
        //LOG("in func StructSpecifier, after DefList 1\n");
        type->kind = STRUCTURE;
        //LOG("in func StructSpecifier, after DefList 2\n");
        type->u.structure.fieldList = list;
        //LOG("in func StructSpecifier, after DefList 3\n");
        if(name != NULL)
            strcpy(type->u.structure.name, name);
        //LOG("in func StructSpecifier, after DefList 4\n");
        //new hashNode
        struct hashNode *new = newHashNode();
        //LOG("in func StructSpecifier, after DefList 5\n");
        if(name != NULL)
            strcpy(new->name, name);
        //LOG("in func StructSpecifier, after DefList 6\n");
        new->type = type;
        //LOG("in func StructSpecifier, after DefList 7\n");
        insertIntoTable(new, STRUCTTABLE);
        return type;
    }
    // STRUCT Tag
    else
    {
        struct TreeNode *n1 = getChild(root, 1);
        name = Tag(n1);
        struct hashNode *node = getHashNode(name,STRUCTTABLE);
        //结构体没有定义过
        if(node == NULL)
        {
            printSemaError(17,n1->lineNumber);
            return NULL;
        }
        else
        {
            return node->type;
        }
    }

}

struct Type *Specifier(struct TreeNode *root)
{
    LOG("in func Specifier\n");
    if(root == NULL)
    {
        LOG("in Specifier, root=NULL\n");
        return NULL;
    }
    struct TreeNode *n0 = getChild(root, 0);
    // TYPE
    if(strcmp(n0->type,"TYPE")==0)
    {
        struct Type* type=newType();
        type->kind = BASIC;
        if(strcmp(n0->info,"int")==0)
        {
            type->u.basicType=0; // int
        }
        else
        {
            type->u.basicType=1; // float
        }
        return type;
    }
    else // StructSpecifier
    {
        struct TreeNode *n0 = getChild(root,0);
        return StructSpecifier(n0);
    }
}

void ExtDecList(struct TreeNode *root, struct Type *type)
{
    LOG("in func ExtDecList\n");
    // VarDec, 定义单个变量
    if(root->idxMax==1)
    {
        struct TreeNode *n0 = getChild(root,0);
        VarDec(n0, type, 0);
    }
    // VarDec COMMA ExtDecList 定义多个变量
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        VarDec(n0, type, 0);
        ExtDecList(n2,type);
    }
}


struct FieldList *VarDec(struct TreeNode *root, struct Type *type,int isInstruct)
{
    LOG("in func VarDec\n");
    // ID
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        char *varName = n0->info;
        struct hashNode *last1 = getHashNode(varName, SYMTABLE);
        struct hashNode *last2 = getHashNode(varName, STRUCTTABLE);
        if(!isInstruct && (last1 || last2))
        {
            printSemaError(3, n0->lineNumber);
            return NULL;
        }        
        struct FieldList *list = newFieldList();
        list->lineNumber = n0->lineNumber;
        strcpy(list->name, varName);
        //LOG("VarDec 1\n");
        struct hashNode *new = newHashNode();
        strcpy(new->name, varName);
        new->type = type;

        if(last1 == NULL && last2 == NULL)
            insertIntoTable(new, SYMTABLE);
        
        list->type = type;
        return list;
    }
    // VarDec LB INT RB
    // 此处不用考虑a[1.5], 此出错类型放在Exp [ Exp ] 中进行考虑
    else
    {
        LOG("VarDec 2\n");
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        struct FieldList *list = VarDec(n0, type, isInstruct);
        if(list == NULL)
        {
            return NULL;
        }
        struct Type *type = list->type;
        struct Type *new = newType();
        new->kind = ARRAY;
        new->u.array.elem = type;
        new->u.array.size = atoi(n2->info);
        list->type = new;
        //删除掉原来的类型变量，插入结构体的类型变量 
        struct hashNode *hash = getHashNode(list->name,SYMTABLE);
        hash->type = new;

        // for lab3
        if(type->kind == ARRAY)
            printSemaError(12, n0->lineNumber);

        return list;
    }
}

struct FieldList *ParaDec(struct TreeNode *root)
{
    // Specifier VarDec
    LOG("in func ParaDec\n");
    struct TreeNode *n0 = getChild(root, 0);
    LOG("1, n0->type=%s\n", n0->type);
    struct TreeNode *n1 = getChild(root, 1);
    LOG("2\n");    
    struct Type *type = Specifier(n0);
    LOG("type->info=%s\n", type->u.structure.name);
    struct FieldList *list = VarDec(n1, type, 0);


    return list;
}

struct FieldList *VarList(struct TreeNode *root)
{
    LOG("in func VarList\n");
    //ParaDec COMMA VarList
    if(root->idxMax == 3)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        LOG("VarList 3 child, n0->type=%s, n1->type=%s, n2->type=%s\n", n0->type, n1->type, n2->type);
        struct FieldList *list1 = ParaDec(n0);
        struct FieldList *list2 = VarList(n2);
        connectFieldList(list1, list2);
        // for lab3
        struct FieldList *tmp = list1;
        while(tmp!=NULL)
        {
            if(tmp->type->kind == ARRAY)
                printSemaError(12, root->lineNumber);
            tmp = tmp->next;
        }

        return list1;
    }
    //ParaDec
    else
    {
        LOG("VarList 1 child\n");
        struct TreeNode *n0 = getChild(root, 0);
        struct FieldList *list1 = ParaDec(n0);
        // for lab3
        if(list1->type->kind == ARRAY)
            printSemaError(12, root->lineNumber);
        return list1;
    }
}

struct hashNode* FunDec(struct TreeNode *root, struct Type *returnType)
{
    LOG("in func FunDec\n");
    struct TreeNode *n0 = getChild(root, 0);
    char *funcName = n0->info;
    if(getHashNode(funcName,SYMTABLE) || getHashNode(funcName, STRUCTTABLE))
    {
        printSemaError(4,n0->lineNumber);
        return NULL;
    }
    struct hashNode *hash = newHashNode();
    strcpy(hash->name, funcName);
    hash->type = newType();
    hash->type->kind = FUNCTION;
    hash->type->u.function.returnType = returnType;
    // ID LP VarList RP
    if(root->idxMax==4)
    {
        // function with argument;
        struct TreeNode *n2 = getChild(root, 2);
        struct FieldList *list = VarList(n2);
        hash->type->u.function.para = list;
        hash->type->u.function.paraNum = 0;
        while(list->next!=NULL)
        {
            hash->type->u.function.paraNum++;
            list = list->next;
        }
    }
    // ID LP RP
    else
    {
        // function without arguments
        hash->type->u.function.para = NULL;
        hash->type->u.function.paraNum = 0; 
    }
    return hash;
}
// return 1 if hava return
int Stmt(struct TreeNode *root, struct Type* funcReturnType)
{
    LOG("in func Stmt\n");
    //CompSt
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        return CompSt(n0, funcReturnType);
    }
    // Exp SEMI
    else if(root->idxMax == 2)
    {
        struct TreeNode *n0 = getChild(root, 0);
        Exp(n0);
    }
    // RETURN Exp SEMI
    else if(root->idxMax == 3)
    {
        struct TreeNode *n1 = getChild(root, 1);
        struct Type *type = Exp(n1);
        if(type!=NULL)
            LOG("in Stmt, Exp type=%d, %d\n", type->kind, type->u.basicType);
        LOG("in Stmt, returnType=%d, %d\n", funcReturnType->kind, funcReturnType->u.basicType);
        if(compareType(type, funcReturnType) == 0)
        {
            LOG("error8 1\n");
            printSemaError(8, n1->lineNumber);
        }
        return 1;
    }
    else if(root->idxMax == 5)
    {
        // IF LP Exp RP Stmt || WHILE LP Exp RP Stmt
        struct TreeNode *n2 = getChild(root, 2);
        struct TreeNode *n4 = getChild(root, 4);
        struct Type *type = Exp(n2);
        if(type == NULL || type->kind!=BASIC || type->u.basicType!=0)
        {
            printSemaError(7, n2->lineNumber);
        }
        return Stmt(n4, funcReturnType);
    }
    // IF LP Exp RP Stmt ELSE Stmt
    else
    {
        //如果if else 两个当中返回值类型不一样，也要报错
        struct TreeNode *n2 = getChild(root, 2);
        struct TreeNode *n4 = getChild(root, 4);
        struct TreeNode *n6 = getChild(root, 6);
        struct Type *type = Exp(n2);
        if(type==NULL || type->kind!=BASIC || type->u.basicType!=0)
        {
            printSemaError(7, n2->lineNumber);
        }           
        int res1 = Stmt(n4, funcReturnType);
        int res2 = Stmt(n6, funcReturnType);
        return (res1 || res2);
    }
    return 0;
}

int StmtList(struct TreeNode *root, struct Type* funcReturnType)
{
    LOG("in func StmtList\n");
    // Stmt StmtList 
    if(root->idxMax == 2)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        int res1 = Stmt(n0, funcReturnType);
        int res2 = StmtList(n1, funcReturnType);
        return (res1 || res2);
    }
    // empty
    return 0;
}

int CompSt(struct TreeNode *root, struct Type* funcReturnType)
{
    LOG("in func CompSt\n");
    struct TreeNode *n1 = getChild(root, 1);
    struct TreeNode *n2 = getChild(root, 2);
    DefList(n1, 0);
    int res = StmtList(n2, funcReturnType);
    return res;
}    

// return 1 if same
// else return 0
int compareType(struct Type *t1, struct Type *t2)
{
    LOG("in func compareType\n");
    if(t1 == NULL && t2 == NULL)
        return 1;
    if(t1 == NULL || t2 == NULL)
        return 0;
    if(t1->kind != t2->kind)
        return 0;
    if(t1->kind == BASIC)
    {
        if(t1->u.basicType != t2->u.basicType)
            return 0;
        else
            return 1;
    }
    else if(t1->kind == ARRAY)
    {
        return compareType(t1->u.array.elem, t2->u.array.elem);
    }
    else if(t1->kind == STRUCTURE)
    {
        if(strcmp(t1->u.structure.name,t2->u.structure.name) == 0)
            return 1;
        else
            return 0;
    }
    //函数类型, 无需进行比较
    else
    {
        return 0;
    }
    return 0;
}

void ExtDef(struct TreeNode *root)
{
    LOG("in func ExtDef\n");
    if(root->idxMax==3)
    {
        struct TreeNode *n0=getChild(root,0);
        struct TreeNode *n1=getChild(root,1);
        struct TreeNode *n2=getChild(root,2);
        //Specifier ExtDecList SEMI
        if(strcmp(n2->type,"SEMI") == 0)
        {
            struct Type *type = Specifier(n0);
            ExtDecList(n1, type);
        }
        //Sepcifier FunDec Compst
        else
        {
            struct Type *returnType = Specifier(n0);
            struct hashNode *funcType = FunDec(n1, returnType);
            
            if(funcType == NULL)
                return;
            // for lab3
            // 函数重复定义
            if(getHashNode(funcType->name, SYMTABLE)!=NULL || getHashNode(funcType->name, STRUCTTABLE)!=NULL)
            {
                printSemaError(4, n1->lineNumber);
            }
            insertIntoTable(funcType, SYMTABLE);

            //  函数定义，应当把声明的return类型，不断传入，直到stmt中出现return 的位置，进行判断。同时，出现return也应当进行标记，防止程序没有return
            int res = CompSt(n2, returnType);
            // 函数没有返回值
            if(res == 0 )
            {
                LOG("error8 2\n");
                //printSemaError(8, n0->lineNumber);
            }
           
        }
    }
    //Specifier SEMI
    else
    {
        //此处定义了一种结构体，应当加入符号表, 在后续函数中会进行添加
        struct TreeNode *n0=getChild(root,0);
        Specifier(n0);
    }
}

// 如果是左值，返回1，否则返回0
// 等号左边只能是：ID 或 Exp DOT ID 或 Exp LB Exp RB
int check_is_left(struct TreeNode *root)
{
    LOG("in func check_is_left\n");
    
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        if(strcmp(n0->type, "ID") == 0)
            return 1;
    }
    else if(root->idxMax == 3)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        if(strcmp(n0->type, "Exp") == 0 && strcmp(n1->type, "DOT") == 0 && strcmp(n2->type, "ID") == 0)
            return 1;
    }
    else if(root->idxMax == 4)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        struct TreeNode *n3 = getChild(root, 3);
        if(strcmp(n0->type, "Exp") == 0 && strcmp(n1->type, "LB") == 0 && strcmp(n2->type, "Exp") == 0 && strcmp(n3->type, "RB") == 0)
            return 1;
    }
    return 0;
}

struct Type* Exp(struct TreeNode *root)
{
    LOG("in func Exp\n");
    if(root->idxMax == 3)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        // Exp ASSIGNOP Exp
        if(strcmp(n1->type, "ASSIGNOP") == 0)
        {
            struct Type* t1 = Exp(n0);
            struct Type* t2 = Exp(n2);
            if(compareType(t1,t2)==0)
            {
                printSemaError(5, n1->lineNumber);
                return NULL;
            }
            if(t1 == NULL || t2 == NULL)
            {
                return NULL;
            }
            if(check_is_left(n0) ==0)
            {
                printSemaError(6, n1->lineNumber);
            }
            return t1;
        }
        // 逻辑运算：只有int类型的变量才能参加
        else if(strcmp(n1->type, "AND")==0 || strcmp(n1->type, "OR") == 0  )
        {
            struct Type* t1 = Exp(n0);
            struct Type* t2 = Exp(n2);
            if(t1 == NULL || t2==NULL)
            {
                return NULL;
            }
            if(!(t1->kind==BASIC  && t1->u.basicType==0 && t2->kind == BASIC && t2->u.basicType==0))
            {
                printSemaError(7, n1->lineNumber);
            }
            return t1;
        }
        else if(strcmp(n1->type, "RELOP") == 0)
        {
            struct Type* t1 = Exp(n0);
            struct Type* t2 = Exp(n2);
            if(t1 == NULL || t2==NULL)
            {
                return NULL;
            }
            if(!compareType(t1, t2))
            {
                printSemaError(7, n1->lineNumber);
                return NULL;
            }
            struct Type* res = newType();
            res->kind = BASIC;
            res->u.basicType = 0;
            return res;
        }
        // 加减乘除，判断两侧是否类型相同
        else if(strcmp(n1->type, "STAR") == 0 || strcmp(n1->type, "DIV") == 0 || strcmp(n1->type, "PLUS") == 0 || strcmp(n1->type, "MINUS") == 0)
        {
            struct Type* t1 = Exp(n0);
            struct Type* t2 = Exp(n2);
            if(t1 == NULL || t2==NULL)
            {
                return NULL;
            }
            if(compareType(t1, t2)==0)
            {
                printSemaError(7, n1->lineNumber);
                return NULL;
            }
            return t1;
        }
        // LP Exp RP
        else if(strcmp(n1->type, "Exp") == 0)
        {
            return Exp(n1);
        }
        // ID LP RP
        else if(strcmp(n0->type, "ID") == 0)
        {
            char *funcname = n0->info;
            struct hashNode *hash = getHashNode(funcname, SYMTABLE);
            if(hash == NULL)
            {
                printSemaError(2, n0->lineNumber);
                return NULL;
            }
            if(hash->type->kind!=FUNCTION)
            {
                printSemaError(11, n0->lineNumber);
                return NULL;
            }
            if(hash->type->u.function.para!=0)
            {
                printSemaError(9, n0->lineNumber);
                return hash->type->u.function.returnType;
            }
            return hash->type->u.function.returnType;
        }
        // Exp DOT ID
        else if(strcmp(n1->type, "DOT") == 0)
        {
            struct Type *type = Exp(n0);
            if(type == NULL || type->kind != STRUCTURE)
            {
                printSemaError(13, n1->lineNumber);
                return NULL;
            }
            LOG("Exp DOT ID, %d, n0->type = %d, n2->info=%s\n", n1->lineNumber, type->kind, n2->info);
            struct FieldList *list = type->u.structure.fieldList;
            int flag = 0;
            while(list != NULL)
            {
                if(strcmp(list->name, n2->info) == 0)
                {
                    flag = 1;
                    LOG("Exp DOT ID, type=%d\n", list->type->kind);
                    return list->type;
                    break;
                }
                list = list->next;
            }
            printSemaError(14, n1->lineNumber);
            return NULL;
        }
    }
    // NOT Exp | MINUS Exp
    else if(root->idxMax == 2)
    {
        //struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        return Exp(n1);
    }
    
    else if(root->idxMax == 4)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        // ID LP Args RP
        if(strcmp(n0->type, "ID") == 0)
        {
            struct hashNode* functionType = getHashNode(n0->info, SYMTABLE);
            if(functionType == NULL)
            {
                printSemaError(2,n0->lineNumber);
                return NULL;
            }
            LOG("funcName = %s\n", functionType->name);
            if(functionType->type->kind!=FUNCTION)
            {
                printSemaError(11, n0->lineNumber);
                return NULL;
            }
            struct FieldList *list = Arg(n2);
            if(fieldListSame(list, functionType->type->u.function.para) == 0)
            {
                printSemaError(9, n0->lineNumber);
            }
            return functionType->type->u.function.returnType;
        }
        // Exp LB Exp RB
        else
        {
            struct Type* type1 = Exp(n0);
            struct Type* type2 = Exp(n2);
            if(type1 == NULL || type2==NULL)
            {
                return NULL;
            }
            if(type1 == NULL || type1->kind!=ARRAY)
            {
                LOG("type1->kind=%d\n", type1->kind);
                printSemaError(10, n0->lineNumber);
                return NULL;
            }

            if(type2 == NULL || !(type2->kind==BASIC && type2->u.basicType==0))
            {
                printSemaError(12, n0->lineNumber);
                return NULL;
            }
            return type1->u.array.elem;
        }
    }
    else if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        if(strcmp(n0->type, "ID") == 0)
        {
            struct hashNode *hash = getHashNode(n0->info, SYMTABLE);
            if(hash == NULL)
            {
                printSemaError(1, n0->lineNumber);
                return NULL;
            }
            return hash->type;
        }
        else if(strcmp(n0->type, "INT") == 0)
        {
            struct Type *res = newType();
            res->kind = BASIC;
            res->u.basicType = 0;
            return res;
        }
        else if(strcmp(n0->type, "FLOAT") == 0)
        {
            struct Type *res = newType();
            res->kind = BASIC;
            res->u.basicType = 1;
            return res;            
        }
    }
    return NULL;
}

struct FieldList *Arg(struct TreeNode *root)
{
    LOG("in func Arg\n");
    // Exp
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct Type* type = Exp(n0);
        if(type == NULL)
            return NULL;
        struct FieldList *res = newFieldList();
        res->lineNumber = n0->lineNumber;
        res->type = type;
        return res; 
    }
    // Exp COMMA Args
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        struct Type* type = Exp(n0);
        if(type == NULL)
            return NULL;
        struct FieldList *list2 = Arg(n2);
        struct FieldList *res = newFieldList();
        res->lineNumber = n0->lineNumber;
        res->type = type;
        connectFieldList(res, list2);
        return res;
    }
}

// if same return 1 else return 0 
int fieldListSame(struct FieldList *l1, struct FieldList *l2)
{
    LOG("in func fieldListSame\n");
    if(l1==NULL && l2==NULL)
        return 1;
    while(l1!=NULL && l2!=NULL)
    {
        if(compareType(l1->type, l2->type)==0)
            return 0;
        l1=l1->next;
        l2=l2->next;
    }
    if(l1!=NULL || l2!=NULL)
        return 0;
    return 1;
}

void ExtDefList(struct TreeNode *root)
{
    LOG("in func ExtDefList\n");
    if(root->idxMax == 2)
    {
        ExtDef(getChild(root,0));
        ExtDefList(getChild(root,1));
    }
}

void createRead()
{
    struct hashNode *readFunc = newHashNode();
    strcpy(readFunc->name, "read");
    
    struct Type *type = newType();
    type->kind = FUNCTION;
    type->u.function.paraNum = 0;
    type->u.function.para = NULL;
    struct Type *returnType = newType();
    returnType->kind = BASIC;
    returnType->u.basicType = 0;
    type->u.function.returnType = returnType;
    
    readFunc->type = type;
    insertIntoTable(readFunc, SYMTABLE);
}

void createWrite()
{
    struct hashNode *writeFunc = newHashNode();
    strcpy(writeFunc->name, "write");
    
    struct Type *type = newType();
    type->kind = FUNCTION;
    type->u.function.paraNum = 1;

    struct FieldList *list = newFieldList();
    struct Type *inType = newType();
    inType->kind = BASIC;
    inType->u.basicType = 0;
    list->type = inType;
    type->u.function.para = list;

    struct Type *returnType = newType();
    returnType->kind = BASIC;
    returnType->u.basicType = 0;
    type->u.function.returnType = returnType;
    writeFunc->type = type;
    insertIntoTable(writeFunc, SYMTABLE);
}

void sematic_check(struct TreeNode *root)
{
    semaSuccess = 1;
    initTables();
    createRead();
    createWrite();
    LOG("in func sematic_check\n");
    struct TreeNode *n0 = getChild(root,0);
    ExtDefList(n0);
}