void swapTwoElements(int *array, int firstIndex, int secondIndex);

void insertionSort(int *array, int length)
{
  if (length == 0 || length == 1)
    return;
  
  // cur = 1
  // [2, 1, 6, 4, 5, 3]
  for (int i = 1; i < length; i++)
    for (int j = i-1; j>=0; j--)
    {
      if (*(array+j)>*(array+j+1))
        swapTwoElements(array, j, j+1);
      else
        break;
    }
}

void swapTwoElements(int *array, int firstIndex, int secondIndex)
{
  int temp = *(array + firstIndex);
  *(array + firstIndex) = *(array + secondIndex);
  *(array + secondIndex) = temp;
}
