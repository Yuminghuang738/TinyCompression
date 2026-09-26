#ifndef BIT_IO_H
#define BIT_IO_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#define BYTE_LENGTH 8 
#define ELEMENT_NUM 1
#define ELEMENT_SIZE 1

struct BitRead
{
    FILE *read_fp;
    uint8_t read_buffer;
    uint8_t bit_left;
};

struct BitWrite 
{
    FILE *write_fp;
    uint8_t write_buffer;
    uint8_t bit_used;
};

void bit_write(struct BitWrite *bitwrite, uint8_t encode_bit); 

void bit_flush(struct BitWrite *bitwrite);

uint8_t bit_read(struct BitRead *bitread);

#endif