# War-Code-Challenge
        
        All cards are stored in 52-byte array "deck," each byte represents an individual round with the low and high nibbles representing
        each player's card used for that turn. High nibble is Player A and low nibble is Player B
        Values for cards: (Hexadecimal)
                2 -> 2
                . . .
                9 -> 9
               10 -> A
             Jack -> B
            Queen -> C
             King -> D 
              Ace -> E
        
        Sample Decks for testing: (Last one is invalid, sum of deck is not 364 assuming Ace = 1)
            deck[52] = { 0x6E, 0xd7, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0xB9, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x82, 0x84, 0xa3, 0xB8 };
            deck[52] = { 0xE6, 0x77, 0xEE, 0xEE, 0xEE, 0x44, 0x39, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x28, 0x48, 0x3A, 0x8B };
            -> deck[52] = { 0xE6, 0x7D, 0xDC, 0xBE, 0x55, 0xB8, 0xD9, 0x29, 0x9B, 0x6C, 0xAE, 0xC7, 0xA2, 0x54, 0x57, 0x32, 0x36, 0xE3, 0x44, 0x9D, 0xC7, 0x6A, 0x28, 0x48, 0x3A, 0x8B };
            deck[52] = { 0x2E, 0x2E, 0xE2, 0x2E, 0x43, 0x43, 0x43, 0x43, 0x65, 0x65, 0x65, 0x65, 0x87, 0x87, 0x87, 0x87, 0xA9, 0xA9, 0x9A, 0xA9, 0xCB, 0xCB, 0xCB, 0xCB, 0xDD, 0xDD };
            deck[52] = { 0x94, 0x9B, 0x83, 0x5D, 0x72, 0x5A, 0x3C, 0xD5, 0xD2, 0x44, 0xB9, 0x42, 0xAC, 0xB3, 0xE8, 0x96, 0xE5, 0x3C, 0xD6, 0x28, 0xAC, 0x6B, 0x78, 0xA7, 0x67, 0xEE };

