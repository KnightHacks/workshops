void swapTwoElements(int *array, int firstIndex, int secondIndex);

void bubbleSort(int *array, int length)
{
  for (int i = 0; i < length - 1; i++)
    for (int j = 0; j < length - i - 1; j++)
      if (*(array + j) > *(array + j + 1))
        swapTwoElements(array, j, j + 1);
}

void swapTwoElements(int *array, int firstIndex, int secondIndex)
{
  int temp = *(array + firstIndex);
  *(array + firstIndex) = *(array + secondIndex);
  *(array + secondIndex) = temp;
}
