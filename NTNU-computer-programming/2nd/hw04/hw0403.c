#include "lib/cstd.h"
#include "lib/utils.h"
#include "hw0403.h"

#define HELP_FILE_PATH "help/hw0403.help"
#define MAX_LEN 100

struct option long_options[] = 
{  
    {"linenum", 0, NULL, 'n'},
    {"color", 0, NULL, 'c'},
    {"language", 1, NULL, 'l'},
    {0, 0, 0, 0},  
};  

int main(int argc, char **argv)
{ 
    add_help_option(argc, argv);
    int32_t c,index; // getopt needded variable
    bool show_linenum = 0,show_color=0;
    char *language = calloc(MAX_LEN,sizeof(char));
    language[0] = 'C'; // default language "C"
    char *filename = calloc(MAX_LEN,sizeof(char));
    strncpy(filename,argv[argc-1],strlen(argv[argc-1]));
    while ( ( c = getopt_long( argc, argv, "hncl:", long_options, &index ) ) != -1 )
    {
        if(c=='n')
        {
            show_linenum = 1;
        }
        else if(c=='c')
        {
            show_color = 1;
        }
        else if(c=='l')
        {
            strncpy(language,optarg,strlen(optarg));   
        }
    }
    print_code_highlighter(filename,show_linenum,show_color,language);
    return 0;
}