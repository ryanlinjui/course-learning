#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct _sVector 
{
    uint8_t type;
    union Component
    {
        struct _sCartesian
        {
            double x;
            double y; 
        } c;
        struct _sPolar 
        {
            double distance;
            double angle; 
        } p;
    } data;
}sVector;

sVector * myvector_init();

int myvector_set( sVector *pVector, uint8_t type, double a, double b )
{
    return 0;
}

int myvector_print( const sVector *pVector, uint8_t type )
{
    return 0;
}

int myvector_add( sVector *pA, const sVector *pB, const sVector *pC )
{
    return 0;
}

int myvector_inner_product( double *pA, const sVector *pB, const sVector *pC )
{
    return 0;
}

int myvector_area( double *pArea, const sVector *pB, const sVector *pC )
{
    return 0;
}

int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB )
{
    return 0;
}