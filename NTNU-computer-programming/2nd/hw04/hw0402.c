#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/fileio.h"

#define HEADERFILE_FORMAT_FILENAME "ip_code_format/header.txt"
#define CFILE_FORMAT_FILENAME "ip_code_format/c.txt"

#define MAX_LEN 1000

void code_generate(char *input_filename,char *struct_name,char *output_filename)
{
    char **ip_text;
    char *ip_format = calloc(MAX_LEN,sizeof(char));
    char *c_txt;
    char *header_txt;
    read_text_file(&c_txt,CFILE_FORMAT_FILENAME);
    read_text_file(&header_txt,HEADERFILE_FORMAT_FILENAME);
    int32_t count = read_text_file_2D(&ip_text,input_filename);
    
    for(int i=0;i<count;i+=2)
    {
        str_to_lower(ip_text[i]);
        char *var_name = calloc(MAX_LEN,sizeof(char));
        for(int j=1,c=0,b=0;j<strlen(ip_text[i]);j++)
        {        
            b++; 
            if(ip_text[i][j]=='|')
            {
                var_name[c] = ';';
                var_name[c+1] = '\n';  
                if((b-1)/16==0)
                {
                    str_insert(&var_name,"    uint8_t ",0);
                }
                else if((b-1)/16==1)
                {
                    str_insert(&var_name,"    uint16_t ",0);
                }
                else if((b-1)/16==2)
                {
                    str_insert(&var_name,"    uint8_t ",0);
                    str_insert(&var_name,"[3]",strlen(var_name)-2);
                }
                else if((b-1)/16==3)
                {
                    str_insert(&var_name,"    uint32_t ",0);
                }                
                strncpy(ip_format+strlen(ip_format),var_name,strlen(var_name));  
                c=0;
                b=0; 
                free(var_name);
                var_name = calloc(MAX_LEN,sizeof(char));
            }
            else if(ip_text[i][j]!=' ')
            {
                var_name[c] = ip_text[i][j];
                c++;
            }
        }
        free(var_name);
    }
    str_replace(&c_txt,"[struct_name]",struct_name);
    str_replace(&header_txt,"[struct_name]",struct_name);
    str_to_lower(struct_name);
    str_replace(&c_txt,"[(lower)struct_name]",struct_name);
    str_replace(&header_txt,"[(lower)struct_name]",struct_name);
    str_replace(&c_txt,"[ip_format]",ip_format);
    str_replace(&header_txt,"[ip_format]",ip_format);
    
    str_insert(&output_filename,".c",strlen(output_filename));
    write_text_file(&c_txt,output_filename);
    str_replace(&output_filename,".c",".h");
    write_text_file(&header_txt,output_filename);
}

struct option long_options[] = 
{  
     {0, 0, 0, 0},  
};  

int main(int argc, char **argv)
{
    add_help_option(argc, argv);

    char *input_filename = calloc(MAX_LEN,sizeof(char));
    char *struct_name = calloc(MAX_LEN,sizeof(char));
    char *output_filename = calloc(MAX_LEN,sizeof(char));
    strncpy(struct_name,"Test",strlen("Test")); // default
    strncpy(output_filename,"test",strlen("test")); // default
    
    int32_t c,index;
    while ( ( c = getopt_long( argc, argv, "i:n:p:", long_options, &index ) ) != -1 )
    {   
        if(c=='i')
        {
            str_copy(input_filename,optarg);
        }
        else if(c=='n')
        {
            str_copy(struct_name,optarg);
        }
        else if(c=='p')
        {
            str_copy(output_filename,optarg);
        }
    }
    code_generate(input_filename,struct_name,output_filename);
    return 0;
}