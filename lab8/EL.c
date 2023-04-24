#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define PRIME 173
#define a 23
#define b 11

// Curve -> y^2 = x^3 + a*x + b

typedef struct point {
    int x;
    int y;
} point;

point generate_point() {
    point alpha;
    srand(time(NULL));
    
    while ((alpha.y * alpha.y) % PRIME != (alpha.x * alpha.x * alpha.x + a * alpha.x + b) % PRIME) {
        alpha.x = rand() % PRIME;
        for (int i = 0; i < PRIME; i++) {
            if ((i * i) % PRIME == (alpha.x * alpha.x * alpha.x + a * alpha.x + b) % PRIME) {
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
    
    if (p1.x == p2.x && p1.y == p2.y) {
        int m = ((3 * p1.x * p1.x + a) * mult_inv(2 * p1.y)) % PRIME;
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

// point multiply_point_double_and_add(point p, int n) {
//     point ps[] = {p};
//     point p1 = p;
//     int i = 0;
//     while (n > 0) {
//         if (n % 2 == 1) {
//             ps[i] = p1;
//             i++;
//         }
//         p1 = add_point(p1, p1);
//         n /= 2;
//     }
//     point p2 = ps[0];
// }



int main() {
    point alpha = generate_point();
    printf("alpha = (%d, %d)\n", alpha.x, alpha.y);

    int a_pk, b_pk;
    printf("Enter private key of Alice (1-150): ");
    scanf("%d", &a_pk);
    
    printf("Enter private key of Bob (1-150): ");
    scanf("%d", &b_pk);
    
    point a_pk_p = multiply_point(alpha, a_pk);
    point b_pk_p = multiply_point(alpha, b_pk);

    printf("Alice's public key = (%d, %d)\n", a_pk_p.x, a_pk_p.y);
    printf("Bob's public key = (%d, %d)\n", b_pk_p.x, b_pk_p.y);

    point sk_p = multiply_point(alpha, a_pk * b_pk);

    printf("Shared key = (%d, %d)\n", sk_p.x, sk_p.y);

    return 0;
}