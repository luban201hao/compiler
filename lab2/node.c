#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
int successFlag;
int lexFlag;
struct TreeNode *root;

struct TreeNode* newNode(char *_type, int _lineNumber)
{
    struct TreeNode *res=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    strcpy(res->type, _type);
    res->lineNumber = _lineNumber;
    res->child_list_size=10;
    res->child_list = (struct TreeNode **)malloc(10*sizeof(struct TreeNode *));
    res->idxMax=0;
    res->hasE=0;
    return res;
}

void add_child(struct TreeNode *fa, struct TreeNode *child)
{
    if(fa->idxMax < fa->child_list_size)
    {
        fa->child_list[fa->idxMax] = child;
        fa->idxMax++;
    }
    else
    {
        fa->child_list_size += 10;
        fa->child_list = (struct TreeNode **)realloc(fa->child_list, fa->child_list_size);
        fa->child_list[fa->idxMax] = child;
        fa->idxMax++;
    }
} 
struct TreeNode * getChild(struct TreeNode *fa, int n)
{
    if(n >= fa->idxMax)
        return NULL;
    else
        return fa->child_list[n];
}


void print_tree(struct TreeNode *curr, int level)
{
    if(successFlag == 0)
    {
        return;
    }
    if(curr!=NULL)
    {

        int cifa= 1;
        for(int i=0;i<strlen(curr->type);++i)
        {
            if(curr->type[i]>='a' && curr->type[i]<='z')
            {
                cifa = 0;
                break;
            }
        }
        if(cifa == 0)
        {

            if(curr->hasE == 0)
            {
                for(int i=0;i<level;++i)
                    printf("  ");
                printf("%s (%d)\n",curr->type, curr->lineNumber);
            }
        }
        else
        {
            for(int i=0;i<level;++i)
                printf("  ");
            if(strcmp(curr->type, "ID")==0 || strcmp(curr->type, "TYPE")==0 || strcmp(curr->type, "INT")==0 )
            {
                printf("%s: %s\n", curr->type, curr->info);
            }
            else if(strcmp(curr->type, "FLOAT")==0)
            {
                float ans=atof(curr->info);
                printf("%s: %.6f\n", curr->type, ans);
            }
            else
                printf("%s\n", curr->type); 
        }
        
        for(int i=0;i<curr->child_list_size;++i)
        {
            print_tree(curr->child_list[i],level+1);
        }
    }
}