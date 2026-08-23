#include "bit_io.h"

#include <stdint.h>
#include <stdio.h>

void bit_write(struct BitWrite *bitwrite, uint8_t encode_bit) 
{
    //write order: MSB -> LSB
    bitwrite->write_buffer |= encode_bit << (7 - bitwrite->bit_used); 
    bitwrite->bit_used++;
    
    if (bitwrite->bit_used == BYTE_LENGTH)
    {
        fwrite(&bitwrite->write_buffer, ELEMENT_SIZE, ELEMENT_NUM, bitwrite->write_fp);
        bitwrite->write_buffer = 0;
        bitwrite->bit_used = 0;
    }
}

void bit_flush(struct BitWrite *bitwrite)
{
    if (bitwrite->bit_used > BYTE_LENGTH)
    {
        fwrite(&bitwrite->write_buffer, ELEMENT_SIZE, ELEMENT_NUM, bitwrite->write_fp);
        bitwrite->write_buffer = 0;
        bitwrite->bit_used = 0;
    }
}

uint8_t bit_read(struct BitRead *bitread)
{
    if (bitread->bit_left == 0)
    {
        fread(&bitread->read_buffer, ELEMENT_SIZE, ELEMENT_NUM, bitread->read_fp);
        bitread->bit_left = BYTE_LENGTH;
    }

    uint8_t decode_bit = (bitread->read_buffer >> (bitread->bit_left - 1)) & 1U;
    bitread->bit_left--;

    return decode_bit;
}