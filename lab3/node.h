
#ifndef NODE_H
#define NODE_H

struct TreeNode
{
    char type[32];
    int lineNumber;

    int hasE;

    char *info;
    int infoint;
    float infofl;

    int child_list_size;
    int idxMax;
    struct TreeNode **child_list;
    // for intercode function
    int arg_num;
    void **argList;
};
extern int successFlag;
extern int lexFlag;
extern struct TreeNode *root;
struct TreeNode* newNode(char *, int );
void add_child(struct TreeNode *, struct TreeNode *);
void print_tree(struct TreeNode *, int);
struct TreeNode * getChild(struct TreeNode *, int);
#endif
