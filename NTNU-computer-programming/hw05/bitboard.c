#include <stdint.h>
#include <stdio.h>

//array order:7,6,5,4,3,2,1,
//            G,F,E,D,C,B,A,
//            ' ',*
uint32_t elememt[16] = {0x10020000,0x00000000,0x00080000,0x00000000,0x00000000,0x02000000,0x40000000
                       ,0x80200000,0x00040000,0x00000000,0x00400000,0x00000000,0x00000000,0x20000000
                       ,0x0C902000,0x0101Dfff};
// *,*,*,*
// *,*,*,*
// *,*,*,*
// *,*, ,*
// 5,F,7,*
//  ,D,G,
//  , ,2,*
// G,1,A,7


uint32_t black = 0x005c7040
        ,red = 0x06030e20
        ,chess = 0xffdfffff;

uint32_t board_y[4] = {0x11111111,0x22222222,0x44444444,0x88888888};
uint32_t board_x[8] = {0x0000000F,0x000000F0,0x00000F00,0x0000F000,0x000F0000,0x00F00000,0x0F000000,0xF0000000};
int _index[32] = {31,0,1,5,2,16,27,6,3,14,17,19,28,11,7,21,30,4,15,26,13,18,10,20,29,25,12,9,24,8,23,22};
uint32_t chess_move[32] = {0x00000012,0x00000025,0x0000004A,0x00000084,0x00000121,0x00000252,0x000004A4,0x00000848,
                        0x00001210,0x00002520,0x00004A40,0x00008480,0x00012100,0x00025200,0x0004A400,0x00084800,
                        0x00121000,0x00252000,0x004A4000,0x00848000,0x01210000,0x02520000,0x04A40000,0x08480000,
                        0x12100000,0x25200000,0x4A400000,0x84800000,0x21000000,0x52000000,0xA4000000,0x48000000};
int color=0;

uint32_t get_least_bit(uint32_t x)
{
    return x & (-x);
}

uint32_t get_first_bit(uint32_t x)
{
    x |= (x>>31);
    x |= (x>>16);
    x |= (x>>8);
    x |= (x>>4);
    x |= (x>>2);
    x |= (x>>1);
    return (x>>1)+1;
}

int get_board_index(uint32_t mask)
{
    return _index[(mask*0x08ED2BE6)>>27];
}

uint32_t c_method_CL(uint32_t x)
{
    if(x)
    {
        uint32_t mask = get_least_bit(x);
        return x^= mask ? get_least_bit(x) : 0;
    }
    else
    {
        return 0;
    }    
}

uint32_t c_method_CR(uint32_t x)
{
    if(x)
    {
        uint32_t mask = get_first_bit(x);
        return x^= mask ? get_first_bit(x) : 0;
    }
    else
    {
        return 0;
    }    
}

uint32_t c_method(int x)
{
    uint32_t co,ro;
    int co_n = x / 4;
    int ro_n = x % 4;
    x = ((board_x[co_n] & chess) ^ (1<<x)) >> (4*co_n);
    if(co_n==0)
    {
        co = c_method_CL(x);
    }
    else if(co_n==1)
    {
        co = c_method_CL(x & 0x11111100);
    }
    else if(co_n==2)
    {
        uint32_t part = 0;
        if((x & 0x00000011) == 0x00000011)
        {
            part |= 1;
        }
        co = part|c_method_CL(x&0x11111000);
    }
    else if(co_n==3)
    {
        uint32_t part = 0;
        part = c_method_CR(x&0x00000111);
        co = part|c_method_CL(x&0x11110000);
    }
    else if(co_n==4)
    {
        uint32_t part = 0;
        part = c_method_CR(x&0x00001111);
        co = part|c_method_CL(x&0x11100000);
    }
    else if(co_n==5)
    {
        uint32_t part = 0;
        part = c_method_CR(x&0x00011111);
        co = part|c_method_CL(x&0x11000000);
    }
    else if(co_n==6)
    {
        co = c_method_CR(x&0x00111111);
    }
    else if(co_n==7)
    {
        co = c_method_CR(x);
    }
    x = ((board_y[ro_n] & chess) ^ (1<<x)) >> (4*ro_n);
    if(ro_n==0)
    {
        ro = c_method_CL(x);
    }
    else if(ro_n==1)
    {
        ro = (((x&12)==12)) ? 8 : 0;
    }
    else if(ro_n==2)
    {
        ro = (((x&3)==3)) ? 1 : 0;
    }
    else if(ro_n==3)
    {
        ro = c_method_CR(x);
    }
    return ro | co;
}

void available()
{
    for(int i=0;i<14;i++)
    {
        uint32_t p = elememt[i];
        while (p)
        {
            uint32_t mask = get_least_bit(p);
            p ^= mask;
            int src = get_board_index(mask);
            uint32_t dest;
            if(i==0 & color==1)
            {
                dest = chess_move[src] & (elememt[7]|elememt[13]|elememt[14]);
            }
            else if(i==1 & color==1)
            {
                dest = c_method(src) & (red|elememt[14]);
            }
            else if(i==2 & color==1)
            {
                dest = chess_move[src] & (elememt[7]|elememt[8]|elememt[9]|elememt[14]);
            }
            else if(i==3 & color==1)
            {
                dest = chess_move[src] & (elememt[7]|elememt[8]|elememt[9]|elememt[10]|elememt[14]);
            }
            else if(i==4 & color==1)
            {
                dest = chess_move[src] & (red^elememt[12]^elememt[13]|elememt[14]);
            }
            else if(i==5 & color==1)
            {
                dest = chess_move[src] & (red^elememt[13]|elememt[14]);
            }
            else if(i==6 & color==1)
            {
                dest = chess_move[src] & (red^elememt[7]|elememt[14]);
            }
            else if(i==7 & color==-1)
            {
                dest = chess_move[src] & (elememt[0]|elememt[6]|elememt[14]);
            }
            else if(i==8 & color==-1)
            {
                dest = c_method(src) & (black|elememt[14]);
            }
            else if(i==9 & color==-1)
            {
                dest = chess_move[src] & (elememt[0]|elememt[1]|elememt[2]|elememt[14]);
            }
            else if(i==10 & color==-1)
            {
                dest = chess_move[src] & (elememt[0]|elememt[1]|elememt[2]|elememt[3]|elememt[14]);
            }
            else if(i==11 & color==-1)
            {
                dest = chess_move[src] & (black^elememt[5]^elememt[6]|elememt[14]);
            }
            else if(i==12 & color==-1)
            {
                dest = chess_move[src] & (black^elememt[6]|elememt[14]);
            }
            else if(i==13 & color==-1)
            {
                dest = chess_move[src] & (black^elememt[0]|elememt[14]);
            }
            else
            {
                dest = 0;
            }
            while (dest)
            {
                uint32_t mask2 = get_least_bit(dest);
                dest ^= mask2;
                int result  = get_board_index(mask2);
                printf("%u,%u\n",src,result);
            }
        }
    }
}

int main()
{
    scanf("%d",&color);
    available();
    return 0;
}
