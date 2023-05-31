//
// Created by tomjojo on 2023/5/30.
//

#pragma once

#include"Header.h"

class Pokemon{
    string name;
    vector<Type> type;
    int maxHp;
    int hp;
    int atk;
    int def;
    int spAtk;
    int spDef;
    int speed;

    int level;
    int exp;

    set<Status> statusList;
public:
    Pokemon() = default;
    Pokemon(string _name, vector<Type> _type, int _hp, int _atk, int _def, int _spAtk, int _spDef, int _speed,int _level,int _exp);
    void init(int, set<Status>);
    string getName() const;
    vector<Type> getType() const;

    int getMaxHp() const;
    int getHp() const;
    int getAtk() const;
    int getDef() const;
    int getSpAtk() const;
    int getSpDef() const;
    int getLevel() const;

    void heal(int offset);
    void damage(int offset);
    void addStatus(Status);
    void removeStatus(Status);
    bool hasStatus(Status);
};