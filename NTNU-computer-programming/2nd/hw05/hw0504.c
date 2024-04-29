#include "lib/cstd.h"
#include "lib/utils.h"
#include "hw0504.h"

#define MAX_LEN 1000

int main(int argc, char **argv)
{
    add_help_option(argc, argv);
    char *wav1 = calloc(MAX_LEN, sizeof(char));
    char *wav2 = calloc(MAX_LEN, sizeof(char));
    printf("input: ");
    CHECK_VALID(scanf("%[^\n]%*c",wav1) == 1, "Invalid input string!!");
    generate_tone(wav1,wav2);
    printf("output: %s\n",wav2);
    generate_wav(wav2);
    puts("out.wav has been generated.");
    return 0;
}