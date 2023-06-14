#include "GameBase.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace {
    BattlePokemon readPokemon(std::map<std::string, Pokemon> &pokemonMap, std::map<std::string, Move> &moveMap,
                              std::istream &input) {
        std::string pokemonName;
        size_t moveCount;
        input >> pokemonName >> moveCount;
        const auto pokemonIt = pokemonMap.find(pokemonName);
        if (pokemonIt == pokemonMap.cend()) {
            throw PokemonNotfoundError(pokemonName);
        }

        std::map<std::string, Move> moveList;
        for (size_t j = 0; j < moveCount; ++j) {
            std::string moveName;
            input >> moveName;
            const auto moveIt = moveMap.find(moveName);
            if (moveIt == moveMap.cend()) {
                throw MoveNotFoundError(moveName);
            }
            moveList.emplace(moveName, moveIt->second);
        }
        return {pokemonIt->second, std::move(moveList)};
    }
}

GameBase::GameBase(const std::string &pokemonFile, const std::string &moveFile, const std::string &gameDataFile) {
    std::map<std::string, Pokemon> pokemonMap;
    std::map<std::string, Move> moveMap;

    // open Pokemon file and read Pokemon
    std::fstream inputFile(pokemonFile);
    if (!inputFile.is_open()) {
        throw FileOpenError(pokemonFile);
    }
    for (std::string name; inputFile >> name;) {
        pokemonMap.insert({name, Pokemon::fromInput(inputFile, name)});
    }
    inputFile.close();

    // open move file and read move
    inputFile.open(moveFile);
    if (!inputFile.is_open()) {
        throw FileOpenError(moveFile);
    }
    for (std::string name; inputFile >> name;) {
        moveMap.insert({name, Move::fromInput(inputFile, name)});
    }
    inputFile.close();

    // open game data file and read player's Pokemon
    inputFile.open(gameDataFile);
    if (!inputFile.is_open()) {
        throw FileOpenError(gameDataFile);
    }
    size_t pokemonCount;
    inputFile >> pokemonCount;
    if (pokemonCount == 0) {
        throw NoPokemonError();
    }
    std::string currentPokemonName;
    {
        BattlePokemon pokemon = readPokemon(pokemonMap, moveMap, inputFile);
        currentPokemonName = pokemon.getName();
        playerPokemonMap.emplace(pokemon.getName(), std::move(pokemon));
    }
    for (size_t i = 1; i < pokemonCount; ++i) {
        BattlePokemon pokemon = readPokemon(pokemonMap, moveMap, inputFile);
        playerPokemonMap.emplace(pokemon.getName(), std::move(pokemon));
    }
    playerPokemonIt = playerPokemonMap.find(currentPokemonName);

    // read opponent's Pokemon
    inputFile >> pokemonCount;
    if (pokemonCount == 0) {
        throw NoPokemonError();
    }
    for (size_t i = 0; i < pokemonCount; ++i) {
        opponentPokemonList.emplace_back(std::move(readPokemon(pokemonMap, moveMap, inputFile)));
    }
    opponentPokemonIt = opponentPokemonList.begin();
    inputFile.close();
}

std::string GameBase::opponentPrefix(const std::string &pokemonName, const bool isOpponent) {
    return isOpponent ? "The opposing " + pokemonName : pokemonName;
}

void GameBase::addOutput(const std::string &message) {
    std::stringstream stream;
    stream << message;
    for (const auto &pokemonPair: playerPokemonMap) {
        stream << '$' << pokemonPair.first << ' ' << pokemonPair.second.getHp();
        for (const auto &movePair: pokemonPair.second.getMoveMap()) {
            stream << ' ' << movePair.second.getName() << ' ' << movePair.second.getPowerPoint();
        }
        stream << pokemonPair.second.getStatusString();
    }

    for (const BattlePokemon &pokemon: opponentPokemonList) {
        stream << '$' << pokemon.getName() << ' ' << pokemon.getHp();
        for (const auto &movePair: pokemon.getMoveMap()) {
            stream << ' ' << movePair.second.getName() << ' ' << movePair.second.getPowerPoint();
        }
        stream << pokemon.getStatusString();
    }
    outputs.emplace(stream.str());
}

void GameBase::outputParalyzed(const std::string &attackerName, const bool isOpponent) {
    addOutput(opponentPrefix(attackerName, isOpponent) + " is paralyzed!");
    addOutput("It can't move!");
}

void GameBase::outputMove(const std::string &attackerName, const std::string &moveName, const bool isOpponent) {
    addOutput(opponentPrefix(attackerName, isOpponent) + " used " + moveName + '!');
}

void GameBase::outputAvoid(const std::string &defenderName, const bool isOpponent) {
    addOutput(opponentPrefix(defenderName, isOpponent) + " avoid the attack!");
}

void GameBase::outputTypeEffect(const double effect) {
    if (effect >= 2.0) {
        addOutput("It's super effective!");
    } else if (effect <= 0.5) {
        addOutput("It's not very effective...");
    } else if (effect == 0.0) {
        addOutput("It's not effective!");
    }
}

void GameBase::outputCriticalHit() {
    addOutput("A critical hit!");
}

void GameBase::outputAdditionalEffect(const std::string &defenderName, const Status status, const bool isOpponent) {
    const std::string pokemonName = opponentPrefix(defenderName, isOpponent);
    switch (status) {
        case Status::PARALYSIS:
            addOutput(pokemonName + " is paralyzed, so it may be unable to move!");
            break;
        case Status::BURN:
            addOutput(pokemonName + " was burned!");
            break;
        case Status::POISON:
            addOutput(pokemonName + " was poisoned!");
            break;
        default:
            break;
    }
}

void GameBase::outputPerformStatus(const std::string &pokemonName, Status status, const bool isOpponent) {
    if (status == Status::BURN) {
        addOutput(opponentPrefix(pokemonName, isOpponent) + " is hurt by its burn!");
    } else if (status == Status::POISON) {
        addOutput(opponentPrefix(pokemonName, isOpponent) + " is hurt by its poisoning!");
    }
}

void GameBase::outputStatus() {
    const BattlePokemon &playerPokemon = playerPokemonIt->second;
    const BattlePokemon &opponentPokemon = * opponentPokemonIt;
    addOutput(playerPokemon.getName() + ' ' + std::to_string(playerPokemon.getHp()) +
              playerPokemon.getStatusString() + ' ' +
              opponentPokemon.getName() + ' ' + std::to_string(opponentPokemon.getHp()) +
              opponentPokemon.getStatusString());
}

void GameBase::outputCheck() {
    std::stringstream stream;
    for (const auto &pair: playerPokemonIt->second.getMoveMap()) {
        stream << pair.second.getName() << ' ' << pair.second.getPowerPoint() << ' ';
    }
    addOutput(stream.str());
}

void GameBase::outputPotion(const std::string &pokemonName, const std::string &potionName, const bool isOpponent) {
    addOutput(std::string(isOpponent ? "Opponent" : "You") + " used a " + potionName + '!');
    addOutput(opponentPrefix(pokemonName, isOpponent) + " had its HP restored.");
}

void GameBase::outputFainted(const std::string &defenderName, const bool isOpponent) {
    addOutput(opponentPrefix(defenderName, isOpponent) + " fainted!");
}

void GameBase::outputComeBack(const std::string &pokemonName, const bool isOpponent) {
    if (isOpponent) {
        addOutput("(Opponent) " + pokemonName + ", switch out!");
        addOutput("(Opponent) Come back!");
    } else {
        addOutput(pokemonName + ", switch out!");
        addOutput("Come back!");
    }
}

void GameBase::outputGo(const std::string &pokemonName, const bool isOpponent) {
    if (isOpponent) {
        addOutput("(Opponent) Go! " + pokemonName + '!');
    } else {
        addOutput("Go! " + pokemonName + '!');
    }
}

void GameBase::outputWin(const bool isOpponent) {
    addOutput(isOpponent ? "You lose" : "You win");
}

void GameBase::flushOutputs(std::ostream &out) {
    const std::string prefix = "[Turn " + std::to_string(turn) + "] ";
    while (!outputs.empty()) {
        std::string output = outputs.front();
        out << prefix << output << ';' << std::endl;
        outputs.pop();
    }
}

void GameBase::playerSwapPokemon(const std::string &pokemonName) {
    const auto it = playerPokemonMap.find(pokemonName);
    if (it == playerPokemonMap.cend()) {
        throw PokemonNotfoundError(pokemonName);
    }
    if (it->second.isFainting()) {
        throw InvalidPokemonError(pokemonName + " is fainted");
    }
    playerPokemonIt = it;
}

void GameBase::opponentSwapPokemon(const std::string &pokemonName) {
    const auto it = std::find(opponentPokemonList.begin(), opponentPokemonList.end(), pokemonName);
    if (it == opponentPokemonList.cend()) {
        throw PokemonNotfoundError(pokemonName);
    }
    if (it->isFainting()) {
        throw InvalidPokemonError(pokemonName + " is fainted");
    }
    opponentPokemonIt = it;
}

void GameBase::playerUsePotion(const std::string &potionName, const std::string &pokemonName) {
    const auto it = playerPokemonMap.find(pokemonName);
    if (it == playerPokemonMap.cend()) {
        throw PokemonNotfoundError(pokemonName);
    }
    if (it->second.isFainting()) {
        throw InvalidPokemonError(pokemonName + " is fainted");
    }
    it->second.heal(PotionMap.at(potionName));
}

void GameBase::opponentUsePotion(const std::string &potionName, const std::string &pokemonName) {
    const auto it = std::find(opponentPokemonList.begin(), opponentPokemonList.end(), pokemonName);
    if (it == opponentPokemonList.cend()) {
        throw PokemonNotfoundError(pokemonName);
    }
    if (it->isFainting()) {
        throw InvalidPokemonError(pokemonName + " is fainted");
    }
    it->heal(PotionMap.at(potionName));
}


