#include <stdio.h>

int main(){
  int a = 5;
  double b = 0.2;
  char c = 'c';

  int* x;     // int* x = &a;     // Can also initialize
  double* y;  // double* y = &b;     // Can also initialize
  char* z;    // char* z = &c;     // Can also initialize

  x = &a;
  y = &b;
  z = &c;

  printf("%d\n", *x); // Prints "5"
  printf("%f\n", *y); // Prints "0.2"
  printf("%c\n", *z); // Prints 'c'
  return 0;
}
