#pragma once
#include "cstd.h"

//string compare
#define is_str_same(str1, str2) (!strcmp(str1, str2))

//string copy
#define str_copy(dest,str) ({ \
    dest = realloc(dest,sizeof(char*)*(strlen(str)+1)); \
    strncpy(dest,str,strlen(str)); \
    (dest)[strlen(str)] = 0; \
})

//get string length
#define get_str_length(str) strlen(str)

//string insert
void str_insert(char **str,char *insert_str,uint32_t index) //only support allocated string
{
    char *new_str = calloc(strlen(*str)+strlen(insert_str)+1,sizeof(char));   
    for(int i=0,c=0;i<strlen(*str)+strlen(insert_str);)
    {
        if(i==index)
        {
            for(int j=0;j<insert_str[j];j++)
            {
                new_str[i] = insert_str[j];
                i++;
            }
        }
        else
        {
            new_str[i] = (*str)[c];
            c++;
            i++;
        }
    }
    str_copy(*str,new_str);
    free(new_str);
}

//string to_lower_case
#define str_to_lower(str) ({ \
    for(char *c = str; *c; c++) \
    *c = *c > 0x40 && *c < 0x5b ? *c + 0x20 : *c; \
}) 

//string to_upper_case
#define str_to_upper(str) ({ \
    for(char *c = str; *c; c++) \
    *c = *c > 0x60 && *c < 0x7b ? *c - 0x20 : *c; \
}) 

//string trim by string

//string trim by index

//string split

//string find
uint32_t str_find(char *str, char *target,uint32_t **index) //return row number of index array
{
    uint32_t count = 0;
    for(int i=0,c=0; str[i]; i++,c++)
    {
        for(int j=0; target[j]; j++)
        {
            if(str[i+j] != target[j])
            {
                break;
            }
            if(j==strlen(target)-1)
            {   
                *index = (uint32_t*)realloc(*index,sizeof(uint32_t*)*(count+1));
                (*index)[count] = i;
                count++; 
            }
        }
    }
    return count;
}

//string replace
void str_replace(char **str,char *target,char *new_word)
{
    char *new_str = calloc(100000,sizeof(char));   
    for(int i=0,c=0; (*str)[i];)
    {
        // new_str = realloc(new_str,(c+2)*sizeof(char));
        
        for(int j=0; target[j]; j++)
        {
            if((*str)[i+j] != target[j])
            {
                new_str[c] = (*str)[i];
                new_str[c+1] = 0;
                i++;
                c++;
                break;
            }
            if(j==strlen(target)-1)
            {   
                // new_str = realloc(new_str,(c+strlen(new_word)+1)*sizeof(char));
                strncpy(new_str+c,new_word,strlen(new_word));
                c = strlen(new_str);
                i+=strlen(target);
                
            }
        }
    }
    
    str_copy(*str,new_str);
    free(new_str);
}


//string connect

//string index

