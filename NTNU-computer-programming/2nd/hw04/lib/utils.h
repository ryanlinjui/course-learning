#pragma once
#include "cstd.h"
#include "fileio.h"

// set valid arguments
#define CHECK_VALID(condition, format, args...) ({ \
    if (!(condition)) { \
        fprintf(stderr, format"\n", ##args); \
        exit(0); \
    } \
})

//  ANSI Set Graphics Mode
//  formate: ESC[Ps;...;Psm 
//  note: Ps = Selective parameter.
//  ref: https://web.archive.org/web/20060206022229/http://enterprise.aacc.cc.md.us/~rhs/ansi.html
#define ESC "\x1b"
#define SET_CLI_COLOR(str,args) ESC "[" # args "m" # str


// debug message print
#if defined(_DEBUG_) // issue: it's not work
    #define DUBUG_PRINT(fmt,...) \ 
        fprintf(stderr,"%s:%d:%s(): " fmt,\
                __FILE__, __LINE__, __func__, __VA_ARGS__)
#else
    #define DUBUG_PRINT() {}
#endif


// when option --help added, print help text file
void show_help_info(char *help_filename)
{
    char *text;
    read_text_file(&text, help_filename);
    puts(text);
    exit(0);
}
