#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long int square_and_multiply(int x, int pow) {
    long int result = 1;
    while (pow > 0) {
        if (pow % 2 == 1) 
            result *= x;
        x *= x;
        pow /= 2;
    }

    return result;
}

int main() {
    int x, pow;
    printf("Enter x and pow: ");
    scanf("%d %d", &x, &pow);
    printf("%d ^ %d = %ld\n", x, pow, square_and_multiply(x, pow));
    return 0;
}