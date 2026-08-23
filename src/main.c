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

    struct HuffmanCode huffmancode[BYTE_RANGE];
    huffman_encode(&statistics, huffmancode);

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
    
    rewind(file_ptr);
    code_output(huffmancode, file_ptr, &bitwrite);

    return 0;
}