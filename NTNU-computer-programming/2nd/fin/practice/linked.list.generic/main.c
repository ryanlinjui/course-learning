#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "mylinkedlist.h"

typedef enum
{
    BOOK_LITERATURE, 
    BOOK_MATH,
    BOOK_SCIENCE,
    BOOK_PHILOSOPHY,
    BOOK_ART,
    BOOK_MAX
} eBookClass; 

typedef struct _sBook
{
    int32_t     id;
    char        title[64];
    char        author[64];
    eBookClass  class;
} sBook;

int32_t cmp( const void *ptr1, const void *ptr2 )
{
    sBook *pBook1 = ( sBook * )ptr1;
    sBook *pBook2 = ( sBook * )ptr2;
    
    if( pBook1 -> id == pBook2 -> id )
    {
        return 0;
    }
    else if ( pBook1 -> id > pBook2 -> id )
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void myfree( void *ptr )
{
    sBook *pBook = ( sBook * )ptr;
    if( pBook )
    {
        free( pBook );
    }
    return ;
}

void myprint( const void *ptr )
{
    sBook *pBook = ( sBook * )ptr;
    puts( "-----" );
    printf( "ID: %d; ", pBook -> id );
    printf( "TITLE: %s; ", pBook -> title );
    printf( "AUTHOR: %s; ", pBook -> author );
    printf( "CLASS: %d\n", pBook -> class );
    puts( "-----" );
}

int main()
{
    sList *pBookList = createList();
    
    regCmpCallback( pBookList, cmp );
    regFreeCallback( pBookList, myfree );
    regPrintCallback( pBookList, myprint );
    
    srand( time( 0 ) );
    
    for( int32_t i = 0 ; i < 10 ; i++ )
    {
        sBook   *pBook = calloc( 1, sizeof( sBook ) );
        pBook -> id = i;
        pBook -> title[0] = rand() % 26 + 'A';
        pBook -> title[1] = '\0';
        pBook -> author[0] = rand() % 26 + 'a';
        pBook -> author[1] = '\0';
        pBook -> class = rand() % BOOK_MAX; 
        
        addNode( pBookList, pBook );
    }
    
    printf( "size: %d\n", getListSize( pBookList ) );
    printList( pBookList );
    
    sBook book;
    book.id = 5;
    delNode( pBookList, &book );
    
    printf( "size: %d\n", getListSize( pBookList ) );
    printList( pBookList );
    
    freeList( pBookList );
    
    return 0;
    
}