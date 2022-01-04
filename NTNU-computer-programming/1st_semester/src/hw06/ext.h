#pragma once

#include <stdint.h>

// If a < b, return -1 and c is meaningless.
// If a and b are co-prime, return 1 and c is the
// multiplicative inverse of b mod a.
// If a and b are not co-prime, return 0 and c is the gcd.
int32_t ext_euclidean( uint32_t a, uint32_t b, uint32_t *c );