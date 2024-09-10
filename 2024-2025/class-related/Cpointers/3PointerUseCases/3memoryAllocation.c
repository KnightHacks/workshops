#include <stdio.h>
#include <stdlib.h>

int main(){
  int X;
  int* array;
  printf("Enter X (size of array): ");
  scanf("%d", &X);
  
  // Requesting to allocate memory for X sized array
  array = (int *) malloc(X * sizeof(int));
  
  for (int i=0; i<X; i++){
    array[i] = i+1;
    printf("%d, ", array[i]); // Prints 1, 2, ... , X
  }
  printf("\n");
  free(array);  // Requesting to free/release the allocated memory
  return 0;
}

