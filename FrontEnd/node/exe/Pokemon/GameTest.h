#pragma once

#include "GameBase.h"

using namespace std;

class GameTest : public GameBase {
private:
    istream &input;

public:
    GameTest(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName,
             istream &input);
    void serve(std::ostream&) override;

    bool battle();
    bool bag();
    bool swap();
    bool move(const Pokemon &attacker, Pokemon &defender, Move &move, bool isOpponent);
    bool performStatus();
    bool checkWin(bool isOpponent);
};
