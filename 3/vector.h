#ifndef VECTOR_H
#define VECTOR_H
#define VECTOR_SIZE 100000

typedef struct vectorr
{
    int start;
    int end;
    int data[VECTOR_SIZE];
} VECTOR;

VECTOR *createVector();
void printVector(VECTOR *vector);
int popVector(VECTOR *vector);
void pushToVector(VECTOR *vector, int item);
void copyEndToStart(VECTOR *vector);
int len(VECTOR *vector);

#endif