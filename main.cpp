#include <iostream>

inline void setLowerNibble(int &byte, int nibble) {
    byte &= 0xF0; // Clear out the lower nibble
    byte |= (nibble & 0x0F); // OR in the desired mask
}

inline void setUpperNibble(int &byte, int nibble) {
    byte &= 0x0F; // Clear out the upper nibble
    byte |= ((nibble << 4) & 0xF0);
}

void sortDeck(int *deck) {
    // deck[x] >> 4 extracts the high nibble from the byte stored at deck[x], deck[x] & 0x0F extracts the low nibble
    for(int i = 0; i < 51 && deck[i+1] != 0; i++) {
        setUpperNibble(deck[i], deck[i+1] >> 4);
        setLowerNibble(deck[i], deck[i+1] & 0x0F);
    }
}

void giveFirstTwoCardsToPlayerA(int *deck, int &aLastCardIndex, int &bLastCardIndex) {
    setUpperNibble(deck[aLastCardIndex++], deck[0] >> 4);
    // The whole array is shifted one unit back every time it is sorted; no need to increment lastCardIndex a second time
    setUpperNibble(deck[aLastCardIndex], deck[0] & 0x0F);
    bLastCardIndex--;
    std::cout << "\x1B[31mPlayer A has won a bloody battle against his adversary!" << std::endl;
}
void giveFirstTwoCardsToPlayerB(int *deck, int &aLastCardIndex, int &bLastCardIndex) {
    setLowerNibble(deck[bLastCardIndex++], deck[0] & 0x0F);
    setLowerNibble(deck[bLastCardIndex], deck[0] >> 4);
    aLastCardIndex--;
    std::cout << "\x1B[36mPlayer B has bashed the head in of all his foes!" << std::endl;
}

int main() {
    int offset = 0,
        aLastCardIndex = 26,
        bLastCardIndex = 26,
        deck[52] = { 0xE6, 0x7D, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x28, 0x48, 0x3A, 0x8B };
    
    while(aLastCardIndex < 52 && bLastCardIndex < 52) {
        if(deck[0] % 17 == 0) {
            offset = 4;
            std::cout << "\x1B[33m\x1B[1mThe armies are locked in a deadly stalemate!\x1B[0m" << std::endl;
            // "Lay three cards face down" then loop through cards until a player runs out of cards or a non-tie match is find. In binary, multiples
            //      of 17 up to 255 are represented by two equal nibbles in binary (Ex. 0x11, 0x22 . . . 0xFF) so this can be used to check 
            //      if the current match is a draw.
            while(deck[offset] % 17 == 0) {
                offset++;
                if(offset > aLastCardIndex || offset > bLastCardIndex) {
                    std::cout << "\x1B[31m\x1B[1mThe loser has run out of troops to send!!!\x1B[0m" << std::endl;
                    break;
                } 
            }
            std::cout << "\x1B[37m\x1B[1mA breakthrough has occurred and the stalemate has ended! Continue with battle!\x1B[0m" << std::endl;
        }

        void (*transferCardsToWinnerCallback)(int*, int&, int&) =  (deck[offset] >> 4) > (deck[offset] & 0x0F)
            ? giveFirstTwoCardsToPlayerA
            : giveFirstTwoCardsToPlayerB;

        for(int i = 0; i < offset + 1; i++) {
            transferCardsToWinnerCallback(deck, aLastCardIndex, bLastCardIndex);
            deck[0] = 0;
            sortDeck(deck);
        }
        offset = 0;
    }
    std::cout << "\x1B[35mPlayer " << ((aLastCardIndex > bLastCardIndex) ? "A" : "B") << " has won!\x1B[0m" << std::endl;
}