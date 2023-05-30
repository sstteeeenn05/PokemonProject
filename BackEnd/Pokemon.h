//
// Created by tomjojo on 2023/5/30.
//

#ifndef BACKEND_POKEMON_H
#define BACKEND_POKEMON_H

#include"Header.h"

class Pokemon{
    string name;
    vector<string> type;
    int hp;
    int atk;
    int def;
    int spAtk;
    int spDef;
    int speed;

    int level;
    int exp;

    vector<Stat> stat;
public:
    Pokemon() = default;
    Pokemon(string _name, vector<string> _type, int _hp, int _atk, int _def, int _spAtk, int _spDef, int _speed,int _level,int _exp);
    string getName() const;
    vector<string> getType() const;

    void changeHp(int offset);

    int getHp() const;
    int getAtk() const;
    int getDef() const;
    int getSpAtk() const;
    int getSpDef() const;
    int getLevel() const;



};

#endif //BACKEND_POKEMON_H
