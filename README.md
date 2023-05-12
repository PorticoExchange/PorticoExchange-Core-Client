# Portico  Exchange Core-Client 

Portico Exchange Client is a  implementation of the Lightning Network protocol based on [Core Lightning](https://github.com/ElementsProject/Lightning)

-Allows client to register to main Portico instance in order to signal supported pairs

-Accept and Execute trustless swaps

# Disclaimer

-Portico is beta software.

-We currently only recommend using Portico with small balances on mainnet or signet/testnet

-THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Roadmap
- [X] Testnet
- [ ] Mainnet
- [X] Fees
- [X] UI via web browser (Github Page) 
- [X] P2P Swap
- [X] API (Hypercore)
- [x] Beta ready
- [X] Bitcoin Core/Nix Bitcoin
- [X] Finalize SwapIn and SwapOut
- [X] Add Lightning wallets (Zebedee and Marina)
- [ ] RGB integration


# Demo Swap

UI simple with 'swap' between Bitcoin timechains

![image](https://user-images.githubusercontent.com/83122757/227936051-bacfd5d4-21a5-43a9-bc2c-d705c78381f1.png)


# Run Client

Pre requisite

-Elements Node default by Liquid

-Lightning Node (Core Lightning)

-Bitcoin Core 

-Laguage C installed

-Linux

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
# Ossification  and Contribution
 
Nowadays, core functionality is freezed and as a part of ossification only bugfixes are accepted

The core team of Portico not accept Pull Request from non Bitcoins protocols or layers (e.g. ETH, SOL, ADA, etc). Our vision this protocol is done for Bitcoiners
  
Any Pull Request will be automatically declined
 
[More details about Contribution](https://github.com/PorticoExchange/PorticoExchange-Core-Client/blob/main/CONTRIBUTING.md)
  
# Lightning implementation 

Built on Core Lightning


