#include "output.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "statistics.h"
#include "bit_io.h"

void code_output(struct HuffmanCode *huffmancode, FILE *read_fp, struct BitWrite *bitwrite)
{
    struct Buffer *buffer = malloc(sizeof(struct Buffer));
    if (buffer == NULL)
    {
        perror("Error while allowcating buffer struct!\n");
        return;
    }

    buffer->size = sizeof(*(buffer->buffer_ptr)) * READ_COUNT;
    buffer->buffer_ptr = malloc(buffer->size);
    if (buffer->buffer_ptr == NULL)
    {
        perror("Error while allowcating buffer memory!\n");
        free(buffer);
        return;
    }

    size_t count = 0;
    while ((count = fread(buffer->buffer_ptr, READ_SIZE, READ_COUNT, read_fp)) > 0)
    {
        for (size_t cur_byte = 0; cur_byte < count; cur_byte++)
        {   
            uint8_t byte = buffer->buffer_ptr[cur_byte];
            uint32_t code_val = huffmancode[byte].code_val;
            uint8_t code_len = huffmancode[byte].code_len;

            for (size_t bit_pos = 0; bit_pos < code_len; bit_pos++)
            {
                bit_write(bitwrite, (code_val >> (code_len - 1 - bit_pos)) & 1U);
            }
        }
    }
    bit_flush(bitwrite);

    free(buffer->buffer_ptr);
    free(buffer);
}