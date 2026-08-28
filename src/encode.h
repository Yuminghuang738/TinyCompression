#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>
#include <stddef.h>

#include "statistics.h"

struct HuffmanTree
{
    uint8_t byte_value;
    size_t freq;
    struct HuffmanTree *left;
    struct HuffmanTree *right;
    struct HuffmanTree *next;
};

struct HuffmanCode
{
    uint32_t code_val;
    uint8_t code_len;
};

struct HuffmanTree *huffman_encode(struct Statistics *statistics, struct HuffmanTree *huffmantree, struct HuffmanCode *huffmancode);

#endif