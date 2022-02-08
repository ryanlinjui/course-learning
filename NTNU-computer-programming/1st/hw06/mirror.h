#pragma once
#include <stdint.h>

// Use (x1,y1) and (x2,y2) to determine a line.
// If the input is not a valid line, use previous valid one.
void set_line( double x1, double y1, double x2, double y2 );

// Q(c,d) is the mirror of P(a,b) according to the pre-
// determined line.
// If there is no valid line, return -1; otherwise , return 0.
int32_t get_mirror( double a, double b, double *c, double *d );
