#include <stdio.h> 
#include <stdint.h>

void Incorrect_print_binary(int32_t number)
{
    printf("\n=====Incorrect Example=====\n");
    int32_t bit = 1;
    bit = bit << 31;
    for( int i = 0 ; i < 32 ; i++ ) 
    {
        if( bit & number )
            printf( "1" ); 
        else
            printf( "0" ); 
        bit = bit >> 1;
    }
    printf("\n");
}

void correct_print_binary(int32_t number)
{
    printf("\n=====Correct Example=====\n");
    uint32_t bit = 1;
    bit = bit << 31;
    for( int i = 0 ; i < 32 ; i++ ) 
    {
        if( bit & number )
            printf( "1" ); 
        else
            printf( "0" ); 
        bit = bit >> 1;
    }
    printf("\n");
}


int main() 
{
    int32_t number = 0; 
    scanf( "%d", & number );
    Incorrect_print_binary(number);
    correct_print_binary(number);
    return 0;
}