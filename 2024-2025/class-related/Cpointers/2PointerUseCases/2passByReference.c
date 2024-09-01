#include <stdio.h>
void doubleValue(int* val);

int main(){
  int a = 5;
  int* b;
  b = &a;
  doubleValue(b);
  printf("%d\n", a); // Prints "10" !!!
  return 0;
}

void doubleValue(int* val){
  *val = *val * 2;
}
