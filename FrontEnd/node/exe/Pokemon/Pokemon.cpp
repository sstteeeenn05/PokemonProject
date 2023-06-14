#include "Pokemon.h"

#include <sstream>

Pokemon::Pokemon(
        std::string name,
        std::set<Type> &typeList,
        const int maxHp,
        const int atk,
        const int def,
        const int spAtk,
        const int spDef,
        const int speed,
        const int level
) : name(std::move(name)),
    typeList(typeList),
    maxHp(maxHp),
    attack(atk),
    defense(def),
    specialAttack(spAtk),
    specialDefense(spDef),
    speed(speed),
    hp(maxHp),
    level(level) {}

Pokemon Pokemon::fromInput(std::istream &input, std::string name) {
    size_t typeCount;
    int maxHp, attack, defense, specialAttack, specialDefense, speed;

    input >> typeCount;
    std::set<Type> typeList;
    for (size_t i = 0; i < typeCount; ++i) {
        std::string typeName;
        input >> typeName;
        typeList.insert(TypeMap.at(typeName));
    }

    input >> maxHp >> attack >> defense >> specialAttack >> specialDefense >> speed;
    return {std::move(name), typeList, maxHp, attack, defense, specialAttack, specialDefense, speed};
}

const std::string &Pokemon::getName() const {
    return name;
}

const std::set<Type> &Pokemon::getTypeList() const {
    return typeList;
}

int Pokemon::getMaxHp() const {
    return maxHp;
}

int Pokemon::getAttack() const {
    return attack;
}

int Pokemon::getDefense() const {
    return defense;
}

int Pokemon::getSpecialAttack() const {
    return specialAttack;
}

int Pokemon::getSpecialDefense() const {
    return specialDefense;
}

int Pokemon::getSpeed() const {
    return hasStatus(Status::PARALYSIS) ? (speed >> 1) : speed;
}

int Pokemon::getLevel() const {
    return level;
}

int Pokemon::getHp() const {
    return hp;
}

const std::set<Status> &Pokemon::getStatusList() const {
    return statusList;
}

bool Pokemon::isFainting() const {
    return hp <= 0;
}

bool Pokemon::isFaster(const Pokemon &pokemon) const {
    return speed >= pokemon.speed;
}

std::string Pokemon::getStatusString() const {
    std::stringstream stream(name);
    stream << ' ' << hp;
    for (const Status status : statusList) {
        stream << ' ' << StatusName[static_cast<size_t>(status)];
    }
    return stream.str();
}

void Pokemon::heal(const int amount) {
    hp = std::min(hp + amount, maxHp);
}

void Pokemon::damage(const int amount) {
    hp = std::max(0, hp - amount);
}

void Pokemon::addStatus(const Status status) {
    if (status != Status::NONE) {
        statusList.insert(status);
    }
}

bool Pokemon::hasStatus(const Status status) const {
    return statusList.find(status) != statusList.cend();
}

void Pokemon::performStatus() {
    for (const Status status : statusList) {
        if (status == Status::BURN || status == Status::POISON) {
            damage(maxHp >> 4);
        }
    }
}
