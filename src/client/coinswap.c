#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COINS 10

// Multisig escrow address struct
typedef struct {
    int value;
    char* pub_key1;
    char* pub_key2;
} MultisigEscrowAddress;

// Function to create 2-of-2 multisig escrow address
MultisigEscrowAddress create_multisig_escrow_address(int value, char* pub_key1, char* pub_key2) {
    MultisigEscrowAddress address;
    address.value = value;
    address.pub_key1 = pub_key1;
    address.pub_key2 = pub_key2;
    return address;
}

int main() {
    srand(time(NULL));  // seed random number generator

    // Alice and Bob's public keys (dummy values)
    char* alice_pub_key = "Alice's public key";
    char* bob_pub_key = "Bob's public key";

    // Create 2-of-2 multisig escrow addresses
    MultisigEscrowAddress address1 = create_multisig_escrow_address(20, alice_pub_key, bob_pub_key);
    MultisigEscrowAddress address2 = create_multisig_escrow_address(20, bob_pub_key, alice_pub_key);

    // Initialize array of coins with random values
    int coins[NUM_COINS];
    for (int i = 0; i < NUM_COINS; i++) {
        coins[i] = rand() % 10 + 1;  // random value between 1 and 10
    }

    // Print the initial array of coins
    printf("Initial coins: ");
    for (int i = 0; i < NUM_COINS; i++) {
        printf("%d ", coins[i]);
    }
    printf("\n");

    // Perform coinswap algorithm
    int i = 0;
    int j = NUM_COINS - 1;
    while (i < j) {
        // Alice sends coin to escrow address 1
        if (coins[i] % 2 == 0) {
            printf("Alice sends coin %d to escrow address 1\n", coins[i]);
            address1.value += coins[i];
        }
        // Bob sends coin to escrow address 2
        if (coins[j] % 2 == 1) {
            printf("Bob sends coin %d to escrow address 2\n", coins[j]);
            address2.value += coins[j];
        }
        int temp = coins[i];
        coins[i] = coins[j];
        coins[j] = temp;
        i++;
        j--;
    }

    // Alice and Bob each sign transaction to release coins from escrow
    printf("Alice and Bob each sign transaction to release coins from escrow\n");
    int alice_share = address1.value / 2;
    int bob_share = address2.value / 2;
    printf("Alice receives %d coins and Bob receives %d coins\n", alice_share, bob_share);

    // Print the final array of coins
    printf("Final coins: ");
    for (int i = 0; i < NUM_COINS; i++) {
        printf("%d ", coins[i]);
    }
    printf("\n");

    return 0;
}
