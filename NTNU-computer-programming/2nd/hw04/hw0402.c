#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/bmp.h"


struct option long_options[] = 
{  
     {"help", 0, NULL, 'h'}, 
     {0, 0, 0, 0},  
};  

int main(int argc, char **argv)
{
    int32_t c,index;
    while ( ( c = getopt_long( argc, argv, "i:n:p:", long_options, &index ) ) != -1 )
    {
        printf( "index: %d\n", index );
        if(c=='h')
        {

        }
        else if(c=='i')
        {

        }
        else if(c=='n')
        {
            
        }
        else if(c=='p')
        {

        }
    }
    return 0;
}