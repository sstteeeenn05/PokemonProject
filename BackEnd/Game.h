//
// Created by tomjojo on 2023/5/30.
//

#pragma once

#include"Header.h"

#include"Pokemon.h"

class Game{
    const double typeEff[TYPE_COUNT][TYPE_COUNT] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1,1,0.5,1},
        {1,0.5,0.5,1,2,2,1,1,1,1,1,2,0.5,1,0.5,1,2,1},
        {1,2,0.5,1,0.5,1,1,1,2,1,1,1,2,1,0.5,1,1,1},
        {1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5,1,1,1},
        {1,0.5,2,1,0.5,1,1,0.5,2,0.5,1,0.5,2,1,0.5,1,0.5,1},
        {1,0.5,0.5,1,2,0.5,1,1,2,2,1,1,1,1,2,1,0.5,1},
        {2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1,2,2,0.5},
        {1,1,1,1,2,1,1,0.5,0.5,1,1,1,0.5,0.5,1,1,0,2},
        {1,2,1,2,0.5,1,1,2,1,0,1,0.5,2,1,1,1,2,1},
        {1,1,1,0.5,2,1,2,1,1,1,1,2,0.5,1,1,1,0.5,1},
        {1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1,0,0.5,1},
        {1,0.5,1,1,2,1,0.5,0.5,1,0.5,2,1,1,0.5,1,2,0.5,0.5},
        {1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1,1,0.5,1},
        {0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5,0},
        {1,1,1,1,1,1,0.5,1,1,1,2,1,1,2,1,0.5,1,0.5},
        {1,0.5,0.5,0.5,1,2,1,1,1,1,1,1,2,1,1,1,0.5,2},
        {1,0.5,1,1,1,1,2,0.5,1,1,1,1,1,1,2,2,0.5,1}
    };
    vector<Pokemon> pokemon;
    map<string, Pokemon> pokemons;

public:
    Game() = default;
    void addPokemon(Pokemon&);
    void reset();
    queue<string> move(string, string, string, Type, bool, int, int, Status);
    double calcTypeEff(Type, vector<Type>);
    void print();

    Game(Pokemon& pokemon1,Pokemon& pokemon2);
    void attack(string name,vector<string> type, string moveType,int power,int accuracy);
    double typeCount();

};
