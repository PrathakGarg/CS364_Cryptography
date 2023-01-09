#include <stdio.h>
#include <ctype.h>
#include <string.h>

void main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    char shift;
    scanf("%s", plaintext);
    scanf("\n%c", &shift);
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = (tolower(plaintext[i]) - 'a' + tolower(shift) - 'a') % 26 + 'a';
        decrypted[i] = (ciphertext[i] - 'a' - tolower(shift) + 'a' + 26) % 26 + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
    decrypted[strlen(plaintext)] = '\0';
    printf("Ciphertext: %s\nDecrypted: %s\n", ciphertext, decrypted);
}