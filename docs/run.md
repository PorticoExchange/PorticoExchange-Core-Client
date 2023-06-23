# Run client from Portico Exchange

This doc teachs people run own client from Portico Exchange

## Pre requesites 

- Elements Node default by Liquid

- Lightning Node (Core Lightning)

-  Bitcoin Core

- NPM

- Node.js

- Git

- Linux

# Run Client

Copy/paste
````

Git clone github.com/PorticoExchange-Core-Client.git
````

Install C in your machine

````

sudo npm install -g npm
````

Portico-client
````

-g npm Portico-Exchange-Core-Client 
````

Compile

Now, just Type ./<output name> to run the program.
````

npm Portico-Exchange-Core-Client
````

Change the RPC of Bitcoin Core, CLN and Elements

````

npm PorticoExchange-Core-Client/elements-bitcoin

````

Change the .env of Alice and Bob and put the Bob and Alice address 
  ````
Example: 

Alice: Liquid address
Bob: On-chain or invoice
````
Make the atomic transactions
````
npm PorticoExchange-Core-Client/swapin
````
