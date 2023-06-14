#include "GameTest.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

    const string pokemonFileName = "file/PokemonLib.txt";
    const string moveFileName = "file/MoveLib.txt";
    const string gameDataFileName = "file/GameData.txt";

    if (argc > 1 && string(argv[1]) == "Test") {
        ifstream testFile("file/TestCase.txt");
        GameTest game(pokemonFileName, moveFileName, gameDataFileName, testFile);
        game.serve();
        testFile.close();
    } else {
        // GameAI game(pokemonFileName, moveFileName, gameDataFileName);
        // game.serve();
    }

    cin.ignore(1000);
    return 0;
}
