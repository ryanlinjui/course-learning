#pragma once
#include "cstd.h"

#define CHECK_VALID(condition, format, args...) ({ \
    if (!(condition)) { \
        fprintf(stderr, format"\n", ##args); \
        exit(0); \
    } \
})
