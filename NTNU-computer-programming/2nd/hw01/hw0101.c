#include <stdio.h>
#include <stdlib.h>

char str_to_hex(char st,char nd)
{
    int16_t num1 = (int16_t)st;
    int16_t num2 = (int16_t)nd;
    int16_t total = 0,reverse = 0;
    if(((num1>=48&&num1<=57)||num1>=65&&num1<=70||num1>=97&&num1<=102)&&
        ((num2>=48&&num2<=57)||num2>=65&&num2<=70||num2>=97&&num2<=102))
    {
        num1 = (num1>=48&&num1<=57) ? num1-48 : num1;
        num1 = (num1>=65&&num1<=70) ? num1-55 : num1;
        num1 = (num1>=97&&num1<=102) ? num1-87 : num1;
        num2 = (num2>=48&&num2<=57) ? num2-48 : num2;
        num2 = (num2>=65&&num2<=70) ? num2-55 : num2;
        num2 = (num2>=97&&num2<=102) ? num2-87 : num2;
        total = num1*16+num2;
        for(int i=0; i<8;i++)
        {
            reverse <<= 1;
            reverse = (total&1) ? reverse+1 : reverse;
            total >>=1;
        }
        
    }
    else
    {
        printf("Invaild Input!!\n");
        exit(1);
    }
    if(reverse<32||reverse>126)
    {
        printf("Invaild Input!!\n");
        exit(1);
    }
    return (char)reverse;
}

int main()
{   
    char *input_str= malloc(10000000);
    char ans[5000000];
    int count=0;
    printf("$ ./hw0101\n");
    printf("Please enter the hex string: ");
    scanf("%s",input_str);
    for(int i=0;input_str[i]!=0;i+=2)
    {
        if(input_str[i]=='0'&&input_str[i+1]=='0')
        {
            break;
        }
        ans[count]= str_to_hex(input_str[i],input_str[i+1]);
        count++;
    }
    for(int i=0;i<count;i++)
    {
        printf("%c",ans[i]);
    }
    printf("\n");
    free(input_str);
    return 0;
}