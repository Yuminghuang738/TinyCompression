#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "statistics.h"
#include "encode.h"
#include "bit_io.h"
#include "output.h"
#include "input.h"
#include "decode.h"

int main(int argc, char *argv[])
{   
    //argv[0]: ./tc, argv[1]: mode parameter, "-c" for compression, "-d" for decompression, argv[2]: file path
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <mode_paremeter> <file_path>\n", argv[0]);
        
        return 1;
    }

    const char *parameter = argv[1];
    const char *file_path = argv[2];

    //compression mode
    if (strcmp(parameter, "-c") == 0)
    {
        FILE *read_fp = fopen(file_path, "rb");
        if (read_fp == NULL)
        {
            perror("Error while opening file!");
            
            return 1;
        }

        struct Statistics statistics;
        byte_statistics(read_fp, &statistics);

        struct HuffmanTree huffmantree[BYTE_RANGE];
        struct HuffmanCode huffmancode[BYTE_RANGE];
        struct HuffmanTree *root = huffman_encode(&statistics, huffmantree, huffmancode);

        size_t len = strlen(file_path);
        char *new_path = malloc(len + 4);
        if (new_path == NULL)
        {
            fclose(read_fp);
            
            return 1;
        }
        strcpy(new_path, file_path);
        strcat(new_path, ".tc");

        struct BitWrite bitwrite =
        {
            .write_fp = fopen(new_path, "w+"),
            .write_buffer = 0,
            .bit_used = 0
        };
        if (bitwrite.write_fp == NULL)
        {
            perror("Error while opening file!");
            
            fclose(read_fp);
            return 1;
        }

        head_output(root, &bitwrite, statistics.total_counts);
        rewind(read_fp);
        code_output(huffmancode, &bitwrite, read_fp);

        fclose(read_fp);
        fclose(bitwrite.write_fp);
        free(new_path);
    }
    //decompression mode
    else if (strcmp(parameter, "-d") == 0)
    {
        uint64_t total_counts;
        
        size_t len = strlen(file_path);
        char *new_path = malloc(len - 3 + 1);
        if (new_path == NULL)
        {
            return 1;
        }
        strncpy(new_path, file_path, len - 3);
        new_path[len - 3] = '\0';
        
        FILE *write_fp = fopen(new_path, "w+");
        if (write_fp == NULL)
        {
            free(new_path);
            
            return 1;
        }

        struct BitRead bitread = 
        {
            .read_fp = fopen(file_path, "rb"),
            .read_buffer = 0,
            .bit_left = 0  
        };
        if (bitread.read_fp == NULL)
        {
            perror("Error while opening file!");
            
            fclose(write_fp);
            free(new_path);
            return 1;
        }

        struct HuffmanTree *root = head_input(&bitread, &total_counts);
        huffman_decode(root, &bitread, write_fp, total_counts);

        fclose(write_fp);
        fclose(bitread.read_fp);
        free(new_path);
    }
    else
    {
        fprintf(stderr, "Error: unknown parameter!\n");
        return 1;
    }

    return 0;
}