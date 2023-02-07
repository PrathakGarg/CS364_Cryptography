#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

int rounds = 5;
uint16_t SBOX[16] = {0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7};
uint16_t PBOX[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
uint16_t SINV[16] = {0xE, 0x3, 0x4, 0x8, 0x1, 0xC, 0xA, 0xF, 0x7, 0xD, 0x9, 0x6, 0xB, 0x2, 0x0, 0x5};   
uint16_t PINV[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

uint16_t* keyGen(uint32_t key) {
    uint16_t *roundKeys = (uint16_t*) malloc(rounds * sizeof(uint16_t));

    // Get the 16-bit round keys from the 32-bit key, by shifting the key to the right by 4*(4-i) bits
    for (int i = 0; i < rounds; i++) {roundKeys[i] = (key >> 4*(4-i)) & 0xFFFF;}
    return roundKeys;
}

uint16_t subBytes(uint16_t pt, uint16_t *SBOX) {
    uint16_t ct = 0;
    for (int i = 0; i < 4; i++) {
        // For each hex bit in the plaintext, get the corresponding value from the SBOX
        int curr = (pt >> 4*(3-i)) & 0xF;
        ct |= SBOX[curr] << 4*(3-i);
    }

    return ct;
}

uint16_t permute(uint16_t pt, uint16_t *PBOX) {
    uint16_t ct = 0;
    for (int i = 0; i < 16; i++) {
        // For each bit in the plaintext, shift it to the right by the index of the bit in the permutation box
        ct |= (((pt >> (16 - PBOX[i])) & 1) << (16-i-1));
    }

    return ct;
}

uint16_t encrypt(uint16_t pt, uint32_t key) {
    uint16_t *roundKeys = keyGen(key);
    uint16_t ct = pt;

    // For each round (except the last 2) -> XOR, Sub, Permute
    for (int i = 0; i < rounds-2; i++) {
        ct ^= roundKeys[i];
        printf("XOR-ed %d: %hx\n", i+1, ct);
        ct = subBytes(ct, SBOX);
        printf("SubBytes %d: %hx\n", i+1, ct);
        ct = permute(ct, PBOX);
        printf("Permuted %d: %hx\n\n", i+1, ct);
    }

    // For the second last round -> XOR, Sub
    ct ^= roundKeys[rounds-2];
    printf("XOR-ed %d: %hx\n", rounds-1, ct);
    ct = subBytes(ct, SBOX);
    printf("SubBytes %d: %hx\n\n", rounds-1, ct);

    // For the last round only -> XOR with key
    ct ^= roundKeys[rounds-1];
    printf("XOR-ed %d: %hx\n\n", rounds, ct);

    return ct;
}

// Encryption is the same as decryption, except the order of the rounds is reversed
uint16_t decrypt(uint16_t ct, uint32_t key) {
    uint16_t *roundKeys = keyGen(key);
    uint16_t pt = ct;

    pt ^= roundKeys[rounds-1];
    printf("XOR-ed %d: %hx\n\n", rounds, pt);

    pt = subBytes(pt, SINV);
    printf("SubBytes %d: %hx\n\n", rounds-1, pt);
    pt ^= roundKeys[rounds-2];
    printf("XOR-ed %d: %hx\n", rounds-1, pt);

    for (int i = rounds-3; i >= 0; i--) {
        pt = permute(pt, PINV);
        printf("Permuted %d: %hx\n", i+2, pt);
        pt = subBytes(pt, SINV);
        printf("SubBytes %d: %hx\n", i+1, pt);
        pt ^= roundKeys[i];
        printf("XOR-ed %d: %hx\n\n", i+1, pt);
    }

    return pt;
}

void main() {
    uint16_t pt;
    uint32_t key;

    printf("Enter the plaintext (16-bit hex): ");
    scanf("%hx", &pt);

    printf("Enter the key (32-bit hex): ");
    scanf("%x", &key);

    printf("\n");
    uint16_t ct = encrypt(pt, key);
    printf("---------------------------\n");
    printf("| The ciphertext is: %hx |\n", ct);
    printf("---------------------------\n");

    printf("\n");
    uint16_t decrypted = decrypt(ct, key);
    printf("--------------------------\n");
    printf("| The plaintext is: %hx |\n", decrypted);
    printf("--------------------------\n");
}