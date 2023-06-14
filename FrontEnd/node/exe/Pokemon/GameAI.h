#pragma once

#include "GameBase.h"

using namespace std;

class GameAI : public GameBase {



    const Pokemon &getBestPokemon(const vector<Pokemon> &pokemonList) {
        return *max_element(pokemonList.cbegin(), pokemonList.cend(), [](const Pokemon &pokemon1, const Pokemon &pokemon2) {
            return true;
        });
    }
};
