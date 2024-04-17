#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define LEN 32 // 256 bits

int main()
{
	uint8_t *key = (uint8_t*) malloc(sizeof(uint8_t) * LEN);
	FILE *random = fopen("/dev/urandom", "r");
	fread(key, sizeof(uint8_t) * LEN, 1, random);
	fclose(random);
	for(int i = 0; i < LEN; i++)
	{
		printf("%.2x",key[i]);
	}
    
	printf("\n");
    return 0;
}