#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/bmp.h"

#define MAX_LEN 1000

struct option long_options[] = 
{  
    {0, 0, 0, 0},  
}; 

int main(int argc, char **argv)
{
    add_help_option(argc, argv);
    int32_t c=0,index=0;
    int32_t width=1024,height=768;
    
    return 0;
}