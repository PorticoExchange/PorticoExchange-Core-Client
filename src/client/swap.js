const bitcoin = require('bitcoin-js-lib');
const lightning = require('lightning-js-lib');
const crypto = require('crypto');

const HASH_LENGTH = 20;
const SECRET_LENGTH = 32;
const HTLC_TIMEOUT = 144;

// Helper function to compute the SHA-256 hash of a given message.
function sha256(message) {
  const hash = crypto.createHash('sha256');
  hash.update(message);
  return hash.digest();
}

// Helper function to generate a random secret.
function generateSecret() {
  const secret = crypto.randomBytes(SECRET_LENGTH);
  return secret;
}

// Function to create a new HTLC.
function newHTLC(message, timeout) {
  const htlc = {
    hash: sha256(message),
    secret: generateSecret(),
    timeout: timeout
  };
  return htlc;
}

// Function to verify the hash of a given message matches a given hash.
function verifyHash(message, hash) {
  const computedHash = sha256(message);
  return bitcoin.utils.buffer.compare(hash, computedHash) === 0;
}

// Function to redeem an HTLC with the secret.
function redeemHTLC(htlc, secret) {
  return bitcoin.utils.buffer.compare(htlc.secret, secret) === 0;
}

// Example usage:
const message = 'Hello, world!';
const timeout = HTLC_TIMEOUT;
const htlc = newHTLC(message, timeout);
console.log('HTLC:', htlc);

// Verify the hash
const isValidHash = verifyHash(message, htlc.hash);
console.log('Is Hash Valid?', isValidHash);

// Redeem the HTLC with the secret
const secret = generateSecret();
const isRedeemed = redeemHTLC(htlc, secret);
console.log('Is HTLC Redeemed?', isRedeemed);


