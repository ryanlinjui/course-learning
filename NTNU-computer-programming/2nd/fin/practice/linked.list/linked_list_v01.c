#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _sListNode
{
    int32_t             data;
    struct _sListNode   *pNext;
} ListNode;

int32_t addNode( ListNode *pHead, int32_t val )
{
    if( pHead == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }    
    
    ListNode *pNewNode = calloc( 1, sizeof( ListNode ) );
    pNewNode -> data = val;
    pNewNode -> pNext = NULL;
    
    // Why Do This?
    ListNode *pNode = pHead;
    
    while( pNode -> pNext )
    {
        pNode = pNode -> pNext;
    }
    pNode -> pNext = pNewNode;
    
    return 0;    
}

int32_t delNode( ListNode *pHead, int32_t val )
{
    // Return 0 if successful removing the element.
    // Return -1 if NULL pointer or not found.
    return 0;
}

int32_t getListSize( ListNode *pHead )
{
    int32_t size = 0;
    return size;
}

int32_t printList( ListNode *pHead )
{
    if( pHead == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    int32_t counter = 0;
    ListNode *pNode = pHead -> pNext;
    
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
    ListNode head = { 0, NULL }; 
    
    addNode( &head, 10 );
    addNode( &head, 37 );
    addNode( &head, 6 );
    addNode( &head, 49 );
    addNode( &head, 87 );
    addNode( &head, 13 );
    addNode( &head, 92 );
    addNode( &head, 76 );
    addNode( &head, 52 );
    addNode( &head, 97 );
    addNode( NULL, -100 );
    
    printList( &head );
    
    delNode( &head, 92 );
    
    printf( "List size = %d\n", getListSize( &head ) );
    printList( &head );
    
    delNode( &head, 90 );
    
    printf( "List size = %d\n", getListSize( &head ) );
    printList( &head );

    return 0;
}
