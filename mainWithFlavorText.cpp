#include <iostream>
#include <array>
#include <string>

inline int readNibble(std::array<unsigned char, 26>& deck, int position) {
    // All even || 0 positions are an upper nibble, note that 0 % 2 == 0 && 0 / 2 == 0 in C++
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
    int playerBFirstCardIndex = 26, // 0 always represents Player A's first card
        offset = 0; // 1 + offset is how many cards will be transferred once a winner is detected, used to handle ties.
    std::array<unsigned char, 26> deck = { 0xE6, 0xD7, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0xD9, 0xC7, 0xA6, 0x28, 0x48, 0x3A, 0x8B };
        //deck = { 0x6E, 0xd7, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0xB9, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x82, 0x84, 0xa3, 0xB8 };
        //deck = { 0xE6, 0x77, 0xEE, 0xEE, 0xEE, 0x44, 0x39, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x28, 0x48, 0x3A, 0x8B };
        //deck = { 0xE6, 0x7D, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x28, 0x48, 0x3A, 0x8B };
        //deck = { 0x2E, 0x2E, 0xE2, 0x2E, 0x43, 0x43, 0x43, 0x43, 0x65, 0x65, 0x65, 0x65, 0x87, 0x87, 0x87, 0x87, 0xA9, 0xA9, 0x9A, 0xA9, 0xCB, 0xCB, 0xCB, 0xCB, 0xDD, 0xDD };
        //deck = { 0xE2, 0xE2, 0xE2, 0xE2, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x65, 0x87, 0x87, 0x87, 0x87, 0xA9, 0xA9, 0x9A, 0xA9, 0xCB, 0xCB, 0xCB, 0xCB, 0xDD, 0xDD };
        //deck = { 0x94, 0x9B, 0x83, 0x5D, 0x72, 0x5A, 0x3C, 0xD5, 0xD2, 0x44, 0xB9, 0x42, 0xAC, 0xB3, 0xE8, 0x96, 0xE5, 0x3C, 0xD6, 0x28, 0xAC, 0x6B, 0x78, 0xA7, 0x67, 0xEE };

    while(playerBFirstCardIndex > 0 && playerBFirstCardIndex < 52) {
        int aCard = readNibble(deck, 0 + offset),
            bCard = readNibble(deck, playerBFirstCardIndex + offset);

        std::cout << "\nBattalions:\n\x1b[34mPlayer A: ";
        for(int i = 0; i < playerBFirstCardIndex; i++) {
            std::cout << readNibble(deck, i) << " ";
            if(readNibble(deck, i) < 10) {
                std::cout << " ";
            }
        }
        std::cout << "\n\x1b[33mPlayer B: ";
        for(int i = playerBFirstCardIndex; i < 52; i++) {
            std::cout << readNibble(deck, i) << " ";
            if(readNibble(deck, i) < 10) {
                std::cout << " ";
            }
        }
        std::cout << "\x1b[0m\n" << std::endl;

        if(aCard == bCard) {
            (offset == 0) ? offset = 4 : offset++;
            if(offset >= playerBFirstCardIndex || offset > 51 - playerBFirstCardIndex) {
                std::cout << "\x1B[31m\x1B[1m\x1b[3m\"Send forth more men!\" the desperate general cried, but only a ghostly echo responded from the barren war chamber, for the loser had at last exhausted their final reserves of courageous souls to send to the merciless battlefront.\x1B[0m" << std::endl;
                break;
            }
            continue;
        } else if(aCard > bCard) {
            for(int i = 0; i <= offset; i++) {
                std::cout << "\x1B[31m\x1B[1mThe desolate landscape awakens as an earth shattering blast is heard. Before they can properly regain their bearings, Player B's forces are reduced to ash.\x1B[0m" << std::endl;
                moveNibble(deck, 0, playerBFirstCardIndex++);
            }
        } else {
            for(int i = 0; i <= offset; i++) {
                std::cout << "\x1B[32m\x1B[1mThe darkened horizon suddenly burst into sinister light as the final wave of artillery rained down hellfire across the battered landscape, utterly annihilating the remainder of Player A's forces.\x1B[0m" << std::endl;
                moveNibble(deck, 0, 51);
                moveNibble(deck, --playerBFirstCardIndex, 51);
            }
        }
        offset = 0;
    }
    if(playerBFirstCardIndex == 26) {
        std::cout << "\x1B[35mThe walls of the capital city smoldered as the final artillery barrage ceased, leaving an eerie silence hanging heavily in the air. Blood and ash stained the barren earth that was once fertile farmland, now churned into a graveyard by years of endless carnage. As the last ragged soldiers limped away from the front lines, too exhausted to celebrate or mourn, it was clear the long war had resolved nothing yet destroyed everything.\x1B[0m" << std::endl;
    } else {
        std::cout << "\x1B[35m" << ((playerBFirstCardIndex > 26) ? "Mushroom clouds bloomed ominously on the horizon as Player A unleashed their remaining arsenal of nuclear warheads, obliterating Player B's cities in flashes of apocalyptic fury after years of relentless warfare. Amid the radioactive ruins, Player A stood victorious, their tattered flag raised over the scorched earth - though any sense of triumph was muted by the unimaginable destruction wrought by both sides' thirst for total war." : "The few ragged survivors of Player B's army stood in silence amidst the smoldering ruins of civilization, having finally defeated Player A after years of apocalyptic war. A blackened wind scattered ashes across the graveyard that was once a thriving world, serving as the only witness to Player B's pyrrhic victory, for no cheer would ever be heard in this tomb of nuclear winter.") << "\x1B[0m" << std::endl;
    }
}