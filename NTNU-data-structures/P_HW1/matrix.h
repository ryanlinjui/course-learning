#include <stdint.h>

typedef struct _sBase
{
    int32_t row;
    int32_t column;
    int32_t value;
}Base;

typedef struct _sMatrix
{
    char *name;
    Base *data;
}Matrix;

int32_t main_menu();
int32_t choose_matrix_menu(Matrix **m_list,int32_t list_length);
void list_matrix(Matrix **m_list,int32_t list_length);

Matrix *init(Matrix *m);
void info(Matrix *m);

Matrix *submatrix(Matrix *m,int32_t row,int32_t col);
Matrix *transpose(Matrix *m);
Matrix *element_wise(Matrix *m1,Matrix *m2);
Matrix *multiplication(Matrix *m1,Matrix *m2);
Matrix *square(Matrix *m,int32_t exp);

