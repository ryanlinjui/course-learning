#include "lib/cstd.h"
#include "lib/utils.h"
#include "lib/bmp.h"

#define MAX_LEN 100

struct
{
    
}PZ;


uint8_t step_valid(char *pz_name)
{
    return 0;
}

int main()
{
    char *img_name = malloc(MAX_LEN);
    char *pz_name = malloc(MAX_LEN);
    printf("Please enter the image: ");
    CHECK_VALID(scanf("%[^\n]%*c",img_name) == 1, "Invalid image name!!");
    printf("Please enter the puzzle: ");
    CHECK_VALID(scanf("%[^\n]%*c",pz_name) == 1, "Invalid puzzle name!!");
    BITMAP img;
    read_img(&img, img_name);
    // CHECK_VALID(step_valid() == 1, "Invalid step!!");
    //write_img(&img, output_img_name);
    return 0;
}