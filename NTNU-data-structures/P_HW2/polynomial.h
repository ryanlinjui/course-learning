#include <stdint.h>

typedef struct _sPolynomial Polynomial;
struct _sPolynomial
{
    int32_t coef;
    int32_t exp;
    Polynomial *link;
};

int32_t menu();

Polynomial* init(Polynomial *p);

void info(Polynomial *p,char* prefix_str);
int32_t get_coef(Polynomial *p,int32_t exp);

Polynomial *attach_term(Polynomial *p,int32_t coef,int32_t exp);
Polynomial *remove_term(Polynomial *p,int32_t exp);

Polynomial *add(Polynomial *p1,Polynomial *p2);
Polynomial *sub(Polynomial *p1,Polynomial *p2);
Polynomial *multiply(Polynomial *p1,Polynomial *p2);
Polynomial *divide(Polynomial *p1,Polynomial *p2);