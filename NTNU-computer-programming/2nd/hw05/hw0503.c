#include "lib/cstd.h"
#include "lib/utils.h"
#include "hw0503.h"

#define MAX_LEN 1000

struct option long_options[] = 
{  
    {"enc", 1, NULL, 'e'},
    {"dec", 1, NULL, 'd'},
    {"output", 1, NULL, 'o'},
    {0, 0, 0, 0},  
};

int main(int argc, char **argv)
{
    add_help_option(argc, argv);

    int32_t c=0,index=0,enc_func=0,dec_func=0;
    char *input_filename = calloc(MAX_LEN,sizeof(char));
    char *output_filename = calloc(MAX_LEN,sizeof(char));
    while ( ( c = getopt_long( argc, argv, "e:d:o:", long_options, &index ) ) != -1 )
    {
        if(c=='e')
        {
            enc_func = 1;
            str_copy_(input_filename,optarg);
        }
        else if(c=='d')
        {
            dec_func = 1;
            str_copy_(input_filename,optarg);
        }
        else if(c=='o')
        {
            str_copy_(output_filename,optarg);
        }
    }
    CHECK_VALID((enc_func==1&&dec_func==0)||(enc_func==0&&dec_func==1),"Option -d or -e error");
    if(enc_func)
    {
        encode_base64(input_filename,output_filename);
    }
    else if(dec_func)
    {
        decode_base64(input_filename,output_filename);
    }
    return 0;
}