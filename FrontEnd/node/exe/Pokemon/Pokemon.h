#pragma once

#include <iostream>
#include <set>
#include "Types.h"

class Pokemon {
private:
    const std::string name;
    const std::set<Type> typeList;
    const int maxHp;
    const int attack;
    const int defense;
    const int specialAttack;
    const int specialDefense;
    const int speed;
    const int level;

    int hp;
    std::set<Status> statusList;

public:
    Pokemon(std::string name, std::set<Type> &typeList,
            int maxHp, int atk, int def, int spAtk, int spDef, int speed, int level = 50);
    Pokemon(const Pokemon &pokemon) = default;
    Pokemon(Pokemon &&pokemon) noexcept = default;
    static Pokemon fromInput(std::istream &input, std::string name);

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const std::set<Type> &getTypeList() const;
    [[nodiscard]] int getMaxHp() const;
    [[nodiscard]] int getAttack() const;
    [[nodiscard]] int getDefense() const;
    [[nodiscard]] int getSpecialAttack() const;
    [[nodiscard]] int getSpecialDefense() const;
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getHp() const;
    [[nodiscard]] const std::set<Status> &getStatusList() const;

    [[nodiscard]] bool hasStatus(Status status) const;
    [[nodiscard]] bool isFainting() const;
    [[nodiscard]] bool isFaster(const Pokemon &pokemon) const;
    [[nodiscard]] std::string getStatusString() const;

    void heal(int amount);
    void damage(int amount);
    void addStatus(Status status);
    void performStatus();
};
