# Run client from Portico Exchange

This doc teachs people run own client from Portico Exchange

# Pre requesites 

-Elements Node default by Liquid

-Lightning Node (Core Lightning)

-Laguage C installed

# Run Client

Copy/paste
````

Git clone github.com/PorticoExchange-Core-Client.git
````

Install C in your machine

````

sudo apt-get install build-essential
````

Portico-client
````

nano Portico-Exchange-Core-Client.c
````

Compile
````

gcc Portico-Exchange-Core-Client.c -o Portico-Exchange-Core-Client
````

Now, just Type ./<output name> to run the program.
````

~$ ./Portico-Exchange-Core-Client
````

Change the RPC of Bitcoin Core, CLN and Elements

````

$./PorticoExchange-Core-Client/elements-bitcoin

````

Make the atomic transactions

````
$./PorticoExchange-Core-Client/swapin
````
