#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char plaintext[], char shift, char ciphertext[]) {
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = (tolower(plaintext[i]) - 'a' + tolower(shift) - 'a') % 26 + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(char ciphertext[], char shift, char decrypted[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        decrypted[i] = (ciphertext[i] - 'a' - tolower(shift) + 'a' + 26) % 26 + 'a';
    }
    decrypted[strlen(ciphertext)] = '\0';
}

void main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    char shift;
    scanf("%s", plaintext);
    scanf("\n%c", &shift);
    
    encrypt(plaintext, shift, ciphertext);
    decrypt(ciphertext, shift, decrypted);

    printf("Ciphertext: %s\nDecrypted: %s\n", ciphertext, decrypted);
}