// Prathak Garg
// Roll No: 202051144
// Date: 24/03/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AES S-box
unsigned char sub[16][16] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

// Inverse S-Box
unsigned char invsub[16][16] = {{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                                {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
                                {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                                {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                                {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                                {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                                {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                                {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                                {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                                {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                                {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                                {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                                {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                                {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                                {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                                {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};

// MixColumns matrix
unsigned char mix[4][4] = {{1, 4, 4, 5},
                           {5, 1, 4, 4},
                           {4, 5, 1, 4},
                           {4, 4, 5, 1}};

// Inverse MixColumns matrix
unsigned char invmix[4][4] = {{165, 7, 26, 115},
                              {115, 165, 7, 26},
                              {26, 115, 165, 7},
                              {7, 26, 115, 165}};

// Round constants
unsigned int rcon[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};

// Helper function to print the text matrix
void printMatrix(unsigned int pt[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%02x ", pt[i][j]);
        printf("\n");
    }
}

// Divide each plaintext byte into two nibbles. Use the first nibble as row index and second nibble as column index to get the corresponding byte from the S-box.
void subbytes(unsigned int pt[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int ii = pt[i][j] >> 4;
            int jj = pt[i][j] & 0b1111;
            pt[i][j] = sub[ii][jj];
        }
    }
}

// Inverse of subbytes. Same as subbytes but use the inverse S-box.
void invSubbytes(unsigned int pt[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int ii = pt[i][j] >> 4;
            int jj = pt[i][j] & 0b1111;
            pt[i][j] = invsub[ii][jj];
        }
    }
}

// Shift the rows of the plaintext matrix by the row number. For example, the first row is not shifted, the second row is shifted by 1, the third row is shifted by 2 and the fourth row is shifted by 3.
void shiftRows(unsigned int pt[4][4]) {
    unsigned int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = pt[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pt[i][j] = temp[i][(j + i) % 4];
        }
    }
}

// Inverse of shiftRows. Same as shiftRows but shift the rows in the opposite direction.
void invShiftRows(unsigned int pt[4][4]) {
    unsigned int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = pt[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pt[i][j] = temp[i][(j - i + 4) % 4];
        }
    }
}

// Helper function to multiply two bytes in GF(2^8) using the irreducible polynomial x^8 + x^4 + x^3 + x + 1.
unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char hi_bit_set;
    for (int i = 0; i < 8; i++) {
        if ((b & 1) == 1) p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80) a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

// Multiply each column of the plaintext matrix with the MixColumns matrix. The result is the new plaintext matrix.
void mixColumns(unsigned int pt[4][4]) {
    unsigned int temp[4][4];

    // Copy the plaintext matrix to a temporary matrix
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            temp[i][j] = pt[i][j];

    // Multiply the temporary matrix with the MixColumns matrix
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++)
            pt[i][j] = gmul(mix[i][0], temp[0][j]) ^ gmul(mix[i][1], temp[1][j]) ^ gmul(mix[i][2], temp[2][j]) ^ gmul(mix[i][3], temp[3][j]);
}

// Inverse of mixColumns. Same as mixColumns but multiply with the inverse MixColumns matrix.
void invMixColumns(unsigned int pt[4][4]) {
    unsigned int temp[4][4];
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            temp[i][j] = pt[i][j];

    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++)
            pt[i][j] = gmul(invmix[i][0], temp[0][j]) ^ gmul(invmix[i][1], temp[1][j]) ^ gmul(invmix[i][2], temp[2][j]) ^ gmul(invmix[i][3], temp[3][j]);
}

// Rotate the word by one byte to the left. For example, if the word is 0x12345678, the rotated word is 0x23456781.
unsigned int rotWord(unsigned int word) {
    return (word << 8) | (word >> 24);
}

// Divide word into 4 bytes and substitute each byte using the S-box as before.
unsigned int subWord(unsigned int word) {
    unsigned int subW = 0;
    for (int i = 0; i < 4; i++) {
        int ii = (word >> (24 - 8 * i) & 0xff) >> 4;
        int jj = (word >> (24 - 8 * i) & 0xff) & 0xf;
        subW |= sub[ii][jj] << (24 - 8 * i);
    }

    return subW;
}

// Generate the round keys from the original key.
void roundKeyGen(unsigned int key[4][4], unsigned int roundKeys[11][4]) {
    unsigned int words[44];

    // For the first 4 words, copy the original key
    for (int i = 0; i < 4; i++) 
        words[i] = key[i][0] << 24 | key[i][1] << 16 | key[i][2] << 8 | key[i][3];
    
    // For the rest of the words, generate the round keys using the previous words
    for (int i = 4; i < 44; i++) {
        unsigned int temp = words[i - 1];
        if (i % 4 == 0) 
            temp = subWord(rotWord(temp)) ^ rcon[i / 4 - 1];

        words[i] = words[i - 4] ^ temp;
    }

    // Copy the round keys to the roundKeys matrix combining 4 words into 1 key
    for (int i = 0; i < 11; i++) 
        for (int j = 0; j < 4; j++) 
            roundKeys[i][j] = words[i * 4 + j];
}

void addRoundKey(unsigned int pt[4][4], unsigned int key[4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pt[i][j] ^= key[i] >> (24 - 8 * j) & 0xff;
        }
    }
}

void AESEncrypt(unsigned int pt[4][4], unsigned int key[4][4]) {
    // Generate the round keys
    unsigned int roundKeys[11][4];
    roundKeyGen(key, roundKeys);

    // For the first 9 rounds, add the round key, substitute bytes (After 2*x+1), shift rows, mix columns, and repeat.
    for (int k = 0; k < 9; k++) {
        // Add the round key
        addRoundKey(pt, roundKeys[k]);

        printf("Round %d: \n", k+1);
        printMatrix(pt);

        // 2*x+1 before subbytes
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                unsigned int msb = pt[i][j] >> 7;
                pt[i][j] = (pt[i][j] << 1) ^ 1;
                if (msb == 1) pt[i][j] ^= 0b100011011;
            }
        }

        // Subbytes as explained above
        printf("\n");
        subbytes(pt);

        printf("Subbytes: \n");
        printMatrix(pt);

        // Shift rows as explained above
        printf("\n");
        shiftRows(pt);

        printf("ShiftRows: \n");
        printMatrix(pt);

        // Mix columns as explained above
        printf("\n");
        mixColumns(pt);

        printf("MixColumns: \n");
        printMatrix(pt);

        printf("\n");
    }

    // For the last round, add the round key, substitute bytes (After 2*x+1), shift rows, and add the last round key. Do not mix columns.
    // Add the round key
    addRoundKey(pt, roundKeys[9]);

    printf("Round 10: \n");
    printMatrix(pt);

    // 2*x+1 before subbytes
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned int msb = pt[i][j] >> 7;
            pt[i][j] = (pt[i][j] << 1) ^ 1;
            if (msb == 1) pt[i][j] ^= 0b100011011;
        }
    }

    // Subbytes as explained above
    printf("\n");
    subbytes(pt);

    printf("Subbytes: \n");
    printMatrix(pt);

    // Shift rows as explained above
    printf("\n");
    shiftRows(pt);

    printf("ShiftRows: \n");
    printMatrix(pt);

    // Add the last round key
    addRoundKey(pt, roundKeys[10]);
    printf("\n");
}

// Decryption is the same as encryption except the order of the round keys is reversed and the mix columns step is omitted in the first decryption round.
void AESDecrypt(unsigned int ct[4][4], unsigned int key[4][4]) {
    // Generate the round keys
    unsigned int roundKeys[11][4];
    roundKeyGen(key, roundKeys);

    // For the first round of decryption, add the round key, inverse shift rows, inverse subbytes, (x-1)/2.
    // Add the round key
    addRoundKey(ct, roundKeys[10]);

    printf("Round 10: \n");
    printMatrix(ct);

    // Inverse shift rows as explained above
    printf("\n");
    invShiftRows(ct);

    printf("InvShiftRows: \n");
    printMatrix(ct);

    // Inverse subbytes as explained above
    printf("\n");
    invSubbytes(ct);

    printf("InvSubbytes: \n");
    printMatrix(ct);

    // (x-1)/2 after inverse subbytes
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned int lsb = ct[i][j] & 1;
            if (lsb == 1) 
                ct[i][j] = ct[i][j] >> 1;
            else
                ct[i][j] = (ct[i][j] ^ 0b100011010) >> 1;
        }
    }

    // For the next 9 rounds of decryption, add the round key, inverse mix columns, inverse shift rows, inverse subbytes, (x-1)/2.
    for (int k = 9; k > 0; k--) {
        // Add the round key
        addRoundKey(ct, roundKeys[k]);

        printf("\nRound %d: \n", k);
        printMatrix(ct);

        // Inverse mix columns as explained above
        printf("\n");
        invMixColumns(ct);

        printf("InvMixColumns: \n");
        printMatrix(ct);

        // Inverse shift rows as explained above
        printf("\n");
        invShiftRows(ct);

        printf("InvShiftRows: \n");
        printMatrix(ct);

        // Inverse subbytes as explained above
        printf("\n");
        invSubbytes(ct);

        printf("InvSubbytes: \n");
        printMatrix(ct);

        // (x-1)/2 after inverse subbytes
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                unsigned int lsb = ct[i][j] & 1;
                if (lsb == 1) 
                    ct[i][j] = ct[i][j] >> 1;
                else
                    ct[i][j] = (ct[i][j] ^ 0b100011010) >> 1;
            }
        }
    }

    printf("\n");
    // Finally, add the first round key.
    addRoundKey(ct, roundKeys[0]);
}

void main() {
    unsigned int pt[4][4], key[4][4];

    // Test Plaintext: 00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff
    // Test Key: 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f

    // Taking plaintext and key as input in 4x4 hexadecimal
    printf("Enter the plaintext: ");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scanf("%x", &pt[j][i]);

    printf("Enter the key: ");
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++)
            scanf("%x", &key[i][j]);

    // Printing the original plaintext
    printf("\nPlaintext: \n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) 
            printf("%02x ", pt[i][j]);
        printf("\n");
    }

    printf("\n");

    AESEncrypt(pt, key);

    printf("====================================\n");
    printf("Encrypted: \n");
    printMatrix(pt);
    printf("====================================\n");

    printf("\n");

    AESDecrypt(pt, key);

    printf("Decrypted: \n");
    printMatrix(pt);

    // Check if the decrypted text is same as the original plaintext
}