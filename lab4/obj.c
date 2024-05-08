#include "hash.h"
#include "node.h"
#include "translate.h"
#include "obj.h"
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

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

const char data[] = ".data\n"
"_prompt: .asciiz \"Enter an integer:\"\n"
"_ret: .asciiz \"\\n\"\n"
".globl main\n"
".text\n"
"read:\n"
"   li $v0, 4\n"
"   la $a0, _prompt\n"
"   syscall\n"
"   li $v0, 5\n"
"   syscall\n"
"   jr $ra\n"
"write:\n"
"   li $v0, 1\n"
"   syscall\n"
"   li $v0, 4\n"
"   la $a0, _ret\n"
"   syscall\n"
"   move $v0, $0\n"
"   jr $ra\n";

char *regName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "Ss7",
"$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

struct Register reg[32];
struct Variable* get_var(struct Operand *);

struct Variable* varlist[1024];
int varIdx = 0;
int offset = 0;

static void init_reg()
{
    for(int i=0; i<32; ++i)
    {
        reg[i].name = regName[i];
        reg[i].used = 0;
        reg[i].var = NULL;
    }
}


static void create_var(struct Operand *op)
{
    if(op->kind == OP_CONSTANT)
        return;
    if(get_var(op) == NULL)
    {
        offset +=4;
        varlist[varIdx] = (struct Variable *)malloc(sizeof(struct Variable));
        varlist[varIdx]->op = op;
        varlist[varIdx]->offset = -offset;
        varlist[varIdx]->reg = -1;
        varIdx++;
        
    }
}

static void create_param(struct Operand *op, int idx)
{
    varlist[varIdx] = (struct Variable *)malloc(sizeof(struct Variable));
    varlist[varIdx]->op = op;
    varlist[varIdx]->offset = 8 + idx * 4;
    varlist[varIdx]->reg = -1;
    varIdx++;
}

static void create_dec(struct Operand *op, int sz)
{
    offset +=sz;
    varlist[varIdx] = (struct Variable *)malloc(sizeof(struct Variable));
    varlist[varIdx]->op = op;
    varlist[varIdx]->offset = -offset;
    varlist[varIdx]->reg = -1;    
    varIdx++; 
}

struct Variable* get_var(struct Operand *op)
{
    for(int i=0; i<varIdx; ++i)
    {
        if(varlist[i]->op == op)
            return varlist[i];
        if(varlist[i]->op->kind == op->kind && varlist[i]->op->u.tempno == op->u.tempno)
            return varlist[i];
    }
    LOG("get var fail!!!!!!!!!!!!!!!!!!!\n");
    return NULL;
}

static void clear_varlist()
{
    for(int i = 0; i < varIdx; ++i)
    {
        if(varlist[i] != NULL)
        {
            free(varlist[i]);
            varlist[i] = NULL;
        }
    }
    varIdx = 0;
}

static void clear_reg()
{
    for(int i=8; i<16; ++i)
    {
        reg[i].used = 0;
        reg[i].var = NULL;
    }
}

int find_reg(struct Operand *op, FILE *fp)
{
    if(op->kind!=OP_CONSTANT)
    {
        struct Variable *var = get_var(op);
        for(int i=8; i<16; ++i)
        {
            if(reg[i].used == 0)
            {
                fprintf(fp, "    lw %s, %d($fp)\n", reg[i].name, var->offset);
                reg[i].used = 1;
                reg[i].var = var;
                return i;
            }
        }
    }
    else
    {
        for(int i=8; i<16; ++i)
        {
            if(reg[i].used == 0)
            {
                fprintf(fp, "    li %s, %d\n", reg[i].name, op->u.val);
                reg[i].used = 1;
                reg[i].var = NULL;
                return i;
            }
        }
    }
    return -1;
}

int find_reg_without_load(struct Operand *op)
{
    struct Variable *var = get_var(op);
    for(int i=8; i<16; ++i)
    {
        if(reg[i].used == 0)
        {
            reg[i].used = 1;
            reg[i].var = var;
            return i;
        }
    }    
    return -1;
}


static void gen_function(FILE *fp, struct CodeList *curr)
{
    if(strcmp(curr->code->funcName, "main") == 0)
        fprintf(fp, "%s:\n", curr->code->funcName);
    else
        fprintf(fp, "_%s:\n", curr->code->funcName);
    fprintf(fp, "    addi $sp, $sp, -8\n");
    // save old $fp
    fprintf(fp, "    sw $fp, 0($sp)\n");
    // save return address
    fprintf(fp, "    sw $ra, 4($sp)\n");
    // fp = sp
    fprintf(fp, "    move $fp, $sp\n");
    curr = curr->next;
    offset = 0;
    clear_varlist();
    int paramIdx = 0;

    LOG("begin gen_function\n");
    while(curr !=icHead && curr->code->kind == IC_PARAM)
    {
        create_param(curr->code->op1, paramIdx);
        paramIdx++;
        curr = curr->next;
    }
    while(curr != icHead && curr->code->kind != IC_FUNCTION)
    {
        switch (curr->code->kind)
        {
            case IC_RETURN:
            case IC_READ:
            case IC_WRITE:
            case IC_CALL:
                create_var(curr->code->op1);
                break;
            case IC_ASSIGN:
            case IC_GETADDR:
            case IC_DEREF:
            case IC_DEREFASSIGN:
 
                create_var(curr->code->op1);
                create_var(curr->code->op2);
                break;
            case IC_ADD:
            case IC_SUB:
            case IC_MUL:
            case IC_DIV:
            case IC_IFGOTO:
                create_var(curr->code->op1);
                create_var(curr->code->op2);
                create_var(curr->code->op3);
                break;
            case IC_DEC:
                create_dec(curr->code->op1, curr->code->op2->u.val);
                break;
            default:
                break;
        }
        curr = curr->next;
    }
    fprintf(fp, "    addi, $sp, $sp, %d\n", -1 * offset);
    LOG("end gen_function\n");
    clear_reg();
}

static void gen_label(FILE *fp, struct InterCode *ic)
{
    fprintf(fp, "    label%d:\n", ic->op1->u.labelno);
}


static void gen_assign(FILE *fp, struct InterCode *ic)
{
    struct Variable *var1 = get_var(ic->op1);
    int reg2 = find_reg(ic->op2, fp);
    fprintf(fp, "    sw %s, %d($fp)\n", reg[reg2].name, var1->offset);
    clear_reg();
}

static void gen_calc(FILE *fp, struct InterCode *ic)
{
    struct Variable *var1 = get_var(ic->op1);
    int reg2 = find_reg(ic->op2, fp);
    int reg3 = find_reg(ic->op3, fp);
    if(ic->kind == IC_ADD)
    {
        fprintf(fp, "    add %s, %s, %s\n", reg[reg2].name, reg[reg2].name, reg[reg3].name);
    } 
    else if(ic->kind == IC_SUB)
    {
        fprintf(fp, "    sub %s, %s, %s\n", reg[reg2].name, reg[reg2].name, reg[reg3].name);
    }
    else if(ic->kind == IC_MUL)
    {
        fprintf(fp, "    mul %s, %s, %s\n", reg[reg2].name, reg[reg2].name, reg[reg3].name);
    }
    else
    {
        fprintf(fp, "    div %s, %s, %s\n", reg[reg2].name, reg[reg2].name, reg[reg3].name);
    }

    fprintf(fp, "    sw %s, %d($fp)\n", reg[reg2].name, var1->offset);
    clear_reg();
}

static void gen_getAddr(FILE *fp, struct InterCode *ic)
{
    int reg2 = 8;
    struct Variable *var1 = get_var(ic->op1);
    struct Variable *var2 = get_var(ic->op2);
    fprintf(fp, "    addi %s, $fp, %d\n", reg[reg2].name, var2->offset);
    fprintf(fp, "    sw %s, %d($fp)\n", reg[reg2].name, var1->offset);

}

// t1 = *t2

static void gen_deref(FILE *fp, struct InterCode *ic)
{
    int reg2 = find_reg(ic->op2, fp);
    int tmpreg = 0;
    for(int i=8; i<16; ++i)
    {
        if(reg[i].used == 0)
        {
            reg[i].used = 1;
            tmpreg = i;
            break;
        }
    }
    fprintf(fp, "    lw %s, 0(%s)\n", reg[tmpreg].name, reg[reg2].name);
    int reg1 = find_reg_without_load(ic->op1);
    fprintf(fp, "    sw %s, %d($fp)\n", reg[tmpreg].name, reg[reg1].var->offset);
    clear_reg();
}
// *t1 = t2
static void gen_derefassign(FILE *fp, struct InterCode *ic)
{
    int reg1 = find_reg_without_load(ic->op1);
    fprintf(fp, "    lw %s, %d($fp)\n", reg[reg1].name, reg[reg1].var->offset);
    int reg2 = find_reg(ic->op2, fp);
    fprintf(fp, "    sw %s, 0(%s)\n", reg[reg2].name, reg[reg1].name);
    clear_reg();
}

static void gen_goto(FILE *fp, struct InterCode *ic)
{
    fprintf(fp, "    j label%d\n", ic->op1->u.labelno);
}

static void gen_ifgoto(FILE *fp, struct InterCode *ic)
{
    int reg1 = find_reg(ic->op1, fp);
    int reg2 = find_reg(ic->op2, fp);
    if(strcmp(ic->relop, "==") == 0)
    {
        fprintf(fp, "    beq %s, %s, label%d\n", reg[reg1].name, reg[reg2].name, ic->op3->u.labelno);
    }
    else if(strcmp(ic->relop, "!=") == 0)
    {
        fprintf(fp, "    bne %s, %s, label%d\n", reg[reg1].name, reg[reg2].name, ic->op3->u.labelno);
    }
    else if(strcmp(ic->relop, ">") == 0)
    {
        fprintf(fp, "    bgt %s, %s, label%d\n", reg[reg1].name, reg[reg2].name, ic->op3->u.labelno);
    }
    else if(strcmp(ic->relop, "<") == 0)
    {
        fprintf(fp, "    blt %s, %s, label%d\n", reg[reg1].name, reg[reg2].name, ic->op3->u.labelno);
    }
    else if(strcmp(ic->relop, ">=") == 0)
    {
        fprintf(fp, "    bge %s, %s, label%d\n", reg[reg1].name, reg[reg2].name, ic->op3->u.labelno);
    }
    else if(strcmp(ic->relop, "<=") == 0)
    {
        fprintf(fp, "    ble %s, %s, label%d\n", reg[reg1].name, reg[reg2].name, ic->op3->u.labelno);
    }
    clear_reg();
}

static void gen_return(FILE *fp, struct InterCode *ic)
{
    fprintf(fp, "    lw $ra, 4($fp)\n");
    fprintf(fp, "    addi $sp, $fp, 8\n");
    int reg1 = find_reg(ic->op1, fp);
    fprintf(fp, "    lw $fp, 0($fp)\n");
    fprintf(fp, "    move $v0, %s\n", reg[reg1].name);
    fprintf(fp, "    jr $ra\n");
    clear_reg();
}

static struct CodeList* gen_arg(FILE *fp, struct CodeList *curr)
{
    int argNum = 0;
    // push args in stack
    while(curr->code->kind == IC_ARG)
    {
        fprintf(fp, "    addi $sp, $sp -4\n");
        int reg1 = find_reg(curr->code->op1, fp);
        fprintf(fp, "    sw %s, 0($sp)\n", reg[reg1].name);
        clear_reg();
        argNum++;
        curr = curr->next;
    }
    // call function
    if(strcmp(curr->code->funcName, "main") == 0)
    {
        fprintf(fp, "    jal %s\n", curr->code->funcName);
    }
    else
    {
        fprintf(fp, "    jal _%s\n", curr->code->funcName);
    }
    fprintf(fp, "    addi $sp, $sp, %d\n", argNum * 4);
    struct Variable *var1 = get_var(curr->code->op1);
    fprintf(fp, "    sw $v0, %d($fp)\n", var1->offset);
    return curr;
}

static void gen_read(FILE *fp, struct InterCode *ic)
{
    fprintf(fp, "    addi $sp, $sp, -4\n");
    fprintf(fp, "    sw $ra, 0($sp)\n");
    fprintf(fp, "    jal read\n");
    fprintf(fp, "    lw $ra, 0($sp)\n");
    fprintf(fp, "    addi $sp, $sp, 4\n");
    struct Variable *var = get_var(ic->op1);
    fprintf(fp, "    sw $v0, %d($fp)\n", var->offset);
}

static void gen_write(FILE *fp, struct InterCode *ic)
{
    int reg1 = find_reg(ic->op1, fp);
    fprintf(fp, "    move $a0, %s\n", reg[reg1].name);
    fprintf(fp, "    addi $sp, $sp, -4\n");
    fprintf(fp, "    sw $ra, 0($sp)\n");
    fprintf(fp, "    jal write\n");
    fprintf(fp, "    lw $ra, 0($sp)\n");
    fprintf(fp, "    addi $sp, $sp, 4\n");
    clear_reg();    
}

void gen_obj(FILE *fp)
{
    LOG("in gen_obj\n");
    init_reg();

    fprintf(fp, "%s", data);
    struct CodeList *curr = icHead->next;
    while(curr != icHead)
    {
        struct InterCode *ic = curr->code;
        LOG("ic->code = %d\n", ic->kind);
        if(ic->kind == IC_FUNCTION)
        {
            LOG("name = %s\n", ic->funcName);
        }
        switch(ic->kind)
        {
            case IC_LABEL:
                gen_label(fp, ic);
                break;
            case IC_FUNCTION:
                gen_function(fp, curr);
                break;
            case IC_ASSIGN:
                gen_assign(fp, ic);
                break;
            case IC_ADD:
            case IC_SUB:
            case IC_MUL:
            case IC_DIV:
                gen_calc(fp, ic);
                break;
            case IC_GETADDR:
                gen_getAddr(fp, ic);
                break;
            case IC_DEREF:
                gen_deref(fp, ic);
                break;
            case IC_DEREFASSIGN:
                gen_derefassign(fp, ic);
                break;
            case IC_GOTO:
                gen_goto(fp, ic);
                break;
            case IC_IFGOTO:
                gen_ifgoto(fp, ic);
                break;
            case IC_RETURN:
                gen_return(fp, ic);
                break;
            // handled in gen_function
            case IC_DEC:
                break;
            case IC_ARG:
            // return curr in IC_CALL
                curr = gen_arg(fp, curr);
                break;
            // handled in IC_ARG
            case IC_CALL:
            // handled in gen_function
            case IC_PARAM:
                break;
            case IC_READ:
                gen_read(fp, ic);
                break;
            case IC_WRITE:
                gen_write(fp, ic);
                break;
            default:
                LOG("unrecognize intercode\n");
                break;
        }
        curr = curr->next;
    }
}
