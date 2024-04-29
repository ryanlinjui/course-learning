#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct _sVector 
{
    uint8_t type; // 1: Cartesian coordinates; 2: polar coordinates union Component
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

// Memory allocation. Fill zeros to all memory block.
sVector * myvector_init();

// If error, return -1; otherwise, return 0;
int myvector_set( sVector *pVector, uint8_t type, double a, double b );

// Print the given vector according to the given type.
// If Cartesian, print (x,y).
// If polar, print (distance, theta-pi). EX: distance=2 and angle=90 degree,
// print (2,0.5-pi).
// Theta must be between 0 and 2.
// If error, return -1; otherwise, return 0;
int myvector_print( const sVector *pVector, uint8_t type );

// A = B + C
// A's type is set to B's type.
// If error, return -1; otherwise, return 0;
int myvector_add( sVector *pA, const sVector *pB, const sVector *pC );

// A = B dot C
// If error, return -1; otherwise, return 0;
int myvector_inner_product( double *pA, const sVector *pB, const sVector *pC );

// Get the area of the parallelogram spanned by two vectors.
// If error, return -1; otherwise, return 0;
int myvector_area( double *pArea, const sVector *pB, const sVector *pC );

// Given a target point, find the closest point which can be combined from two given vectors with integer coefficients.
// (*pX,*pY) = m*A + n*B, m and n must be integers.
// (*pX,*pY) is the closet point to (*pTx,*pTy)
// If error, return -1; otherwise, return 0;
int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB );