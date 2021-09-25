#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

VECTOR *createVector()
{
    VECTOR *vector;
    size_t arrayLength = 0;

    vector = malloc(sizeof(VECTOR));
    vector->end = arrayLength;
    return vector;
}

int popVector(VECTOR *vector)
{
    if (vector->start == vector->end)
        return 0;
    vector->start++;
    return vector->data[vector->start - 1];
}

void pushToVector(VECTOR *vector, int item)
{
    if (VECTOR_SIZE == vector->end)
    {
        copyEndToStart(vector);
    }

    vector->data[vector->end] = item;
    vector->end++;
}

void copyEndToStart(VECTOR *vector)
{
    for (int i = vector->start, z = 0; i < vector->end; z++, i++)
    {
        vector->data[z] = vector->data[i];
    }
    vector->end = vector->end - vector->start;
    vector->start = 0;
}
int len(VECTOR *vector) { return vector->end - vector->start; }

void printVector(VECTOR *vector)
{
    printf("[ ");
    for (int i = vector->start; i < vector->end; i++)
    {
        printf("%d, ", vector->data[i]);
    }
    printf("]");
    printf("  start=%d, end=%d\n", vector->start, vector->end);
}