#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct _sExpTree ExpTree;
struct _sExpTree
{
    char item;
    ExpTree *left;
    ExpTree *right;
};

char* get_postfix(char *infix);
int32_t cal_postfix(char *postfix);
ExpTree* init_postfix_tree(char* postfix);

void preorder(ExpTree *t);
void postorder(ExpTree *t);
void levelorder(ExpTree *t);

