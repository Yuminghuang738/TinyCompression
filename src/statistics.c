#include "statistics.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void byte_statistics(FILE *file_ptr, struct Statistics *statistics)
{
    if (file_ptr == NULL)
    {
        perror("Error while opening file!\n");
        return;
    }
    
    if (statistics == NULL)
    {
        perror("Invalid argument!\n");
        return;
    }

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

    size_t count;
    memset(statistics, 0, sizeof(*statistics));
    while ((count = fread(buffer->buffer_ptr, READ_SIZE, READ_COUNT, file_ptr)) > 0)
    {
        for (size_t statistics_count = 0; statistics_count < count; statistics_count++)
        {
            statistics->counts[buffer->buffer_ptr[statistics_count]]++;
        }
        statistics->total_counts += count;
    }

    free(buffer->buffer_ptr);
    free(buffer);
}