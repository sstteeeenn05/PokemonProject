//
// Created by tomjojo on 2023/6/3.
//

#ifndef BACKEND_GAMEMANAGER_H
#define BACKEND_GAMEMANAGER_H

#include "Header.h"
#include "Game.h"
#include "Pokemon.h"

class commandError : public exception{};


class GameManager{
public:
    //name pokemon

    map<string,Type> TypeMap = {
            {"Normal",      Normal},
            {"Fire",        Fire},
            {"Water",       Water},
            {"Electric",    Electric},
            {"Grass",       Grass},
            {"Ice",         Ice},
            {"Fighting",    Fighting},
            {"Poison",      Poison},
            {"Ground",      Ground},
            {"Flying",      Flying},
            {"Psychic",     Psychic},
            {"Bug",         Bug},
            {"Rock",        Rock},
            {"Ghost",       Ghost},
            {"Dragon",      Dragon},
            {"Dark",        Dark},
            {"Steel",       Steel},
            {"Fairy",       Fairy},
            {"TYPE_COUNT",  TYPE_COUNT},
    };
    map<string,Pokemon> pokemonData;
    commandError error;
    char spilt = ';';

    void readPokemon(const string& path);
    void readMove(const string& path);
    void readGame(const string& path);

    void run();



    void readCase(const string& path);
    void command();
    void moveIO();
};

#endif //BACKEND_GAMEMANAGER_H
