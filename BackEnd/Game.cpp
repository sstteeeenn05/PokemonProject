//
// Created by tomjojo on 2023/5/30.
//
#include "Game.h"

void Game::addPokemon(Pokemon& pokemon) {
    pokemons[pokemon.getName()] = pokemon;
}

void Game::reset() {
    pokemons.clear();
}

queue<string> Game::move(string who, string target, string name, Type type, bool isPhysical, int power, int accuracy, Status status) {
    if (rand() % 100 > accuracy) return queue<string>({ "avoided the attack!" });

    Pokemon& atk = pokemons[who];
    Pokemon& def = pokemons[target];

    int A = isPhysical ? atk.getAtk() : def.getSpAtk();
    int D = isPhysical ? atk.getDef() : def.getSpDef();

    bool isCritical = rand() & 1;

    auto& types = atk.getType();
    bool isStab = find(types.cbegin(), types.cend(), type) != types.cend();

    int damage = ((double)(2 * atk.getLevel() + 10) / 250.0 * power * ((double)A / D) + 2) * (isCritical ? 1.5 : 1) * (isStab ? 1.5 : 1) * calcTypeEff(type, def.getType());
    def.damage(damage);
    
    def.addStatus(status);
    if (def.hasStatus(POISON)) def.damage(def.getMaxHp() / 16);
    if (def.hasStatus(BURN)) def.damage(def.getMaxHp() / 16);
}

double Game::calcTypeEff(Type atk, vector<Type>& defs) {
    double value = 1;
    for (auto def : defs) value *= typeEff[atk][def];
    return value;
}

void Game::print() {
    for (int i = 0; i < TYPE_COUNT; i++) {
        for (int j = 0; j < TYPE_COUNT; j++) {
            if (typeEff[i][j] == 2) printf("¡´");
            if (typeEff[i][j] == 1) printf("¡@");
            if (typeEff[i][j] == 0.5) printf("¡¿");
            if (typeEff[i][j] == 0) printf("¡³");
        }
        puts("");
    }
}

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
    /*auto types = atkPokemon.getType();
    for(auto i : type){
        if(find(types.begin(),types.end(),i) != types.end())  {
            STAB = 1.5;
            break;
        }
    }*/

    double Type = typeCount();



    double damage = ((((2 * atkPokemon.getLevel() + 10) / 250) * power *  A / D) + 2) * critical * STAB * Type;

    defPokemon.damage((int)damage);
}

double Game::typeCount() {
    return 1;
}

Game::Game(Pokemon& pokemon1, Pokemon& pokemon2) {
    pokemon.push_back((pokemon1));
    pokemon.push_back((pokemon2));
}
