#include "lib/cstd.h"
#include "lib/utils.h"
#include "fin02.h"

#define MAX_LEN 1000

struct option long_options[] = 
{  
    {"country",0, NULL, 'c'},
    {"start",0, NULL, 's'},
    {"end",0, NULL, 'e'},
    {"output",0, NULL, 'o'},
    {0, 0, 0, 0},  
}; 

int main(int argc, char **argv)
{
    add_help_option(argc, argv);
    int32_t c=0,index=0;
    int32_t width=1024,height=768;
    char *country = calloc(MAX_LEN,sizeof(char));
    char *start = calloc(MAX_LEN,sizeof(char));
    char *end = calloc(MAX_LEN,sizeof(char));
    char *output = calloc(MAX_LEN,sizeof(char));
    strncpy(country,"Taiwan",strlen("Taiwan"));
    strncpy(start,"01-23-2020",strlen("01-23-2020"));
    strncpy(end,"12-31-2021",strlen("12-31-2021"));
    strncpy(output,"output.csv",strlen("output.csv"));

    while ( ( c = getopt_long( argc, argv, "c:s:e:o:", long_options, &index ) ) != -1 )
    {
        if(c=='c')
        {
            strncpy(country,optarg,strlen(optarg));
            country[strlen(optarg)] = '\0';
            CHECK_VALID(strlen(country) > 0, "Invalid country name!!");
        }
        else if(c=='s')
        {
            strncpy(start,optarg,strlen(optarg));
            CHECK_VALID(strlen(start) == 10, "Invalid start date value!!");
        }
        else if(c=='e')
        {
            strncpy(end,optarg,strlen(optarg));
            CHECK_VALID(strlen(end) == 10, "Invalid end date name!!");
        }
        else if(c=='o')
        {
            strncpy(output,optarg,strlen(optarg));
            output[strlen(optarg)] = '\0';
            CHECK_VALID(strlen(output) > 0, "Invalid output name!!");
        }
        else
        {
            puts("Command Error!!");
            return 0;
        }
    }
    create_plot(country,start,end,output);
    free(country);
    free(start);
    free(end);
    free(output);
    return 0;

}