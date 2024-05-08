#ifndef HASH_H
#define HASH_H
#include "node.h"
struct Type
{
    enum {BASIC, ARRAY, STRUCTURE, FUNCTION} kind;
    union 
    {
        //基本类型：给INT(0), FLOAT(1)用
        int basicType;
        //数组类型
        struct {
            struct Type* elem;
            int size;
        }array;
        //结构体类型
        struct {
            char name[128];
            struct FieldList* fieldList;
        } structure;
        //函数类型信息
        struct {
            int paraNum;
            struct FieldList *para;
            struct Type* returnType;
        } function;
    }u;
};
struct FieldList{
    //域的名字
    char name[128];
    //可以再次包含数组或变量
    struct Type *type;
    int lineNumber;
    //下一个成员
    struct FieldList *next;
};

struct hashNode{
    //定义的变量名，函数名, 结构体变量名等
    char name[128];
    struct Type *type;
    struct hashNode *next;
    int varNo;
    int isParam;
};
#define HASHSIZE 0x40000
#define SYMTABLE 1
#define STRUCTTABLE 2

unsigned int hash_pjw(char *);
void initTables();
void insertIntoTable(struct hashNode *, int);
void printSemaError(int, int);
struct hashNode* getHashNode(char *, int);


void sematic_check(struct TreeNode *);
extern int semaSuccess;
#endif