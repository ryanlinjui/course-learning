#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _sList
{
    int32_t             size;
    struct _sListNode   *pHead;
    struct _sListNode   *pTail;
} sList;

typedef struct _sListNode
{
    int32_t             data;
    struct _sListNode   *pNext;
} sListNode;

int32_t initList( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }
    
    pList -> size = 0;
    pList -> pHead = NULL; 
    pList -> pTail = NULL; 
    
    return 0;
}

int32_t addNode( sList *pList, int32_t val )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }    
    
    sListNode *pNewNode = calloc( 1, sizeof( sListNode ) );
    pNewNode -> data = val;
    pNewNode -> pNext = NULL;
    
    if( pList -> size == 0 )
    {
        pList -> pHead = pNewNode;
        pList -> pTail = pNewNode;
    }
    else
    {
        pList -> pTail -> pNext = pNewNode;
        pList -> pTail = pNewNode;
    }
    
    pList -> size += 1;
    
    return 0;    
}

int32_t delNode( sList *pList, int32_t val )
{
    // Return 0 if successful removing the element.
    // Return -1 if NULL pointer or not found.
    
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    if( pList -> size == 0 )
    {
        return -1;
    }
    
    sListNode *pNode = pList -> pHead;
    sListNode *pPreNode = NULL;
    
    if( pNode -> data == val )
    {
        if( pList -> pHead == pList -> pHead )
        {
            free( pList -> pHead );
            pList -> pHead = NULL;
            pList -> pTail = NULL;
        }
        else
        {
            pList -> pHead = pNode -> pNext;
            free( pNode );
        }
        pList -> size -= 1;
        return 0;
    }
        
    while ( pNode != NULL && pNode -> data != val ) 
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
        
        free( pNode );
        pList -> size -= 1;
        return 0;
    }
    
    return -1;
}

int32_t getListSize( sList *pList )
{
    return pList -> size;
}

int32_t printList( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    int32_t counter = 0;
    sListNode *pNode = pList -> pHead;
    
    while( pNode )
    {
        printf( "%d -> ", pNode -> data );
        
        counter++;
        if( counter % 8 == 0 )
        {
            printf( "\n" );
        }
        
        pNode = pNode -> pNext;
    }
    
    printf( "NULL\n" );
    
    return 0;
}

int main()
{
    sList list; 
    
    initList( &list );
    
    addNode( &list, 10 );
    addNode( &list, 37 );
    addNode( &list, 6 );
    addNode( &list, 49 );
    addNode( &list, 87 );
    addNode( &list, 13 );
    addNode( &list, 92 );
    addNode( &list, 76 );
    addNode( &list, 52 );
    addNode( &list, 97 );
    addNode( NULL, -100 );
    
    printf( "List size = %d\n", getListSize( &list ) );
    printList( &list );
    
    delNode( &list, 92 );
    
    printf( "List size = %d\n", getListSize( &list ) );
    printList( &list );
    
    delNode( &list, 97 );
    
    printf( "List size = %d\n", getListSize( &list ) );
    printList( &list );
    
    delNode( &list, 90 );
    
    printf( "List size = %d\n", getListSize( &list ) );
    printList( &list );

    return 0;
}
