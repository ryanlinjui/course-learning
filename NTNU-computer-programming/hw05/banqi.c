#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "bitboard.h"

char board[32];
char r_board[32]={'7','7','7','7','7','6','6','5','5','4','4','3','3','2','2','1',
                  'G','G','G','G','G','F','F','E','E','D','D','C','C','B','B','A'};
int char_to_int_board[23] = {6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,13,12,11,10,9,8,7};
int player=0;
int draw_step=0;
int color=0;
int turn=0;
int *available_step;
int init_color=1;
char player_identity[3];

void initial_game()
{   
    init_color=1;
    int random_degree=100;

    for (int i=0;i<32;i++)
    {
        board[i] = '*';
    }
    srand(time(NULL));
    for (int i=0;i<random_degree;i++)
    {   
        int r1=rand()%32,r2=rand()%32;
        int temp = r_board[r1];
        r_board[r1] = r_board[r2];
        r_board[r2] = temp;
    }
    draw_step=0;
    color=0;
    turn=1;   
}

int end_game()
{
    for(int i=0;i<32*32;i++)
    {    
        if(available_step[i])
        {
            break;
        }
        if(i==32*32-1)
        {
            // if(color==1)
            // {
            //     printf("RED WIN!!\n");
            // }
            // else
            // {
            //     printf("BLACK WIN!!\n");
            // }
            printf("Player %c win!!\n",player_identity[color+1]);
            return 1;
        }
    }
    if(draw_step>=50)
    {
        printf("DRAW!!\n");
        return 1;
    }
    return 0;
}

void set_color()
{
    for(int i=0; i<32&&init_color;i++)
    {
        if(board[i] != '*')
        {
            if(board[i] >= 49&&board[i]<=55)
            {
                color = 1;
                player_identity[0] = '1';
                player_identity[2] = '2';
            }
            else
            {
                color = -1;
                player_identity[0] = '2';
                player_identity[2] = '1';
            }
            init_color = 0;
        }
    }
    color *= -1;
}

void create_available()
{
    uint32_t element[16]={0};
    uint32_t black,red,chess;
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<4;j++)
        {
            if(board[j*8+i] == '*')
            {
                element[15] |= (1<<(i*4+j));
            }
            else if(board[j*8+i] == ' ')
            {
                element[14] |= (1<<(i*4+j));
            }
            else
            {
                element[char_to_int_board[board[j*8+i]-49]] |= (1<<(i*4+j));
            }
        }
    }
    available_step = available(element,color);
}

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

void board_update()
{
    int action[2]={0,0};
    while(1)
    {
        // if(color==1)
        // {
        //     printf("BLACK\n");
        // }
        // else if(color==-1)
        // {
        //     printf("RED\n");
        // }
        int invalid=0,x=0,y=0;
        if(turn==1)
        {
            printf("Player 1 (x,y):");
            scanf("%d,%d",&x,&y);
            action[0] = (x-1)+(y-1)*8;
            if(action[0]<0||action[0]>31)
            {
                invalid = 1;
            }
            else if(board[action[0]]=='*')
            {
                action[1] = action[0];
            }
            else
            {
                printf("To (x,y): ");
                scanf("%d,%d",&x,&y);
                action[1] = (x-1)+(y-1)*8;
            }
        }
        else if(turn==-1)
        {
            printf("Player 2 (x,y):");
            scanf("%d,%d",&x,&y);
            action[0] = (x-1)+(y-1)*8;
            if(action[0]<0||action[0]>31)
            {
                invalid = 1;
            }
            else if(board[action[0]]=='*')
            {
                action[1] = action[0];
            }
            else
            {
                printf("To (x,y): ");
                scanf("%d,%d",&x,&y);
                action[1] = (x-1)+(y-1)*8;
            }
        }
        if((action[0]<0&action[0]>31)||(action[1]<0&action[1]>31)||invalid)
        {
            printf("Invalid Action!!\n");
            continue;
        }
        if(available_step[action[0]*32+action[1]])
        {
            if(board[action[1]]==' ')
            {
                draw_step += 1;
            }
            else
            {
                draw_step = 0;
            }
            if(action[0]==action[1])
            {
                board[action[0]] = r_board[action[0]];
            }
            else
            {
                board[action[1]] = board[action[0]];
                board[action[0]] = ' ';
            }
            turn *= -1;
            break;
        }
        else
        {
            printf("Invalid Action!!\n");
            continue;
        }
    }
}

void loop_game()
{
    initial_game();
    show_board();
    while(1)
    {
        set_color();
        create_available();
        if(end_game())
        {
            break;
        }
        board_update();
        show_board();
    }
}