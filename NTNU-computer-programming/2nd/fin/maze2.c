#include <stdlib.h>
#include <string.h>
#include "maze.h"

sNode *init_node(int32_t id, int32_t flag, char *name)
{
    sNode *pNode = malloc(sizeof(sNode));

    pNode->id = id;
    pNode->flag = flag;
    strncpy(pNode->name, name, 32);
    pNode->next_node_list.prev = &(pNode->next_node_list);
    pNode->next_node_list.next = &(pNode->next_node_list);

    return pNode;
}

void add_edge(sNode *from, sNode *to)
{
    sNodeAddress *pEdge = malloc(sizeof(sNodeAddress));
    pEdge->pNode = to;
    list_add_tail(&(pEdge->list), &(from->next_node_list));
}

// Node1 (start) --> Node2 (Exit)
sNode *maze_gen(void)
{
    // Node Generation
    sNode *pNode1 = init_node(1, 0, "Welcome");
    sNode *pNode2 = init_node(2, 2, "A");
    sNode *pNode3 = init_node(3, 2, "B");
    sNode *pNode4 = init_node(4, 2, "C");
    sNode *pNode5 = init_node(5, 2, "D");
    sNode *pNode6 = init_node(6, 1, "End");
    sNode *pNode7 = init_node(7, 2, "E");
    sNode *pNode8 = init_node(8, 2, "F");

    // Unidirectional Edge Generation
    // Node1 -> Node2
    add_edge(pNode1, pNode2);
    add_edge(pNode2, pNode3);
    add_edge(pNode2, pNode5);
    add_edge(pNode3, pNode4);
    add_edge(pNode4, pNode8);
    add_edge(pNode5, pNode7);
    add_edge(pNode5, pNode8);
    add_edge(pNode8, pNode6);


    // 迷宮：
    //         7
    //         ↑
    // 1 → 2 → 5 → 8 → 6
    //     ↓       ↑
    //     3   →   4
    //  
    // 答案：1 -> 2 -> 5 -> 8 -> 6
    
    // Return
    return pNode1;
}