#ifndef STATISTICS_H
#define STATISTICS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

//fread parameters,current buffer size:64kb
#define READ_SIZE 1
#define READ_COUNT 65536

//uint8_t range
#define BYTE_RANGE 256

//buffer struct
struct Buffer
{
    uint8_t *buffer_ptr;
    uint32_t size;
};

//statistics struct
struct Statistics
{
    size_t counts[BYTE_RANGE];
    size_t total_counts;
};

//statistics type
void byte_statistics(FILE *file_ptr, struct Statistics *Statistics);

#endif