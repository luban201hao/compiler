#include "hash.h"
#include "node.h"
#include "translate.h"
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define MYDEBUG
#ifdef MYDEBUG
#define LOG(x, arg...) \
do \
{   \
    printf(x, ##arg); \
} while(0)
#else
#define LOG(x, arg...) 
#endif

struct Operand* tra_VarDec(struct TreeNode *);
struct Operand* tra_Exp(struct TreeNode *);
void tra_Args(struct TreeNode *, struct TreeNode *);
void getNowIdx(struct TreeNode *, struct Operand **, int *);
void tra_Stmt(struct TreeNode *);
void tra_CompSt(struct TreeNode *);

int var_num = 0, label_num = 0, temp_num = 0;
//icHead中不存储任何内容, 作为dummy节点
struct CodeList *icHead = NULL;

int getTypeSize(struct Type *type)
{
    if(type->kind == BASIC)
        return 4;
    else if(type->kind == ARRAY)
    {
        int res = type->u.array.size;
        int mul = getTypeSize(type->u.array.elem);
        return res * mul;
    }
    else if(type->kind == STRUCTURE)
    {
        struct FieldList *field = type->u.structure.fieldList;
        int res = 0;
        while(field!=NULL)
        {
            res += getTypeSize(field->type);
            field = field->next;
        }
        return res;
    }
    return 0;
}

struct CodeList *newCodeList()
{
    struct CodeList *ret = (struct CodeList *)malloc(sizeof(struct CodeList));
    ret->code = NULL;
    ret->prev = NULL;
    ret->next = NULL;
    return ret;
}

void insertIntoList(struct CodeList *prev, struct CodeList *curr)
{
    struct CodeList *next = prev->next;
    curr->next = next;
    curr->prev = prev;
    prev->next = curr;
    next->prev = curr;
}

void insertICToTail(struct InterCode *code)
{
    struct CodeList *new  = newCodeList();
    new->code = code;
    struct CodeList *last = icHead->prev;
    insertIntoList(last, new);
}



struct Operand *newOperand(int kind, int info, char *name, struct Type *type)
{
    struct Operand *ret = (struct Operand *)malloc(sizeof(struct Operand));
    memset(ret, 0, sizeof(struct Operand));
    ret->kind = kind;
    ret->u.labelno = info;
    ret->name = name;
    ret->type = type;
    return ret;
}

struct InterCode *newInterCode(int kind, struct Operand *op1, struct Operand *op2, struct Operand *op3)
{
    struct InterCode *ret = (struct InterCode *)malloc(sizeof(struct InterCode));
    memset(ret, 0, sizeof(struct InterCode));
    ret->kind = kind;
    ret->op1 = op1;
    ret->op2 = op2;
    ret->op3 = op3;
    return ret;
}

// ===================================================================================================

struct hashNode* getStructHash(struct TreeNode *root)
{
    LOG("getStructHash, root->info = %s, lineNumber = %d, root->idxMax = %d\n", root->info, root->lineNumber, root->idxMax);
    // ID
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 =getChild(root, 0);
        LOG("n0->info = %s, lineNumber = %d\n", n0->info, n0->lineNumber);
        struct hashNode *ret = getHashNode(n0->info, SYMTABLE);
        LOG("hashNode->type = %d, name = %s\n", ret->type->kind, ret->type->u.structure.name);
        return ret;
    }
    // Exp LB Exp RP, // 第一个Exp里面可能再次包含Exp LB Exp RP
    else if(root->idxMax == 4)
    {
        struct TreeNode *n0 =getChild(root, 0);
        return getStructHash(n0);
    }
    // Exp DOT Exp   f.x[10]
    else if(root->idxMax == 3)
    {
        struct TreeNode *n0 =getChild(root, 0);
        struct TreeNode *n2 =getChild(root, 2);
        LOG("n0->idxMax = %d, n2->idxMax = %d\n", n0->idxMax, n2->idxMax);      
        return getStructHash(n2);
    }
    else if(root->idxMax == 0)
    {
        return getHashNode(root->info, SYMTABLE);
    }
    return NULL;
}

// for struct member, get offset in struct
int getOffset(struct Type *type, char *name)
{
    LOG("getOffset=================================\n");
    struct FieldList *list = type->u.structure.fieldList;
    int ret = 0;
    while(list!=NULL)
    {
        LOG("get offset, list->name = %s, name = %s\n", list->name, name);
        if(strcmp(list->name, name) == 0)
        {
            LOG("get offset return = %d\n", ret);
            return ret;
        }
        else
        {
            ret += getTypeSize(list->type);
            LOG("ret now = %d\n", ret);
        }
        list = list->next;
    }
    LOG("get offset, no match\n");
    return 0;
}

struct hashNode *getArrHash(struct TreeNode *root)
{
    LOG("getArrHash\n");
    // Exp
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        return getHashNode(n0->info, SYMTABLE);
    }
    // Exp LB Exp RB
    else if(root->idxMax == 4)
    {
        struct TreeNode *n0 = getChild(root, 0);
        return getArrHash(n0);
    }
    // Exp DOT Exp
    else
    {
        struct TreeNode *n2 = getChild(root, 2);
        LOG("getArrHash, n2->info = %s\n", n2->info);
        return getHashNode(n2->info, SYMTABLE);
    }  
}

struct Operand* tra_Exp(struct TreeNode *root)
{
    LOG("tra_Exp, root->line_number=%d, info=%s, type=%s\n", root->lineNumber, root->info, root->type);
    
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        // 进入此处时，只能是变量。结构体和数组会被事先处理好
        // 但是在Args中出现时，此处可能是一个结构体
        if(strcmp(n0->type, "ID") == 0)
        {
            LOG("Exp ID = %s\n", n0->info);
            struct hashNode *hash = getHashNode(n0->info, SYMTABLE);
            if(hash->varNo == -1)
            {
                hash->varNo = var_num++;
            }
            struct Operand *ret = newOperand(OP_VARIABLE, hash->varNo, n0->info, hash->type);
            return ret;
        }
        else if(strcmp(n0->type, "INT") == 0)
        {
            LOG("Exp INT, info = %s\n", n0->info);
            struct Operand *ret = newOperand(OP_CONSTANT, atoi(n0->info), NULL, NULL);
            return ret;
        }
        else if(strcmp(n0->type, "FLOAT") == 0)
        {
            LOG("Exp FLOAT, info = %s\n", n0->info);
            // no float
            struct Operand *ret = newOperand(OP_CONSTANT, atoi(n0->info), NULL, NULL);
            return ret;
        }
    }
    else if(root->idxMax == 3)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        if(strcmp(n1->type, "ASSIGNOP") == 0)
        {
            LOG("Exp ASSIGNOP Exp\n");
            struct Operand *left = tra_Exp(n0);
            struct Operand *right = tra_Exp(n2);
            if(right->kind == OP_ADDRESS)
            {
                struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                // tmp = *right
                struct InterCode *deref = newInterCode(IC_DEREF, tmp, right, NULL);
                insertICToTail(deref);
                // right = tmp
                right = tmp;
            }
            if(left->kind != OP_ADDRESS)
            {
                // left = right
                struct InterCode *new = newInterCode(IC_ASSIGN, left, right, NULL);
                insertICToTail(new);
            }
            else
            {
                // *left = right
                struct InterCode *new = newInterCode(IC_DEREFASSIGN, left, right, NULL);
                insertICToTail(new);
            }
            return left;
        }
        else if(strcmp(n1->type, "AND") == 0)
        {
            LOG("Exp AND Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
            struct Operand *zero = newOperand(OP_CONSTANT, 0, NULL, NULL);
            struct Operand *one = newOperand(OP_CONSTANT, 1, NULL, NULL);
            struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            // if x1 == 0 goto label1
            struct InterCode *new = newInterCode(IC_IFGOTO, x1, zero, label1); 
            strcpy(new->relop,"==");
            insertICToTail(new);
            // if x2 == 0 goto label1
            new = newInterCode(IC_IFGOTO, x2, zero, label1);
            strcpy(new->relop,"==");
            insertICToTail(new);
            // tmp = 1
            new = newInterCode(IC_ASSIGN, tmp, one, NULL);
            insertICToTail(new);
            // GOTO label2
            new = newInterCode(IC_GOTO, label2, NULL, NULL);
            insertICToTail(new);
            // LABEL label1:
            new = newInterCode(IC_LABEL, label1, NULL, NULL);
            insertICToTail(new);
            // tmp = 0
            new = newInterCode(IC_ASSIGN, tmp, zero, NULL);
            insertICToTail(new);            
            // LABEL label2:
            new = newInterCode(IC_LABEL, label2, NULL, NULL);
            insertICToTail(new);
            return tmp;
        }
        else if(strcmp(n1->type, "OR") == 0)
        {
            LOG("Exp OR Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
            struct Operand *zero = newOperand(OP_CONSTANT, 0, NULL, NULL);
            struct Operand *one = newOperand(OP_CONSTANT, 1, NULL, NULL);
            struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            // if x1 != 0 goto label1
            struct InterCode *new = newInterCode(IC_IFGOTO, x1, zero, label1); 
            strcpy(new->relop,"!=");
            insertICToTail(new);
            // if x2 != 0 goto label1
            new = newInterCode(IC_IFGOTO, x2, zero, label1);
            strcpy(new->relop,"!=");
            insertICToTail(new);
            // tmp = 0
            new = newInterCode(IC_ASSIGN, tmp, zero, NULL);
            insertICToTail(new);
            // GOTO label2
            new = newInterCode(IC_GOTO, label2, NULL, NULL);
            insertICToTail(new);
            // LABEL label1:
            new = newInterCode(IC_LABEL, label1, NULL, NULL);
            insertICToTail(new);
            // tmp = 1
            new = newInterCode(IC_ASSIGN, tmp, one, NULL);
            insertICToTail(new);            
            // LABEL label2:
            new = newInterCode(IC_LABEL, label2, NULL, NULL);
            insertICToTail(new);
            return tmp;            
        }
        else if(strcmp(n1->type, "RELOP") == 0)
        {
            LOG("Exp RELOP Exp, RELOP: %s\n", n1->info);
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
            struct Operand *zero = newOperand(OP_CONSTANT, 0, NULL, NULL);
            struct Operand *one = newOperand(OP_CONSTANT, 1, NULL, NULL);
            struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            // if x1 relop x2 goto label1
            struct InterCode *new = newInterCode(IC_IFGOTO, x1, x2, label1);
            strcpy(new->relop, n1->info);
            insertICToTail(new);
            // tmp = 0
            new = newInterCode(IC_ASSIGN, tmp, zero, NULL);
            insertICToTail(new);
            // GOTO label2
            new = newInterCode(IC_GOTO, label2, NULL, NULL);
            insertICToTail(new);
            // LABEL label1:
            new = newInterCode(IC_LABEL, label1, NULL, NULL);
            insertICToTail(new);
            // tmp = 1
            new = newInterCode(IC_ASSIGN, tmp, one, NULL);
            insertICToTail(new);            
            // LABEL label2:
            new = newInterCode(IC_LABEL, label2, NULL, NULL);
            insertICToTail(new);
            return tmp; 
        }
        else if(strcmp(n1->type, "PLUS") == 0)
        {
            LOG("Exp PLUS Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            LOG("in exp + exp 1\n");
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
             LOG("in exp + exp 2\n");
            struct InterCode *new = newInterCode(IC_ADD, tmp, x1, x2);
            insertICToTail(new);
            return tmp;
        }
        else if(strcmp(n1->type, "MINUS") == 0)
        {
            LOG("Exp MINUS Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
            struct InterCode *new = newInterCode(IC_SUB, tmp, x1, x2);
            insertICToTail(new);
            return tmp;            
        }
        else if(strcmp(n1->type, "STAR") == 0)
        {
            LOG("Exp STAR Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
            struct InterCode *new = newInterCode(IC_MUL, tmp, x1, x2);
            insertICToTail(new);
            return tmp;              
        }
        else if(strcmp(n1->type, "DIV") == 0)
        {
            LOG("Exp DIV Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *x1 = tra_Exp(n0);
            struct Operand *x2 = tra_Exp(n2);
            if(x1->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x1, NULL);
                insertICToTail(deref);
                x1 = tmpderef;
            }
            if(x2->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x2, NULL);
                insertICToTail(deref);
                x2 = tmpderef;
            }
            struct InterCode *new = newInterCode(IC_DIV, tmp, x1, x2);
            insertICToTail(new);
            return tmp;             
        }
        // LP Exp RP
        else if(strcmp(n1->type, "Exp") == 0)
        {
            LOG("LP Exp RP\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            LOG("LP Exp RP 1\n");
            struct Operand *ret = tra_Exp(n1);
            if(ret->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, tmp, NULL);
                insertICToTail(deref);
                ret = tmpderef;
            }            
            LOG("LP Exp RP 2\n");
            struct InterCode *new = newInterCode(IC_ASSIGN, tmp, ret, NULL);
            insertICToTail(new);
            LOG("LP Exp RP 3\n");
            return tmp;
        }
        // ID LP RP
        else if(strcmp(n0->type, "ID") == 0)
        {
            LOG("ID LP RP, info = %s\n", n0->info);
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            if(strcmp(n0->info,"read") == 0)
            {
                struct InterCode *new = newInterCode(IC_READ, tmp, NULL, NULL);
                insertICToTail(new);
            }
            else
            {
                struct hashNode *hash = getHashNode(n0->info, SYMTABLE);
                struct InterCode *new = newInterCode(IC_CALL, tmp, NULL, NULL);
                new->funcName = hash->name;
                insertICToTail(new);
            }
            return tmp;
        }
        // Exp DOT ID  
        else if(strcmp(n1->type, "DOT") == 0)
        {
            LOG("Exp DOT ID, lineNumber = %d\n", n1->lineNumber);
            struct hashNode *structType = getStructHash(n0);
            LOG("Exp DOT ID 1, lineNumber = %d\n", n1->lineNumber);
            // exp is not an array
            if(structType->type->kind == STRUCTURE)
            {
                int offset = getOffset(structType->type, n2->info);
                LOG("offset = %d\n", offset);
                struct Operand *base = newOperand(OP_VARIABLE, structType->varNo, structType->name, structType->type);
                struct Operand *add = newOperand(OP_CONSTANT, offset, NULL, NULL);
                struct Operand *ret = newOperand(OP_ADDRESS, temp_num++, NULL, NULL);
                struct InterCode *new;
                // ret := &base
                if(!structType->isParam)
                {
                    new = newInterCode(IC_GETADDR, ret, base, NULL);
                    insertICToTail(new);
                }
                // ret = base;
                else
                {
                    new = newInterCode(IC_ASSIGN, ret, base, NULL);
                    insertICToTail(new);
                }
                // ret := ret + #add
                new = newInterCode(IC_ADD, ret, add, ret);
                insertICToTail(new);
                return ret;
            }
            // Exp is an array
            else
            {
                struct Operand* ret = tra_Exp(n0);

                struct Type *type = structType->type;
                while(type->kind == ARRAY)
                {
                    type = type->u.array.elem;
                }
                int offset = getOffset(type, n2->info);
                LOG("in get Offset 2, offset = %d, n2->info = %s, hash->name = %s, type->kind = %d********************************\n", offset, n2->info, structType->name, type->kind);
                struct Operand* add = newOperand(OP_CONSTANT, offset, NULL, NULL);
                // ret = ret + offset
                struct InterCode *new = newInterCode(IC_ADD, ret ,ret, add);
                insertICToTail(new);
                return ret;
            }
        }
    }
    else if(root->idxMax == 2)
    {
        LOG("Exp has 2 child\n");
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        // MINUS Exp
        if(strcmp(n0->type, "MINUS") == 0)
        {
            LOG("MINUS Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *zero = newOperand(OP_CONSTANT, 0, NULL, NULL);
            struct Operand *x = tra_Exp(n1);
            if(x->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x, NULL);
                insertICToTail(deref);
                x = tmpderef;
            }
            struct InterCode *new = newInterCode(IC_SUB, tmp, zero, x);
            insertICToTail(new);
            return tmp;
        }
        // NOT Exp
        else
        {
            LOG("NOT Exp\n");
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *zero = newOperand(OP_CONSTANT, 0, NULL, NULL);
            struct Operand *one = newOperand(OP_CONSTANT, 1, NULL, NULL);
            struct Operand *x = tra_Exp(n1);
            if(x->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x, NULL);
                insertICToTail(deref);
                x = tmpderef;
            }
            struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            // if x!=0 goto label1
            struct InterCode *new = newInterCode(IC_IFGOTO, x, zero, label1);
            strcpy(new->relop,"!=");
            insertICToTail(new);
            // tmp = 1
            new = newInterCode(IC_ASSIGN, tmp, one, NULL);
            insertICToTail(new);
            // goto label2
            new = newInterCode(IC_GOTO, label2, NULL, NULL);
            insertICToTail(new);
            // LABEL label1
            new = newInterCode(IC_LABEL, label1, NULL, NULL);
            insertICToTail(new);
            // tmp = 0
            new = newInterCode(IC_ASSIGN, tmp, zero, NULL);
            insertICToTail(new);
            // label2
            new = newInterCode(IC_LABEL, label2, NULL, NULL);
            insertICToTail(new);
            return tmp;
        }
    }
    else if(root->idxMax == 4)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        struct TreeNode *n3 = getChild(root, 3);
        // Exp LB Exp RB, n0 is x or x[10]...
        if(strcmp(n0->type, "Exp") == 0)
        {
            LOG("Exp LB Exp RB, lineNumber = %d\n", n0->lineNumber);
            struct hashNode *hash = getArrHash(n0);

            // 此处解析出所有下标
            struct Operand *idx[100];
            memset(idx, 0 ,sizeof(idx));
            int mx1 = 0; 
            idx[mx1] = tra_Exp(n2);
            mx1++;
            getNowIdx(n0, idx, &mx1);
            LOG("mx1 = %d\n", mx1);
            for(int i=0; i<mx1; ++i)
            {
                LOG("idx[%d] = %d, %d\n", i, idx[i]->kind, idx[i]->u.val);
            }

            // 此处得到所有原始数组的下标
            int decl_sz[100];
            int mx2 = 0;
            memset(decl_sz, 0, sizeof(decl_sz));
            struct Type *array_type = hash->type; 
            while(array_type->kind == ARRAY)
            {
                decl_sz[mx2] = array_type->u.array.size;
                mx2++;
                array_type = array_type->u.array.elem;
            }
            struct InterCode *new;
            struct Operand *tmp = newOperand(OP_ADDRESS, temp_num++, NULL, NULL);
            if(n0->idxMax!=3)
            {
                // tmp = &arrbegin
                struct Operand *arrbegin = newOperand(OP_VARIABLE, hash->varNo, hash->name, hash->type);
                new = newInterCode(IC_GETADDR, tmp, arrbegin, NULL); 
                insertICToTail(new);
            }
            // Exp DOT Exp
            else
            {
                // tmp = arr
                struct Operand *arrbegin = tra_Exp(n0);
                new = newInterCode(IC_ASSIGN, tmp, arrbegin, NULL);
                insertICToTail(new);
            }
            // add = 0
            struct Operand *add = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct Operand *zero = newOperand(OP_CONSTANT, 0, NULL, NULL);
            new = newInterCode(IC_ASSIGN, add, zero, NULL);
            insertICToTail(new);
            
            for(int i = mx1-1; i >= 0; --i)
            {
                struct Operand *mul = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                // mul  = 1
                struct Operand *one  = newOperand(OP_CONSTANT, 1, NULL, NULL);
                new = newInterCode(IC_ASSIGN, mul, one, NULL);
                insertICToTail(new);

                for(int j=i-1; j>=0; --j)
                {
                    struct Operand *curr = newOperand(OP_CONSTANT, decl_sz[j], NULL, NULL);
                    new = newInterCode(IC_MUL, mul, curr, mul);
                    insertICToTail(new);
                }
                struct Operand *curr2 = idx[i];
                if(curr2->kind == OP_ADDRESS)
                {
                    struct Operand *tmp2 = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                    // tmp2 = *curr2
                    new = newInterCode(IC_DEREF, tmp2, curr2, NULL);
                    insertICToTail(new);
                    curr2 = tmp2;
                }
                new = newInterCode(IC_MUL, mul, curr2, mul);
                insertICToTail(new);
                new = newInterCode(IC_ADD, add, add, mul);
                insertICToTail(new);
            }
            int baseSz = getTypeSize(array_type);
            // add = baseSz * add;
            struct Operand *baseMul = newOperand(OP_CONSTANT, baseSz, NULL, NULL);
            new = newInterCode(IC_MUL, add, baseMul, add);
            insertICToTail(new);
            // tmp = tmp + add
            new = newInterCode(IC_ADD, tmp, tmp, add);
            insertICToTail(new);
            tmp->type = array_type;

            LOG("after Exp LB Exp RB\n");

            return tmp;
        }

        // ID LP Args RP
        else
        {
            LOG("ID LP Args RP\n");
            if(strcmp(n0->info, "write") == 0)
            {
                // Args -> Exp
                struct TreeNode *expType = getChild(n2, 0);
                struct Operand *x = tra_Exp(expType);
                if(x->kind == OP_ADDRESS)
                {
                    struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                    // tmp = *x
                    struct InterCode *new = newInterCode(IC_DEREF, tmp, x, NULL);
                    insertICToTail(new);
                    x = tmp;
                }
                struct InterCode *new1 = newInterCode(IC_WRITE, x, NULL, NULL);
                insertICToTail(new1);
            }
            else
            {
                n0->argList = (void **)calloc(100, sizeof(struct Operand *));
                n0->arg_num = 0;
                tra_Args(n2, n0);
                struct hashNode *hash = getHashNode(n0->info, SYMTABLE);
                struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                
                for(int i=0; i<n0->arg_num; ++i)
                {
                    struct InterCode *new = newInterCode(IC_ARG, (struct Operand *)n0->argList[i], NULL, NULL);
                    insertICToTail(new);
                }

                struct InterCode *new = newInterCode(IC_CALL, tmp, NULL, NULL);
                new->funcName = hash->name;
                insertICToTail(new);    
                return tmp;    
            }
        }
    }
    return NULL;
}

// for array
void getNowIdx(struct TreeNode *root, struct Operand **idx, int *curr)
{
    LOG("getNowIdx\n");
    // Exp
    if(root->idxMax == 1)
    {
        LOG("getNodeIdx, root->idxMax = 1\n");
        return;
    }
    // Exp LB Exp RB
    else if(root->idxMax == 4)
    {
        LOG("getNodeIdx, root->idxMax = %d\n", root->idxMax);
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        // n2 is a number        
        *(idx + *curr) = tra_Exp(n2);
        (*curr)++;
    }
    // Exp DOT Exp 
    else
    {
        LOG("getNodeIdx, root->idxMax = %d\n", root->idxMax);
        return;
    }
}



void tra_Args(struct TreeNode *root, struct TreeNode *funcNode)
{
    LOG("tra_Args\n");
    struct TreeNode *n0 = getChild(root, 0);
    // Exp
    if(root->idxMax == 1)
    {
        struct Operand *x = tra_Exp(n0);
        //结构体类型，传入引用。其余类型（包括数组元素），传值。
        if(x->kind == OP_ADDRESS)
        {
            if(!(x->type != NULL && x->type->kind == STRUCTURE))
            {
                struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                // tmp = *x
                struct InterCode *new = newInterCode(IC_DEREF, tmp, x, NULL);
                insertICToTail(new);
                x = tmp;
            }
            else
            {
                LOG("************arg is structure, root->linenumber = %d\n", root->lineNumber);
            }
        }
        funcNode->argList[funcNode->arg_num] = x;
        funcNode->arg_num++;
    }
    // Exp COMMA Args
    else
    {
        struct TreeNode *n2 = getChild(root, 2);
        tra_Args(n2, funcNode);
        struct Operand *x = tra_Exp(n0);
        //结构体类型，传入引用。其余类型（包括数组元素），传值。
        if(x->kind == OP_ADDRESS)
        {
            if(!(x->type != NULL && x->type->kind == STRUCTURE))
            {
                struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                // tmp = *x
                struct InterCode *new = newInterCode(IC_DEREF, tmp, x, NULL);
                insertICToTail(new);
                x = tmp;
            }
            else
            {
                LOG("************arg is structure, root->linenumber = %d\n", root->lineNumber);
            }
        }
        funcNode->argList[funcNode->arg_num] = x;
        funcNode->arg_num++;      
    }
}

void tra_Dec(struct TreeNode *root)
{
    LOG("tra_Dec\n");
    // VarDec
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        tra_VarDec(n0);
    }
    // VarDec ASSIGNOP Exp
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        // 结构体和数组变量不能初始赋值，因而无需考虑left deref
        struct Operand *left = tra_VarDec(n0);
        struct Operand *right = tra_Exp(n2);
        // for right is address
        if(right->kind == OP_ADDRESS)
        {
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            // tmp = *right
            struct InterCode *deref = newInterCode(IC_DEREF, tmp, right, NULL);
            insertICToTail(deref);
            // right = tmp
            right = tmp;
        }
        struct InterCode *new = newInterCode(IC_ASSIGN, left, right, NULL);
        insertICToTail(new);
    }
}

void tra_DecList(struct TreeNode *root)
{
    LOG("tra_DecList\n");
    // Dec
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        tra_Dec(n0);
    }
    // Dec COMMA DecList
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        tra_Dec(n0);
        tra_DecList(n2);
    }
}

void tra_Def(struct TreeNode *root)
{
    LOG("tra_Def\n");
    // Specifier DecList SEMI
    struct TreeNode *n1 = getChild(root, 1);
    tra_DecList(n1);
}

void tra_DefList(struct TreeNode *root)
{
    LOG("tra_DefList\n");
    // Def DefList
    if(root->idxMax == 2)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        tra_Def(n0);
        tra_DefList(n1);
    }
}

void tra_Stmt(struct TreeNode *root)
{
    LOG("tra_Stmt\n");
    // Exp SEMI
    if(root->idxMax == 2)
    {
        struct TreeNode *n0 = getChild(root, 0);
        tra_Exp(n0);
    }
    // CompSt
    else if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        tra_CompSt(n0);
    }
    // RETURN Exp SEMI
    else if(root->idxMax == 3)
    {
        struct TreeNode *n1 = getChild(root, 1);
        struct Operand *x = tra_Exp(n1);
        if(x->kind == OP_ADDRESS)
        {
            struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x, NULL);
            insertICToTail(deref);
            x = tmpderef;
        }
        struct InterCode *new = newInterCode(IC_RETURN, x, NULL, NULL);
        insertICToTail(new);
    }
    else if(root->idxMax == 5)
    {

        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        struct TreeNode *n4 = getChild(root, 4);
        // IF LP Exp RP Stmt
        if(strcmp(n0->type, "IF") == 0)
        {
            LOG("IF LP Exp RP Stmt");
            struct Operand *x = tra_Exp(n2);
            if(x->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x, NULL);
                insertICToTail(deref);
                x = tmpderef;
            }
            struct Operand *zero = newOperand(OP_CONSTANT, 0 ,NULL, NULL);
            struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            // if x!=0 goto label1
            struct InterCode *new = newInterCode(IC_IFGOTO, x, zero, label1);
            strcpy(new->relop,"!=");
            insertICToTail(new);
            // goto label2
            new = newInterCode(IC_GOTO, label2, NULL, NULL);
            insertICToTail(new);
            // LABEL label1:
            new = newInterCode(IC_LABEL, label1, NULL, NULL);
            insertICToTail(new);
            //Stmt (n4)
            tra_Stmt(n4);
            // LABEL label2:
            new = newInterCode(IC_LABEL, label2, NULL, NULL);
            insertICToTail(new);
        }
        // WHILE LP Exp RP Stmt
        else
        {
            LOG("WHILE LP Exp RP Stmt\n");

            struct Operand *zero = newOperand(OP_CONSTANT, 0 ,NULL, NULL);
            struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            struct Operand *label3 = newOperand(OP_LABEL, label_num++, NULL, NULL);
            
            // LABEL label1
            struct InterCode *new = newInterCode(IC_LABEL, label1, NULL, NULL);
            insertICToTail(new);
            // tmp = x
            struct Operand *x = tra_Exp(n2);
            if(x->kind == OP_ADDRESS)
            {
                struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
                struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x, NULL);
                insertICToTail(deref);
                x = tmpderef;
            }
            struct Operand *tmp = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            new = newInterCode(IC_ASSIGN, tmp, x, NULL);
            insertICToTail(new);
            
            // if tmp!=0 goto label2
            new = newInterCode(IC_IFGOTO, tmp, zero, label2);
            strcpy(new->relop,"!=");
            insertICToTail(new);
            // goto lable3
            new = newInterCode(IC_GOTO, label3, NULL, NULL);
            insertICToTail(new);
            // LABEL label2:
            new = newInterCode(IC_LABEL, label2, NULL, NULL);
            insertICToTail(new);                     
            // stmt
            tra_Stmt(n4);
            // GOTO label1
            new = newInterCode(IC_GOTO, label1, NULL, NULL);
            insertICToTail(new);
            // LABEL label3:
            new = newInterCode(IC_LABEL, label3, NULL, NULL);
            insertICToTail(new); 
        }
    }
    else if(root->idxMax == 7)
    {
        LOG("IF LP Exp RP Stmt ELSE Stmt\n");
        // IF LP Exp RP Stmt ELSE Stmt
        struct TreeNode *n2 = getChild(root, 2);
        struct TreeNode *n4 = getChild(root, 4);
        struct TreeNode *n6 = getChild(root, 6);
        struct Operand *x = tra_Exp(n2);
        if(x->kind == OP_ADDRESS)
        {
            struct Operand *tmpderef = newOperand(OP_TEMP, temp_num++, NULL, NULL);
            struct InterCode *deref = newInterCode(IC_DEREF, tmpderef, x, NULL);
            insertICToTail(deref);
            x = tmpderef;
        }
        struct Operand *zero = newOperand(OP_CONSTANT, 0 ,NULL, NULL);
        struct Operand *label1 = newOperand(OP_LABEL, label_num++, NULL, NULL);
        struct Operand *label2 = newOperand(OP_LABEL, label_num++, NULL, NULL);
        // if x!=0 goto label1
        struct InterCode *new = newInterCode(IC_IFGOTO, x, zero, label1);
        strcpy(new->relop,"!=");
        insertICToTail(new);
        // Stmt (n6)
        tra_Stmt(n6);
        // goto label2
        new = newInterCode(IC_GOTO, label2, NULL, NULL);
        insertICToTail(new);
        // LABEL label1:
        new = newInterCode(IC_LABEL, label1, NULL, NULL);
        insertICToTail(new);
        //Stmt (n4)
        tra_Stmt(n4);
        // LABEL label2:
        new = newInterCode(IC_LABEL, label2, NULL, NULL);
        insertICToTail(new);
    }
}

void tra_StmtList(struct TreeNode *root)
{
    LOG("tra_StmtList\n");
    // Stmt StmtList
    if(root->idxMax == 2)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        tra_Stmt(n0);
        tra_StmtList(n1);
    }
}

void tra_FunDec(struct TreeNode *root)
{
    LOG("tra_FunDec\n");
    // ID LP VarList RP
    if(root->idxMax == 4)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n2 = getChild(root, 2);
        struct hashNode *hash = getHashNode(n0->info, SYMTABLE);
        
        struct InterCode *func = newInterCode(IC_FUNCTION, NULL, NULL, NULL);
        func->funcName = hash->name;
        insertICToTail(func);
        // 从fieldList当中获取所有函数参数  
        struct FieldList *list = hash->type->u.function.para;         
        while(list!=NULL)
        {
            struct Type *curr = list->type;
            struct hashNode *hash = getHashNode(list->name, SYMTABLE);
            // 此处必定第一次出现该变量，设置varNum
            hash->varNo = var_num++;
            struct Operand *op1 = newOperand(OP_VARIABLE, hash->varNo, hash->name, hash->type);
            hash->isParam = 1;
            struct InterCode *new = newInterCode(IC_PARAM, op1, NULL, NULL);
            insertICToTail(new);
            list = list->next;
        }
    }
    // ID LP RP
    else 
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct hashNode *hash = getHashNode(n0->info, SYMTABLE);
        struct InterCode *func = newInterCode(IC_FUNCTION, NULL, NULL, NULL);
        func->funcName = hash->name;
        insertICToTail(func);
    }
}

void tra_CompSt(struct TreeNode *root)
{
    LOG("tra_CompSt\n");
    // LC DefList StmtList RC
    struct TreeNode *n1 = getChild(root, 1);
    struct TreeNode *n2 = getChild(root, 2);
    tra_DefList(n1);
    tra_StmtList(n2);
}

struct Operand* tra_VarDec(struct TreeNode *root)
{
    LOG("tra_VarDec\n");
    // VarDec
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        char *name = n0->info;
        struct hashNode *hash = getHashNode(name, SYMTABLE);
        int sz = getTypeSize(hash->type);
        // 第一次出现该变量，设置varNum
        if(hash->varNo == -1)
        {
            hash->varNo = var_num;
            var_num++; 
        }       
        if(sz != 4)
        {
            // 指定数组变量的编号，例如v14。注意这里v14也表示数组的第一个元素，对其取地址可以得到数组首地址。
            struct Operand *op1 = newOperand(OP_VARIABLE, hash->varNo, hash->name, hash->type);
            // 立即数，表示开辟空间大小
            struct Operand *op2 = newOperand(OP_CONSTANT, sz, NULL, NULL);            
            struct InterCode *new = newInterCode(IC_DEC, op1, op2, NULL);
            insertICToTail(new);
            return op1;
        }
        else
        {
            struct Operand *op1 = newOperand(OP_VARIABLE, hash->varNo, hash->name, hash->type);
            return op1;
        }
    }
    // VarDec LB INT RB
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        return tra_VarDec(n0);
    }
}

void tra_ExtDecList(struct TreeNode *root)
{
    LOG("tra_ExtDecList\n");
    if(root->idxMax == 1)
    {
        struct TreeNode *n0 = getChild(root, 0);
        tra_VarDec(n0);
    }
    else
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        tra_VarDec(n0);
        tra_ExtDecList(n2);
    }
}

void tra_ExtDef(struct TreeNode *root)
{
    LOG("tra_ExtDef\n");
    if(root->idxMax == 3)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        struct TreeNode *n2 = getChild(root, 2);
        // Specifier ExtDecList SEMI
        if(strcmp(n1->type, "EXtDecList") == 0)
        {
            tra_ExtDecList(n1);
        }
        // Specifer FunDec CompSt
        else if(strcmp(n1->type, "FunDec") == 0)
        {
            tra_FunDec(n1);
            tra_CompSt(n2);
        }
    }
    // Specifier: ignore
}

void tra_ExtDefList(struct TreeNode *root)
{
    LOG("tra_ExtDefList, root->lineNumber = %d, root->child = %d\n", root->lineNumber, root->idxMax);
    if(root->idxMax == 2)
    {
        struct TreeNode *n0 = getChild(root, 0);
        struct TreeNode *n1 = getChild(root, 1);
        tra_ExtDef(n0);
        tra_ExtDefList(n1);
    }
}

void tra_Program(struct TreeNode *root)
{
    LOG("tra_Program\n");
    icHead = newCodeList();
    icHead->next = icHead;
    icHead->prev = icHead;

    struct TreeNode *n0 = getChild(root, 0);
    tra_ExtDefList(n0);
}

void tra_variable(struct Operand *op, char *reg)
{
    if(op->kind == OP_VARIABLE)
    {
        sprintf(reg, "v%d", op->u.varno);
    }
    else if(op->kind == OP_TEMP || op->kind == OP_ADDRESS)
    {
        sprintf(reg, "t%d", op->u.tempno);
    }
    else if(op->kind == OP_CONSTANT)
    {
        sprintf(reg, "#%d", op->u.val);
    }
    else
    {
        sprintf(reg, "error%d\n", op->kind);
    }
}

void printIr(FILE *fp)
{
    struct CodeList *curr = icHead->next;
    while(curr != icHead)
    {
        
        struct InterCode *ic = curr->code;
        //LOG("ic->kind = %d\n", ic->kind);
        char reg1[32];
        char reg2[32];
        char reg3[32];
        memset(reg1, 0, sizeof(reg1));
        memset(reg2, 0, sizeof(reg2));
        memset(reg3, 0, sizeof(reg3));
        switch (ic->kind)
        {
            case IC_LABEL:
                fprintf(fp, "LABEL label%d :\n", ic->op1->u.labelno);
                break;
            case IC_FUNCTION:
                fprintf(fp, "FUNCTION %s :\n", ic->funcName);
                break;
            case IC_ASSIGN:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                fprintf(fp, "%s := %s\n", reg1, reg2);
                break;
            case IC_ADD:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                tra_variable(ic->op3, reg3);
                fprintf(fp, "%s := %s + %s\n", reg1, reg2, reg3);
                break;
            case IC_SUB:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                tra_variable(ic->op3, reg3);
                fprintf(fp, "%s := %s - %s\n", reg1, reg2, reg3);
                break;
            case IC_MUL:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                tra_variable(ic->op3, reg3);
                fprintf(fp, "%s := %s * %s\n", reg1, reg2, reg3);
                break;
            case IC_DIV:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                tra_variable(ic->op3, reg3);
                fprintf(fp, "%s := %s / %s\n", reg1, reg2, reg3);
                break;
            case IC_GETADDR:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                fprintf(fp, "%s := &%s\n", reg1, reg2);
                break;
            case IC_DEREF:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                fprintf(fp, "%s := *%s\n", reg1, reg2);
                break;    
            case IC_DEREFASSIGN:
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                fprintf(fp, "*%s := %s\n", reg1, reg2);
                break;        
            case IC_GOTO:
                fprintf(fp, "GOTO label%d\n", ic->op1->u.labelno);
                break;                            
            case IC_IFGOTO:
                LOG("here is if goto\n");
                tra_variable(ic->op1, reg1);
                tra_variable(ic->op2, reg2);
                fprintf(fp, "IF %s %s %s GOTO label%d\n", reg1, ic->relop, reg2, ic->op3->u.labelno);
                break;
            case IC_RETURN:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "RETURN %s\n", reg1);
                break;
            case IC_DEC:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "DEC %s %d\n", reg1, ic->op2->u.val);
                break;
            case IC_ARG:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "ARG %s\n", reg1);
                break;
            case IC_CALL:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "%s := CALL %s\n", reg1, ic->funcName);
                break;
            case IC_PARAM:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "PARAM %s\n", reg1);
                break;
            case IC_READ:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "READ %s\n", reg1);
                break;
            case IC_WRITE:
                tra_variable(ic->op1, reg1);
                fprintf(fp, "WRITE %s\n", reg1);
                break;            
            default:
                LOG("error in printIr\n");
                break;
        }
        curr = curr->next;
    }
}