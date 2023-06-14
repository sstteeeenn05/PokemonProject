#pragma once

#include <vector>
#include <queue>
#include "Move.h"
#include "GameError.h"

class BattlePokemon : public Pokemon {
private:
    std::map<std::string, Move> moveMap;

public:
    BattlePokemon(Pokemon pokemon, std::map<std::string, Move> moveMap) :
            Pokemon(std::move(pokemon)), moveMap(std::move(moveMap)) {}

    Move &getMove(const std::string &moveName) {
        const auto it = moveMap.find(moveName);
        if (it == moveMap.cend()) {
            throw InvalidMoveError(moveName);
        }
        return it->second;
    }
};

class GameBase {
protected:
    std::map<std::string, BattlePokemon> playerPokemonMap;
    std::map<std::string, BattlePokemon>::iterator playerPokemonIt;
    std::vector<BattlePokemon> opponentPokemonList;
    std::vector<BattlePokemon>::iterator opponentPokemonIt;

    int turn = 1;
    std::queue<std::string> outputs;

    static std::string opponentPrefix(const std::string &pokemonName, bool isOpponent = true);
    void outputParalyzed(const std::string &attackerName, bool isOpponent);
    void outputMove(const std::string &attackerName, const std::string &moveName, bool isOpponent);
    void outputAvoid(const std::string &defenderName, bool isOpponent);
    void outputTypeEffect(double effect);
    void outputCriticalHit();
    void outputAdditionalEffect(const std::string &defenderName, Status status, bool isOpponent);
    void outputPerformStatus(const std::string &pokemonName, Status status, bool isOpponent);
    void outputStatus();
    void outputPotion(const std::string &pokemonName, const std::string &potionName, bool isOpponent);
    void outputComeBack(const std::string &pokemonName, bool isOpponent);
    void outputGo(const std::string &pokemonName, bool isOpponent);
    void outputWin(bool isOpponent);
    void flushOutputs();

    void playerSwapPokemon(const std::string &pokemonName);
    void opponentSwapPokemon();



public:
    GameBase(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName);

    virtual void serve() = 0;
};
