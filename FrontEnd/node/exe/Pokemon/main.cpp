#include "GameTest.h"

using namespace std;

int main() {

    const string pokemonFileName = "file/PokemonLib.txt";
    const string moveFileName = "file/MoveLib.txt";
    const string gameDataFileName = "file/GameData.txt";

    string testMode;
    getline(cin, testMode);
    if (testMode == "Test") {
        GameTest game(pokemonFileName, moveFileName, gameDataFileName);
        game.serve();
    } else {
        // GameAI game(pokemonFileName, moveFileName, gameDataFileName);
        // game.serve();
    }

    return 0;
}
