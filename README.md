# War-Code-Challenge
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
