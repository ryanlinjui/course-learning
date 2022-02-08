#pragma once

#include <stdint.h>
#include <stddef.h>
double get_mean( const int32_t input[], size_t size ); 
double get_median( const int32_t input[], size_t size ); 
int32_t get_mode( const int32_t input[], size_t size );
double get_stddev( const int32_t input[], size_t size );