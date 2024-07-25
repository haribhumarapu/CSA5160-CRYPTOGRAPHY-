#include <stdio.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>
#include <openssl/err.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

void print_signature(unsigned char* sig, unsigned int sig_len) {
    for (unsigned int i = 0; i < sig_len; i++) {
        printf("%02x", sig[i]);
    }
    printf("\n");
}

int main() {
    // Initialize OpenSSL algorithms
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Generate DSA key
    DSA* dsa = DSA_new();
    if (DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL) != 1) {
        handleErrors();
    }
    if (DSA_generate_key(dsa) != 1) {
        handleErrors();
    }

    // Message to be signed
    unsigned char* message = (unsigned char*)"This is a test message";
    unsigned int message_len = strlen((char*)message);

    // Hash the message
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(message, message_len, hash);

    // Sign the hash
    unsigned char sig[DSA_size(dsa)];
    unsigned int sig_len;

    if (DSA_sign(0, hash, SHA256_DIGEST_LENGTH, sig, &sig_len, dsa) != 1) {
        handleErrors();
    }

    printf("DSA Signature 1: ");
    print_signature(sig, sig_len);

    // Sign the hash again (to show different signatures for the same message)
    unsigned char sig2[DSA_size(dsa)];
    unsigned int sig_len2;

    if (DSA_sign(0, hash, SHA256_DIGEST_LENGTH, sig2, &sig_len2, dsa) != 1) {
        handleErrors();
    }

    printf("DSA Signature 2: ");
    print_signature(sig2, sig_len2);

    // Cleanup
    DSA_free(dsa);
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
