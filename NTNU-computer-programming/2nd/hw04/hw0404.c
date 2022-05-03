#include "lib/cstd.h"
#include "lib/utils.h"
#include "hw0404.h"

#define MAX_LEN 100

int main(int argc, char **argv)
{   
    add_help_option(argc, argv);
    puts(Welcome_MSG);
    int32_t choice = -1;
    uint8_t func_num = 0;
    char *filename = calloc(MAX_LEN,sizeof(char)); // ../../../../Desktop/pm2/F101.GNX
    CHECK_VALID(scanf("%[^\n]%*c",filename) == 1 , "Invalid input filename!!");
    set_modifier(filename);
    while(1)
    {   
        func_arr[func_num](choice, &func_num);
    }
    return 0;
}