#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <stdint.h>

#include "encode.h"
#include "bit_io.h"

void huffman_decode(struct HuffmanTree *root, struct BitRead *bitread, FILE *write_fp,
                    uint64_t total_counts);

#endif