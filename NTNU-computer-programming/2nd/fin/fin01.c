#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/bmp.h"

#define MAX_LEN 1000

struct option long_options[] = 
{  
    {0, 0, 0, 0},  
}; 

int main(int argc, char **argv)
{
    add_help_option(argc, argv);
    int32_t c=0,index=0;
    int32_t width=1024,height=768;
    char *output_img_name = calloc(MAX_LEN,sizeof(char));
    strncpy(output_img_name,"output.bmp",strlen("output.bmp"));
    while ( ( c = getopt_long( argc, argv, "w:h:o:", long_options, &index ) ) != -1 )
    {
        if(c=='w')
        {
            width = atoi(optarg);
            CHECK_VALID(width>0&&width<=2000,"Invalid input width value!!");
        }
        else if(c=='h')
        {
            height = atoi(optarg);
            CHECK_VALID(height>0&&height<=2000,"Invalid input height value!!");
        }
        else if(c=='o')
        {
            strncpy(output_img_name,optarg,strlen(optarg));
            CHECK_VALID(strlen(output_img_name) > 0, "Invalid output image name!!");
        }
        else
        {
            puts("Command Error!!");
            return 0;
        }
    }
    COLOR tl,tr,bl,br;
    int32_t r=0,g=0,b=0;
    printf("%s","Please enter (R,G,B) in the top left pixel: ");
    CHECK_VALID(scanf("%d,%d,%d",&r,&g,&b) == 3 && r>=0 && r<=255 && g>=0 && g<= 255 && b>=0 && b<= 255, "Invalid input top left pixel!!");
    tl.red = (uint8_t)r;
    tl.green = (uint8_t)g;
    tl.blue = (uint8_t)b;

    printf("%s","Please enter (R,G,B) in the top right pixel: ");	
    CHECK_VALID(scanf("%d,%d,%d",&r,&g,&b) == 3 && r>=0 && r<=255 && g>=0 && g<= 255 && b>=0 && b<= 255, "Invalid input top right pixe!!");
    tr.red = (uint8_t)r;
    tr.green = (uint8_t)g;
    tr.blue = (uint8_t)b;

    printf("%s","Please enter (R,G,B) in the bottom left pixel: ");	
    CHECK_VALID(scanf("%d,%d,%d",&r,&g,&b) == 3 && r>=0 && r<=255 && g>=0 && g<= 255 && b>=0 && b<= 255, "Invalid input bottom left pixe!!");
    bl.red = (uint8_t)r;
    bl.green = (uint8_t)g;
    bl.blue = (uint8_t)b;

    printf("%s","Please enter (R,G,B) in the bottom right pixel: ");
    CHECK_VALID(scanf("%d,%d,%d",&r,&g,&b) == 3 && r>=0 && r<=255 && g>=0 && g<= 255 && b>=0 && b<= 255, "Invalid input bottom right pixe!!");
    br.red = (uint8_t)r;
    br.green = (uint8_t)g;
    br.blue = (uint8_t)b;

    create_color_gradient(width,height,tl,tr,bl,br,output_img_name);
    puts("Done");
    return 0;
}