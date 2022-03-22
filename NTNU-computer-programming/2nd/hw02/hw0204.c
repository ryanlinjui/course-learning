#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 4096

typedef struct _sMixedNumber 
{ 
    int64_t integer;
    int64_t numerator;
    int64_t denominator;

}sMixedNumber;

void is_valid(int64_t r1_d,int64_t r2_d)
{
    if(!(r1_d&&r2_d))
    {
        printf("Invalid Input!!\n");
        exit(0);
    }
}

void simple(sMixedNumber *pNumber)
{   
    int64_t p_i = pNumber->integer;
    int64_t p_n = pNumber->numerator;
    int64_t p_d = pNumber->denominator;
    if(p_n<0&&p_d<0)
    {
        p_n *= -1;
        p_d *= -1;
    }
    int64_t c = ((p_n)<0) ? -1 : 1;
    int64_t n1=p_n*c, n2=p_d;
    while(n1!=n2)
    {
        if(n1 > n2)
        {
            n1 -= n2;
        }
        else
        {
            n2 -= n1;
        }
    }
    int64_t gcd = n1;
    p_i = (int64_t)(p_n/p_d);
    pNumber->integer = p_i;
    pNumber->denominator = p_d/gcd;
    pNumber->numerator = ((p_i>=0) ? p_n/gcd : -(p_n/gcd))-((p_d/gcd)*p_i);
}

void mixed_add( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2) // pNumber = r1 + r2
{
    is_valid(r1.denominator,r2.denominator);
    int64_t c1 = (r1.integer<0) ? -1 : 1;
    int64_t c2 = (r2.integer<0) ? -1 : 1;
    pNumber->denominator = r1.denominator * r2.denominator;
    pNumber->numerator = (c1*r1.numerator+(r1.denominator*r1.integer)) * r2.denominator + r1.denominator * (c2*r2.numerator+(r2.denominator*r2.integer));
}

void mixed_sub( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2) // pNumber = r1 - r2
{
    is_valid(r1.denominator,r2.denominator);
    int64_t c1 = (r1.integer<0) ? -1 : 1;
    int64_t c2 = (r2.integer<0) ? -1 : 1;
    pNumber->denominator = r1.denominator * r2.denominator;
    pNumber->numerator = (c1*r1.numerator+(r1.denominator*r1.integer)) * r2.denominator - r1.denominator * (c2*r2.numerator+(r2.denominator*r2.integer));
}

void mixed_mul( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2) // pNumber = r1 * r2
{
    is_valid(r1.denominator,r2.denominator);
    int64_t c1 = (r1.integer<0) ? -1 : 1;
    int64_t c2 = (r2.integer<0) ? -1 : 1;
    pNumber->denominator = r1.denominator * r2.denominator;
    pNumber->numerator = (c1*r1.numerator+(r1.denominator*r1.integer)) * (c2*r2.numerator+(r2.denominator*r2.integer));
}

void mixed_div( sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2) //// pNumber = r1 / r2
{
    is_valid(r1.denominator,r2.denominator);
    int64_t c1 = (r1.integer<0) ? -1 : 1;
    int64_t c2 = (r2.integer<0) ? -1 : 1;
    pNumber->denominator = r1.denominator * (c2*r2.numerator+(r2.denominator*r2.integer));
    pNumber->numerator = (c1*r1.numerator+(r1.denominator*r1.integer)) * r2.denominator;
}

sMixedNumber* analysis_frac(char *frac)
{
    int64_t num[3]={0};
    int64_t c=0;
    for(c=0;*frac;)
    {
        if(*frac>=48&&*frac<=57)
        {
            num[c] = strtol(frac,&frac,10);
            c++;
        }
        else if(*frac=='(')
        {
            frac+=1;
            num[c] = strtol(frac,&frac,10);
            c++;
        }
        else if(*frac=='\\')
        {
            frac+=6;
            num[c] = strtol(frac,&frac,10);
            c++;
        }
        else if(*frac=='}')
        {
            frac+=2; 
            num[c] = strtol(frac,&frac,10);
            c++;
            break;
        }
        else
        {
            frac++;
        }
    }
    if(c==1)
    {
        num[2] = 1;
        num[1] = 0;
    }
    else if(c==2)
    {
        num[2] = num[1];
        num[1] = num[0];
        num[0] = 0;   
    }
    return &(sMixedNumber){
        .integer=num[0],
        .numerator=num[1],
        .denominator=num[2]
    };
}

void solve(char *question)
{
    sMixedNumber *r = NULL;
    char *op = NULL;
    int last_i=0;
    for(int i=0,j=0,b=0;question[i];i++)
    {
        if(question[i]=='}')
        {
            b++;
        }
        if(b==2||question[i]==')')
        {   
            i++;
            i = (question[i]==')') ? i+1 : i;
            op = realloc(op,(j+1)*sizeof(char));
            r = realloc(r,(j+1)*sizeof(sMixedNumber)); // \frac{-1}{2}*(-2)+(-1\frac{5}{6})
            op[j] = question[i];
            char *question_cp = malloc(i-last_i+1);
            strncpy(question_cp,question+last_i,i-last_i);
            last_i = i+1;
            r[j] = *analysis_frac(question_cp);
            // printf("%ld,%ld,%ld --> %c\n",r[j].integer,r[j].numerator,r[j].denominator,op[j]);
            j++;
            b=0;
            free(question_cp);
        }
    }
    sMixedNumber ans={
        .integer=0,
        .numerator=0,
        .denominator=1
    };
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<op[j];j++)
        {
            if(i==0)
            {
                if(op[j]=='*')
                {
                    mixed_mul(&ans,r[j],r[j+1]);
                }
                else if(op[j]=='/')
                {
                    mixed_div(&ans,r[j],r[j+1]);
                }   
            }
            else
            {
                uint8_t next_frac = (j==0) ? 0 : 1;
                if(op[j]=='+')
                {
                    mixed_add(&ans,r[j+next_frac],ans);
                }
                else if(op[j]=='-')
                {
                    mixed_sub(&ans,r[j+next_frac],ans);
                }
            }   
        }
    }
    simple(&ans);
    printf("A: ");
    if(ans.integer<0)
    {
        printf("(%ld\\frac{%ld}{%ld})",ans.integer,ans.numerator,ans.denominator);
    }
    else if(ans.integer==0)
    {
        printf("\\frac{%ld}{%ld}",ans.numerator,ans.denominator);    
    }
    else if(ans.integer>0)
    {
        printf("%ld\\frac{%ld}{%ld}",ans.integer,ans.numerator,ans.denominator);
    }
    else if((ans.numerator==1)&&(ans.denominator==1))
    {
        printf("%ld",ans.integer);
    }
    printf("\n");
    free(r);
    free(op);
}

int main()
{
    // \frac{1}{2}+1\frac{5}{6}*2\frac{3}{10}
    // \frac{-1}{2}*(-2)+(-1\frac{5}{6})
    // \frac{1}{2}+1\frac{5}{6}*2\frac{3}{10}*(-3)/\frac{-2}{5} = -12\frac{11}{20}
    char *question=malloc(MAX_LEN),*answer=malloc(MAX_LEN);
    printf("Q: ");
    scanf("%s", question);
    solve(question);
    return 0;
}