#pragma once

#include "lib/array.h"
#include "lib/string.h"
#include "lib/fileio.h"

#define STD_COLOR "\x1b[37;40m"
#define KEYBOARD_COLOR "\x1b[34;40m"

const char *C[44] = 
{
    "auto","break","case","char",
    "const","continue","default","do",
    "double","else","enum","extern",
    "float","for","goto","if",
    "inline","int","long","register",
    "restrict","return","short","signed",
    "sizeof","static","struct","switch",
    "typedef","union","unsigned","void",
    "volatile","while","_Alignas","_Alignof",
    "_Atomic","_Bool","_Complex","_Generic",
    "_Imaginary","_Noreturn","_Static_assert","_Thread_local"
};

const char *Cpp[84] = 
{
    "alignas","alignof","asm","auto",
    "bool","break","case","catch",
    "char","char16_t","char32_t","class",
    "const","constexpr","const_cast","continue",
    "decltype","default","delete","do",
    "double","dynamic_cast","else","enum",
    "explicit","export","extern","false",
    "float","for","friend","goto",
    "if","inline","int","long",
    "mutable","namespace","new","noexcept",
    "nullptr","operator","private","protected",
    "public","register","reinterpret_cast","return",
    "short","signed","sizeof","static",
    "static_assert","static_cast","struct","switch",
    "template","this","thread_local","throw",
    "true","try","typedef","typeid",
    "typename","union","unsigned","using",
    "virtual","void","volatile","wchar_t",
    "while","and","and_eq","bitand",
    "bitor","compl","not","not_eq",
    "or","or_eq","xor","xor_eq"
};

const char *JS[38] =
{
    "await","break","case","catch",
    "class","const","continue","debugger",
    "default","delete","do","else",
    "enum","export","extends","false",
    "finally","for","function","if",
    "import","in","instanceof","new",
    "null","return","super","switch",
    "this","throw","true","try",
    "typeof","var","void","while",
    "with","yield"
};

const char *Java[51] =
{
    "abstract","assert","boolean","break",
    "byte","case","catch","char",
    "class","const","continue","default",
    "do","double","else","enum",
    "extends","final","finally","float",
    "for","if","goto","implements",
    "import","instanceof","int","interface",
    "long","native","new","package",
    "private","protected","public","return",
    "short","static","strictfp","super",
    "switch","synchronized","this","throw",
    "throws","transient","try","void",
    "volatile","while","_"
};

const char *Rust[53] =
{
    "as","break","const","continue",
    "crate","else","enum","extern",
    "false","fn","for","if",
    "impl","in","let","loop",
    "match","mod","move","mut",
    "pub","ref","return","self",
    "Self","static","struct","super",
    "trait","true","type","unsafe",
    "use","where","while","async",
    "await","dyn","abstract","become",
    "box","do","final","macro",
    "override","priv","typeof","unsized",
    "virtual","yield","try","union",
    "\'static"
};

void print_code_highlighter(char *filename,bool show_linenum,bool show_color,char *language)
{
    char **keyboard = (char**)malloc(1000);
    uint32_t keyboard_count = 0;
    if(is_str_same(language,"C"))
    {
        memcpy(keyboard,C,get_array_length(C)*sizeof(char*));
        keyboard_count = get_array_length(C);
    }
    else if(is_str_same(language,"C++"))
    {
        memcpy(keyboard,Cpp,get_array_length(Cpp)*sizeof(char*));
        keyboard_count = get_array_length(Cpp);
    }
    else if(is_str_same(language,"JS"))
    {
        memcpy(keyboard,JS,get_array_length(JS)*sizeof(char*));
        keyboard_count = get_array_length(JS);
    }
    else if(is_str_same(language,"Java"))
    {
        memcpy(keyboard,Java,get_array_length(Java)*sizeof(char*));
        keyboard_count = get_array_length(Java);
    }
    else if(is_str_same(language,"Rust"))
    {
        memcpy(keyboard,Rust,get_array_length(Rust)*sizeof(char*));
        keyboard_count = get_array_length(Rust);
    }
    char **text = NULL;
    int32_t row_count = read_text_file_2D(&text,filename);
    for(int i = 0; i < row_count;i++)
    {
        if(show_linenum)
        {
            printf(STD_COLOR"%8d  ",i+1);
        }
        if(show_color)
        {   
            for(int n=0;n<keyboard_count;n++)
            {
                uint32_t *index = NULL;
                uint32_t count = str_find(text[i],keyboard[n],&index);
                for(int j = 0,offset = 0; j < count; j++)
                {
                    str_insert(&(text[i]),KEYBOARD_COLOR,index[j]+offset);
                    offset += strlen(KEYBOARD_COLOR);
                    str_insert(&(text[i]),STD_COLOR,index[j]+strlen(keyboard[n])+offset);
                    offset += strlen(STD_COLOR);
                }
            }
        }
        printf(STD_COLOR"%s",text[i]);
    }
    free(text);
    free(keyboard);
}