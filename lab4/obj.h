#ifndef OBJ_H
#define OBJ_H
struct Variable
{
    struct Operand *op;
    int reg;
    int offset;
};

struct Register
{
    int used;
    char *name;
    struct Variable *var;
};
void gen_obj(FILE *);
#endif