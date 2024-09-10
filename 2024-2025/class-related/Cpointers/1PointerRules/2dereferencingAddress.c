#include <stdio.h>

int main(){
  int a = 5;
  printf("%d\n", *(&a)); // Prints "5", Dereferencing the address of a
  double b = 0.2;
  printf("%f\n", *(&b)); // Prints "0.2", Dereferencing the address of b
  char c = 'c';
  printf("%c\n", *&c); // Prints 'c', Dereferencing the address of c
  // Notice how we are not touching arrays for now…
  return 0;
}
