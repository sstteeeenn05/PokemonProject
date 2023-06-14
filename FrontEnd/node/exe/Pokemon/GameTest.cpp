#include "GameTest.h"
#include <sstream>
#include <fstream>

GameTest::GameTest(const std::string &pokemonFileName, const std::string &moveFileName,
                   const std::string &gameDataFileName, std::istream &input) :
        GameBase(pokemonFileName, moveFileName, gameDataFileName), input(input) {

    for (string line; getline(input, line) && line != "Test";) {}
}

void GameTest::serve() {
    turn = 1;
    ofstream outputFile("TestOutput.txt");
    for (string command; getline(input, command);) {
        if (command == "Status") {
            outputStatus();
            continue;
        } else if (command == "Check") {
            outputCheck();
            continue;
        } else if (command == "Run") {
            break;
        }

        if (command == "Battle") {
            if (battle()) {
                break;
            }
        } else if (command == "Bag") {
            if (bag()) {
                break;
            }
        } else if (command == "Pokemon") {
            if (swap()) {
                break;
            }
        } else {
            throw InvalidCommandError("unknown command " + command);
        }
        flushOutputs(outputFile);
        ++turn;
    }
    flushOutputs(outputFile);
    outputFile.close();
}

bool GameTest::battle() {
    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;
    if (playerPokemon.isFainting()) {
        throw InvalidCommandError(playerPokemon.getName() + " is fainted, thus must be swapped first");
    }

    string playerMoveName, opponentMoveName;
    getline(input, playerMoveName);
    getline(input, opponentMoveName);

    Move &playerMove = playerPokemon.getMove(playerMoveName);
    Move &opponentMove = opponentPokemon.getMove(opponentMoveName);

    // both move
    if (playerPokemon.isFaster(opponentPokemon)) {
        if (move(playerPokemon, opponentPokemon, playerMove, false)) {
            if (checkWin(false)) {
                return true;
            }
        } else if (move(opponentPokemon, playerPokemon, opponentMove, true)) {
            if (checkWin(true)) {
                return true;
            }
        }
    } else {
        if (move(opponentPokemon, playerPokemon, opponentMove, true)) {
            if (checkWin(true)) {
                return true;
            }
        } else if (move(playerPokemon, opponentPokemon, playerMove, false)) {
            if (checkWin(false)) {
                return true;
            }
        }
    }
    return performStatus();
}

bool GameTest::bag() {
    if (playerPokemonIt->second.isFainting()) {
        throw InvalidCommandError(playerPokemonIt->second.getName() + " is fainted, thus must be swapped first");
    }
    string potionName, pokemonName;
    getline(input, potionName);
    getline(input, pokemonName);
    playerUsePotion(potionName, pokemonName);
    outputPotion(pokemonName, potionName, false);

    string opponentMoveName;
    getline(input, opponentMoveName);

    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;
    Move &opponentMove = opponentPokemon.getMove(opponentMoveName);

    if (move(opponentPokemon, playerPokemon, opponentMove, true) && checkWin(true)) {
        return true;
    }
    return performStatus();
}

bool GameTest::swap() {
    string pokemonName;
    getline(input, pokemonName);
    if (!playerPokemonIt->second.isFainting()) {
        outputComeBack(playerPokemonIt->second.getName(), false);
    }
    playerSwapPokemon(pokemonName);
    outputGo(pokemonName, false);

    string opponentMoveName;
    getline(input, opponentMoveName);

    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;
    Move &opponentMove = opponentPokemon.getMove(opponentMoveName);

    if (move(opponentPokemon, playerPokemon, opponentMove, true)) {
        return true;
    }
    return performStatus();
}

bool GameTest::move(const Pokemon &attacker, Pokemon &defender, Move &move, const bool isOpponent) {
    move.use();
    if (attacker.hasStatus(Status::PARALYSIS)) {
        outputParalyzed(attacker.getName(), isOpponent);
        return false;
    }

    const int baseDamage = move.calcBaseDamage(attacker, defender);
    const double stab = move.calcSTAB(attacker.getTypeList());
    const double typeEffect = move.calcTypeEffect(defender.getTypeList());
    defender.addStatus(move.getAdditionalEffect());

    const int damage = static_cast<int>(baseDamage * stab * typeEffect);
    defender.damage(damage);

    outputMove(attacker.getName(), move.getName(), isOpponent);
    if (move.getDamageType() != DamageType::STATUS) {
        outputTypeEffect(typeEffect);
    }
    if (move.getAdditionalEffect() != Status::NONE) {
        outputAdditionalEffect(defender.getName(), move.getAdditionalEffect(), !isOpponent);
    }
    return defender.isFainting();
}

bool GameTest::performStatus() {
    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;

    playerPokemon.performStatus();
    opponentPokemon.performStatus();
    if (checkWin(false) || checkWin(true)) {
        return true;
    }

    if (!playerPokemon.isFainting()) {
        for (const Status status: playerPokemon.getStatusList()) {
            outputPerformStatus(playerPokemon.getName(), status, false);
        }
    }
    if (!opponentPokemon.isFainting()) {
        for (const Status status: opponentPokemon.getStatusList()) {
            outputPerformStatus(opponentPokemon.getName(), status, true);
        }
    }
    return false;
}

bool GameTest::checkWin(const bool isOpponent) {
    if (isOpponent) {
        if (opponentPokemonIt->isFainting()) {
            outputFainted(opponentPokemonIt->getName(), true);
            ++opponentPokemonIt;
            if (opponentPokemonIt == opponentPokemonList.cend()) {
                outputWin(false);
                return true;
            }
        }
        return false;
    } else {
        if (playerPokemonIt->second.isFainting()) {
            outputFainted(playerPokemonIt->second.getName(), false);
            for (const auto &pair: playerPokemonMap) {
                if (!pair.second.isFainting()) {
                    return false;
                }
            }
            outputWin(true);
            return true;
        }
        return false;
    }
}