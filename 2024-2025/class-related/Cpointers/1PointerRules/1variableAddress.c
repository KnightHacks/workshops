#include <stdio.h>

int main(){
  int a = 5;
  // %d prints address in a decimal representation
  printf("%d\n", &a); // Prints address of integer a
  double b = 0.2;
  // %p prints address in a hex representation
  printf("%p\n", &b); // Prints address of double b
  char c = 'c';
  printf("%p\n", &c); // Prints address of char c
  int arr[2] = {1,2};
  printf("%p\n", &arr); // Prints address of integer array arr
  return 0;
}
