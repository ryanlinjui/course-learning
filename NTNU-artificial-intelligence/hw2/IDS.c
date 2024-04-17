#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LEN 10000
#define LIMIT_DEPTH 50

int n = 0, top = 0;
int *sol_step = NULL;

int dfs(uint64_t board, int depth);
int ids(uint64_t board, int depth);
uint64_t update_board(uint64_t board, int n, int move);

// IDS alg
int ids(uint64_t board, int depth)
{
    for (int i = 1; i < depth; i++) // try every depth
    {
        sol_step = calloc(MAX_LEN,sizeof(int));
        if (dfs(board, i)) return 1;
        free(sol_step);
    }
    return 0;
}

// dfs alg
int dfs(uint64_t board, int depth)
{
    if (!board) return 1; // reach target
    if (!depth) return 0; // limit depth
    uint64_t next_board = 0;
    for (int i = 0; i < n; i++)
    {
        if(!(board & (1 << i))) continue; // is move valid
        next_board = update_board(board,n,i); // update board
        sol_step[top++] = n-i; // store move
        if (dfs(next_board, depth-1)) return 1;
        top--;
    }
    return 0;
}


// Bitboard mask processing
uint64_t update_board(uint64_t board, int n, int move)
{
    board ^= (1 << move);
    uint64_t next_board = 0, mask_board = 0;
    for(int i = 0; i < n; i++)
    {
        mask_board = board & (1 << i);
        if(!mask_board) continue;
        next_board |= ((mask_board << 1) | (mask_board >> 1));
    }
    return (next_board | (1 << n)) ^ (1 << n);
}

int main()
{
    uint64_t board=0;

    // input board
    int32_t input=0;
    while (scanf("%d",&input) != EOF)
    {
        board <<= 1;
        board += input;
        n++;
    }

    // solve
    clock_t start,end;  
    start = clock();
    if(ids(board,LIMIT_DEPTH) && top > 0)
    {
        end = clock();
        printf("Total run tume = %f seconds.\n",(double)(end-start)/CLOCKS_PER_SEC);
        printf("An optimal solution has %d moves:\n",top);
        for(int i = 0; i < top; i++)
        {
            printf("%d ",sol_step[i]);
        }
        printf("\n");
    }
    else
    {
        end = clock();
        printf("Total run tume = %f seconds.\n",(double)(end-start)/CLOCKS_PER_SEC);
        printf("There is no solution.\n");
    }
    return 0;
}
