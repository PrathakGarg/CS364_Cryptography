#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

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

void main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int a, b;

    scanf("%s\n", plaintext);
    scanf("%d %d", &a, &b);
    assert(gcd(a, 26) == 1);

    for (int i=0; i<strlen(plaintext); i++) {
        ciphertext[i] = (((tolower(plaintext[i]) - 'a') * a) + b) % 26 + 'a';
        decrypted[i] = ((tolower(ciphertext[i]) - 'a' + 26 - b) * inverse(a)) % 26 + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
    decrypted[strlen(plaintext)] = '\0';

    printf("%s\n%s\n", ciphertext, decrypted);
}