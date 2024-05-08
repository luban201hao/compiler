
#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "hash.h"
struct Operand{
    enum{
        OP_VARIABLE,
        OP_CONSTANT,
        OP_ADDRESS,
        OP_LABEL,
        // OP_ARR,
        // OP_STRUCT,
        OP_TEMP,
    }kind;
    union {
        int varno;  // 变量编号
        int val;  // 立即数的值
        int labelno; // 标签编号
        int tempno; // 临时变量的编号
    } u;
    struct Type *type;
    // 保存原始变量名或函数名 
    char *name;
    // 表示是函数参数
    int isPara;    
};

struct InterCode{
    enum {
        IC_LABEL,
        IC_FUNCTION,
        IC_ASSIGN,
        IC_ADD,
        IC_SUB,
        IC_MUL,
        IC_DIV,
        IC_GETADDR,
        IC_DEREF,
        IC_DEREFASSIGN,
        IC_GOTO,
        IC_IFGOTO,
        IC_RETURN,
        IC_DEC,
        IC_ARG,
        IC_CALL,
        IC_PARAM,
        IC_READ,
        IC_WRITE
    } kind;
    struct Operand *op1;
    struct Operand *op2;
    struct Operand *op3;
    // using for CALL / FUNCTION
    char *funcName;
    char relop[5];
};

struct CodeList{
    struct InterCode *code;
    struct CodeList *prev;
    struct CodeList *next;
};

void tra_Program(struct TreeNode *root);
void printIr(FILE *);

#endif