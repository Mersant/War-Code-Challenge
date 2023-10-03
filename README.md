# War-Code-Challenge
## How it works
All cards are stored as a single "deck" with each card represented by 4 bit nibbles in a 26 byte array. The index of Player A's first card is always deck[0], whereas the index of Player B's first card is separately stored in a variable.
```
2 -> 0x02 (0010)
. . .
10 -> 0xA (1010)
Jack -> 0xB (1011)
Queen -> 0xC (1100)
King -> 0xD (1101)
Ace -> 0xE (1110)
```
## Running
Executables were compiled on windows. If you need to compile them yourself, ensure you have a C++ compiler installed. There are a few, though I use the GNU Compiler Collection. (GCC) To install GCC on Windows, [use this guide.](https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j) Mac users can install GCC by following [this guide](https://osxdaily.com/2023/05/02/how-install-gcc-mac/) though it may be easier to just use Clang. (Run "xcode-select --install" in your terminal and install the command line tools. You can then "use" GCC even though behind the scenes you're really just using Apple's Clang compiler.)

After you have the proper compiler installed use it to compile mainNoFlavorText.cpp or mainWithFlavorText.cpp. mainWithFlavorText is far more interesting so you should probably do that one. In GCC, the command to do this would be
```
g++ mainNoFlavorText.cpp -o War
```
Then run it on Mac in Terminal or on Windows in PowerShell by running:
```
./War
```
