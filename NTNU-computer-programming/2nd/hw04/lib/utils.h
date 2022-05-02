#pragma once
#include "cstd.h"
#include "string.h"

// set valid arguments
#define CHECK_VALID(condition, format, args...) ({ \
    if (!(condition)) { \
        fprintf(stderr, format"\n", ##args); \
        exit(0); \
    } \
})

#include "fileio.h" //CHECK_VALID in there, put here after CHECK_VALID

//  ANSI Set Graphics Mode
//  formate: ESC[Ps;...;Psm 
//  note: Ps = Selective parameter.
//  ref: https://web.archive.org/web/20060206022229/http://enterprise.aacc.cc.md.us/~rhs/ansi.html
#define ESC "\x1b"
#define SET_CLI_COLOR(str,args) ESC "[" # args "m" # str

/*
// debug message print
#if defined(_DEBUG_) // issue: it's not work
    #define DUBUG_PRINT(fmt,...) \ 
        fprintf(stderr,"%s:%d:%s(): " fmt,\
                __FILE__, __LINE__, __func__, __VA_ARGS__)
#else
    #define DUBUG_PRINT() {}
#endif
*/


// when option --help added, print help text file
void add_help_option(char argc, char **argv)
{
    for(int i = 0; i < argc; i++)
    {
        if(is_str_same(argv[i], "--help")) break;
        if(i==argc-1) return;
    }
    char *filename = calloc(strlen(argv[0])+1,sizeof(char));
    strncpy(filename,argv[0]+2,strlen(argv[0]+2));
    str_insert(&filename, "help/",0);
    str_insert(&filename, ".help",strlen(filename));
    char *text;
    read_text_file(&text,filename);
    puts(text);
    free(filename);
    exit(0);
}
