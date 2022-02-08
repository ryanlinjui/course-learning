#include <stdint.h> 
#include <stdio.h>
unsigned int ui = 0; 
unsigned short us = 0; 
signed int si = -1;
int main() 
{
    int64_t r1 = ui + si; 
    int64_t r2 = us + si; 
    printf("%ld %ld\n", r1, r2);
}