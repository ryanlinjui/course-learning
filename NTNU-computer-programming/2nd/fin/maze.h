#pragma once

#include <stdint.h>
#include "linuxlist.h"

typedef struct _sNode
{
	int32_t id;
	int32_t flag;	   // 0: entrance; 1: exit; 2: otherwise
	char    name[32]; // Location name.
	
	struct list_head next_node_list; // sNodeAddress List
} sNode;

typedef struct _sNodeAddress
{
	sNode *pNode;
	
	struct list_head list;
} sNodeAddress;

sNode *maze_gen( void );