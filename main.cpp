#include <iostream>
#include <bitset>
#include "Board.h"

int main() {
    Board board;

    for (int i = 0; i < 12; i++) {
        std::cout << std::bitset<64>(board.bitboards[i]) << std::endl;
    }



    return 0;
}
