//
// Created by tomjojo on 2023/5/30.
//
#include "Game.h"

void Game::addPokemon(Pokemon& pokemon) {
    pokemons[pokemon.name] = pokemon;
}

void Game::reset() {
    pokemons.clear();
}
Game::Game(Pokemon& pokemon1, Pokemon& pokemon2) {
    addPokemon(pokemon1);
    addPokemon(pokemon2);
}

void Game::init(Pokemon pokemon1,Pokemon pokemon2){
    addPokemon(pokemon1);
    addPokemon(pokemon2);
}

queue<string> Game::move(string who, string target, Type type, bool isPhysical, int power, int accuracy, Status status) {
    if (rand() % 100 > accuracy) return queue<string>({ "avoided the attack!" });

    Pokemon& atk = pokemons[who];
    Pokemon& def = pokemons[target];

    int A = isPhysical ? atk.atk : def.spAtk;
    int D = isPhysical ? atk.def : def.spDef;

    bool isCritical = rand() & 1;

    vector<Type> types = atk.type;
    bool isStab = find(types.cbegin(), types.cend(), type) != types.cend();

    int damage = ((2.0 * atk.level + 10) / 250.0 * power * (A / D) + 2) * (isCritical ? 1.5 : 1) * (isStab ? 1.5 : 1) * calcTypeEff(type, def.type);
    def.damage(damage);
    
    def.addStatus(status);
    if (def.hasStatus(POISON)) def.damage(def.maxHp / 16);
    if (def.hasStatus(BURN)) def.damage(def.maxHp / 16);

    return queue<string>({ "damage" , to_string(damage)});
}

double Game::calcTypeEff(Type atk, vector<Type> defs) {
    double value = 1;
    for (auto def : defs) value *= typeEff[atk][def];
    return value;
}

void Game::print() {
    for (int i = 0; i < TYPE_COUNT; i++) {
        for (int j = 0; j < TYPE_COUNT; j++) {
            if (typeEff[i][j] == 2) printf("��");
            if (typeEff[i][j] == 1) printf("�@");
            if (typeEff[i][j] == 0.5) printf("��");
            if (typeEff[i][j] == 0) printf("��");
        }
        puts("");
    }
}

double Game::typeCount() {
    return 1;
}


