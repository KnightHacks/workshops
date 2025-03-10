#include <stdio.h>

int main(){
  int arr[3] = {0, 1, 2};

  printf("%p\n", arr);            // prints same address as line below
  printf("%p\n\n", &(arr[0]));    // prints same address as line above

  printf("%d\n", *(arr+0));       // prints "0"
  printf("%d\n", *(arr+1));       // prints "1"
  printf("%d\n\n", *(arr+2));     // prints "2"

  printf("%d\n", arr[0]);         // prints "0"
  printf("%d\n", arr[1]);         // prints "1"
  printf("%d\n", arr[2]);         // prints "2"
  
  return 0;
}
