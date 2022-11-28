#pragma once

typedef struct {
    int* array;
    size_t used;
    size_t size;
} Array;

void initArray(Array* a, size_t initialSize);

void addArray(Array* a, double element);

void freeArray(Array* a);