#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"

int main()
{
    Polynomial *p1 = NULL;
    Polynomial *p2 = NULL;

    int32_t total = 0;
    while(1)
    {
        system("clear");

        info(p1,"P1: ");
        info(p2,"P2: ");
        int32_t choose = menu();
        
        if (p1==NULL && p2==NULL && choose != 1 && choose != 9)
        {
            puts("\nYou haven't initial any polynomial");
            choose = 0;
        }

        if(choose==1)
        {
            char p_choose[2] = {0,0};
            printf("P1 or P2: ");
            scanf("%s",p_choose);
            if (p_choose[0] == 'P' && p_choose[1] == '1') 
            {
                p1 = init(p1);
                puts("\nSuccessfully initial Polynomial 1");
            }
            else if (p_choose[0] == 'P' && p_choose[1] == '2')
            {
                p2 = init(p2);
                puts("\nSuccessfully initial Polynomial 2");
            }
            else puts("\nInvalid Input");
        }
        else if(choose==2)
        {
            int32_t exp=0;
            printf("Exponent: ");
            scanf("%d",&exp);
            if(p1==NULL) printf("\nP1: <empty>\n");
            else printf("\nP1: %d\n",get_coef(p1,exp));
            if(p2==NULL) printf("\nP2: <empty>\n");
            else printf("\nP2: %d\n",get_coef(p2,exp));
        }
        else if(choose==3)
        {
            char p_choose[2] = {0,0};
            printf("P1 or P2: ");
            scanf("%s",p_choose);

            int32_t coef=0,exp=0;
            printf("Coefficient: ");
            scanf("%d",&coef);
            printf("Exponent: ");
            scanf("%d",&exp);
            
            if (p_choose[0] == 'P' && p_choose[1] == '1') p1 = attach_term(p1,coef,exp);
            else if (p_choose[0] == 'P' && p_choose[1] == '2') p2 = attach_term(p2,coef,exp);
            else puts("\nInvalid Input");            
        }
        else if(choose==4)
        {
            char p_choose[2] = {0,0};
            printf("P1 or P2: ");
            scanf("%s",p_choose);

            int32_t exp=0;
            printf("Exponent: ");
            scanf("%d",&exp);

            if (p_choose[0] == 'P' && p_choose[1] == '1') p1 = remove_term(p1,exp);
            else if (p_choose[0] == 'P' && p_choose[1] == '2') p2 = remove_term(p2,exp);
            else puts("\nInvalid Input");
        }
        else if(choose==5) info(add(p1,p2),"Addition Result: "); 
        else if(choose==6) info(sub(p1,p2),"Subtraction Result: "); 
        else if(choose==7) info(multiply(p1,p2),"Multiplication Result: "); 
        else if(choose==8) puts("Sorry... Division function is not finish yet...");
        else if(choose==9) break;
        else puts("\nInvalid Input");

        puts("\nPlease enter to continue......");
        fflush(stdin);
        getchar();
    }

    free(p1);
    free(p2);
    return 0;
}