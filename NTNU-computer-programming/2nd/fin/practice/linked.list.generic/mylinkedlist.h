#pragma once

#include <stdint.h>

struct _sListNode;
struct _sListParam;

typedef struct _sList
{
    struct _sListParam  *pParam;
    struct _sListNode   *pHead;
    struct _sListNode   *pTail;
} sList;

sList * createList();
int32_t freeList( sList * );

void    regCmpCallback( sList *, int32_t (*)( const void *, const void * ) );
void    regFreeCallback( sList *, void  (*)( void * ) );
void    regPrintCallback( sList *, void  (*)( const void * ) );

int32_t addNode( sList *, void * );
int32_t delNode( sList *, void * );
int32_t getListSize( sList * ); 
int32_t printList( sList * );