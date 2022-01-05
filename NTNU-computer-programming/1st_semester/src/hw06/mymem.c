#include <stdlib.h>

void my_realloc( void **pptr, size_t before, size_t after )
{
    realloc(pptr, sizeof(size_t)*after);
}