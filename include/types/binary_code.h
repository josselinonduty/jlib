#ifndef __BYTE_H__
#define __BYTE_H__

#include <stdio.h>
#include <stdbool.h>
#include "base/generic.h"

typedef int bit;
typedef bit *binary_code;

binary_code binary_code_create();
void binary_code_destroy(binary_code code);
void binary_code_set(binary_code code, int index, bit b);
bit binary_code_get(binary_code code, int index);
int binary_code_length(binary_code code);

void binary_code_print(binary_code code);
binary_code binary_code_copy(binary_code code);
void binary_code_free(binary_code code);
bool binary_code_compare(binary_code a, binary_code b);

#endif // __BYTE_H__