#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"

typedef enum {LPAREN,RPAREN,PLUS,MINUS,TIMES,DIVIDE,MOD,EOS,OPERAND} precedence;
precedence get_token(char symbol)
{
    if(symbol=='(') return LPAREN;
    else if(symbol==')') return RPAREN;
    else if(symbol=='+') return PLUS;
    else if(symbol=='-') return MINUS;
    else if(symbol=='*') return TIMES;
    else if(symbol=='/') return DIVIDE;
    else if(symbol=='%') return MOD;
    else if(symbol==' ') return EOS;
    else return OPERAND;
}
char get_op(precedence token)
{
    if(token==LPAREN) return '(';
    else if(token==RPAREN) return ')';
    else if(token==PLUS) return '+';
    else if(token==MINUS) return '-';
    else if(token==TIMES) return '*';
    else if(token==DIVIDE) return '/';
    else if(token==MOD) return '%';
    else if(token==EOS) return ' ';
    else return 0;
}

char* get_postfix(char *infix)
{
    infix[strlen(infix)] = ' ';
    char *postfix = calloc(100,sizeof(char));
    precedence stack[MAX_SIZE];
    int32_t top=-1,c=-1;

    precedence token;
    int32_t isp[] = {0,19,12,12,13,13,13,0};
    int32_t icp[] = {20,19,12,12,13,13,13,0};

    int i=0;
    for(token=get_token(infix[i]); token!=EOS; token=get_token(infix[++i]))
    {
        
        if(token==OPERAND) postfix[++c] = infix[i];
        else if(token==RPAREN)
        {
            while(stack[top]!=LPAREN) postfix[++c]=get_op(stack[top--]);
            top--;
        }
        else
        {
            while (isp[stack[top]]>=icp[token]) postfix[++c]=get_op(stack[top--]);
            stack[++top] = token;
        }
    }
    while(top>-1&&(token=stack[top--])!=EOS)
    {
        postfix[++c]=get_op(token);
    }
    return postfix;
}

int32_t cal_postfix(char *postfix)
{
    postfix[strlen(postfix)] = ' ';
    int32_t stack[MAX_SIZE];
    int32_t top=-1;
    int32_t op1=0,op2=0;

    int i=0;
    precedence token = get_token(postfix[i++]);

    while (token!=EOS)
    {
        if(token==OPERAND) stack[++top] = postfix[i-1] - '0';
        else
        {
            op2 = stack[top--];
            op1 = stack[top--];
            if(token==PLUS) stack[++top] = op1+op2;
            else if(token==MINUS) stack[++top] = op1-op2;
            else if(token==TIMES) stack[++top] = op1*op2;
            else if(token==DIVIDE) stack[++top] = op1/op2;
            else if(token==MOD) stack[++top] = op1%op2;
        }
        token = get_token(postfix[i++]);
    }
    return stack[top--];
}

ExpTree* init_postfix_tree(char* postfix)
{   
    postfix[strlen(postfix)] = ' ';
    ExpTree* stack[MAX_SIZE];

    int32_t top=-1;
    ExpTree *node=NULL;


    int i=0;
    precedence token = get_token(postfix[i++]);

    while (token!=EOS)
    {
        if(token==OPERAND)
        {
            node = (ExpTree*)calloc(1,sizeof(ExpTree));
            node->item = postfix[i-1];
            node->left = NULL;
            node->right = NULL;
            stack[++top] = node;
        }
        else
        {
            node = (ExpTree*)calloc(1,sizeof(ExpTree));
            node->item = postfix[i-1];
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
        token = get_token(postfix[i++]);
    }
    return stack[top--];
}

void preorder(ExpTree *t)
{
    if(t)
    {
        printf("%c ",t->item);
        preorder(t->left);
        preorder(t->right);
    }
}

void postorder(ExpTree *t)
{
    if(t)
    {   
        postorder(t->left);
        postorder(t->right);
        printf("%c ",t->item);
    }
}

void levelorder(ExpTree *t)
{
    int32_t front=-1,rear=-1;
    ExpTree* queue[MAX_SIZE]={NULL};
    if(!t) return;
    queue[++rear] = t;
    while(1)
    {
        ExpTree *ptr = queue[++front];
        if(ptr)
        {
            printf("%c ",ptr->item);
            if(ptr->left) queue[++rear]=ptr->left;
            if(ptr->right) queue[++rear]=ptr->right;
        }
        else break;
    }
}