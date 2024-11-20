#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selectionSort.h"
#include "bubbleSort.h"
#include "insertionSort.h"
#include "mergeSort.h"
#include "quickSort.h"

int main(int argc, char **argv)
{
  FILE *fp;
  char buffer[16], c;
  int arrayLength;
  int temp;
  int *array;

  for (int i = 1; i < argc; i++)
  {
    fp = fopen(*(argv + i), "r");

    fscanf(fp, "%d\n", &arrayLength);
    array = (int *)malloc(arrayLength * sizeof(int));

    for (int i = 0; i < arrayLength; i++)
    {
      fscanf(fp,"%s, ", buffer);
      sscanf(buffer, "%d", array+i);
    }

    printf("\nBefore the sort:\n---------------\n");
    for (int i=0; i< arrayLength; i++)
    {
      printf("%d\n", array[i]);
    }

    /* The 5 sorting algorithms */ 
    // selectionSort(array, arrayLength);
    // bubbleSort(array, arrayLength);
    // insertionSort(array, arrayLength);
    // mergeSort(array, arrayLength);
    quickSort(array, arrayLength);

    printf("\nAfter the sort:\n--------------\n");
    for (int i=0; i< arrayLength; i++)
    {
      printf("%d\n", array[i]);
    }

    free(array);
    fclose(fp);
  }
  return 0;
}
