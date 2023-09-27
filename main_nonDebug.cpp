#include <iostream>

inline void setLowerNibble(int &byte, int nibble) {
    byte &= 0xF0; // Clear out the lower nibble
    byte |= (nibble & 0x0F); // OR in the desired mask
}

inline void setUpperNibble(int &byte, int nibble) {
    byte &= 0x0F; // Clear out the upper nibble
    byte |= ((nibble << 4) & 0xF0);
}

void sortNibbles(int* deck, int (*getCardValueFromByte)(int), void (*setNibble)(int*, int)) {
    // Loop through nibbles and get rid of any 0s in the array except trailing 0s
    int index = 0,
        offset = 0;

    while(index + offset < 52) {
        int cardValue = getCardValueFromByte(deck[index + offset]);
        if(cardValue == 0) {
            offset++;
            continue;
        }
        setNibble(&deck[index], cardValue);
        setNibble(&deck[index + offset], 0);
        index++;
    }
}

void sortDeck(int *deck) {
    // Sort high nibbles of deck (Player A)
    sortNibbles(deck, 
        [](int byte) -> int { return byte >> 4; },
        [](int *deck, int value) -> void { setUpperNibble(*deck, value); }
    );
    // Sort low nibbles of deck (Player B)
    sortNibbles(deck,
        [](int byte) -> int { return byte & 0x0F; },
        [](int *deck, int value) -> void { setLowerNibble(*deck, value); }
    );
}

void handlePlayerAWin(int *deck, int &aLastCardIndex, int &bLastCardIndex) {
    setUpperNibble(deck[aLastCardIndex++], deck[0] >> 4);
    // The whole array is shifted one unit back every time it is sorted; no need to increment lastCardIndex a second time
    setUpperNibble(deck[aLastCardIndex], deck[0] & 0x0F);
    bLastCardIndex--;
    deck[0] = 0; // First array element should be 0 for sorting algorithm to work properly
    sortDeck(deck);
}
void handlePlayerBWin(int *deck, int &aLastCardIndex, int &bLastCardIndex) {
    setLowerNibble(deck[bLastCardIndex++], deck[0] & 0x0F);
    setLowerNibble(deck[bLastCardIndex], deck[0] >> 4);
    aLastCardIndex--;
    deck[0] = 0;
    sortDeck(deck);
}

int main() {
    int aLastCardIndex = 26,
        bLastCardIndex = 26,
        deck[52] = { 0x16, 0x7D, 0xDC, 0xB1, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xA1, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0x13, 0x44, 0x9D, 0xC7, 0x6A, 0x28, 0x48, 0x3A, 0x8B };
    
    while (aLastCardIndex < 52 && bLastCardIndex < 52) {
        // Multiples of 17 up to 255 are represented by two equal nibbles in binary (Ex. 0x11, 0x22 . . . 0xFF) so this can be used to check 
        //      if the current match is a draw.
        if(deck[0] % 17 != 0) {
            // deck[0] >> 4 extracts the high nibble from the byte stored at deck[0], deck[0] & 0x0F extracts the low nibble
            (deck[0] >> 4) > (deck[0] & 0x0F)
                ? handlePlayerAWin(deck, aLastCardIndex, bLastCardIndex)
                : handlePlayerBWin(deck, aLastCardIndex, bLastCardIndex);
        } else {
            int potOffset = 4;
            // "Lay three cards face down" then loop through cards until a player runs out of cards or a non-tie match is find.
            while(deck[potOffset] % 17 == 0) {
                potOffset++;
                if(potOffset > aLastCardIndex || potOffset > bLastCardIndex) {
                    break;
                } 
            }
            void (*transferCardsToWinnerCallback)(int*, int&, int&) =  (deck[potOffset] >> 4) > (deck[potOffset] & 0x0F)
                ? handlePlayerAWin
                : handlePlayerBWin;

            for(int i = 0; i < potOffset; i++) {
                transferCardsToWinnerCallback(deck, aLastCardIndex, bLastCardIndex);
            }
        } 
    }
    std::cout << "\x1B[35mPlayer " << ((aLastCardIndex > bLastCardIndex) ? "A" : "B") << " has won!\x1B[0m" << std::endl;
    return 1;
}