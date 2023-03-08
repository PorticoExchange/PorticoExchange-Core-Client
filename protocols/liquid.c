#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <lightningd/jsonrpc.h>

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

// Helper function to initiate an atomic swap from the Liquid Network to the Core Lightning Network.
void initiate_swap(char *asset, int amount, char *invoice) {
    // Generate a random preimage for the HTLC.
    unsigned char preimage[SECRET_LENGTH];
    generate_secret(preimage);
    
    // Create an HTLC on the Liquid Network.
    char *elements_htlc_command = "elements-cli htlcissue {\"asset\":\"%s\",\"amount\":%d,\"redeemscript\":\"hashlock(%s)\",\"locktime\":%d,\"fee\":0.0001}";
    char elements_htlc_command_formatted[1024];
    sprintf(elements_htlc_command_formatted, elements_htlc_command, asset, amount, preimage, HTLC_TIMEOUT);
    char *elements_htlc_response = jsonrpc_request(elements_htlc_command_formatted);
    printf("Elements HTLC: %s\n", elements_htlc_response);
    
    // Create an HTLC on the Core Lightning Network.
    char *core_htlc_command = "lightning-cli htlc --pay %s %d %d \"%s\"";
    char core_htlc_command_formatted[1024];
    sprintf(core_htlc_command_formatted, core_htlc_command, asset, amount, HTLC_TIMEOUT, invoice);
    char *core_htlc_response = jsonrpc_request(core_htlc_command
