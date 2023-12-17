#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/flags.h"
#include "types/queue.h"
#include "types/huffman_tree.h"
#include "types/statistic.h"

void read_stats(char *filename, long int *stats)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        stats[c]++;
    }

    fclose(fp);
}

queue build_queue(long int *stats)
{
    queue q = queue_create(FLAG_SORTED, huffman_tree_copy, huffman_tree_free, huffman_tree_compare);

    for (int i = 0; i < 256; i++)
    {
        if (stats[i] == 0)
        {
            continue;
        }

        stat s = {i, stats[i]};
        huffman_tree hf = huffman_tree_create(&s);
        queue_enqueue(&q, &hf);
    }

    return q;
}

const char DEFAULT_CHAR = ' ';

huffman_tree *build_tree(queue q)
{
    while (queue_length(q) > 1)
    {
        huffman_tree *t1 = queue_dequeue(&q);
        huffman_tree *t2 = queue_dequeue(&q);

        stat *s1 = huffman_tree_get_data(*t1);
        stat *s2 = huffman_tree_get_data(*t2);

        stat *s = malloc(sizeof(stat));
        s->byte = DEFAULT_CHAR;
        s->count = s1->count + s2->count;

        huffman_tree *t = malloc(sizeof(huffman_tree));
        *t = huffman_tree_create(s);
        huffman_tree_set_left(*t, *t1);
        huffman_tree_set_right(*t, *t2);

        queue_enqueue(&q, t);
    }
    return (huffman_tree *)queue_dequeue(&q);
}

void create_encoding_table_recursive(huffman_tree tree, char **table, char *encoding)
{
    if (binary_tree_is_leaf(tree))
    {
        table[huffman_tree_get_data(tree)->byte] = encoding;
        return;
    }

    char *encodingLeft = malloc(sizeof(encoding) + 1);
    strcpy(encodingLeft, encoding);
    char *encodingRight = malloc(sizeof(encoding) + 1);
    strcpy(encodingRight, encoding);

    strcat(encodingLeft, "0");
    strcat(encodingRight, "1");

    create_encoding_table_recursive(huffman_tree_get_left(tree), table, encodingLeft);
    create_encoding_table_recursive(huffman_tree_get_right(tree), table, encodingRight);
}

void create_encoding_table(huffman_tree tree, char **table)
{
    create_encoding_table_recursive(tree, table, "");
}

void compress(char *filename)
{
    long int stats[256] = {0};
    read_stats(filename, stats);

    for (int i = 0; i < 256; i++)
    {
        if (stats[i] > 0)
        {
            printf("%c: %ld\n", i, stats[i]);
        }
    }

    queue q = build_queue(stats);

    huffman_tree *res = build_tree(q);
    huffman_tree_print(res);
    printf("\n");

    char *table[256];
    create_encoding_table(*res, table);

    for (int i = 0; i < 256; i++)
    {
        if (stats[i] == 0)
        {
            continue;
        }

        printf("%c: %s\n", i, table[i]);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s compress <filename>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "compress") == 0)
    {
        compress(argv[2]);
    }
    else if (strcmp(argv[1], "decompress") == 0)
    {
        printf("decompress\n");
    }
    else
    {
        printf("Usage: %s compress|decompress <filename>\n", argv[0]);
        exit(1);
    }

    return 0;
}