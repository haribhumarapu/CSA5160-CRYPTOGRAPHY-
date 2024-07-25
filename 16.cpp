//Possible Keys Without Considering Identical Results:

#include <stdio.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n = 25;
    unsigned long long result = factorial(n);
    printf("The number of possible keys for the Playfair cipher is: %llu\n", result);
    return 0;
}


//Effectively Unique Keys Considering Identical Results:


#include <stdio.h>
#include <math.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double log2_factorial(int n) {
    double result = 0.0;
    for (int i = 1; i <= n; i++) {
        result += log2(i);
    }
    return result;
}

int main() {
    int n = 25;
    unsigned long long fact = factorial(n);
    double log2_fact = log2_factorial(n);
    printf("The number of possible keys for the Playfair cipher is: %llu\n", fact);
    printf("Log base 2 of 25! is approximately: %.2f\n", log2_fact);
    return 0;
}



//Unique Keys:



#include <stdio.h>
#include <math.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double log2_factorial(int n) {
    double result = 0.0;
    for (int i = 1; i <= n; i++) {
        result += log2(i);
    }
    return result;
}

int main() {
    int n = 25;
    unsigned long long fact = factorial(n);
    double log2_fact = log2_factorial(n);
    unsigned long long unique_keys = fact / 4;
    double log2_unique_keys = log2(unique_keys);

    printf("The number of possible keys for the Playfair cipher is: %llu\n", fact);
    printf("Log base 2 of 25! is approximately: %.2f\n", log2_fact);
    printf("The estimated number of unique keys considering symmetries is: %llu\n", unique_keys);
    printf("Log base 2 of estimated unique keys is approximately: %.2f\n", log2_unique_keys);
    
    return 0;
}
