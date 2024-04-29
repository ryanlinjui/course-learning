#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/bmp.h"

#define MAX_LEN 100

int main()
{
    char *input_img_name = malloc(MAX_LEN);
    char *output_img_name = malloc(MAX_LEN);
    printf("Please enter the input image name: ");
    CHECK_VALID(scanf("%[^\n]%*c",input_img_name) == 1, "Invalid input image name!!");
    printf("Please enter the output image name: ");
    CHECK_VALID(scanf("%[^\n]%*c",output_img_name) == 1, "Invalid output image name!!");
    BITMAP img;
    read_img(&img, input_img_name);
    change_depth(&img,5,6,5);
    write_img(&img, output_img_name);
    puts("Done!");
    return 0;
}