#pragma once

#include <vector>
#include <queue>
#include <algorithm>
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
            std::cout << name << std::endl;
            throw MoveNotFoundError(moveName);
        }
        return it->second;
    }

    [[nodiscard]] const std::map<std::string, Move> &getMoveMap() const {
        return moveMap;
    }

    bool operator==(const std::string &pokemonName) const {
        return name == pokemonName;
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
    void addOutput(const std::string &message);
    void outputParalyzed(const std::string &attackerName, bool isOpponent);
    void outputMove(const std::string &attackerName, const std::string &moveName, bool isOpponent);
    void outputAvoid(const std::string &defenderName, bool isOpponent);
    void outputTypeEffect(double effect);
    void outputCriticalHit();
    void outputAdditionalEffect(const std::string &defenderName, Status status, bool isOpponent);
    void outputPerformStatus(const std::string &pokemonName, Status status, bool isOpponent);
    void outputStatus();
    void outputCheck();
    void outputPotion(const std::string &pokemonName, const std::string &potionName, bool isOpponent);
    void outputFainted(const std::string &defenderName, bool isOpponent);
    void outputComeBack(const std::string &pokemonName, bool isOpponent);
    void outputGo(const std::string &pokemonName, bool isOpponent);
    void outputWin(bool isOpponent);
    void flushOutputs(std::ostream &out);

    void playerSwapPokemon(const std::string &pokemonName);
    void opponentSwapPokemon(const std::string &pokemonName);
    void playerUsePotion(const std::string &potionName, const std::string &pokemonName);
    void opponentUsePotion(const std::string &potionName, const std::string &pokemonName);

public:
    GameBase(const std::string &pokemonFileName, const std::string &moveFileName, const std::string &gameDataFileName);

    virtual void serve() = 0;
};
