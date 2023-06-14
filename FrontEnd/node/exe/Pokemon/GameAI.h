#pragma once

#include "GameBase.h"

using namespace std;

class GameAI: public GameBase{
    GameAI(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName) :
            GameBase(pokemonFileName, moveFileName, gameDataFileName) {};

    void serve() override;

    void calc();
    int getDamage(Move& move,Pokemon& attacker, Pokemon& defender);

    Move& atk( BattlePokemon& token, BattlePokemon& enemy);
};

