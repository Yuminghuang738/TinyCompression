#ifndef OUTPUT_H
#define OUTPUT_H

#include <stddef.h>
#include <stdint.h>

#include "encode.h"
#include "bit_io.h"

#define WRITE_NUM 1

#define MERGE_NODE 0
#define LEAF_NODE 1

void head_output(struct HuffmanTree *root, struct BitWrite *bitwrite, uint64_t total_counts);

void code_output(struct HuffmanCode *huffmancode, struct BitWrite *bitwrite, FILE *read_fp);

#endif