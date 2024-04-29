/**
 *  @file hw0401.c
 *  @brief It is a example code from hw04 of 
 *  NTNU computer programming II (neokent).
 *  @author Ryan
 *  @date 2022-06-09 
*/

#include "lib/cstd.h"
#include "lib/utils.h" 
#include "lib/bmp.h"

#define HELP_FILE_PATH "help/hw0401.help" /**< @brief help file path */

/**
 *  @brief image cryptography.
 *  @param[in] img
 *  @param[in] layer1
 *  @param[in] layer2
 *  @param[in] overlap
*/ 

void visual_cryptography(BITMAP *img,BITMAP *layer1,BITMAP *layer2,BITMAP *overlap)
{   
    srand(time(NULL));
    resize(img,2560,1708);
    threshold(img,128,255,255);
    threshold(img,0,127,0);
    copy_img(img,layer1);
    copy_img(img,layer2);
    copy_img(img,overlap);
    for(int i=0;i<img->DIBHEADER.BITMAPINFOHEADER.height;i+=2)
    {
        for(int j=0;j<img->DIBHEADER.BITMAPINFOHEADER.width;j+=2)
        {      
            if(img->pixel[i][j].red==255)
            {
                if(rand()%2)
                {
                    layer1->pixel[i][j] = (COLOR){0,0,0};
                    layer1->pixel[i+1][j] = (COLOR){255,255,255};
                    layer1->pixel[i][j+1] = (COLOR){255,255,255};
                    layer1->pixel[i+1][j+1] = (COLOR){0,0,0};
                    layer2->pixel[i][j] = (COLOR){0,0,0};
                    layer2->pixel[i+1][j] = (COLOR){255,255,255};
                    layer2->pixel[i][j+1] = (COLOR){255,255,255};
                    layer2->pixel[i+1][j+1] = (COLOR){0,0,0};
                    overlap->pixel[i][j] = (COLOR){0,0,0};
                    overlap->pixel[i+1][j] = (COLOR){255,255,255};
                    overlap->pixel[i][j+1] = (COLOR){255,255,255};
                    overlap->pixel[i+1][j+1] = (COLOR){0,0,0};
                }
                else
                {
                    layer1->pixel[i][j] = (COLOR){255,255,255};
                    layer1->pixel[i+1][j] = (COLOR){0,0,0};
                    layer1->pixel[i][j+1] = (COLOR){0,0,0};
                    layer1->pixel[i+1][j+1] = (COLOR){255,255,255};
                    layer2->pixel[i][j] = (COLOR){255,255,255};
                    layer2->pixel[i+1][j] = (COLOR){0,0,0};
                    layer2->pixel[i][j+1] = (COLOR){0,0,0};
                    layer2->pixel[i+1][j+1] = (COLOR){255,255,255};
                    overlap->pixel[i][j] = (COLOR){255,255,255};
                    overlap->pixel[i+1][j] = (COLOR){0,0,0};
                    overlap->pixel[i][j+1] = (COLOR){0,0,0};
                    overlap->pixel[i+1][j+1] = (COLOR){255,255,255};
                }
            }
            else
            {
                if(rand()%2)
                {
                    layer1->pixel[i][j] = (COLOR){0,0,0};
                    layer1->pixel[i+1][j] = (COLOR){255,255,255};
                    layer1->pixel[i][j+1] = (COLOR){255,255,255};
                    layer1->pixel[i+1][j+1] = (COLOR){0,0,0};
                    layer2->pixel[i][j] = (COLOR){255,255,255};
                    layer2->pixel[i+1][j] = (COLOR){0,0,0};
                    layer2->pixel[i][j+1] = (COLOR){0,0,0};
                    layer2->pixel[i+1][j+1] = (COLOR){255,255,255};
                    overlap->pixel[i][j] = (COLOR){0,0,0};
                    overlap->pixel[i+1][j] = (COLOR){0,0,0};
                    overlap->pixel[i][j+1] = (COLOR){0,0,0};
                    overlap->pixel[i+1][j+1] = (COLOR){0,0,0};
                }
                else
                {
                    
                    layer1->pixel[i][j] = (COLOR){255,255,255};
                    layer1->pixel[i+1][j] = (COLOR){0,0,0};
                    layer1->pixel[i][j+1] = (COLOR){0,0,0};
                    layer1->pixel[i+1][j+1] = (COLOR){255,255,255};
                    layer2->pixel[i][j] = (COLOR){0,0,0};
                    layer2->pixel[i+1][j] = (COLOR){255,255,255};
                    layer2->pixel[i][j+1] = (COLOR){255,255,255};
                    layer2->pixel[i+1][j+1] = (COLOR){0,0,0};
                    overlap->pixel[i][j] = (COLOR){0,0,0};
                    overlap->pixel[i+1][j] = (COLOR){0,0,0};
                    overlap->pixel[i][j+1] = (COLOR){0,0,0};
                    overlap->pixel[i+1][j+1] = (COLOR){0,0,0};
                }
            }
        }
    }
}

/**
 *  @brief This is the main function
 *  @param[in] argc
 *  @param[in] argv
*/

int main(int argc, char **argv)
{   
    add_help_option(argc, argv); 
    BITMAP img,layer1,layer2,overlap;
    read_img(&img,argv[1]);
    to_grayscale(&img); 
    visual_cryptography(&img,&layer1,&layer2,&overlap);
    char *n1 = "_layer1.bmp";
    char *n2 = "_layer2.bmp";
    char *n3 = "_overlap.bmp";
    char *name = calloc(1000,sizeof(char));
    strncpy(name,argv[1],strlen(argv[1])-4);
    strcpy(name+strlen(name),n1);
    write_img(&layer1,name);
    strcpy(name+strlen(name)-11,n2);
    write_img(&layer2,name);
    strcpy(name+strlen(name)-11,n3);
    write_img(&overlap,name);
    return 0;
}