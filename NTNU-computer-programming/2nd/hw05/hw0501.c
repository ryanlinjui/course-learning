#include "lib/cstd.h"
#include "lib/utils.h"
#include "hw0501.h"

struct option long_options[] = 
{  
    {"bytes", 0, NULL, 'b'},
    {"kilo", 0, NULL, 'k'},
    {"mega", 0, NULL, 'm'},
    {"seconds",1, NULL, 's'},
    {"count", 1, NULL, 'c'},
    {0, 0, 0, 0},  
};  

int main(int argc, char **argv)
{
    add_help_option(argc, argv);
    int32_t c=0,index=0;
    int32_t count=1,second=0,func_sec=0;
    double show_byte=1;
    while ( ( c = getopt_long( argc, argv, "bkms:c:", long_options, &index ) ) != -1 )
    {
        if(c=='b')
        {
            show_byte = 1024;
        }
        else if(c=='k')
        {
            show_byte = 1;
        }
        else if(c=='m')
        {
            show_byte = (double)1/1024;
        }
        else if(c=='s')
        {
            second = atoi(optarg);
            func_sec = 1;
        }
        else if(c=='c')
        {
            count = atoi(optarg);
        }
        else
        {
            return 0;
        }
    }
    if(func_sec) CHECK_VALID(second>0,"Option invalid!!");
    CHECK_VALID(count>0,"Option invalid!!");
    memory_monitor(show_byte,second,count);
    return 0;
}