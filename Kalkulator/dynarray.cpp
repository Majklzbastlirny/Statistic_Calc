#include "dynarray.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex>
#include <iostream>
/*
typedef struct {
    int* array;
    size_t used;
    size_t size;
} Array;*/

void initArray(Array* a, size_t initialSize) {
    a->array = (int*)malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void addArray(Array* a, double element) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size 
    if (a->used == a->size) {
        a->size *= 2;
//        a->array = (double*)realloc(a->array, a->size * sizeof(double));
    }
    a->array[a->used++] = element;
}

void freeArray(Array* a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}