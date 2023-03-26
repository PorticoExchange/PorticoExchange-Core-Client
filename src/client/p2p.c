// include necessary libraries
#include <lightningd/lightningd.h>
#include <lightningd/peer_control.h>
#include <lightningd/subd.h>
#include <wire/gen_peer_wire.h>
#include <wire/tlvstream.h>

// initialize payment channel
struct channel *channel = channel_new(...);

// create a Taproot-based asset
struct asset *asset = asset_new(...);

// generate a pre-image for the HODL invoice
u8 preimage[32];
generate_preimage(preimage);

// create an HODL invoice and add an unresolved HTLC
struct invoice *invoice = invoice_create(...);
add_htlc(channel, invoice, asset, preimage);

// send the invoice to the other party
struct peer *peer = get_peer(channel);
send_hodl_invoice(peer, invoice);

// wait for the other party to pay the invoice
u8 *payment = wait_for_payment(peer, invoice);

// add the other party's payment as an unresolved HTLC
add_htlc(channel, invoice, asset, preimage);

// send the HODL invoice to the other party
send_hodl_invoice(peer, invoice);

// wait for the other party to pay the invoice
payment = wait_for_payment(peer, invoice);

// both transfers have now been completed
