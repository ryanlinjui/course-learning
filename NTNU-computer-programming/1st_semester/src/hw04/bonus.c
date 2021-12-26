#include <stdio.h>

int main()
{
    printf("----------PRINTf EXAMPLE----------\n");
    int num1=printf("Apple");
    printf("\nThe total number of printed characters is %d\n",num1);
    int num2=printf("Cat");
    printf("\nThe total number of printed characters is %d\n\n",num2);
    printf("----------SCANF EXAMPLE----------\n");
    int p1,p2,p3;
    printf("Please input one number: ");
    num1=scanf("%d",&p1);
    printf("You input %d number(s) -->(%d)\n",num1,p1);
    printf("Please input three number: ");
    num2=scanf("%d %d %d",&p1,&p2,&p3);
    printf("You input %d number(s) -->(%d,%d,%d)\n\n",num2,p1,p2,p3);
    return 0;
}