#include <stdint.h>
#include <stdio.h>

int32_t max_black_chain( int32_t board[][19])
{
    int32_t b_black[19][19];
    int32_t num=0;
    for (int i = 0; i <19;i++)
    {
        for (int j = 0; j <19;j++)
        {
            b_black[i][j] = 0;
        }
    }
    
    for (int i = 0; i <19;i++)
    {
        for (int j = 0; j <19;j++)
        {
            if(board[i][j]==1)
            {
                if(i+1!=19)
                {
                    if(board[i+1][j]==0)
                    {
                        b_black[i+1][j] = 1;
                    }
                }
                if(i-1!=-1)
                {
                    if(board[i-1][j]==0)
                    {
                        b_black[i-1][j] = 1;
                    }
                }
                if(j+1!=19)
                {
                    if(board[i][j+1]==0)
                    {
                        b_black[i][j+1] = 1;
                    }
                }
                if(j-1!=-1)
                {
                    if(board[i][j-1]==0)
                    {
                        b_black[i][j-1] = 1;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i <19;i++)
    {
        for (int j = 0; j <19;j++)
        {
            num += b_black[i][j];
        }
    }

    return num;
}