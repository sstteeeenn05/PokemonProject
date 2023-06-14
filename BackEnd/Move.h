#pragma once

#include "Pokemon.h"

class Move {
private:
    const std::string name;
    const Type type;
    const DamageType damageType;
    const int power;
    const int accuracy;
    const Status additionalEffect;

    int powerPoint;

public:
    Move(std::string name, Type type, DamageType damageType,
         int power, int accuracy, int powerPoint, Status additionalEffect = Status::NONE);
    Move(const Move &move) = default;
    Move(Move &&move) noexcept = default;
    static Move fromInput(std::istream &input, std::string);

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] Type getType() const;
    [[nodiscard]] DamageType getDamageType() const;
    [[nodiscard]] int getPower() const;
    [[nodiscard]] int getAccuracy() const;
    [[nodiscard]] int getPowerPoint() const;
    [[nodiscard]] const Status &getAdditionalEffect() const;

    [[nodiscard]] int calcBaseDamage(const Pokemon &attacker, const Pokemon &defender) const;
    [[nodiscard]] double calcSTAB(const std::set<Type> &attackerTypeList) const;
    [[nodiscard]] double calcTypeEffect(const std::set<Type> &defenderTypeList) const;
    [[nodiscard]] bool canUse() const;

    void use();
};
