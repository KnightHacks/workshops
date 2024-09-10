#include <stdio.h>

int main(){
  // Int Example
  int x;
  x = 5;

  int* y;
  y = &x;

  int** z;
  z = &y;

  printf("%d\n", x);    // prints "5"
  printf("%d\n", *y);   // prints "5"
  printf("%d\n\n", **z);  // prints "5"
  
  // Float Example
  float a;
  a = 0.2;

  float* b;
  b = &a;

  float** c;
  c = &b;

  printf("%f\n", a);    // prints "0.2"
  printf("%f\n", *b);   // prints "0.2"
  printf("%f\n", **c);  // prints "0.2"

  return 0;
}
