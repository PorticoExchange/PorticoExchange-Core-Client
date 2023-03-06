#ifndef PORTICO_SWAP_H
#define PORTICO_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define HASH_LENGTH 20
#define SECRET_LENGTH 32
#define HTLC_TIMEOUT 144

typedef struct {
    unsigned char hash[HASH_LENGTH];
    unsigned char secret[SECRET_LENGTH];
    int timeout;
} HTLC;

// Helper function to compute the SHA-256 hash of a given message.
void sha256(unsigned char *message, size_t message_len, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, message, message_len);
    SHA256_Final(hash, &sha256);
}

// Helper function to generate a random secret.
void generate_secret(unsigned char *secret) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(secret, 1, SECRET_LENGTH, fp);
    fclose(fp);
}

// Function to create a new HTLC.
HTLC* new_htlc(unsigned char *message, size_t message_len, int timeout) {
    HTLC *htlc = malloc(sizeof(HTLC));
    sha256(message, message_len, htlc->hash);
    generate_secret(htlc->secret);
    htlc->timeout = timeout;
    return htlc;
}

// Function to verify the hash of a given message matches a given hash.
int verify_hash(unsigned char *message, size_t message_len, unsigned char *hash) {
    unsigned char computed_hash[HASH_LENGTH];
    sha256(message, message_len, computed_hash);
    return memcmp(hash, computed_hash, HASH_LENGTH) == 0;
}

// Function to redeem an HTLC with the secret.
int redeem_htlc(HTLC *htlc, unsigned char *secret) {
    if (memcmp(htlc->secret, secret, SECRET_LENGTH) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check if an HTLC has timed out.
int htlc_timed_out(HTLC *htlc, int current_block_height) {
    return current_block_height > htlc->timeout;
}

int main() {
    // Create a new HTLC with a message and a timeout.
    char message[] = "Hello, world!";
    size_t message_len = strlen(message);
    int timeout = 100;
    HTLC *htlc = new_htlc((unsigned char*) message, message_len, timeout);
    
    // Verify the hash of the message matches the hash in the HTLC.
    if (verify_hash((unsigned char*) message, message_len, htlc->hash)) {
        printf("Hash verification succeeded!\n");
    } else {
        printf("Hash verification failed!\n");
    }
    
    // Redeem the HTLC with the secret.
    unsigned char secret[SECRET_LENGTH];
    generate_secret(secret);
    if (redeem_htlc(htlc, secret)) {
        printf("HTLC redemption succeeded!\n");
    } else {
        printf("HTLC redemption failed!\n");
    }
    
    // Check if the HTLC has timed out.
    int current_block_height = 200;
    if (htlc_timed_out(htlc, current_block_height)) {
        printf("HTLC timed out!\n");
    } else {
        printf("HTLC has not timed out yet.\n");
    }
    
    free(htlc);
    
    return 0;
}

