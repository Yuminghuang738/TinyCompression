#ifndef OUTPUT_H
#define OUTPUT_H

#include "encode.h"
#include "bit_io.h"

void code_output(struct HuffmanCode *huffmancode, FILE *read_fp, struct BitWrite *bitwrite);

#endif