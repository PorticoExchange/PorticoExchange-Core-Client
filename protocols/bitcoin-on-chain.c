BITCOIN_NETWORK_H
BITCOIN_NETWORK_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define HASH_LENGTH 32
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

// Helper function to initiate an atomic swap from the Liquid Network to Bitcoin on-chain.
void initiate_swap(char *asset, int amount, char *address) {
    // Generate a random preimage for the HTLC.
    unsigned char preimage[SECRET_LENGTH];
    generate_secret(preimage);
    
    // Create an HTLC on the Liquid Network.
    HTLC *liquid_htlc = new_htlc(preimage, SECRET_LENGTH, HTLC_TIMEOUT);
    char *liquid_htlc_script = "OP_SHA256 %02X OP_EQUAL";
    char liquid_htlc_script_formatted[1024];
    sprintf(liquid_htlc_script_formatted, liquid_htlc_script, liquid_htlc->hash);
    char *liquid_htlc_command = "liquid-cli sendtoaddress %s %d \"\" \"\" false \"\" 0.0001 \"%s\"";
    char liquid_htlc_command_formatted[1024];
    sprintf(liquid_htlc_command_formatted, liquid_htlc_command, address, amount, liquid_htlc_script_formatted);
    char *liquid_htlc_response = system(liquid_htlc_command_formatted);
    printf("Liquid HTLC: %s\n", liquid_htlc_response);
    
    // Create an HTLC on the Bitcoin network.
    HTLC *bitcoin_htlc = new_htlc(preimage, SECRET_LENGTH, HTLC_TIMEOUT);
    char *bitcoin_htlc_script = "OP_SHA256 %02X OP_EQUAL
