#pragma once

#include "GameBase.h"

using namespace std;

class GameTest : public GameBase {
public:
    GameTest(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName) :
            GameBase(pokemonFileName, moveFileName, gameDataFileName) {};

    void serve() override;
};
