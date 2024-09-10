#include <stdio.h>

int main(){
  int a[5][5][5][5];

  for(int i=0; i<5; i++)
    for (int j=0; j<5; j++)
      for (int k=0; k<5; k++)
        for (int l=0; l<5; l++)
          a[i][j][k][l] = i*1000 + j*100 + k*10 + l*1;

  printf("%d\n", a[1][2][3][4]);
  printf("%d\n", 0);

  return 0;
}
