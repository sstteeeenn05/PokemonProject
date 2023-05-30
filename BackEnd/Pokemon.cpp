//
// Created by tomjojo on 2023/5/30.
//
#include "Pokemon.h"
#include<utility>

Pokemon::Pokemon(
        string _name,
        vector<string> _type,
        int _hp,
        int _atk,
        int _def,
        int _spAtk,
        int _spDef,
        int _speed,
        int _level,
        int _exp
    ):name(std::move(_name)),type(std::move(_type)),hp(_hp),atk(_atk),def(_def),spAtk(_spAtk),spDef(_spDef),speed(_speed),level(_level),exp(_exp) {}

string Pokemon::getName() const {
    return name;
}

vector<string> Pokemon::getType() const {
    return type;
}

int Pokemon::getHp() const {
    return hp;
}

int Pokemon::getAtk() const {
    return atk;
}

int Pokemon::getDef() const {
    return def;
}

int Pokemon::getSpAtk() const {
    return spAtk;
}

int Pokemon::getSpDef() const {
    return spDef;
}

int Pokemon::getLevel() const {
    return level;
}

void Pokemon::changeHp(int offset) {
    hp += offset;
}
