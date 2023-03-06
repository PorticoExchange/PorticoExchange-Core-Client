#include <bitcoin/chainparams.h>
#include <bitcoin/privkey.h>
#include <bitcoin/pubkey.h>
#include <bitcoin/script.h>
#include <bitcoin/tx.h>
#include <ccan/tal/str/str.h>
#include <common/amount.h>
#include <common/htlc_tx.h>
#include <common/key_derive.h>
#include <common/utils.h>
#include <stdio.h>
#include <wally_bip32.h>

/* Define the on-chain and Lightning network parameters */
static const struct chainparams *chainparams = &chainparams_main;
static const u32 locktime = 1573819200; /* 15 Nov 2019 */

/* Define the on-chain and Lightning network transaction outputs */
static const struct amount_sat onchain_output = AMOUNT_SAT(500000);
static const struct amount_msat lightning_output = AMOUNT_MSAT(1000000);

int main(void) {
    /* Generate a random private key for the user */
    struct privkey user_privkey;
    randombytes_buf(&user_privkey, sizeof(user_privkey));

    /* Derive the corresponding public key for the user */
    struct pubkey user_pubkey;
    if (!pubkey_from_privkey(&user_privkey, &user_pubkey))
        return 1;

    /* Generate a random preimage for the HTLC */
    struct sha256 preimage;
    randombytes_buf(&preimage, sizeof(preimage));

    /* Compute the hash of the preimage */
    struct sha256 hash;
    sha256(&hash, &preimage, sizeof(preimage));

    /* Construct the HTLC script for the on-chain transaction */
    u8 *onchain_htlc_script = bitcoin_htlc_onchain_witness_script(
        &chainparams->payment_basepoint,
        &user_pubkey,
        &chainparams->htlc_secretkey,
        &chainparams->htlc_point,
        locktime,
        &hash,
        HTLC_TIMEOUT
    );

    /* Construct the HTLC output for the on-chain transaction */
    struct bitcoin_tx_output onchain_tx_output = {
        .amount = onchain_output,
        .script = scriptpubkey_p2wsh(onchain_htlc_script)
    };

    /* Construct the HTLC output for the Lightning network transaction */
    struct bitcoin_tx_output lightning_tx_output = {
        .amount = amount_msat_to_sat_round_down(lightning_output),
        .script = scriptpubkey_p2wpkh(&user_pubkey)
    };

    /* Generate a random multisig key for the swap */
    struct pubkey swap_multisig_key;
    if (!generate_keypair(&swap_multisig_key, NULL))
        return 1;

    /* Construct the HTLC script for the Lightning network transaction */
    u8 *lightning_htlc_script = bitcoin_htlc_success_tx(
        &chainparams->payment_basepoint,
        &swap_multisig_key,
        &chainparams->htlc_secretkey,
        &chainparams->htlc_point,
        &hash,
        HTLC_SUCCESS
    );

    /* Construct the multisig output for the Lightning network transaction */
    struct bitcoin_tx_output lightning_multisig_output = {
        .amount = amount_msat_to_sat_round_down(lightning_output),
        .script = scriptpubkey_p2wsh(scriptpubkey_2of2(
            &swap_multisig_key, &user_pubkey))
    };

    /* Construct the transaction input for the on-chain transaction */
    struct bitcoin_tx_input onchain_tx_input = {
        .txid = { .u
