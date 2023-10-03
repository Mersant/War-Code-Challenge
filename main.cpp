#include <iostream>
#include <array>
#include <string>

inline int readNibble(std::array<unsigned char, 26>& deck, int position) {
    // All even || 0 positions are an upper nibble, note that 0 % 2 == 0 & 0 / 2 == 0 in C++
    return (position % 2 == 0)
        ? deck[position / 2] >> 4
        : deck[(position - 1) / 2] & 0x0F;
}

inline void writeNibble(std::array<unsigned char, 26>& deck, int position, int nibble ) {
    (position % 2 == 0)
        ? deck[position / 2] = (deck[position / 2] & 0x0F) | ((nibble << 4) & 0xF0) // Set upper nibble
        : deck[(position - 1) / 2] = (deck[(position - 1) / 2] & 0xF0) | (nibble & 0x0F); //  Set lower nibble
}

void moveNibble(std::array<unsigned char, 26>& deck, int sourceIndex, int destinationIndex) {
    int card = readNibble(deck, sourceIndex++);
    for(int i = sourceIndex; i <= destinationIndex; i++) {
        writeNibble(deck, i - 1, readNibble(deck, i));
    }
    writeNibble(deck, destinationIndex, card);
}

int main() {
    int deckSeparatorIndex = 26, // this represents the index of Player B's first card. 0 always represents Player A's first card
        offset = 0;
    std::array<unsigned char, 26> deck = { 0xE6, 0xD7, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0xD9, 0xC7, 0xA6, 0x28, 0x48, 0x3A, 0x8B };

    while(deckSeparatorIndex > 0 && deckSeparatorIndex < 52) {
        int aCard = readNibble(deck, 0),
            bCard = readNibble(deck, deckSeparatorIndex);

        std::cout << "Begin a match!\n" << "Player A: " << aCard << "\nPlayer B: " << bCard << std::endl; 

        if(aCard > bCard) { // Player A wins
            std::cout << "A has won! " << aCard << " against " << bCard << std::endl;
            moveNibble(deck, 0, deckSeparatorIndex++);
        }  else if (aCard < bCard) { // Player B wins
            std::cout << "B has won! " << bCard << " against " << aCard << std::endl;
            moveNibble(deck, 0, 51);
            moveNibble(deck, --deckSeparatorIndex, 51);
        } else { // Tie
            std::cout << "A tie!!! " << aCard << " against " << bCard << std::endl;
            int offset = 4,
                sourceIndex = 0,
                destinationIndex = 0;

            while(readNibble(deck, offset) == readNibble(deck, deckSeparatorIndex + offset) && offset < 27) { 
                std::cout << "Another tie!!!" << std::endl;
                offset++;
            }
            std::cout << "Tie has broken!!!" << std::endl;
            if(readNibble(deck, offset) > readNibble(deck, deckSeparatorIndex + offset)) { // Player A won
                destinationIndex = deckSeparatorIndex; // sourceIndex is already 0, no need to set
            } else { // Player B won
                sourceIndex = deckSeparatorIndex;
                destinationIndex = 51;
            }
            std::cout << "Source index: " << sourceIndex << "\nDestination index: " << destinationIndex << std::endl;
            for(int i = 0; i < offset; i++) {
                moveNibble(deck, sourceIndex, destinationIndex);
            }
        }

        std::cout << "End match!\n\nDecks:\n\x1b[34mPlayer A: ";
        for(int i = 0; i < deckSeparatorIndex; i++) {
            std::cout << readNibble(deck, i) << " ";
        }
        std::cout << "\n\x1b[33mPlayer B: ";
        for(int i = deckSeparatorIndex; i < 52; i++) {
            std::cout << readNibble(deck, i) << " ";
        }
        std::cout << "\x1b[0m\n" << std::endl;
    }
    return 0;
}















inline void setLowerNibble(int &byte, int nibble) {
    byte &= 0xF0; // Clear out the lower nibble
    byte |= (nibble & 0x0F); // OR in the desired mask
}

/*
 0->0110    2-> 1001
 1->1010    3-> 1010
*/



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
}

void giveFirstTwoCardsToPlayerB(int *deck, int &aLastCardIndex, int &bLastCardIndex) {
    setLowerNibble(deck[bLastCardIndex++], deck[0] & 0x0F);
    setLowerNibble(deck[bLastCardIndex], deck[0] >> 4);
    aLastCardIndex--;
}

int main1() {
    return 0;
    int offset = 0,
        aLastCardIndex = 25,
        bLastCardIndex = 25,
        deck[52] = { 0xE6, 0xD7, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0xD9, 0xC7, 0xA6, 0x28, 0x48, 0x3A, 0x8B };
        //deck[52] = { 0xEE, 0xEE, 0xDD, 0xDD, 0xCC, 0xCC, 0xBB, 0xBB, 0xAA, 0xAA, 0x99, 0x99, 0x88, 0x88, 0x77, 0x77, 0x66, 0x66, 0x55, 0x55, 0x44, 0x44, 0x33, 0x33, 0x22, 0x22 };
    
    while(aLastCardIndex < 52 && bLastCardIndex < 52) {
        if(deck[0] % 17 == 0) {
            offset = 4;
            std::cout << "\x1B[33m\x1B[1mThe armies are locked in a deadly stalemate!\x1B[0m" << std::endl;
            // "Lay three cards face down" then loop through cards until a player runs out of cards or a non-tie match is find. In binary, multiples
            //      of 17 up to 255 are represented by two equal nibbles in binary (Ex. 0x11, 0x22 . . . 0xFF) so this can be used to check 
            //      if the current match is a draw.
            while(deck[offset] % 17 == 0 && offset < 26) {
                offset++;
            }
            if(offset > aLastCardIndex || offset > bLastCardIndex) {
                std::cout << "\x1B[31m\x1B[1m\"Send forth more men!\" the desperate general cried, but only a ghostly echo responded from the barren war chamber, for the loser had at last exhausted their final reserves of courageous souls to send to the merciless battlefront.\x1B[0m" << std::endl;
                break;
            } 
            std::cout << "\x1B[37m\x1B[1mThe darkened horizon suddenly burst into sinister light as the final wave of artillery rained down hellfire across the battered landscape, utterly annihilating the remainder of Player " << ((aLastCardIndex > bLastCardIndex) ? "A" : "B") << "'s forces.\x1B[0m" << std::endl;
        }

        void (*transferCardsToWinnerCallback)(int*, int&, int&) =  (deck[offset] >> 4) > (deck[offset] & 0x0F)
            ? giveFirstTwoCardsToPlayerA
            : giveFirstTwoCardsToPlayerB;

        for(int i = 0; i < offset + 1; i++) {
            transferCardsToWinnerCallback(deck, aLastCardIndex, bLastCardIndex);
            sortDeck(deck);
        }
        offset = 0;
    }
    if(aLastCardIndex == bLastCardIndex) {
        std::cout << "\x1B[35mThe walls of the capital city smoldered as the final artillery barrage ceased, leaving an eerie silence hanging heavily in the air.\nBlood and ash stained the barren earth that was once fertile farmland, now churned into a graveyard by years of endless carnage.\nAs the last ragged soldiers limped away from the front lines, too exhausted to celebrate or mourn, it was clear the long war had\nresolved nothing yet destroyed everything.\x1B[0m" << std::endl;
    } else {
        std::cout << "\x1B[35m" << ((aLastCardIndex >= bLastCardIndex) ? "Mushroom clouds bloomed ominously on the horizon as Player A unleashed their arsenal of nuclear warheads, obliterating Player B's cities in flashes of apocalyptic fury after years of relentless warfare. Amid the radioactive ruins, Player A stood victorious, their tattered flag raised over the scorched earth - though any sense of triumph was muted by the unimaginable destruction wrought by both sides' thirst for total war." : "The few ragged survivors of Player B's army stood in silence amidst the smoldering ruins of civilization, having finally defeated Player A after years of apocalyptic war. A blackened wind scattered ashes across the graveyard that was once a thriving world, serving as the only witness to Player B's pyrrhic victory, for no cheer would ever be heard in this tomb of nuclear winter.") << "\x1B[0m" << std::endl;
    }
}