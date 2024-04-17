#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "matrix.h"

#define MAX_MATRIX_NAME_LEN 30

int32_t main_menu()
{
    system("clear");
    puts("======= Matrix Tools =======");
    puts("(1) Create a Matrix");
    puts("(2) Show Matrix info");
    puts("(3) Show a Submatrix");
    puts("(4) Show a Transpose Matrix");
    puts("(5) Matrix element wise");
    puts("(6) Matrix multiplication");
    puts("(7) Matrix square");
    puts("(8) List Matrix");
    puts("(9) Exit");
    puts("============================\n");
    printf("Input: ");
    int32_t choose = 0;
    scanf("%d",&choose);
    return (choose >= 1 && choose <= 9) ? choose : 0;
}

void list_matrix(Matrix **m_list,int32_t list_length)
{
    puts("Matrix List:");
    for(int i=0;i<list_length;i++)
    {
        puts(m_list[i]->name);
    }
}

int32_t choose_matrix_menu(Matrix **m_list,int32_t list_length)
{
    list_matrix(m_list,list_length);
    char *name = calloc(MAX_MATRIX_NAME_LEN+1,sizeof(char));
    printf("\nSpecify the matrix name: ");
    scanf("%s",name);
    printf("\n");

    name[MAX_MATRIX_NAME_LEN] = 0;
    for(int i=0;i<list_length;i++)
    {
        if (!strcmp(name, m_list[i]->name)) return i;
    }
    return -1;
}

Matrix *init(Matrix *m)
{   
    m = (Matrix*)calloc(1,sizeof(Matrix*));
    m->name = calloc(MAX_MATRIX_NAME_LEN+1,sizeof(char));
    printf("Name (limit to 10 chars): ");
    scanf("%s",m->name);
    m->name[MAX_MATRIX_NAME_LEN] = 0;

    m->data = (Base*)calloc(1,sizeof(Base));
    printf("Row size (limit to 99 size): ");
    scanf("%d",&(m->data[0].row));
    printf("Column size (limit to 99 size): ");
    scanf("%d",&(m->data[0].column));
    puts("\n==== Input matrix data ====");

    for (int i=0,count=1;i<m->data[0].row;i++)
    {
        printf("Row%d(input %d values): ",i,m->data[0].column);
        for (int j = 0; j < m->data[0].column; j++)
        {
            int32_t num = 0;
            scanf("%d",&num);
            if (num != 0)
            {
                m->data = (Base*)realloc(m->data,(count+1)*sizeof(Base));
                m->data[count].row = i;
                m->data[count].column = j;
                m->data[count].value = num;
                m->data[0].value = count;
                count++;
            }
        }
    }
    return m;
}

void info(Matrix *m)
{
    printf("Name: %s\n",m->name);
    printf("Row: %d\n",m->data[0].row);
    printf("Column: %d\n\n",m->data[0].column);
    
    for (int i=0;i<m->data[0].row;i++)
    {
        for (int j = 0; j < m->data[0].column; j++)
        {
            for(int n=1;n<=m->data[0].value;n++)
            {
                if(m->data[n].row==i && m->data[n].column==j)
                {
                    printf("%5d",m->data[n].value);
                    break;
                }
                if(n==m->data[0].value) printf("%5d",0);
            }
        }
        puts("\n");
    }
    return;
}

Matrix *submatrix(Matrix *m,int32_t row,int32_t col)
{
    Matrix *result = (Matrix*)calloc(1,sizeof(Matrix));
    result->name = calloc(MAX_MATRIX_NAME_LEN+1,sizeof(char));
    strncpy(result->name,"submatrix result",18);

    result->data = (Base*)calloc(1,sizeof(Base));
    result->data[0].row =  m->data[0].row-1;
    result->data[0].column =  m->data[0].column-1;

    for(int i=1,count=1;i<=m->data[0].value;i++)
    {
        if(m->data[i].row != row && m->data[i].column != col )
        {
            result->data = (Base*)realloc(result->data,(count+1)*sizeof(Base));            
            result->data[count].row = m->data[i].row;
            result->data[count].column = m->data[i].column;
            if (m->data[i].row > row) result->data[count].row--;
            if (m->data[i].column > col) result->data[count].column--;
            result->data[count].value = m->data[i].value;
            result->data[0].value = count;
            count++;
        }
    }
    return result;
}

Matrix *transpose(Matrix *m)
{
    Matrix *result = (Matrix*)calloc(1,sizeof(Matrix));
    result->name = calloc(MAX_MATRIX_NAME_LEN+1,sizeof(char));
    strncpy(result->name,"transpose result",17);
    result->data = (Base*)calloc(m->data[0].value+2,sizeof(Base));

    int32_t row_terms[100], starting_pos[100];
    int32_t i,j,num_cols=m->data[0].column,num_terms=m->data[0].value;
    result->data[0].row = num_cols; result->data[0].column = m->data[0].row;
    result->data[0].value = num_terms;
    if (num_terms>0)
    {
        for(i=0;i<num_cols;i++)
        {
            row_terms[i] = 0;
        }
        for(i=1;i<num_terms;i++)
        {
            row_terms[m->data[i].column]++;
        }
        starting_pos[0] = 1;
        for(i=1;i<num_cols;i++)
        {
            starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
        }
        for(i=1;i<=num_terms;i++)
        {
            j = starting_pos[m->data[i].column]++;
            result->data[j].row = m->data[i].column;
            result->data[j].column = m->data[i].row;
            result->data[j].value = m->data[i].value;
        }
    }
    return result;
}

Matrix *element_wise(Matrix *m1,Matrix *m2)
{
    Matrix *result = (Matrix*)calloc(1,sizeof(Matrix));
    result->name = calloc(MAX_MATRIX_NAME_LEN+1,sizeof(char));
    strncpy(result->name,"element wise result",21);
    result->data = (Base*)calloc(m1->data[0].value+2,sizeof(Base));
    
    result->data[0].row = m1->data[0].row;
    result->data[0].column = m1->data[0].column;

    for(int i=1,count=1;i<=m1->data[0].value;i++)
    {
        for(int j=1;j<=m2->data[0].value;j++)
        {
            if(m1->data[i].row == m2->data[j].row && m1->data[i].column == m2->data[j].column)
            {
                result->data[count].row = m1->data[i].row;
                result->data[count].column = m1->data[i].column;
                result->data[count].value = m1->data[i].value * m2->data[j].value;
                result->data[0].value = count;
                count++;
                break;
            }
        }
    }
    return result;
}

Matrix *multiplication(Matrix *m1,Matrix *m2)
{   
    // int32_t i,j,column,totalb = m2->data[0].value,totald=0;
    // int32_t rows_a= m1->data[0].row,cols_a = m1->data[0].column;
    // int32_t totala = m1->data[0].value,cols_b=m2->data[0].column;
    // int32_t row_begin = 1,row = m1->data[1].row,sum=0;

    // if(cols_a != m2->data[0].row)
    // {
    //     fprintf("Incompatible matrices\n",stderr);
    //     exit(1);
    // }
    // Matrix *result = transpose(m2);
    // strncpy(result->name,"multiplication result",25);
    // m1->data[totala+1].row = rows_a;
    // result->data[totalb+1].row = cols_b;
    // result->data[totalb+1].column = 0;
    // for(i=1;i<=totala;)
    // {
    //     column = result->data[1].row;
    //     for(j=1;j<=totalb+1;)
    //     {
    //         if(m1->data[i].row != row)
    //         {
                
    //         }
    //     }
    // }
    return m1;
}

Matrix *square(Matrix *m,int32_t exp)
{
    Matrix *result = (Matrix*)calloc(1,sizeof(Matrix));
    result->name = calloc(MAX_MATRIX_NAME_LEN+1,sizeof(char));
    strncpy(result->name,"square result",15);
    result->data = (Base*)calloc(m->data[0].value+2,sizeof(Base));
    
    for(int i=0;i<=m->data[0].value;i++)
    {
        result->data[i].row = m->data[i].row;
        result->data[i].column = m->data[i].column;
        result->data[i].value = (i==0) ? m->data[i].value : pow(m->data[i].value,exp);
    }
    return result;
}