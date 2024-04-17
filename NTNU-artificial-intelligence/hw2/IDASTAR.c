#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 100000

int n = 0, top = 0;
int *sol_step = NULL;

int dfs(uint64_t board, int depth, int max_depth);
void ida_star(uint64_t board);
uint64_t update_board(uint64_t board, int n, int move);
int h(uint64_t board);

int h(uint64_t board) // heuristic(n) caculate number of virus
{
    // board &= 0b01010101010101010101010101010101010101010101010101010101010; 
    board &= ~(1 | (1 << (n-1)));
    uint64_t uCount = board - ((board >> 1) & 0333333333333333333333) - ((board >> 2) & 0111111111111111111111);
    return (((uCount + (uCount >> 3)) & 0307070707070707070707) % 63) * 2 - !(board==0);
    // return (((uCount + (uCount >> 3)) & 0307070707070707070707) % 63);
}

// IDA* alg
void ida_star(uint64_t board)
{
    int threshold = h(board);
    while(1)
    {
        sol_step = calloc(MAX_LEN,sizeof(int));
        threshold = dfs(board,0,threshold);
        if (threshold < 0) break;
        free(sol_step);
    }
}

int dfs(uint64_t board, int value, int threshold)  
{  
    if (!h(board)) return -1; // reach target
    int f = value + h(board); // f(n) = g(n) + h(n)
    if (f > threshold) return f; // f(n) > threshold: pruning
    
    uint64_t next_board = 0;
    int min = 1e9;
    for (int i = 0, t = 0; i < n; i++)
    {
        if(!(board & (1 << i))) continue; // is move valid
        next_board = update_board(board,n,i); // update board
        sol_step[top++] = n - i; // store move
        t = dfs(next_board, value+1, threshold);
        if (t == -1) return -1;
        if (t < min) min = t;
        top--;
    }
    return min;
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
    ida_star(board);
    end = clock();
    if (top > 0)
    {
        printf("Total run tume = %f seconds.\n",(double)(end-start)/CLOCKS_PER_SEC);
        printf("An optimal solution has %d moves:\n",top);
        for(int i = 0; i < top; i++)
        {
            printf("%d ",sol_step[i]);
        }
    }
    else
    {
        printf("Total run tume = %f seconds.\n",(double)(end-start)/CLOCKS_PER_SEC);
        printf("There is no solution.");
    }
    printf("\n");
    return 0;
}
