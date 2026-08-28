#include "encode.h"

#include <stddef.h>
#include <stdlib.h>

#include "statistics.h"

struct HuffmanTree *huffman_encode(struct Statistics *statistics, struct HuffmanTree *huffmantree, struct HuffmanCode *huffmancode)
{
    //initial tree struct
    size_t node_count = 0;
    for (size_t i = 0; i < BYTE_RANGE; i++)
    {
        if (statistics->counts[i] != 0)
        {
            huffmantree[node_count].byte_value = i; 
            huffmantree[node_count].freq = statistics->counts[i];
            huffmantree[node_count].left = NULL;
            huffmantree[node_count].right = NULL;
            huffmantree[node_count].next = NULL;
            node_count++;   
        }
    }

    //insertion sort
    struct HuffmanTree *queue_head = NULL;
    for (size_t i = 0; i < node_count; i++)
    {
        struct HuffmanTree *node = &huffmantree[i];
        if (queue_head == NULL || node->freq < queue_head->freq)
        {
            node->next = queue_head;
            queue_head = node;
        }
        else
        {
            struct HuffmanTree *cur = queue_head;
            while (cur->next != NULL && cur->next->freq <= node->freq)
            {
                cur = cur->next;
            }
            node->next = cur->next;
            cur->next = node;
        }
    }

    //build huffman tree
    while (queue_head != NULL && queue_head->next != NULL)
    {
        struct HuffmanTree *left_node = queue_head;
        struct HuffmanTree *right_node = queue_head->next;
        queue_head = queue_head->next->next;

        left_node->next = NULL;
        right_node->next = NULL;

        struct HuffmanTree *merge_node = malloc(sizeof(struct HuffmanTree));
        merge_node->freq = left_node->freq + right_node->freq;
        merge_node->left = left_node;
        merge_node->right = right_node;

        if (queue_head == NULL || merge_node->freq < queue_head->freq)
        {
            merge_node->next = queue_head;
            queue_head = merge_node;
        }
        else
        {
            struct HuffmanTree *cur = queue_head;
            while (cur->next != NULL && cur->next->freq <= merge_node->freq)
            {
                cur = cur->next;
            }
            merge_node->next = cur->next;
            cur->next = merge_node;
        }
    }
    struct HuffmanTree *root = queue_head;

    //traversal huffman tree
    traversal_tree(root, 0, 0, huffmancode);

    return root;
}

void static traversal_tree(struct HuffmanTree *node, uint32_t current_code_val, uint8_t current_depth, 
                    struct HuffmanCode *huffmancode)
{
    if (node == NULL)
    {
        return;
    }
    if (node->left == NULL && node->right == NULL)
    {
        huffmancode[node->byte_value].code_val = current_code_val;
        huffmancode[node->byte_value].code_len = current_depth;
        
        return;
    }

    traversal_tree(node->left, current_code_val << 1, current_depth + 1, huffmancode);
    traversal_tree(node->right, (current_code_val << 1) | 1U, current_depth + 1, huffmancode);
}