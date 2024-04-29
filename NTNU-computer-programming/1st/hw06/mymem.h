#pragma once
#include <stdlib.h>

// *pptr is the original pointer.
// before is the original size and after is the wanted size.
// You need to make sure that the first min( before, after )
// bytes are the same.
void my_realloc( void **pptr, size_t before, size_t after );