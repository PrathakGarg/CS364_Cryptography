#include <stdio.h>
#include <string.h>

void main() {
    char ciphertext[100];
    int shift;

    printf("Enter ciphertext: ");
    scanf("%s", ciphertext);

    printf("Enter shift: ");
    scanf("%d", &shift);

    char plaintext[strlen(ciphertext)];

    for (int i=0; i < strlen(ciphertext); i++) {
        int temp = tolower(ciphertext[i]);
        temp = temp - 'a';
        temp = (temp + 26 - shift) % 26;
        temp = temp + 'a';
        plaintext[i] = temp;
    }
    plaintext[strlen(ciphertext)] = '\0';

    printf("Plaintext: %s\n", plaintext);
}

// a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z