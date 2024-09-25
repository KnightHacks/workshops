#include <stdio.h>

void debuggerExample() {
    int x = 10;
    int y = 20;
    int sum = x + y;

    printf("The sum of %d and %d is %d\n", x, y, sum);

    for (int i = 0; i < 5; i++) {
        printf("i = %d\n", i);
    }
}

int main() {
    debuggerExample();

    return 0;
}