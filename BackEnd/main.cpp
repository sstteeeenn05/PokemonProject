#include <iostream>
#include"Game.h"

int main() {
    srand(time(NULL));
    /*Pokemon hi("hi", {"ra"}, 100, 10, 10, 10, 10, 10, 10, 10);
    Pokemon ra("ra", {"hi"}, 100, 10, 10, 10, 10, 8, 10, 10);
    Game game(hi,ra);
    game.attack("hi",{"ra"},"Special",10,100);*/
    Game game;
    game.print();
}
