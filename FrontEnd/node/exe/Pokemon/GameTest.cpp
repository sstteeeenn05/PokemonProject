#include "GameTest.h"
#include <queue>

void GameTest::serve() {
    queue<string> outputs;
    for (string command; getline(cin, command);) {
        if (command == "Battle") {
            string moveName1, moveName2;
            getline(cin, moveName1);
            getline(cin, moveName2);

            BattlePokemon &pokemon1 = playerPokemonIt->second;
            BattlePokemon &pokemon2 = *opponentPokemonIt;
            Move &move1 = pokemon1.getMove(moveName1);
            Move &move2 = pokemon2.getMove(moveName2);

            int damage1 = move1.calcDamage(pokemon1, pokemon2);
            int damage2 = move2.calcDamage(pokemon2, pokemon1);
        }
    }
}