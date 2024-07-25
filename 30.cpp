#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void xor_blocks(unsigned char *out, const unsigned char *in1, const unsigned char *in2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}

void cbc_mac(unsigned char *mac, const unsigned char *key, const unsigned char *message, size_t message_len) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    unsigned char iv[AES_BLOCK_SIZE] = {0};
    unsigned char block[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];

    for (size_t i = 0; i < message_len; i += AES_BLOCK_SIZE) {
        xor_blocks(block, iv, message + i, AES_BLOCK_SIZE);
        AES_encrypt(block, ciphertext, &aes_key);
        memcpy(iv, ciphertext, AES_BLOCK_SIZE);
    }
    memcpy(mac, ciphertext, AES_BLOCK_SIZE);
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = "thisisakey123456";
    unsigned char X[AES_BLOCK_SIZE] = "oneblockmsg1234";
    unsigned char T[AES_BLOCK_SIZE];
    unsigned char X_XOR_T[AES_BLOCK_SIZE];
    unsigned char X_XOR_T_concat[AES_BLOCK_SIZE * 2];
    unsigned char mac_two_block[AES_BLOCK_SIZE];

    // Calculate CBC-MAC for single block message X
    cbc_mac(T, key, X, AES_BLOCK_SIZE);

    printf("CBC-MAC for one-block message X: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", T[i]);
    }
    printf("\n");

    // Calculate X ? T
    xor_blocks(X_XOR_T, X, T, AES_BLOCK_SIZE);

    // Concatenate X and (X ? T)
    memcpy(X_XOR_T_concat, X, AES_BLOCK_SIZE);
    memcpy(X_XOR_T_concat + AES_BLOCK_SIZE, X_XOR_T, AES_BLOCK_SIZE);

    // Calculate CBC-MAC for the two-block message X || (X ? T)
    cbc_mac(mac_two_block, key, X_XOR_T_concat, AES_BLOCK_SIZE * 2);

    printf("CBC-MAC for two-block message X || (X ? T): ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", mac_two_block[i]);
    }
    printf("\n");

    return 0;
}
