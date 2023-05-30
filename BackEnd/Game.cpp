//
// Created by tomjojo on 2023/5/30.
//
#include "Game.h"

void Game::attack(string name, vector<string> type, string moveType, int power, int accuracy) {
    //miss
    if(  (rand() % 100) > accuracy )return ;

    // Define which pokemon
    Pokemon &atkPokemon = pokemon[0],&defPokemon = pokemon[1];
    if(pokemon[1].getName() == name){
        atkPokemon = pokemon[1];
        defPokemon = pokemon[0];
    }

    int A = atkPokemon.getAtk(),D = atkPokemon.getDef();
    if(moveType == "Special") {
        A = atkPokemon.getSpAtk();
        D = atkPokemon.getSpDef();
    }

    //Temp
    double critical = rand() & 1 ? 1.5 : 1;

    double STAB = 1;
    auto types = atkPokemon.getType();
    for(auto i : type){
        if(find(types.begin(),types.end(),i) != types.end())  {
            STAB = 1.5;
            break;
        }
    }

    double Type = typeCount();



    double damage = ((((2 * atkPokemon.getLevel() + 10) / 250) * power *  A / D) + 2) * critical * STAB * Type;

    defPokemon.changeHp(-1 * (int)damage);
}

double Game::typeCount() {
    return 1;
}

Game::Game(Pokemon& pokemon1, Pokemon& pokemon2) {
    pokemon.push_back((pokemon1));
    pokemon.push_back((pokemon2));
}
