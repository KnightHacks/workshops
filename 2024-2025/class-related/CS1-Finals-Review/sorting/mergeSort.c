#include <math.h>
#include <stdlib.h>

void mergeArrays(int *array, int *arrayA, int lengthA, int *arrayB, int lengthB);

void mergeSort(int *array, int length)
{
  if (length < 2)
    return;

  int mid = floor(length / 2);
  int subLength1 = mid;
  int subLength2 = length - mid;
  int *subArray1 = (int *)malloc(sizeof(int) * subLength1);
  int *subArray2 = (int *)malloc(sizeof(int) * subLength2);

  for (int i = 0; i < mid; i++)
    *(subArray1 + i) = *(array + i);
  for (int i = mid; i < length; i++)
    *(subArray2 + i - mid) = *(array + i);

  mergeSort(subArray1, subLength1);
  mergeSort(subArray2, subLength2);

  mergeArrays(array, subArray1, subLength1, subArray2, subLength2);

  free(subArray1);
  free(subArray2);
}

void mergeArrays(int *array, int *arrayA, int lengthA, int *arrayB, int lengthB)
{
  int i = 0, a = 0, b = 0;

  while (a < lengthA && b < lengthB)
  {
    if (*(arrayA + a) < *(arrayB + b))
      *(array + i++) = *(arrayA + a++);
    else
      *(array + i++) = *(arrayB + b++);
  }

  while (a < lengthA)
    *(array + i++) = *(arrayA + a++);

  while (b < lengthB)
    *(array + i++) = *(arrayB + b++);
}
