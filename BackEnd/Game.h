//
// Created by tomjojo on 2023/5/30.
//

#ifndef BACKEND_GAME_H
#define BACKEND_GAME_H

#include"Header.h"

#include"Pokemon.h"

class Game{
    vector<Pokemon> pokemon;

public:
    Game(Pokemon& pokemon1,Pokemon& pokemon2);
    void attack(string name,vector<string> type, string moveType,int power,int accuracy);
    double typeCount();
};



#endif //BACKEND_GAME_H
