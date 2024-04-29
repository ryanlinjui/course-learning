#pragma once
#include "lib/cstd.h"
#include "lib/utils.h"

#define MAX_LEN_ 3000

struct
{
    uint8_t c1 : 6;
    uint8_t c2 : 6;
    uint8_t c3 : 6;
    uint8_t c4 : 6;
}__attribute__((__packed__))EncedBase64;

struct
{
    uint8_t c1;
    uint8_t c2;
    uint8_t c3;
}DecedBase64;

char base64_table[64] = \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
    "abcdefghijklmnopqrstuvwxyz" \
    "0123456789+/";
char *dec_table = NULL;

int32_t mod_table[3] = {0, 2, 1};

// void encode_base64(char *input_filename,char *output_filename)
// {
//     FILE *input_file = fopen(input_filename,"r");
//     FILE *output_file = fopen(output_filename,"w");
//     CHECK_VALID(input_file!=NULL&&output_file!=NULL,"File doesn't exist!!");
//     while(!feof(input_file))
//     {
//         fread(&EncedBase64,sizeof(EncedBase64),1,input_file);
//         printf("c1: %hhu c2: %hhu c3: %hhu c4: %hhu\n",EncedBase64.c1,EncedBase64.c2,EncedBase64.c3,EncedBase64.c4);
//         fprintf(output_file,"%c",base64_table[EncedBase64.c1]);
//         fprintf(output_file,"%c",base64_table[EncedBase64.c2]);
//         fprintf(output_file,"%c",base64_table[EncedBase64.c3]);
//         fprintf(output_file,"%c",base64_table[EncedBase64.c4]);
//     }
//     fclose(input_file);
//     fclose(output_file);
// }

void encode_base64(char *input_filename,char *output_filename)
{
    FILE *file = fopen(input_filename, "rb");
    CHECK_VALID(file!=NULL,"File is not exist!");
    fseek(file, 0, SEEK_END);
    uint64_t file_size = ftell(file);
    rewind(file);
    char *data = calloc(file_size + 1,sizeof(char));
    fread(data, file_size, 1, file);
    fclose(file);
    uint32_t output_size = 4 * ((file_size + 2) / 3);
    char *result = calloc(file_size + 1,sizeof(char));
    for (int i = 0, j = 0; i < file_size;) 
    { 
        uint32_t octet_a = i < file_size ? (uint8_t)data[i++] : 0;
        uint32_t octet_b = i < file_size ? (uint8_t)data[i++] : 0;
        uint32_t octet_c = i < file_size ? (uint8_t)data[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
        result[j++] = base64_table[(triple >> 3 * 6) & 0x3F];
        result[j++] = base64_table[(triple >> 2 * 6) & 0x3F];
        result[j++] = base64_table[(triple >> 1 * 6) & 0x3F];
        result[j++] = base64_table[(triple >> 0 * 6) & 0x3F];
    }
    for (int i = 0; i < mod_table[file_size % 3]; i++)
    {
        result[output_size - 1 - i] = '=';
    }
    file = fopen(output_filename, "w");
    fwrite(result, 1, output_size,file);
    fclose(file);
}

void _build_decoding_table() 
{ 
    dec_table = calloc(256,sizeof(char));
    for (int i = 0; i < 64; i++)
    {
        dec_table[(char)base64_table[i]] = i;
    }
}

void decode_base64(char *input_filename,char *output_filename)
{
    _build_decoding_table();
    FILE *file = fopen(input_filename, "rb");
    CHECK_VALID(file!=NULL,"File is not exist!");
    fseek(file, 0, SEEK_END);
    uint64_t file_size = ftell(file);
    rewind(file);
    char *data = calloc(file_size + 1,sizeof(char));
    fread(data, file_size, 1, file);
    fclose(file);
    CHECK_VALID(file_size%4==0,"Base64 text file format error!!");
    uint32_t output_size = file_size / 4 * 3;
    if (data[file_size - 1] == '=') (output_size)--;
    if (data[file_size - 2] == '=') (output_size)--;
    char *result = calloc(MAX_LEN_,sizeof(char));
    for (int i = 0, j = 0; i < file_size;) 
    {
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : dec_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : dec_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : dec_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : dec_table[data[i++]];
        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);
        if (j < output_size) result[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_size) result[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_size) result[j++] = (triple >> 0 * 8) & 0xFF;
    }
    file = fopen(output_filename, "w");
    fwrite(result, 1, output_size,file);
    fclose(file);
}