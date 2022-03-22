#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SIGN_BIT 1
#define EXPONENT_BIT 11
#define FRACTION_BIT 52

void print_bin(uint64_t num,uint64_t num_exp)
{   
    for(int i=num_exp-1;i>=0;i--)
    {
        if((num>>i)&1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

union
{    
    double num;
    struct
    {
        uint64_t fraction : FRACTION_BIT;
        uint64_t exponent : EXPONENT_BIT;
        uint64_t sign : SIGN_BIT;
    }element;
}ieee;

int main()
{
    printf("Please enter a floating-point number (double precision): ");
    scanf("%lf",&ieee.num);
    printf("Sign: %x\n",ieee.element.sign);
    printf("Exponent: ");
    print_bin(ieee.element.exponent,EXPONENT_BIT);
    printf("Fraction: ");
    print_bin(ieee.element.fraction,FRACTION_BIT);
    printf("%g = (-1)^%d * (1",ieee.num,ieee.element.sign);
    for(int i=FRACTION_BIT-1;i>=0;i--)
    {
        if((ieee.element.fraction>>i)&1)
        {
            printf(" + 2^%d",i-FRACTION_BIT);
        }
    }
    printf(") * 2^(%u-%u)\n",ieee.element.exponent,(1<<(EXPONENT_BIT-1))-1);
    return 0;
}