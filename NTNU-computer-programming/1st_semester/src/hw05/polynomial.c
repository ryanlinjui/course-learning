#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void show(int64_t p[],int64_t p_size)
{
    for(int i = 0; i < p_size;i++)
    {
        if(p[i]==0)
        {
            continue;
        }
        if(p[i]>0&&i!=0)
        {
            printf(" + ");
        }
        else if(p[i]<0&&i!=0)
        {
            printf(" - ");
        }
        if(i==0&&p[i]==-1)
        {
            printf("-x");
        }
        else if((i>0&&p[i]<0&&p[i]!=-1&&p[i]!=1)||(i==p_size-1&&p[i]<0))
        {
            printf("%ld",p[i]*-1);
        }
        else if(p[i]!=1&&p[i]!=-1&&p[i]!=-1||(i==p_size-1&&p[i]>0))
        {
            printf("%ld",p[i]);
        }
        
        if((i!=p_size-1)&&!(i==0&&p[i]==-1))
        {
            printf("x");
        }
        if(i<p_size-2)
        {
            printf("^%ld",p_size-i-1);
        }
    }
}

void show_plus(int64_t p1[],int64_t p1_size,int64_t p2[],int64_t p2_size)
{
    // #define p_ans_size (p1_size>p2_size) ? p1_size : p2_size
    // #define p_diff (p1_size>p2_size) ? p1_size-p2_size : p2_size-p1_size
    int64_t p_ans_size,p_diff;
    if(p1_size>p2_size)
    {
        p_ans_size = p1_size;
        p_diff = p1_size-p2_size;
    }
    else
    {
        p_ans_size = p2_size;
        p_diff = p2_size-p1_size;
    } 
    
    int64_t p_ans[p_ans_size];
    for(int i=0;i<p_ans_size;i++)
    {
        if(p1_size==p_ans_size)
        {
            if(i<p_diff)
            {
                p_ans[i]=p1[i];
            }
            else
            {
                p_ans[i]=p1[i]+p2[i-p_diff];
            }
        }
        else
        {
            if(i<p_diff)
            {
                p_ans[i]=p2[i];
            }
            else
            {
                p_ans[i]=p1[i-p_diff]+p2[i];
            }
        }
    }
    show(p_ans,p_ans_size);
}

void show_substract(int64_t p1[],int64_t p1_size,int64_t p2[],int64_t p2_size)
{
    // #define p_ans_size (p1_size>p2_size) ? p1_size : p2_size
    // #define p_diff (p1_size>p2_size) ? p1_size-p2_size : p2_size-p1_size
    int64_t p_ans_size,p_diff;
    if(p1_size>p2_size)
    {
        p_ans_size = p1_size;
        p_diff = p1_size-p2_size;
    }
    else
    {
        p_ans_size = p2_size;
        p_diff = p2_size-p1_size;
    }
    int64_t p_ans[p_ans_size];
    for(int i=0;i<p_ans_size;i++)
    {
        if(p1_size==p_ans_size)
        {
            if(i<p_diff)
            {
                p_ans[i]=p1[i];
            }
            else
            {
                p_ans[i]=p1[i]-p2[i-p_diff];
            }
        }
        else
        {
            if(i<p_diff)
            {
                p_ans[i]=-p2[i];
            }
            else
            {
                p_ans[i]=p1[i-p_diff]-p2[i];
            }
        }
    }
    show(p_ans,p_ans_size);
}

void show_multiply(int64_t p1[],int64_t p1_size,int64_t p2[],int64_t p2_size)
{
    int64_t p_ans_size=p1_size+p2_size-1;
    int64_t p_ans[p_ans_size];
    for(int i=0;i<p_ans_size;i++)
    {
        p_ans[i] = 0;
    }
    for(int i=0;i<p1_size;i++)
    {
        for(int j=0;j< p2_size;j++)
        {
            p_ans[i+j]+=p1[i]*p2[j];
        }
    }
    show(p_ans,p_ans_size);
}

void calculate_result(int64_t p1[],int64_t p1_size,int64_t p2[],int64_t p2_size)
{
    printf("p1: ");
    show(p1,p1_size);
    printf("\n");
    printf("p2: ");
    show(p2,p2_size);
    printf("\n");
    printf("p1 + p2: ");
    show_plus(p1,p1_size,p2,p2_size);
    printf("\n");
    printf("p1 - p2: ");
    show_substract(p1,p1_size,p2,p2_size);
    printf("\n");
    printf("p1 * p2: ");
    show_multiply(p1,p1_size,p2,p2_size);
    printf("\n");   
}