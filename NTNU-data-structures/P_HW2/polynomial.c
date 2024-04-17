#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "polynomial.h"

int32_t menu()
{
    puts("\n===== Polynomial Tools =====");
    puts("(1) Initial polynomial");
    puts("(2) Show coefficient");
    puts("(3) Attach term");
    puts("(4) Remove term");
    puts("(5) P1 + P2");
    puts("(6) P1 - P2");
    puts("(7) P1 * P2");
    puts("(8) P1 / P2");
    puts("(9) Exit");
    puts("==============================\n");
    printf("Input: ");
    int32_t choose = 0;
    scanf("%d",&choose);
    return (choose >= 1 && choose <= 9) ? choose : 0;
}

Polynomial *init(Polynomial *p)
{
    system("clear");
    puts("===== Please input in order left to right =====\n");
    if (p != NULL) free(p);
    p = (Polynomial*)calloc(1,sizeof(Polynomial)); //header init
    p->exp = -1;
    Polynomial *header = p;
    
    int32_t coef=0,exp=0;

    while(1)
    {
        printf("Please input coefficient (To leave, input 0): ");
        fflush(stdin);
        scanf("%d",&coef);
        if(!coef) break;

        printf("Please input exponent: ");
        fflush(stdin);
        scanf("%d",&exp);
        if(exp<0)
        {
            puts("Invalid input");
            continue;
        }
        Polynomial *temp = (Polynomial*)calloc(1,sizeof(Polynomial));
        temp->coef = coef;
        temp->exp = exp;
        p->link = temp;
        p = temp;
    }
    p->link = header;
    p = header;
    return p;
}

void info(Polynomial *p,char* prefix_str)
{
    printf("%s",prefix_str);
    if(p==NULL)
    {
        puts("<empty>");
        return;
    }
    p=p->link;
    for(int i=0; p->exp!=-1; p=p->link)
    {
        if(!p->coef) continue;
        if(p->coef>0 && i != 0) printf("+");
        if(p->coef>1 || p->coef<-1 || p->exp==0 ) printf("%d",p->coef);
        if(p->coef==-1 && p->exp!=0) printf("-");
        if(p->exp!=0) printf("x");
        if(p->exp>1) printf("^%d",p->exp);
        i++;
    }
    printf("\n");
}

int32_t get_coef(Polynomial *p,int32_t exp)
{
    if (p==NULL) return -1;
    do
    {
        p = p->link;
        if(p->exp == exp) return p->coef;
        
    } while (p->exp != -1);
    return 0;
}

Polynomial *attach_term(Polynomial *p,int32_t coef,int32_t exp)
{
    Polynomial *header = p;
    p = p->link;
    for(;p->exp!=-1;p=p->link)
    {
        if(p->exp == exp) 
        {
            puts("\nSpecify exponent was existed");
            return header;
        }
    }

    if(p->link->exp < exp)
    {
        Polynomial *temp = (Polynomial*)calloc(1,sizeof(Polynomial));
        temp->coef = coef;
        temp->exp = exp;
        temp->link = p->link;
        p->link = temp;
    }
    else
    {
        p = p->link;
        for(;p->exp!=-1;p=p->link)
        {
            if(p->exp > exp && p->link->exp < exp)
            {
                Polynomial *temp = (Polynomial*)calloc(1,sizeof(Polynomial));
                temp->coef = coef;
                temp->exp = exp;
                temp->link = p->link;
                p->link = temp;
                break;
            }
        }
    }
    puts("\nSuccessfully attach new term");
    return header;
}

Polynomial *remove_term(Polynomial *p,int32_t exp)
{
    Polynomial *header = p;
    Polynomial *pre=p;
    p = p->link;
    for(;p->exp!=-1;p=p->link)
    {
        if(p->exp == exp)
        {
            pre->link = p->link;
            free(p);
            puts("\nSuccessfully remove term");
            break;
        }
        if(p->link->exp==-1)
        {
            puts("\nFailed to remove, specify exponent was not found");
        }
        pre = p;
    }
    return header;
}

Polynomial *add(Polynomial *p1,Polynomial *p2)
{
    if(p1==NULL) return p2;
    if(p2==NULL) return p1;
    Polynomial *result = (Polynomial*)calloc(1,sizeof(Polynomial));
    result->exp = -1;
    Polynomial *header = result;
    
    p1 = p1->link;
    p2 = p2->link;
    
    for(;p1->exp!=-1||p2->exp!=-1;result=result->link)
    {
        Polynomial *temp = (Polynomial*)calloc(1,sizeof(Polynomial));
        if(p1->exp==p2->exp)
        {
            temp->coef = p1->coef+p2->coef;
            temp->exp = p1->exp;
            p1 = p1->link;
            p2 = p2->link;
        }
        else if (p1->exp>p2->exp)
        {
            temp->coef = p1->coef;
            temp->exp = p1->exp;
            p1 = p1->link;
        }
        else if (p1->exp<p2->exp)
        {
            temp->coef = p2->coef;
            temp->exp = p2->exp;
            p2 = p2->link;
        }
        result->link = temp;
    }
    result->link = header;
    return header;
}

Polynomial *sub(Polynomial *p1,Polynomial *p2)
{
    if(p1==NULL) return p2;
    if(p2==NULL) return p1;
    Polynomial *result = (Polynomial*)calloc(1,sizeof(Polynomial));
    result->exp = -1;
    Polynomial *header = result;
    
    p1 = p1->link;
    p2 = p2->link;
    
    for(;p1->exp!=-1||p2->exp!=-1;result=result->link)
    {
        Polynomial *temp = (Polynomial*)calloc(1,sizeof(Polynomial));
        if(p1->exp==p2->exp)
        {
            temp->coef = p1->coef-p2->coef;
            temp->exp = p1->exp;
            p1 = p1->link;
            p2 = p2->link;
        }
        else if (p1->exp>p2->exp)
        {
            temp->coef = p1->coef;
            temp->exp = p1->exp;
            p1 = p1->link;
        }
        else if (p1->exp<p2->exp)
        {
            temp->coef = -p2->coef;
            temp->exp = p2->exp;
            p2 = p2->link;
        }
        result->link = temp;
    }
    result->link = header;
    return header;
}

Polynomial *multiply(Polynomial *p1,Polynomial *p2)
{
    if(p1==NULL) return p2;
    if(p2==NULL) return p1;
    Polynomial *result = (Polynomial*)calloc(1,sizeof(Polynomial));
    result->exp = -1;
    Polynomial *header = result;
    
    for(p1=p1->link;p1->exp!=-1;p1=p1->link)
    {
        for(p2=p2->link;p2->exp!=-1;p2=p2->link)
        {            
            Polynomial *temp = (Polynomial*)calloc(1,sizeof(Polynomial));
            temp->coef = p1->coef * p2->coef;
            temp->exp = p1->exp + p2->exp;
            Polynomial *r=header;
            int32_t insert = 1;
            for(r=r->link;r!=NULL;r=r->link)
            {
                if(r->exp==temp->exp)
                {
                    r->coef += temp->coef; 
                    insert = 0;
                    break;
                }
            }
            if(insert)
            {
                result->link = temp;
                result = temp;
            }   
        }
    }
    result->link = header;
    return header;
}

Polynomial *divide(Polynomial *p1,Polynomial *p2)
{
    return NULL;
}