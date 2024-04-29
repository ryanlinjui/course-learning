#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/bmp.h"

#define MAX_LEN 100

int main()
{
    char *input_img_name = malloc(MAX_LEN);
    char *output_img_name = malloc(MAX_LEN);
    int32_t c[2] = {0};
    int32_t r=0;
    printf("Please enter the input image name: ");
    CHECK_VALID(scanf("%[^\n]%*c",input_img_name) == 1, "Invalid input image name!!");
    printf("Please enter the output image name: ");
    CHECK_VALID(scanf("%[^\n]%*c",output_img_name) == 1, "Invalid output image name!!");
    printf("Please enter the center: ");
    CHECK_VALID(scanf("(%d,%d)",&c[0],&c[1])==2 && c[0]>=0 && c[1]>=0, "Invalid center value!!");
    printf("Please enter the radius: "); 
    CHECK_VALID(scanf("%d",&r)==1 && r>0, "Invalid radius value!!");
    BITMAP img;
    read_img(&img,input_img_name);
    circular_focus(&img,c,r,255);    
    write_img(&img,output_img_name);
    return 0;
}