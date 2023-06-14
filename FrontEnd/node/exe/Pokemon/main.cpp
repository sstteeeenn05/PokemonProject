#include "GameTest.h"
#include "GameAI.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

    string path(argv[0]);
    path=path.substr(0, path.rfind('\\'));
    const string pokemonFileName = path + "/file/PokemonLib.txt";
    const string moveFileName = path + "/file/MoveLib.txt";
    const string gameDataFileName = path + "/file/GameData.txt";
    const string testFileName = path + "/file/TestCase.txt";

    if (/*argc > 1 && string(argv[1]) == "Test"*/false) {
        ifstream testFile(testFileName);
        if (!testFile.is_open()) {
            throw FileOpenError(testFileName);
        }
        GameTest game(pokemonFileName, moveFileName, gameDataFileName, testFile);
        ofstream outputFile(path + "/TestOutput.txt");
        game.serve(outputFile);
        testFile.close();
        outputFile.close();
    }
    else {
        GameAI game(pokemonFileName, moveFileName, gameDataFileName);
        ofstream outputFile(path + "/TestOutput.txt");
        game.serve(outputFile);
    }
    cin.ignore(1000);
    return 0;
}
