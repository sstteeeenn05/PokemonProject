#pragma once

#include "GameBase.h"

using namespace std;

class GameAI: public GameBase{
private:
    istream &input;

public:
    GameAI(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName,
             istream &input = cin);

    void serve(std::ostream&) override;
    void computerMove();
    void computerSwap(BattlePokemon &enemy);

    static Move &getBestAction(const BattlePokemon &defender, BattlePokemon &attacker);
    static double getBestActionValue(const BattlePokemon &defender, const BattlePokemon &attacker);
    static int getDamage(const Move &move, const Pokemon &attacker, const Pokemon &defender);
    static double getExpectDamage(const Move &move, const Pokemon &attacker, const Pokemon &defender);

    bool battle();
    bool bag();
    bool swap();
    bool checkWin(bool isOpponent);
    bool performStatus();
    bool move(const Pokemon &attacker, Pokemon &defender, Move &move, bool isOpponent);
};

