#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mylinkedlist.h"

typedef struct _sListParam
{
    int32_t     size;
    int32_t     ( *cmp )( const void *, const void * );
    void        ( *myfree )( void * );
    void        ( *myprint )( const void * );
} sListParam;

typedef struct _sListNode
{
    void                *pData;
    struct _sListNode   *pNext;
} sListNode;

sList * createList( void )
{
    sList   *pList = calloc( 1, sizeof( sList ) );    
    
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return NULL;
    }
    
    pList -> pParam = calloc( 1, sizeof( sListParam ) );
    pList -> pParam -> size = 0;
    pList -> pParam -> cmp = NULL;
    pList -> pParam -> myfree = free;
    pList -> pParam -> myprint = NULL;
    pList -> pHead = NULL; 
    pList -> pTail = NULL; 
    
    return pList;
}

int32_t freeList( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }

    sListNode *pNode = pList -> pHead, *pNodeTmp;
    
    while( pNode )
    {
        pNodeTmp = pNode;
        pNode = pNode -> pNext;
        pList -> pParam -> myfree( pNodeTmp );
    }
    free( pList -> pParam );
    free( pList );
    return 0;
}

void    regCmpCallback( sList *pList, int32_t ( *cmp )( const void *, const void * ) )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return;
    }
    
    pList -> pParam -> cmp = cmp;
    
    return;
}

void    regFreeCallback( sList *pList, void  ( *myfree )( void * ) )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return;
    }
    
    pList -> pParam -> myfree = myfree;
    
    return;
}

void    regPrintCallback( sList *pList, void  ( *myprint )( const void * ) )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return;
    }
    
    pList -> pParam -> myprint = myprint;
    
    return;
}

int32_t addNode( sList *pList, void *pData )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }    
    
    sListNode *pNewNode = calloc( 1, sizeof( sListNode ) );
    pNewNode -> pData = pData;
    pNewNode -> pNext = NULL;
    
    if( pList -> pParam -> size == 0 )
    {
        pList -> pHead = pNewNode;
        pList -> pTail = pNewNode;
    }
    else
    {
        pList -> pTail -> pNext = pNewNode;
        pList -> pTail = pNewNode;
    }
    
    pList -> pParam -> size += 1;
    
    return 0;    
}

int32_t delNode( sList *pList, void *pData )
{
    // Return 0 if successful removing the element.
    // Return -1 if NULL pointer or not found.
    
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    if( pList -> pParam -> cmp == NULL )
    {
        printf( "%s(%d) %s: Not registered cmp yet!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }
    
    if( pList -> pParam -> size == 0 )
    {
        return -1;
    }
    
    sListNode *pNode = pList -> pHead;
    sListNode *pPreNode = NULL;
    
    if( pList -> pParam -> cmp( pData, pNode -> pData )  == 0 )
    {
        if( pList -> pHead == pList -> pHead )
        {
            pList -> pParam -> myfree( pList -> pHead -> pData );
            free( pList -> pHead );
            pList -> pHead = NULL;
            pList -> pTail = NULL;
        }
        else
        {
            pList -> pHead = pNode -> pNext;
            pList -> pParam -> myfree( pNode -> pData );
            free( pNode );
        }
        pList -> pParam -> size -= 1;
        return 0;
    }
        
    while ( pNode != NULL && pList -> pParam -> cmp( pData, pNode -> pData )  != 0 ) 
    { 
        pPreNode = pNode; 
        pNode = pNode -> pNext; 
    } 
    
    if( pNode )
    {
        pPreNode -> pNext = pNode -> pNext;
        
        if( pList -> pTail == pNode )
        {
            pList -> pTail = pPreNode;
        }
        
        pList -> pParam -> myfree( pNode -> pData );
        free( pNode );
        pList -> pParam -> size -= 1;
        return 0;
    }
    
    return -1;
}

int32_t getListSize( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }
    
    return pList -> pParam -> size;
}

int32_t printList( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    if( pList -> pParam -> myprint == NULL )
    {
        printf( "%s(%d) %s: Not registered myprint yet!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }
    
    int32_t counter = 0;
    sListNode *pNode = pList -> pHead;
    
    while( pNode )
    {
        pList -> pParam -> myprint( pNode -> pData );
        printf( " --> \n" );
        pNode = pNode -> pNext;
    }
    
    printf( "NULL\n" );
    
    return 0;
}

