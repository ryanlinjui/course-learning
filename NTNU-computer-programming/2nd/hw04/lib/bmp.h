#pragma once
#include <math.h>
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

typedef struct _BITMAP
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
    for(int i=0;i<img->DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        img->pixel[i] = (COLOR*)calloc(img->DIBHEADER.BITMAPINFOHEADER.width, sizeof(COLOR*));
        fread(img->pixel[i],img->DIBHEADER.BITMAPINFOHEADER.width*sizeof(COLOR),1,file);
    }
    fclose(file);
}
void write_img(BITMAP *img,char *img_name)
{
    FILE *file = fopen(img_name,"wb");
    CHECK_VALID(file!=NULL,"File doesn't exist!!");
    fwrite(&(img->HEADER),HEADER_SIZE,1,file);
    fwrite(&(img->DIBHEADER),img->HEADER.offset-HEADER_SIZE,1,file);
    for(int i=0;i<img->DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        fwrite(img->pixel[i],img->DIBHEADER.BITMAPINFOHEADER.width*sizeof(COLOR),1,file);
    }
    // row_size = (depth * width + 31) / 32 * 4
    // padding = row_size - depth * width
    fclose(file);
}

void circular_focus(BITMAP *img,int32_t center[],int32_t radius,uint8_t color)
{
    for(int x=0;x<(img->DIBHEADER.BITMAPINFOHEADER.width);x++)
    {
        for(int y=0;y<img->DIBHEADER.BITMAPINFOHEADER.height;y++)
        {
            if(sqrt(pow(x-center[0],2)+pow(y-center[1],2))>=(double)radius)
            {
                img->pixel[img->DIBHEADER.BITMAPINFOHEADER.height-y-1][x] = (COLOR){color,color,color};
            }
        }
    }
}

void change_depth(BITMAP *img,uint8_t red,uint8_t green,uint8_t blue)
{
    img->DIBHEADER.BITMAPINFOHEADER.depth = red + green + blue;
    for(int i=0;i<img->DIBHEADER.BITMAPINFOHEADER.height;i++)
    {
        for(int j=0;i<img->DIBHEADER.BITMAPINFOHEADER.width;i++)
        {   
            img->pixel[j][i].red >>= RGB_STANDARD_DEPTH - red;
            img->pixel[j][i].green >>= RGB_STANDARD_DEPTH - green;
            img->pixel[j][i].blue >>= RGB_STANDARD_DEPTH - blue;
        }
    }
}

void to_grayscale(BITMAP *img)
{

}

void zoom(BITMAP *img,double width_val,double height_val)
{

}