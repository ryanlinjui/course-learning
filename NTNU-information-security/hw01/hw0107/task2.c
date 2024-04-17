#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <openssl/aes.h>

#define KEY_SIZE 16
#define TARGET_TIME 1524020929

int main() 
{
    const uint8_t plaintext[KEY_SIZE] = "\x25\x50\x44\x46\x2d\x31\x2e\x35\x0a\x25\xd0\xd4\xc5\xd8\x0a\x34";
    const uint8_t ciphertext[KEY_SIZE] = "\xd0\x6b\xf9\xd0\xda\xb8\xe8\xef\x88\x06\x60\xd2\xaf\x65\xaa\x82";
    const uint8_t iv[KEY_SIZE] = "\x09\x08\x07\x06\x05\x04\x03\x02\x01\x00\xA2\xB2\xC2\xD2\xE2\xF2";
    
    uint8_t key[KEY_SIZE];
    uint8_t decrypted[KEY_SIZE];

    for (int t = TARGET_TIME; t >= TARGET_TIME - (60 * 60 * 2); t--) 
    {
        srand(t);
        uint8_t iv[KEY_SIZE] = "\x09\x08\x07\x06\x05\x04\x03\x02\x01\x00\xA2\xB2\xC2\xD2\xE2\xF2";

        for (int i = 0; i < KEY_SIZE; i++) 
        {
            key[i] = rand() % 256;
        }

        AES_KEY enc_key;
		AES_set_encrypt_key(key, 128 , &enc_key);
		AES_cbc_encrypt(plaintext, decrypted, KEY_SIZE, &enc_key, iv, AES_ENCRYPT);

        bool flag = true;
		for(int i = 0; i < KEY_SIZE; i++)
		{
			if(decrypted[i]!=ciphertext[i])
			{
				flag = false;
				break;
			}
		}

        if (flag)
        {
            printf("Found the key: ");
            for (int i = 0; i < KEY_SIZE; i++) 
            {
                printf("%02x", key[i]);
            }
            printf("\n");
            break;
        }
    }

    return 0;
}