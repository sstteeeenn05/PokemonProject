#pragma once

#include "GameBase.h"

using namespace std;

class GameAI: public GameBase{
private:
    istream &input;

public:
    GameAI(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName,
             istream &input);

    void serve() override;

    void battle();
    static int getDamage(Move& move,Pokemon& attacker, Pokemon& defender);

    Move& atk( BattlePokemon& token, BattlePokemon& enemy);
};

