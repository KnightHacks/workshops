#pragma once

typedef struct t_heap
{
  int size;
  int capacity;
  int *array;
} t_heap;

t_heap *createHeap(int *array, int length);
void heapInsert(t_heap *heap, int value);
int heapPoll(t_heap *heap);
int heapPeek(t_heap *heap);
void freeHeap(t_heap *heap);
