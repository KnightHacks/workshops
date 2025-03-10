#include <stdio.h>
void doubleValue(int val);

int main(){
  int a = 5;
  doubleValue(a);
  printf("%d\n", a); // Prints "5"
  return 0;
}

void doubleValue(int val){
  val = val * 2;
}
