#include <stdio.h>

// Function to calculate the greatest common divisor (gcd)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular multiplicative inverse
int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;

    // Trial-and-error method to find p and q
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Calculate Euler's totient function (phi)
    int phi = (p - 1) * (q - 1);

    // Calculate private key using extended Euclidean algorithm
    int d = modInverse(e, phi);

    printf("Private key (d): %d\n", d);

    return 0;
}
