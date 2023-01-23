#include <stdio.h>
#include <string.h>
#include <ctype.h>

void adjustPlaintext(char pt[]) {
    for (int i = 0; pt[i] != '\0'; i++) {
        if (pt[i] == 'j') {
            pt[i] = 'i';
        }

        if (pt[i] == pt[i + 1]) {
            for (int j = strlen(pt); j > i; j--) {
                pt[j + 1] = pt[j];
            }

            if (pt[i] == 'x') {
                pt[i + 1] = 'q';
            } else {
                pt[i + 1] = 'x';
            }
        }

        if (pt[i + 1] == '\0' && i % 2 == 0) {
            if (pt[i] == 'x') {
                pt[i + 1] = 'q';
            } else {
                pt[i + 1] = 'x';
            }
        }
    }
}

void adjustKey(char key[]) {
    for (int i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'j') {
            key[i] = 'i';
        }

        if (key[i] == ' ') {
            for (int j = i; key[j] != '\0'; j++) {
                key[j] = key[j + 1];
            }
            i--;
        }
    }

    for (int i = 0; key[i] != '\0'; i++) {
        for (int j = i + 1; key[j] != '\0'; j++) {
            if (key[i] == key[j]) {
                for (int k = j; key[k] != '\0'; k++) {
                    key[k] = key[k + 1];
                }
                j--;
            }
        }
    }
}

void generateCipher(char key[], char cipher[5][5]) {
    char alphabet[26] = "abcdefghiklmnopqrstuvwxyz";

    for (int i = 0; key[i] != '\0'; i++) {
        for (int j = 0; alphabet[j] != '\0'; j++) {
            if (key[i] == alphabet[j]) {
                for (int k = j; alphabet[k] != '\0'; k++) {
                    alphabet[k] = alphabet[k + 1];
                }
                j--;
            }
        }
    }

    for (int i = 0; key[i] != '\0'; i++) {
        cipher[i / 5][i % 5] = key[i];
    }

    for (int i = 0; alphabet[i] != '\0'; i++) {
        cipher[(i + strlen(key)) / 5][(i + strlen(key)) % 5] = alphabet[i];
    }
}

void encryptPlayfair(char pt[], char cipher[5][5], char ct[]) {
    for (int i = 0; pt[i] != '\0'; i += 2) {
        int row1, row2, col1, col2;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (pt[i] == cipher[j][k]) {
                    row1 = j;
                    col1 = k;
                }
                if (pt[i + 1] == cipher[j][k]) {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        if (row1 == row2) {
            ct[i] = cipher[row1][(col1 + 1) % 5];
            ct[i + 1] = cipher[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ct[i] = cipher[(row1 + 1) % 5][col1];
            ct[i + 1] = cipher[(row2 + 1) % 5][col2];
        } else {
            ct[i] = cipher[row1][col2];
            ct[i + 1] = cipher[row2][col1];
        }
    }

    ct[strlen(pt)] = '\0';
}

void decryptPlayfair(char ct[], char cipher[5][5], char pt[]) {
    for (int i = 0; ct[i] != '\0'; i += 2) {
        int row1, row2, col1, col2;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (ct[i] == cipher[j][k]) {
                    row1 = j;
                    col1 = k;
                }
                if (ct[i + 1] == cipher[j][k]) {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        if (row1 == row2) {
            pt[i] = cipher[row1][(col1 + 4) % 5];
            pt[i + 1] = cipher[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            pt[i] = cipher[(row1 + 4) % 5][col1];
            pt[i + 1] = cipher[(row2 + 4) % 5][col2];
        } else {
            pt[i] = cipher[row1][col2];
            pt[i + 1] = cipher[row2][col1];
        }
    }

    pt[strlen(ct)] = '\0';
}

int gcd(int a, int b) {
    int ans=1;
    for (int i=2; i<a || i<b; i++) {
        if (a%i == 0 && b%i == 0) ans = i;
    }

    return ans;
}

int inverse(int a) {
    for (int i=1; i<26; i++) {
        if (((a*i) % 26) == 1) return i;
    }
}

void encryptAffine(char plaintext[], int a, int b, char ciphertext[]) {
    for (int i=0; i<strlen(plaintext); i++) {
        ciphertext[i] = (((tolower(plaintext[i]) - 'a') * a) + b) % 26 + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decryptAffine(char ciphertext[], int a, int b, char decrypted[]) {
    for (int i=0; i<strlen(ciphertext); i++) {
        decrypted[i] = ((tolower(ciphertext[i]) - 'a' + 26 - b) * inverse(a)) % 26 + 'a';
    }
    decrypted[strlen(ciphertext)] = '\0';
}

void encryptShift(char plaintext[], char shift, char ciphertext[]) {
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = (tolower(plaintext[i]) - 'a' + tolower(shift) - 'a') % 26 + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decryptShift(char ciphertext[], char shift, char decrypted[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        decrypted[i] = (ciphertext[i] - 'a' - tolower(shift) + 'a' + 26) % 26 + 'a';
    }
    decrypted[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[100], key[100], cipher[5][5];

    printf("Enter plaintext: ");
    scanf("%s", plaintext);
    scanf("%*c");

    printf("Enter key: ");
    scanf("%[^\n]s", key);

    adjustPlaintext(plaintext);
    printf("\nFormatted plaintext: %s\n", plaintext);

    adjustKey(key);
    printf("Formatted key: %s\n", key);

    generateCipher(key, cipher);
    printf("\nCipher: \n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", cipher[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    char ciphertext[strlen(plaintext)];
    encryptPlayfair(plaintext, cipher, ciphertext);
    printf("Ciphertext (Playfair): %s\n", ciphertext);

    int a=11, b=15;
    
    encryptAffine(ciphertext, a, b, ciphertext);
    printf("\nCiphertext (Playfair + Affine): %s\n", ciphertext);

    char shift;
    printf("\nEnter shift (char): ");
    scanf(" %c", &shift);

    encryptShift(ciphertext, shift, ciphertext);
    printf("\nCiphertext (Playfair + Affine + Shift): %s\n", ciphertext);

    char decrypted[strlen(ciphertext)];

    decryptShift(ciphertext, shift, decrypted); 
    printf("\nDecrypted (Shift): %s\n", decrypted);

    decryptAffine(decrypted, a, b, decrypted);
    printf("\nDecrypted (Affine): %s\n", decrypted);

    decryptPlayfair(decrypted, cipher, decrypted);
    printf("\nDecrypted (Playfair): %s -> Original Input (Formatted)\n", decrypted);
}