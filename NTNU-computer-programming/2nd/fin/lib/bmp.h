#pragma once
#include "utils.h"
#include "cstd.h"

#define HEADER_SIZE 14
#define RGB_STANDARD_DEPTH 8

typedef struct COLOR
{
    /* BMP's RGB Formate
        bbbbbbbb (0~255)
        gggggggg (0~255)
        rrrrrrrr (0~255) */
    uint8_t blue;
    uint8_t green;
    uint8_t red;
}COLOR;

// typedef struct COLOR16
// {
//     /* BMP's RGB(565) Formate
//         bbbbb (0~31)
//         gggggg (0~63)
//         rrrrr (0~31) */
//     uint8_t blue : 5;
//     uint8_t green : 6;
//     uint8_t red : 5;
// }__attribute__((__packed__))COLOR16;

typedef struct _BITMAP //TODO: Complete bmp system
{
    COLOR **pixel;
    struct 
    {
        char     magic[2];
        uint32_t size;
        uint16_t reserve1;
        uint16_t reserve2;
        uint32_t offset;
    }__attribute__((__packed__))HEADER;
    union 
    {
        struct
        {
            uint32_t header_size;
            uint32_t width;
            uint32_t height;
            uint16_t planes;
            uint16_t depth;
            uint32_t compression;
            uint32_t bitmap_size;
            uint32_t horizontal;
            uint32_t vertical;
            uint32_t palette;
            uint32_t important;
        }__attribute__((__packed__))BITMAPINFOHEADER;
        struct
        {
            uint32_t header_size;
            uint32_t width;
            uint32_t height; 
            uint16_t planes;
            uint16_t depth;
            uint32_t compression;
            uint32_t bitmap_size;
            uint32_t horizontal;
            uint32_t vertical;
            uint32_t palette;
            uint32_t important;
            uint32_t red_mask;
            uint32_t green_mask;
            uint32_t blue_mask;
            uint32_t alpha_mask;
            uint64_t cs_type : 52;
            uint32_t end_point;
            uint32_t gamma_red;
            uint32_t gamma_green;
            uint32_t gamma_blue;
        }__attribute__((__packed__))BITMAPV5HEADER;
    }DIBHEADER;
}__attribute__((__packed__)) BITMAP;

void read_img(BITMAP *img,char *img_name)
{
    FILE *file = fopen(img_name,"rb");
    CHECK_VALID(file!=NULL,"File doesn't exist!!");
    fread(&(img->HEADER),HEADER_SIZE,1,file);
    CHECK_VALID(img->HEADER.magic[0]=='B' && img->HEADER.magic[1] == 'M',"It's not a bmp formate image!!");
    fread(&(img->DIBHEADER),img->HEADER.offset-HEADER_SIZE,1,file);
    img->pixel = (COLOR**)calloc(img->DIBHEADER.BITMAPINFOHEADER.height, sizeof(COLOR**));
    for(int i=img->DIBHEADER.BITMAPINFOHEADER.height-1;i>=0;i--)
    {
        img->pixel[i] = (COLOR*)calloc(img->DIBHEADER.BITMAPINFOHEADER.width, sizeof(COLOR*));
        fread(img->pixel[i],img->DIBHEADER.BITMAPINFOHEADER.width*sizeof(COLOR),1,file);
    }
    fclose(file);
}
void write_img(BITMAP *img,char *img_name) //TODO:can change any depth change
{
    FILE *file = fopen(img_name,"wb");
    CHECK_VALID(file!=NULL,"File doesn't exist!!");
    fwrite(&(img->HEADER),HEADER_SIZE,1,file);
    fwrite(&(img->DIBHEADER),img->HEADER.offset-HEADER_SIZE,1,file);
    
    for(int i=img->DIBHEADER.BITMAPINFOHEADER.height-1;i>=0;i--)
    {
        fwrite(img->pixel[i],img->DIBHEADER.BITMAPINFOHEADER.width*sizeof(COLOR),1,file);
    }
    // row_size = (depth * width + 31) / 32 * 4
    // padding = row_size - depth * width
    fclose(file);
}

void copy_img(BITMAP *src,BITMAP *dest)
{
    memcpy(&(dest->HEADER),&(src->HEADER),sizeof(src->HEADER));
    memcpy(&(dest->DIBHEADER),&(src->DIBHEADER),src->HEADER.offset-HEADER_SIZE);
    dest->pixel = (COLOR**)calloc(dest->DIBHEADER.BITMAPINFOHEADER.height, sizeof(COLOR**));
    for(int i=src->DIBHEADER.BITMAPINFOHEADER.height-1;i>=0;i--)
    {
        dest->pixel[i] = (COLOR*)calloc(dest->DIBHEADER.BITMAPINFOHEADER.width, sizeof(COLOR*));
        memcpy(dest->pixel[i],src->pixel[i],src->DIBHEADER.BITMAPINFOHEADER.width*sizeof(COLOR));
    }
}

void circular_focus(BITMAP *img,int32_t center[],int32_t radius,uint8_t color)
{
    for(int x=0;x<(img->DIBHEADER.BITMAPINFOHEADER.width);x++)
    {
        for(int y=0;y<img->DIBHEADER.BITMAPINFOHEADER.height;y++)
        {
            if(sqrt(pow(x-center[0],2)+pow(y-center[1],2))>=(double)radius)
            {
                img->pixel[y][x] = (COLOR){color,color,color};
            }
        }
    }
}

// void change_depth(BITMAP *img,uint8_t red,uint8_t green,uint8_t blue) //consider to remove
// {
//     // img->DIBHEADER.BITMAPINFOHEADER.depth = red + green + blue;
//     for(int x=0;x<(img->DIBHEADER.BITMAPINFOHEADER.width);x++)
//     {
//         for(int y=0;y<img->DIBHEADER.BITMAPINFOHEADER.height;y++)
//         {
//             img->pixel[y][x].red = (img->pixel[y][x].red >> (RGB_STANDARD_DEPTH - red)) & 0xF800;
//             img->pixel[y][x].green = (img->pixel[y][x].green >> (RGB_STANDARD_DEPTH - green)) & 0x07E0;
//             img->pixel[y][x].blue = (img->pixel[y][x].blue >> (RGB_STANDARD_DEPTH - blue)) & 0x001F;
//         }
//     }
// }

void to_grayscale(BITMAP *img)
{
    for(int x=0;x<(img->DIBHEADER.BITMAPINFOHEADER.width);x++)
    {
        for(int y=0;y<(img->DIBHEADER.BITMAPINFOHEADER.height);y++)
        { 
            uint8_t gray = img->pixel[y][x].red*0.299+img->pixel[y][x].green*0.587+img->pixel[y][x].blue*0.114;
            img->pixel[y][x] = (COLOR){gray,gray,gray};
        }
    }
}

void resize(BITMAP *img,uint32_t new_width,uint32_t new_height) //TODO: Complete resize func, only twice func currently
{
    // BITMAP old_img;
    // copy_img(img,&old_img);
    // img->pixel = (COLOR**)realloc(img->pixel,new_height*sizeof(COLOR**));
    // for(int i=img->DIBHEADER.BITMAPINFOHEADER.height-1;i>=0;i--)
    // {
    //     img->pixel[i] = (COLOR*)realloc(img->pixel[i],new_width*sizeof(COLOR*));
    // }
    // img->HEADER.size = new_height*new_width*sizeof(COLOR) + img->HEADER.offset;
    // img->DIBHEADER.BITMAPINFOHEADER.width = new_width;
    // img->DIBHEADER.BITMAPINFOHEADER.height = new_height;
    // double width_mag = new_width/old_img.DIBHEADER.BITMAPINFOHEADER.width;
    // double height_mag = new_height/old_img.DIBHEADER.BITMAPINFOHEADER.height;

    // unsigned long dwsrcX,dwsrcY;
    // unsigned char *pucDest;
    // unsigned char *pucSrc;
    // unsigned char *dest_data=malloc(new_width*new_height*sizeof(COLOR));
    // for(int i=0;i<new_height;i++)
    // {
    //     dwsrcY=i*old_height/new_height;
    //     pucDest=dest_data+i*new_width*sizeof(COLOR);
    //     pucSrc=src_data+dwsrcY*old_width*sizeof(COLOR);
    //     for(int j=0;j<new_width;j++)
    //     {
    //         dwsrcX=j*old_width/new_width;
    //         memcpy(pucDest+j*sizeof(COLOR),pucSrc+dwsrcX*sizeof(COLOR),sizeof(COLOR));
    //     }
    // }
    // for(int i=0;i<new_height;)
    // {
    //     for(int c=i;c<(int)(height_mag+;c++,i++)
    //     {
    //         memcpy(img->pixel[c],old_img.pixel[i],old_img.DIBHEADER.BITMAPINFOHEADER.height*sizeof(COLOR));
    //     }
    //     for(int j=0;j<new_width;j++)
    //     {
    //         for(int c=j;c<(int)(j*height_mag);c++)
    //         {
    //             img->pixel[i][c] = old_img.pixel[i][j];
    //         }
    //     }
    // }
    BITMAP old_img;
    copy_img(img,&old_img);
    img->pixel = (COLOR**)realloc(img->pixel,new_height*sizeof(COLOR**));
    for(int i=0;i<new_height;i++)
    {
        img->pixel[i] = (COLOR*)realloc(img->pixel[i],new_width*sizeof(COLOR*));
    }
    img->HEADER.size = new_height*new_width*sizeof(COLOR) + img->HEADER.offset;
    img->DIBHEADER.BITMAPINFOHEADER.width = new_width;
    img->DIBHEADER.BITMAPINFOHEADER.height = new_height;
    for(int i=0;i<old_img.DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        for(int j=0;j<old_img.DIBHEADER.BITMAPINFOHEADER.width;j++)
        {   
            for(int c=0;c<2;c++)
            {
                img->pixel[2*i][2*j+c] = old_img.pixel[i][j];
            }
        }
        for(int c=1;c<2;c++)
        {
            img->pixel[2*i+c] = img->pixel[2*i];
        }
    }
}
void threshold(BITMAP *img,uint8_t left_scope,uint8_t right_scope,uint8_t color)
{
    for(int i=0;i<img->DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        for(int j=0;j<img->DIBHEADER.BITMAPINFOHEADER.width;j++)
        {   
            if(img->pixel[i][j].red>=left_scope && img->pixel[i][j].red<=right_scope)
            {
                img->pixel[i][j] = (COLOR){color,color,color};
            }
        }
    }
}

void show_info(BITMAP *img)
{
    for(int i=0;i<img->DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        for(int j=0;j<img->DIBHEADER.BITMAPINFOHEADER.width;j++)
        {      
            printf("(%d,%d)[%u,%u,%u]\n",i,j,img->pixel[i][j].red,img->pixel[i][j].green,img->pixel[i][j].blue);
        }
    }
}

void free_img() //TODO: free img
{
    return;
}


void create_color_gradient(int32_t width, int32_t height,COLOR tl,COLOR tr,COLOR bl,COLOR br,char *output_img_name)
{
    BITMAP img;
    FILE *file = fopen("lib/maldives.bmp","rb");
    fread(&(img.HEADER),HEADER_SIZE,1,file);
    fread(&(img.DIBHEADER),img.HEADER.offset-HEADER_SIZE,1,file);
    img.DIBHEADER.BITMAPINFOHEADER.height = (uint32_t)height;
    img.DIBHEADER.BITMAPINFOHEADER.width = (uint32_t)width;
    img.HEADER.size = (uint32_t)height * (uint32_t)width * 3 + 54;
    
    img.pixel = (COLOR**)calloc(img.DIBHEADER.BITMAPINFOHEADER.height, sizeof(COLOR**));
    for(int i=img.DIBHEADER.BITMAPINFOHEADER.height-1;i>=0;i--)
    {
        img.pixel[i] = (COLOR*)calloc(img.DIBHEADER.BITMAPINFOHEADER.width, sizeof(COLOR*));
        fread(img.pixel[i],img.DIBHEADER.BITMAPINFOHEADER.width*sizeof(COLOR),1,file);
    }
    fclose(file);
    for(int i=0;i<img.DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        for(int j=0;j<img.DIBHEADER.BITMAPINFOHEADER.width;j++)
        {   
            if(i<(uint32_t)(height/2)&& j<(uint32_t)(width/2))
            {
                img.pixel[i][j] = tl;
            }
            else if(i<(uint32_t)(height/2)&& j>=(uint32_t)(width/2))
            {
                img.pixel[i][j] = tr;
            }
            else if(i>=(uint32_t)(height/2)&& j<(uint32_t)(width/2))
            {
                img.pixel[i][j] = bl;
            }
            else if(i>=(uint32_t)(height/2)&& j>=(uint32_t)(width/2))
            {
                img.pixel[i][j] = br;
            }
        }
    }
    write_img(&img,output_img_name);
}