#include "statistics.h"
#include "encode.h"
#include "bit_io.h"
#include "output.h"

#include <stdio.h>

int main()
{
    FILE *file_ptr = fopen("/home/bosak/Documents/App_projects/TinyCompression/test/test.txt", "rb");
    if (file_ptr == NULL)
    {
        perror("Error while opening file!\n");
        return 1;
    }

    struct Statistics statistics;
    byte_statistics(file_ptr, &statistics);

    struct HuffmanTree huffmantree[BYTE_RANGE];
    struct HuffmanCode huffmancode[BYTE_RANGE];
    struct HuffmanTree *root = huffman_encode(&statistics, huffmantree, huffmancode);

    struct BitWrite bitwrite =
    {
        .write_fp = fopen("/home/bosak/Documents/App_projects/TinyCompression/test/test.tc", "w+"),
        .write_buffer = 0,
        .bit_used = 0
    };
    if (bitwrite.write_fp == NULL)
    {
        fclose(file_ptr);
        perror("Error while opening file!\n");
        return 1;
    }
    
    head_output(root, &bitwrite, statistics.total_counts);

    rewind(file_ptr);
    code_output(huffmancode, &bitwrite, file_ptr);

    return 0;
}