#include <stdio.h>

void swapTwoElements(int *array, int a, int b);
int generatePartition(int *array, int startIndex, int endIndex);
int placePartition(int *array, int partitionIndex, int startIndex, int endIndex);
void quickSortUtil(int *array, int startIndex, int endIndex);

void quickSort(int *array, int length)
{
  quickSortUtil(array, 0, length - 1);
}

void quickSortUtil(int *array, int startIndex, int endIndex)
{
  if (startIndex >= endIndex)
    return;

  int partitionIndex = generatePartition(array, startIndex, endIndex);

  partitionIndex = placePartition(array, partitionIndex, startIndex, endIndex);

  quickSortUtil(array, startIndex, partitionIndex - 1);
  quickSortUtil(array, partitionIndex + 1, endIndex);
}

int generatePartition(int *array, int startIndex, int endIndex)
{
  int middle = (startIndex + endIndex) / 2;
  return middle;
}

// partition index must be in correct spot after calling this function
int placePartition(int *array, int partitionIndex, int startIndex, int endIndex)
{
  swapTwoElements(array, partitionIndex, startIndex);
  partitionIndex = startIndex;
  startIndex++;

  while (startIndex <= endIndex)
  {
    while (startIndex <= endIndex && *(array + partitionIndex) >= *(array + startIndex))
      startIndex++;
    while (startIndex <= endIndex && *(array + partitionIndex) < *(array + endIndex))
      endIndex--;

    if (startIndex < endIndex)
      swapTwoElements(array, startIndex, endIndex);
  }
  swapTwoElements(array, partitionIndex, endIndex);
  return endIndex;
}

void swapTwoElements(int *array, int a, int b)
{
  int temp = *(array + a);
  *(array + a) = *(array + b);
  *(array + b) = temp;
}
