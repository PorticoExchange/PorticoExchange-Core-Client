const { exec } = require('child_process');

// Define your LND CLI command
function runLndCommand(command, callback) {
    exec(`lncli ${command}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing command: ${error}`);
            return;
        }
        if (stderr) {
            console.error(`Command error: ${stderr}`);
            return;
        }
        callback(stdout);
    });
}

// Open a channel
function openChannel(peerPublicKey, amount) {
    const command = `openchannel --node_key=${peerPublicKey} --local_amt=${amount}`;
    runLndCommand(command, (output) => {
        console.log('Channel opened successfully:');
        console.log(output);
    });
}

// Close a channel
function closeChannel(channelId) {
    const command = `closechannel --channel_point=${channelId}`;
    runLndCommand(command, (output) => {
        console.log('Channel closure initiated:');
        console.log(output);
    });
}

// Replace these with your actual values
const peerPublicKey = 'your_peer_public_key';
const channelAmount = 1000000; // in satoshis
const channelPoint = 'channel_funding_txid:channel_output_index';

// Uncomment and use the functions as needed
// openChannel(peerPublicKey, channelAmount);
// closeChannel(channelPoint);

