from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException

def createHTLC(amount, recipient, preImage, secretHash, expiryTime, network):
    rpc_connection = AuthServiceProxy("http://BitcoinFinane:rpcpassword@127.0.0.1:8332")
    if network == "Bitcoin Lightning":
        # Code to create an HTLC on the Bitcoin Lightning network using Bitcoin Core's RPC interface
        # ...
    elif network == "Liquid":
        # Code to create an HTLC on the Liquid network using Bitcoin Core's RPC interface
        # ...
    else:
        raise ValueError("Invalid network")

def verifyHTLC(amount, recipient, expiryTime, network):
    rpc_connection = AuthServiceProxy("http://rpcuser:rpcpassword@localhost: ElementsRPCPort")
    if network == "Bitcoin Lightning":
        # Code to verify an HTLC on the Bitcoin Lightning network using Bitcoin Core's RPC interface
        # ...
    elif network == "Liquid":
        # Code to verify an HTLC on the Liquid network using Bitcoin Core's RPC interface
        # ...
    else:
        raise ValueError("Invalid network")
