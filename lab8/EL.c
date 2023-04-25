#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define PRIME 173
#define A 23
#define B 11

uint32_t H[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

uint32_t K[] = {
    0b01000010100010100010111110011000, 0b01110001001101110100010010010001, 0b10110101110000001111101111001111, 0b11101001101101011101101110100101,
    0b00111001010101101100001001011011, 0b01011001111100010001000111110001, 0b10010010001111111000001010100100, 0b10101011000111000101111011010101,
    0b11011000000001111010101010011000, 0b00010010100000110101101100000001, 0b00100100001100011000010110111110, 0b01010101000011000111110111000011,
    0b01110010101111100101110101110100, 0b10000000110111101011000111111110, 0b10011011110111000000011010100111, 0b11000001100110111111000101110100,
    0b11100100100110110110100111000001, 0b11101111101111100100011110000110, 0b00001111110000011001110111000110, 0b00100100000011001010000111001100,
    0b00101101111010010010110001101111, 0b01001010011101001000010010101010, 0b01011100101100001010100111011100, 0b01110110111110011000100011011010,
    0b10011000001111100101000101010010, 0b10101000001100011100011001101101, 0b10110000000000110010011111001000, 0b10111111010110010111111111000111,
    0b11000110111000000000101111110011, 0b11010101101001111001000101000111, 0b00000110110010100110001101010001, 0b00010100001010010010100101100111,
    0b00100111101101110000101010000101, 0b00101110000110110010000100111000, 0b01001101001011000110110111111100, 0b01010011001110000000110100010011,
    0b01100101000010100111001101010100, 0b01110110011010100000101010111011, 0b10000001110000101100100100101110, 0b10010010011100100010110010000101,
    0b10100010101111111110100010100001, 0b10101000000110100110011001001011, 0b11000010010010111000101101110000, 0b11000111011011000101000110100011,
    0b11010001100100101110100000011001, 0b11010110100110010000011000100100, 0b11110100000011100011010110000101, 0b00010000011010101010000001110000,
    0b00011001101001001100000100010110, 0b00011110001101110110110000001000, 0b00100111010010000111011101001100, 0b00110100101100001011110010110101,
    0b00111001000111000000110010110011, 0b01001110110110001010101001001010, 0b01011011100111001100101001001111, 0b01101000001011100110111111110011,
    0b01110100100011111000001011101110, 0b01111000101001010110001101101111, 0b10000100110010000111100000010100, 0b10001100110001110000001000001000,
    0b10010000101111101111111111111010, 0b10100100010100000110110011101011, 0b10111110111110011010001111110111, 0b11000110011100010111100011110010
};

uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
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
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Curve -> y^2 = x^3 + A*x + B

typedef struct point {
    int x;
    int y;
} point;

void print_hex(uint32_t arr[8]) {
    for (int i = 0; i < 8; i++) {
        uint8_t *p = (uint8_t *)&arr[i];
        printf("%02x %02x %02x %02x ", p[3], p[2], p[1], p[0]);
        // printf("%08x ", arr[i]);
    }
    printf("\n");
}

point generate_point() {
    point alpha;
    srand(time(NULL));
    
    while ((alpha.y * alpha.y) % PRIME != (alpha.x * alpha.x * alpha.x + A * alpha.x + B) % PRIME) {
        alpha.x = rand() % PRIME;
        for (int i = 0; i < PRIME; i++) {
            if ((i * i) % PRIME == (alpha.x * alpha.x * alpha.x + A * alpha.x + B) % PRIME) {
                alpha.y = i;
                break;
            }
        }
    }

    return alpha;
}

int add_inv(int n) {
    return PRIME - n;
}

int mult_inv(int n) {
    for (int i = 0; i < PRIME; i++) {
        if ((n * i) % PRIME == 1) {
            return i;
        }
    }
}

point add_point(point p1, point p2) {
    point p3;

    if (p1.x == 0 && p1.y == 0) {
        p3.x = p2.x;
        p3.y = p2.y;
        return p3;
    } else if (p2.x == 0 && p2.y == 0) {
        p3.x = p1.x;
        p3.y = p1.y;
        return p3;
    }
    
    if (p1.x == p2.x && p1.y == p2.y) {
        int m = ((3 * p1.x * p1.x + A) * mult_inv(2 * p1.y)) % PRIME;
        p3.x = (m * m - 2 * p1.x) % PRIME;
        p3.y = (m * (p1.x - p3.x) - p1.y) % PRIME;
    } else if (p1.x == p2.x && p1.y == add_inv(p2.y)) {
        p3.x = 0;
        p3.y = 0;
    } else {
        int m = ((p2.y - p1.y) * mult_inv(PRIME + p2.x - p1.x)) % PRIME;
        if (m < 0) {
            m += PRIME;
        }
        p3.x = (m * m - p1.x - p2.x) % PRIME;
        p3.y = (m * (p1.x - p3.x) - p1.y) % PRIME;
    }

    if (p3.x < 0) {
        p3.x += PRIME;
    }

    if (p3.y < 0) {
        p3.y += PRIME;
    }

    return p3;
}

point multiply_point(point p, int n) {
    point p1 = p;
    for (int i = 1; i < n; i++) {
        p1 = add_point(p1, p);
    }

    return p1;
}

uint32_t rotr(uint32_t n, int d) {
    return (n >> d) | (n << (32 - d));
}

uint32_t shr(uint32_t n, int d) {
    return n >> d;
}

uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ ((~x) & z);
}

void sha256(point sk, uint32_t hash[8]) {
    uint8_t sk_x = (uint8_t) sk.x;
    uint8_t sk_y = (uint8_t) sk.y;
    
    uint8_t input[64] = {0};
    input[0] = sk_x;
    input[1] = sk_y;
    input[2] = 0x80;
    input[63] = 0x10;

    uint32_t w[64] = {0};
    for (int i = 0; i < 16; i++) {
        w[i] = (input[4 * i] << 24) | (input[4 * i + 1] << 16) | (input[4 * i + 2] << 8) | (input[4 * i + 3]);
    }
    
    uint32_t s0, s1;
    for (int i = 16; i < 64; i++) {
        s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ shr(w[i - 15], 3);
        s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ shr(w[i - 2], 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    uint32_t a, b, c, d, e, f, g, h;
    a = H[0]; b = H[1]; c = H[2]; d = H[3]; e = H[4]; f = H[5]; g = H[6]; h = H[7];

    uint32_t t1, t2;
    uint32_t maj;

    for (int i = 0; i < 64; i++) {
        s1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
        t1 = h + s1 + ch(e, f, g) + K[i] + w[i];
        s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
        maj = (a & b) ^ (a & c) ^ (b & c);
        t2 = s0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    hash[0] = a + H[0]; hash[1] = b + H[1]; hash[2] = c + H[2]; hash[3] = d + H[3];
    hash[4] = e + H[4]; hash[5] = f + H[5]; hash[6] = g + H[6]; hash[7] = h + H[7];
}

void aes256_key_expansion(uint8_t key[32], uint8_t key_schedule[15][16]) {
    uint8_t rcon[15] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a};
    uint8_t temp[4];

    for (int i = 0; i < 8; i++) {
        key_schedule[0][4 * i] = key[4 * i];
        key_schedule[0][4 * i + 1] = key[4 * i + 1];
        key_schedule[0][4 * i + 2] = key[4 * i + 2];
        key_schedule[0][4 * i + 3] = key[4 * i + 3];
    }

    for (int i = 8; i < 60; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j] = key_schedule[(i - 1) / 4][4 * ((i - 1) % 4) + j];
        }

        if (i % 8 == 0) {
            uint8_t t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];

            temp[0] ^= rcon[i / 8 - 1];
        } else if (i % 8 == 4) {
            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];
        }

        for (int j = 0; j < 4; j++) {
            key_schedule[i / 4][4 * (i % 4) + j] = key_schedule[(i - 8) / 4][4 * ((i - 8) % 4) + j] ^ temp[j];
        }
    }
}

void aes256_cbc_encrypt(uint8_t msg[32], uint8_t key[32], uint8_t iv[16], uint8_t cipher[32]) {
    uint8_t key_schedule[15][16] = {0};
    aes256_key_expansion(key, key_schedule);

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%02x ", key_schedule[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // uint8_t block[16];
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 16; j++) {
    //         block[j] = msg[16 * i + j] ^ iv[j];
    //     }

    //     aes256_encrypt(block, key_schedule, cipher + 16 * i);
    //     for (int j = 0; j < 16; j++) {
    //         iv[j] = cipher[16 * i + j];
    //     }
    // }
}


int main() {
    // point alpha = generate_point();
    point alpha = {88, 26};
    printf("alpha = (%d, %d)\n", alpha.x, alpha.y);

    uint8_t a_pk, b_pk;
    printf("Enter private key of Alice (1-150): ");
    // scanf("%hhd", &a_pk);
    printf("45\n"); a_pk = 45;
    
    printf("Enter private key of Bob (1-150): ");
    // scanf("%hhd", &b_pk);
    printf("65\n"); b_pk = 65;
    
    point a_pk_p = multiply_point(alpha, a_pk);
    point b_pk_p = multiply_point(alpha, b_pk);

    printf("Alice's public key = (%d, %d)\n", a_pk_p.x, a_pk_p.y);
    printf("Bob's public key = (%d, %d)\n", b_pk_p.x, b_pk_p.y);

    point a_sk_p = multiply_point(b_pk_p, a_pk);
    printf("\n");
    point b_sk_p = multiply_point(a_pk_p, b_pk);

    printf("Alice's shared key = (%d, %d)\n", a_sk_p.x, a_sk_p.y);
    printf("Bob's shared key = (%d, %d)\n", b_sk_p.x, b_sk_p.y);

    printf("\n");

    uint32_t a_hash[8];
    sha256(a_sk_p, a_hash);
    uint32_t b_hash[8];
    sha256(b_sk_p, b_hash);

    printf("Alice's hash = ");
    print_hex(a_hash);

    printf("Bob's hash = ");
    print_hex(b_hash);

    printf("\n");

    uint8_t a_msg[32];
    printf("Enter Alice's message (32 bytes): ");
    // for (int i = 0; i < 32; i++) {
    //     scanf("%hhx", &a_msg[i]);
    // }
    for (int i = 0; i < 16; i++) {
        a_msg[i] = 17*i;
        a_msg[i + 16] = 17*i;
    }

    for (int i = 0; i < 32; i++) {
        printf("%02hhx", a_msg[i]);
    }
    printf("\n");

    uint8_t a_cipher[32];
    uint8_t a_iv[16] = {0};
    uint8_t a_key[32];
    for (int i = 0; i < 8; i++) {
        a_key[4 * i] = a_hash[i] >> 24;
        a_key[4 * i + 1] = a_hash[i] >> 16;
        a_key[4 * i + 2] = a_hash[i] >> 8;
        a_key[4 * i + 3] = a_hash[i];
    }

    aes256_cbc_encrypt(a_msg, a_key, a_iv, a_cipher);

    return 0;
}