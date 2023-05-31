//
// Created by tomjojo on 2023/5/30.
//
#include "Pokemon.h"

Pokemon::Pokemon(
        string _name,
        vector<Type> _type,
        int _hp,
        int _atk,
        int _def,
        int _spAtk,
        int _spDef,
        int _speed,
        int _level,
        int _exp
    ):name(std::move(_name)),type(std::move(_type)),maxHp(_hp), hp(_hp), atk(_atk), def(_def), spAtk(_spAtk), spDef(_spDef), speed(_speed), level(_level), exp(_exp) {}

void Pokemon::init(int deltaHp, set<Status> _statusList) {
    hp += deltaHp;
    statusList = _statusList;
}

string Pokemon::getName() const {
    return name;
}

vector<Type> Pokemon::getType() const {
    return type;
}

int Pokemon::getMaxHp() const {
    return maxHp;
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

void Pokemon::heal(int offset) {
    hp += offset;
}

void Pokemon::damage(int offset) {
    hp -= offset;
}

void Pokemon::addStatus(Status status){
    statusList.insert(status);
}

void Pokemon::removeStatus(Status status){
    statusList.erase(status);
}

bool Pokemon::hasStatus(Status status){
    return find(statusList.cbegin(), statusList.cend(), status) != statusList.cend();
}