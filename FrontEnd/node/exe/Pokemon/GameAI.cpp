#include "GameAI.h"

#include <sstream>

using namespace std;

GameAI::GameAI(const std::string &pokemonFileName, const std::string &moveFileName,
               const std::string &gameDataFileName, std::istream &input) :
        GameBase(pokemonFileName, moveFileName, gameDataFileName), input(input) {}

void GameAI::serve() {
    stringstream stream;
    for (string command; getline(input, command); flushOutputs(stream)) {
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

        computerMove();
    }
    flushOutputs(stream);
    cout << stream.str() << endl;
}

Move &GameAI::getBestAction(const BattlePokemon &defender, BattlePokemon &attacker) {
    map<string, Move>::const_iterator bestMoveIt;
    double maxDamage = 0;

    const auto &moves = attacker.getMoveMap();
    for (auto it = moves.cbegin(); it != moves.cend(); ++it) {
        double damage = getExpectDamage(it->second, defender, attacker);

        if (damage > maxDamage) {
            maxDamage = damage;
            bestMoveIt = it;
        }
    }
    return temp;
}

double GameAI::getBestActionValue(const BattlePokemon &defender, const BattlePokemon &attacker) {
    double maxDamage = 0;
    auto moves = attacker.getMoveMap();

    for (auto &move: moves) {
        double damage = getExpectDamage(move.second, attacker, defender);
        if (damage > maxDamage) {
            maxDamage = damage;
        }
    }
    return maxDamage;
}

void GameAI::computerMove() {
    BattlePokemon &pokemon1 = playerPokemonIt->second;
    BattlePokemon &pokemon2 = *opponentPokemonIt;

    // change pokemon

    if (pokemon2.getHp() < 0) {
        computerSwap(pokemon2,pokemon1);
        return;
    }

    // heal
    Move &opponentMaxAct = getBestAction(pokemon2, pokemon1);
    int maxOpponentDamage = getDamage(opponentMaxAct, pokemon1, pokemon2);

    if (maxOpponentDamage > pokemon2.getHp()) {
        if (maxOpponentDamage > pokemon2.getMaxHp()) {
            computerSwap(pokemon2,pokemon1);
            return;
        }
        // use potion
        opponentUsePotion("HyperPotion",pokemon2.getName());
        return;
    }

    // can kill
    Move& mineMaxAct = getBestAction(pokemon1, pokemon2);

    const int damage = getDamage(mineMaxAct,pokemon2,pokemon1);

    mineMaxAct.use();
    bool isOpponent = true;
    outputMove(pokemon2.getName(), mineMaxAct.getName(), isOpponent);
    if (pokemon2.hasStatus(Status::PARALYSIS)) {
        outputParalyzed(pokemon2.getName(), isOpponent);
        return;
    }

    const int baseDamage = mineMaxAct.calcBaseDamage(pokemon2, pokemon1);
    const double stab = mineMaxAct.calcSTAB(pokemon1.getTypeList());
    const double typeEffect = mineMaxAct.calcTypeEffect(pokemon1.getTypeList());
    outputTypeEffect(typeEffect);

    if (mineMaxAct.getAdditionalEffect() != Status::NONE) {
        pokemon1.addStatus(mineMaxAct.getAdditionalEffect());
        outputAdditionalEffect(pokemon2.getName(), mineMaxAct.getAdditionalEffect(), isOpponent);
    }

    move(pokemon2,pokemon1,mineMaxAct, isOpponent);
}

int GameAI::getDamage(Move& move,Pokemon& attacker, Pokemon& defender) {
    const int baseDamage = move.calcBaseDamage(attacker, defender);
    const double stab = move.calcSTAB(defender.getTypeList());
    const double typeEffect = move.calcTypeEffect(defender.getTypeList());
    const int damage = static_cast<int>(baseDamage * stab * typeEffect);
    return damage;
}

bool GameAI::battle() {
    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;
    if (playerPokemon.isFainting()) {
        throw InvalidCommandError(playerPokemon.getName() + " is fainted, thus must be swapped first");
    }

    string playerMoveName, opponentMoveName;
    getline(input, playerMoveName);

    Move &playerMove = playerPokemon.getMove(playerMoveName);
    move(playerPokemon, opponentPokemon, playerMove, false) ;

    return performStatus();
}

bool GameAI::bag() {
    if (playerPokemonIt->second.isFainting()) {
        throw InvalidCommandError(playerPokemonIt->second.getName() + " is fainted, thus must be swapped first");
    }
    string potionName, pokemonName;
    getline(input, potionName);
    getline(input, pokemonName);
    playerUsePotion(potionName, pokemonName);
    outputPotion(pokemonName, potionName, false);
    return true;
    /*
    string opponentMoveName;
    getline(input, opponentMoveName);

    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;
    Move &opponentMove = opponentPokemon.getMove(opponentMoveName);

    if (move(opponentPokemon, playerPokemon, opponentMove, true)) {
        return true;
    }
    return performStatus();*/
}

bool GameAI::swap() {
    string pokemonName;
    getline(input, pokemonName);
    playerSwapPokemon(pokemonName);
    if (!playerPokemonIt->second.isFainting()) {
        outputComeBack(playerPokemonIt->second.getName(), false);
    }
    outputGo(pokemonName, false);
    return true;
    /*
    string opponentMoveName;
    getline(input, opponentMoveName);

    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;
    Move &opponentMove = opponentPokemon.getMove(opponentMoveName);

    if (move(opponentPokemon, playerPokemon, opponentMove, true)) {
        return true;
    }
    return performStatus();*/
}

bool GameAI::move(const Pokemon &attacker, Pokemon &defender, Move &move, const bool isOpponent) {
    move.use();
    outputMove(attacker.getName(), move.getName(), isOpponent);
    if (attacker.hasStatus(Status::PARALYSIS)) {
        outputParalyzed(attacker.getName(), isOpponent);
        return false;
    }

    const int baseDamage = move.calcBaseDamage(attacker, defender);
    const double stab = move.calcSTAB(defender.getTypeList());
    const double typeEffect = move.calcTypeEffect(defender.getTypeList());
    outputTypeEffect(typeEffect);

    if (move.getAdditionalEffect() != Status::NONE) {
        defender.addStatus(move.getAdditionalEffect());
        outputAdditionalEffect(defender.getName(), move.getAdditionalEffect(), isOpponent);
    }

    const int damage = static_cast<int>(baseDamage * stab * typeEffect);
    defender.damage(damage);
    return checkWin(isOpponent);
}

bool GameAI::performStatus() {
    BattlePokemon &playerPokemon = playerPokemonIt->second;
    BattlePokemon &opponentPokemon = * opponentPokemonIt;

    playerPokemon.performStatus();
    opponentPokemon.performStatus();
    for (const Status status: playerPokemon.getStatusList()) {
        outputPerformStatus(playerPokemon.getName(), status, false);
    }
    for (const Status status: opponentPokemon.getStatusList()) {
        outputPerformStatus(opponentPokemon.getName(), status, true);
    }
    return checkWin(false) || checkWin(true);
}

bool GameAI::checkWin(const bool isOpponent) {
    if (isOpponent) {
        if (opponentPokemonIt->isFainting()) {
            outputFainted(opponentPokemonIt->getName(), true);
            ++opponentPokemonIt;
            if (opponentPokemonIt == opponentPokemonList.cend()) {
                outputWin(true);
                return true;
            }
            outputGo(opponentPokemonIt->getName(), true);
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
            outputWin(false);
            return true;
        }
        return false;
    }
}

void GameAI::computerSwap(BattlePokemon &player, BattlePokemon &enemy) {
    string maxPokemonName;
    double maxPokemonDamage = 0;
    bool isOpponent = true;

    for (const BattlePokemon &pokemon: opponentPokemonList) {
        double temp = getBestActionValue(pokemon, enemy);
        if (maxPokemonDamage < temp){
            maxPokemonDamage = temp;
            maxPokemonName = pokemon.getName();
        }
    }

    opponentSwapPokemon(maxPokemonName);
    outputGo(maxPokemonName, isOpponent);
}
