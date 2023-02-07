#include <stdio.h>
#include <math.h>

unsigned long *splitText(unsigned long long pt, unsigned long ptArray[2]) {
    ptArray[0] = pt >> 32;
    ptArray[1] = pt & 0xFFFFFFFF;
    return ptArray;
}

unsigned long encFunc(unsigned long key, unsigned long r) {
    unsigned long long tempEnc = (r ^ key)*(r ^ key);
    unsigned long enc = tempEnc & 0xFFFFFFFF;
    return enc;
}

unsigned long long combineText(unsigned long l, unsigned long r) {
    unsigned long long ct = (l << 32) | r;
    return ct;
}

unsigned long long encryptFiestel(unsigned long long pt, unsigned long key) {
    unsigned long splitPt[2];
    splitText(pt, splitPt);
    unsigned long l0 = splitPt[0], r0 = splitPt[1];

    unsigned long l1 = r0, r1 = l0 ^ encFunc(key, r0);

    unsigned long long ct = combineText(l1, r1);
    return ct;
}

unsigned long long decryptFiestel(unsigned long long ct, unsigned long key) {
    unsigned long splitCt[2];
    splitText(ct, splitCt);
    unsigned long l1 = splitCt[0], r1 = splitCt[1];

    unsigned long r0 = l1, l0 = r1 ^ encFunc(key, l1);

    unsigned long long pt = combineText(l0, r0);
    return pt;
}

void main() {
    unsigned long long plaintext, ciphertext;

    printf("Enter plaintext: ");
    scanf("%llu", &plaintext);
    
    unsigned long key;
    printf("Enter key: ");
    scanf("%lu", &key);

    ciphertext = encryptFiestel(plaintext, key);
    printf("Ciphertext: %llu\n", ciphertext);

    plaintext = decryptFiestel(ciphertext, key);
    printf("Plaintext: %llu\n", plaintext);
}
