#pragma once

#include <stdlib.h>

long int mystrtol(const char *nptr, char **endptr, int base);
char *mystrchr(const char *s, int c); 
char *mystrrchr(const char *s, int c);
size_t mystrspn(const char *s, const char *accept); 
size_t mystrcspn(const char *s, const char *reject);
char *mystrpbrk(const char *s, const char *accept);
char *mystrstr(const char *haystack, const char *needle); 
char *mystrtok(char *str, const char *delim);