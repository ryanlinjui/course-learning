#include <stdio.h>
#include <stdint.h>

char board[32];
int player=0;

void show_board()
{
    printf("  1 2 3 4 5 6 7 8\n");
    printf(" +---------------+\n");
    for (int i=0;i<4;i++)
    {
        printf("%d|",i+1);
        for (int j=0;j<8;j++)
        {
            printf("%c|",board[i*8+j]);
        } 
        if(i<3)
        {
            printf("\n |---------------|\n");
        }
    }
    printf("\n +---------------+\n");
}

void init()
{   
    for (int i=0;i<32;i++)
    {
        board[i] = '*';
    }
    board[21] = 'A';
}

void loop_game()
{
    while(1)
    {
        init();
        show_board();
    }
}