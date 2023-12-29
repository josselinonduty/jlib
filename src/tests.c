#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base/flags.h"
#include "types/queue.h"
#include "types/huffman_tree.h"
#include "types/statistic.h"
#include "types/binary_code.h"

long int read_stats(char *filename, long int *stats)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    long int length = 0;
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        stats[c]++;
        length++;
    }

    fclose(fp);

    return length;
}

void write_stats(char *filename, long int *stats, binary_code *table, long int length)
{
    FILE *fp = fopen(filename, "r");

    char *dest_filename = malloc(strlen(filename) + 5);
    dest_filename = strcat(filename, ".huff");

    FILE *dest_fp = fopen(dest_filename, "w");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fputc('H', dest_fp);
    printf("H");
    fputc('F', dest_fp);
    printf("F");
    printf("\n");

    printf("%lu\n", length);
    fwrite(&length, sizeof(unsigned long int), 1, dest_fp);

    if (NULL == stats || NULL == table)
    {
        printf("File is empty.\n");
        fclose(fp);
        fclose(dest_fp);

        return;
    }

    for (int i = 0; i < 256; i++)
    {
        fwrite(&stats[i], sizeof(unsigned long int), 1, dest_fp);
    }

    int buffer = 0;
    int buffer_length = 0;

    long int compressed_length = 0;
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        for (int i = 0; i < binary_code_length(table[c]); i++)
        {
            buffer <<= 1;
            buffer |= binary_code_get(table[c], i);
            buffer_length++;

            if (buffer_length == 8)
            {
                fputc(buffer, dest_fp);
                buffer = 0;
                buffer_length = 0;
            }

            compressed_length++;
        }
    }
    if (buffer_length > 0)
    {
        buffer <<= (8 - buffer_length);
        fputc(buffer, dest_fp);
    }

    printf("\n");

    double ratio = (double)compressed_length / ((double)length * 8) * 100;
    printf("Final size: %.1f%%\n", ratio);

    fclose(fp);
    fclose(dest_fp);
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

void create_encoding_table_recursive(huffman_tree tree, binary_code *table, binary_code encoding)
{
    if (NULL == tree || binary_tree_is_leaf(tree))
    {
        if (binary_code_length(encoding) < 1)
        {
            binary_code_set(encoding, 0, 1);
        }

        table[huffman_tree_get_data(tree)->byte] = encoding;
        return;
    }

    binary_code encodingLeft = binary_code_copy(encoding);
    binary_code encodingRight = binary_code_copy(encoding);
    binary_code_destroy(encoding);

    if (huffman_tree_get_left(tree) != NULL)
    {
        binary_code_set(encodingLeft, binary_code_length(encodingLeft), 0);
        create_encoding_table_recursive(huffman_tree_get_left(tree), table, encodingLeft);
    }

    if (huffman_tree_get_right(tree) != NULL)
    {
        binary_code_set(encodingRight, binary_code_length(encodingRight), 1);
        create_encoding_table_recursive(huffman_tree_get_right(tree), table, encodingRight);
    }
}

void create_encoding_table(huffman_tree tree, binary_code *table)
{
    binary_code encoding = binary_code_create();
    create_encoding_table_recursive(tree, table, encoding);
}

void compress(char *filename)
{
    clock_t start = clock();

    long int stats[256] = {0};
    long int length = read_stats(filename, stats);

    for (int i = 0; i < 256; i++)
    {
        if (stats[i] > 0)
        {
            printf("%c: %ld\n", i, stats[i]);
        }
    }

    queue q = build_queue(stats);

    if (queue_is_empty(q))
    {
        write_stats(filename, NULL, NULL, 0);
        return;
    }

    huffman_tree *res = build_tree(q);

    binary_code table[256];
    create_encoding_table(*res, table);

    write_stats(filename, stats, table, length);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed: %.3fs\n", time_spent);
}

void decompress(char *filename)
{
    clock_t start = clock();

    FILE *fp = fopen(filename, "r");

    char *dest_filename = malloc(strlen(filename) - 5);
    strncpy(dest_filename, filename, strlen(filename) - 5);

    FILE *dest_fp = fopen(dest_filename, "w");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char c;
    c = fgetc(fp);
    if (c != 'H')
    {
        printf("Invalid file format\n");
        exit(1);
    }
    printf("%c", c);
    c = fgetc(fp);
    if (c != 'F')
    {
        printf("Invalid file format\n");
        exit(1);
    }
    printf("%c", c);
    printf("\n");

    unsigned long int length;
    fread(&length, sizeof(unsigned long int), 1, fp);

    if (length == 0)
    {
        printf("File is empty.\n");
        fclose(fp);
        fclose(dest_fp);

        return;
    }

    long int stats[256] = {0};
    for (int i = 0; i < 256; i++)
    {
        fread(&stats[i], sizeof(unsigned long int), 1, fp);

        if (stats[i] > 0)
        {
            printf("%c: %ld\n", i, stats[i]);
        }
    }

    queue q = build_queue(stats);

    huffman_tree *res = build_tree(q);

    binary_code table[256];
    create_encoding_table(*res, table);

    binary_code buffer = binary_code_create();

    long int decompressed_length = 0;
    while (decompressed_length < length)
    {
        c = fgetc(fp);
        for (int i = 0; i < 8; i++)
        {
            binary_code_set(buffer, binary_code_length(buffer), (c >> (7 - i)) & 0x1);
            for (int j = 0; j < 256; j++)
            {
                if (stats[j] == 0)
                {
                    continue;
                }

                if (binary_code_compare(buffer, table[j]))
                {
                    fputc(j, dest_fp);
                    printf("%c", j);
                    decompressed_length++;
                    binary_code_destroy(buffer);
                    buffer = binary_code_create();
                    break;
                }
            }

            if (decompressed_length == length)
            {
                break;
            }
        }
    }
    printf("\n");

    double ratio = (double)decompressed_length / ((double)length * 8) * 100;
    printf("Final size: %.1f%%\n", ratio);

    fclose(fp);
    fclose(dest_fp);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed: %.3f\ns", time_spent);
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
        decompress(argv[2]);
    }
    else
    {
        printf("Usage: %s compress|decompress <filename>\n", argv[0]);
        exit(1);
    }

    return 0;
}