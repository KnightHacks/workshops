#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Error: Missing filename as an argument\n");
    return -1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("Error: File not found. Filename likely wrong\n");
    return -1;
  }

  int arrayLength;
  int *array;
  fscanf(fp, "%d", &arrayLength);

  if (arrayLength <= 0)
  {
    printf("Error: Given array length in input file is not valid\n");
    fclose(fp);
    return -1;
  }

  array = (int *)malloc(arrayLength * sizeof(int));
  for (int i = 0; i < arrayLength; i++)
    fscanf(fp, "%d,", &array[i]);

  t_heap *heap = createHeap(array, arrayLength);

  int newElementsCount, currentElement;
  
  fscanf(fp, "%d", &newElementsCount);
  for (int i = 0; i < newElementsCount; i++)
  {
    fscanf(fp, "%d,", &currentElement);
    heapInsert(heap, currentElement);
    // printf("s: %d, c: %d\n", heap->size, heap->capacity);
  }

  int numRemovals = heap->size;
  for (int i = 0; i < numRemovals; i++)
  {
    int polledVal = heapPoll(heap);
    printf("%d ", polledVal);
    // printf("s: %d, c: %d\n", heap->size, heap->capacity);
  }
  printf("\n");

  freeHeap(heap);
  fclose(fp);
  return 0;
}
