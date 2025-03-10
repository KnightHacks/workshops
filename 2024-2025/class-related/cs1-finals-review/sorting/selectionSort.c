void swapTwoElements(int *arr, int indexFirst, int indexSecond);

void selectionSort(int *arr, int length)
{
  int min, minIndex = 0;

  for (int i = 0; i < length; i++)
  {
    min = 2147483627;
    for (int j=i; j< length; j++)
    {
      if (*(arr+j) < min)
      {
        min = *(arr+j);
        minIndex = j;
      }
    }
    swapTwoElements(arr, minIndex, i);
  }
}

void swapTwoElements(int *arr, int indexFirst, int indexSecond)
{
  int temp = *(arr + indexFirst);
  *(arr + indexFirst) = *(arr + indexSecond);
  *(arr + indexSecond) = temp;
}
