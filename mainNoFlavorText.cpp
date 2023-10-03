#include <iostream>
#include <array>
#include <string>

inline int readNibble(std::array<unsigned char, 26>& arr, int position) {
    // All even || 0 positions are an upper nibble, note that 0 % 2 == 0 && 0 / 2 == 0 in C++
    return (position % 2 == 0)
        ? arr[position / 2] >> 4
        : arr[(position - 1) / 2] & 0x0F;
}

inline void writeNibble(std::array<unsigned char, 26>& arr, int position, int nibble ) {
    (position % 2 == 0)
        ? arr[position / 2] = (arr[position / 2] & 0x0F) | ((nibble << 4) & 0xF0) // Set upper nibble
        : arr[(position - 1) / 2] = (arr[(position - 1) / 2] & 0xF0) | (nibble & 0x0F); //  Set lower nibble
}

void moveNibble(std::array<unsigned char, 26>& arr, int sourceIndex, int destinationIndex) {
    int nibble = readNibble(arr, sourceIndex++);
    for(int i = sourceIndex; i <= destinationIndex; i++) {
        writeNibble(arr, i - 1, readNibble(arr, i));
    }
    writeNibble(arr, destinationIndex, nibble);
}

int main() {
    int playerBFirstCardIndex = 26, // 0 always represents Player A's first card
        offset = 0; // 1 + offset is how many cards will be transferred once a winner is detected; used to handle ties.
    std::array<unsigned char, 26> deck = { 0xE6, 0xD7, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0xD9, 0xC7, 0xA6, 0x28, 0x48, 0x3A, 0x8B };

    while(playerBFirstCardIndex > 0 && playerBFirstCardIndex < 52) {
        int aCard = readNibble(deck, 0 + offset),
            bCard = readNibble(deck, playerBFirstCardIndex + offset);

        if(aCard == bCard) {
            (offset == 0) ? offset = 4 : offset++;
            if(offset >= playerBFirstCardIndex || offset > 51 - playerBFirstCardIndex) {
                break;
            }
            continue;
        } else if(aCard > bCard) {
            for(int i = 0; i <= offset; i++) {
                moveNibble(deck, 0, playerBFirstCardIndex++);
            }
        } else {
            for(int i = 0; i <= offset; i++) {
                moveNibble(deck, 0, 51);
                moveNibble(deck, --playerBFirstCardIndex, 51);
            }
        }
        offset = 0;
    }
    if(playerBFirstCardIndex == 26) {
        std::cout << "Players tied" << std::endl;
    } else {
        std::cout << "\x1B[35m" << ((playerBFirstCardIndex > 26) ? "Player A wins" : "Player B wins") << "\x1b[0m" << std::endl;
    }
}