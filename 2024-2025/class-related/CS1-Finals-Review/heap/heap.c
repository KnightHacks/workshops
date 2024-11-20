
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct t_heap
{
  int size;
  int capacity;
  int *array;
} t_heap;

void heapify(t_heap *heap);
void percolateUp(t_heap *heap, int index);
void percolateDown(t_heap *heap, int index);

t_heap *createHeap(int *array, int length)
{
  t_heap *heap = (t_heap *)malloc(sizeof(t_heap));
  int heapCapacity = pow(2, ceil(log(length + 1) / log(2)));

  heap->size = length;
  heap->capacity = heapCapacity;
  heap->array = (int *)malloc(sizeof(int) * heapCapacity);

  for (int i = 0; i < length; i++)
    heap->array[i] = array[i];
  for (int i = length; i < heapCapacity; i++)
    heap->array[i] = 0;

  heapify(heap);

  return heap;
}
void heapInsert(t_heap *heap, int value)
{
  int newSize = heap->size + 1;
  int newHeapCapacity = pow(2, ceil(log(newSize + 1) / log(2)));

  if (newHeapCapacity > heap->capacity)
  {
    heap->array = realloc(heap->array, sizeof(int) * newHeapCapacity);
    heap->capacity = newHeapCapacity;
  }

  heap->size = newSize;
  heap->array[newSize - 1] = value;
  percolateUp(heap, newSize - 1);
}

int heapPoll(t_heap *heap)
{
  int root = heap->array[0];
  int newSize = heap->size - 1;
  int newHeapCapacity = pow(2, ceil(log(newSize + 1) / log(2)));

  heap->array[0] = heap->array[heap->size-1];
  heap->array[heap->size-1] = 0;
  percolateDown(heap, 0);

  if (newHeapCapacity < heap->capacity)
  {
    heap->array = realloc(heap->array, sizeof(int) * newHeapCapacity);
    heap->capacity = newHeapCapacity;
  }
  heap->size = newSize;

  return root;
}

int heapPeek(t_heap *heap)
{
  return heap->array[0];
}

void freeHeap(t_heap *heap)
{
  free(heap->array);
  free(heap);
}

void heapify(t_heap *heap)
{
  int currentIndex = heap->capacity / 2 - 2;

  while (currentIndex >= 0)
  {
    percolateDown(heap, currentIndex);
    currentIndex--;
  }
}

void percolateUp(t_heap *heap, int index)
{
  while (index > 0)
  {
    int parentIndex = (index - 1) / 2;
    int value = heap->array[index];
    int parentValue = heap->array[parentIndex];

    if (parentValue > value)
    {
      heap->array[index] = parentValue;
      heap->array[parentIndex] = value;
      index = parentIndex;
    }
    else
    {
      return;
    }
  }
}

void percolateDown(t_heap *heap, int index)
{
  while ((index * 2 + 2) < heap->capacity)
  {
    int currentValue = heap->array[index];
    int leftChildValue = heap->array[index * 2 + 1];
    int rightChildValue = heap->array[index * 2 + 2];

    if (leftChildValue != 0 && currentValue > leftChildValue && rightChildValue != 0 && currentValue > rightChildValue)
    {
      if (leftChildValue < rightChildValue)
      {
        heap->array[index] = leftChildValue;
        heap->array[index * 2 + 1] = currentValue;
        index = index * 2 + 1;
      }
      else // rightChildValue >= leftChildValue
      {
        heap->array[index] = rightChildValue;
        heap->array[index * 2 + 2] = currentValue;
        index = index * 2 + 2;
      }
    }
    else if (leftChildValue != 0 && currentValue > leftChildValue)
    {
      heap->array[index] = leftChildValue;
      heap->array[index * 2 + 1] = currentValue;
      index = index * 2 + 1;
    }
    else if (rightChildValue != 0 && currentValue > rightChildValue)
    {
      heap->array[index] = rightChildValue;
      heap->array[index * 2 + 2] = currentValue;
      index = index * 2 + 2;
    }
    else // in place
    {
      return;
    }
  }
}
