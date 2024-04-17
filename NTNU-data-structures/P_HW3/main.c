#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"

int main()
{
    char *infix = calloc(MAX_SIZE+3,sizeof(char));
    char *postfix = NULL;
    ExpTree *t = NULL;

    while (1)
    {
        printf("Please enter an infix expression and press enter, (input q to exit): ");
        fflush(stdin);
        memset(infix,0,MAX_SIZE);
        scanf("%s",infix);
        if(!strcmp(infix,"q")) break;

        postfix = get_postfix(infix);
        t = init_postfix_tree(postfix);
        
        printf("The postfix expression: ");
        postorder(t);
        printf("\n");

        printf("The prefix expression: ");
        preorder(t);
        printf("\n");

        printf("The level order: ");
        levelorder(t);
        printf("\n");

        printf("= %d\n\n",cal_postfix(postfix));
    }

    free(t);
    free(infix);
    free(postfix);
    return 0;
}