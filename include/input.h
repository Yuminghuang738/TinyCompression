#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

#include "encode.h"
#include "bit_io.h"

struct HuffmanTree *head_input(struct BitRead *bitread, uint64_t *total_counts);

#endif