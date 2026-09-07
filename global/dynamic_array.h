#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include <signal.h>
#include <stdbool.h>

typedef struct{
    void* array;
    unsigned int length;
    int filled;
    int cursor;
} DArray; // Dynamic Array

int* new_int_array(size_t len);
DArray new_array_info(int *array, unsigned int len);
DArray new_darray(size_t len);
int expand(DArray *buf);

int collapse(DArray *buf, size_t len);

int d_insert(DArray *buf, void *item);

int d_remove(DArray *buf, int index);
int d_index_of(DArray *buf, void *item);

void print_darray(DArray *buf);

int d_get_value(DArray *buf, int index);

int d_edit_value(DArray *buf, int index, int value);

void SDL_free_darray(DArray *buf);

#endif