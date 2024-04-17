#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define MAX_STORED_NUM 100

int main()
{
    Matrix **m = (Matrix**)calloc(MAX_STORED_NUM,sizeof(Matrix*));

    int32_t total = 0;
    while(1)
    {
        int32_t choose = main_menu();
        puts("");
        if(choose==1)
        {
            m[total] = init(m[total]);
            total++;
            puts("\nNew matrix has been created!!");
        }
        else if(choose==2)
        {
            int32_t index = choose_matrix_menu(m,total);
            if (index==-1) puts("Invalid!!");
            else info(m[index]);
        }
        else if(choose==3)
        {
            int32_t index = choose_matrix_menu(m,total);
            if (index==-1) puts("Invalid!!");
            else
            {
                int32_t row = 0,col=0;
                printf("Row: ");
                scanf("%d",&row);
                printf("Column: ");
                scanf("%d",&col);
                info(submatrix(m[index],row,col));
            }
            
        }
        else if(choose==4)
        {
            int32_t index = choose_matrix_menu(m,total);
            if (index==-1) puts("Invalid!!");
            else info(transpose(m[index]));
        }
        else if(choose==5)
        {
            int32_t index1 = choose_matrix_menu(m,total);
            int32_t index2 = choose_matrix_menu(m,total);
            if (index1==-1 || index2==-1) puts("Invalid!!");
            else info(element_wise(m[index1],m[index2]));
        }
        else if(choose==6)
        {
            puts("Sorry... It's not be done....");
            // int32_t index1 = choose_matrix_menu(m,total);
            // int32_t index2 = choose_matrix_menu(m,total);   
            // info(multiplication(m[index1],m[index2]));
        }
        else if(choose==7)
        {
            int32_t index = choose_matrix_menu(m,total);
            if (index==-1) puts("Invalid!!");
            else
            {
                int32_t exp = 0;
                printf("Exp: ");
                scanf("%d",&exp);
                info(square(m[index],exp));
            }
        }
        else if(choose==8) list_matrix(m,total);
        else if(choose==9) break;
        else puts("\nInvalid Input!!");
        
        puts("\nPlease enter to continue......");
        fflush(stdin);
        getchar();
    }
    free(m);
    return 0;
}