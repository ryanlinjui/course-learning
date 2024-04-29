#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "linuxlist.h"

typedef struct _sCharacter
{
    int32_t id;
    char    name[32];
    int32_t hp;
    int32_t mp;
    int32_t exp;
    int32_t atk;
    int32_t def;
    int32_t ats;
    int32_t adf;
    int32_t spd;
    
    struct list_head list;
} sCharacter;

sCharacter *allocCharacter( int32_t id )
{
    sCharacter *newComer = calloc( 1, sizeof( sCharacter ) );
        
    newComer -> id = id;
        
    newComer -> name[0] = rand()%26 + 'A';
    for( int32_t j = 1 ; j < 6 ; j++ )
    {
        newComer -> name[j] = rand()%26 + 'a';
    }
        
    newComer ->  hp = rand()%100 + 1;
    newComer ->  mp = rand()%100 + 1;
    newComer ->  exp = rand()%100 + 1;
    newComer ->  atk = rand()%100 + 1;
    newComer ->  def = rand()%100 + 1;
    newComer ->  ats = rand()%100 + 1;
    newComer ->  adf = rand()%100 + 1;
    newComer ->  spd = rand()%100 + 1;
        
    return newComer;
}

void printCharacter( sCharacter *one )
{
    printf( "%04d) ", one -> id );
    printf( "%8s ", one -> name );
    
    for( int32_t *ptr = &( one -> hp ); ptr <= &( one -> spd ); ptr++ )
    {
        printf( "%3d ", *ptr );
    }
    
    printf( "\n" );
    return;
}

int main()
{
    LIST_HEAD( char_list_head );    
    
    srand( time( 0 ) );
    
    for( int32_t i = 0 ; i < 1000 ; i++ )
    {
        sCharacter *newComer = allocCharacter( i + 1 );
        
        list_add( &( newComer -> list ), &char_list_head );
    }
    
    struct list_head *listptr = NULL;
    list_for_each( listptr, &char_list_head )
    {
        sCharacter *cptr = list_entry( listptr, sCharacter, list );
        printCharacter( cptr );
    } 
    
    /*
    list_for_each_prev( listptr, &char_list_head )
    {
        sCharacter *cptr = list_entry( listptr, sCharacter, list );
        printCharacter( cptr );
    } 
    */

    return 0;
}
