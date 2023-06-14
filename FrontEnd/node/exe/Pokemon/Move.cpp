#include "Move.h"
#include "GameError.h"
#include <sstream>

Move::Move(
        std::string name,
        const Type type,
        const DamageType damageType,
        const int power,
        const int accuracy,
        const int powerPoint,
        const Status additionalEffect
) : name(std::move(name)),
    type(type),
    damageType(damageType),
    power(power),
    accuracy(accuracy),
    powerPoint(powerPoint),
    additionalEffect(additionalEffect) {}

Move Move::fromInput(std::istream &input, std::string name) {
    std::string line, typeName, damageTypeName, statusName;
    int power, accuracy, powerPoint;

    std::getline(input, line);
    std::stringstream stream(line);

    stream >> typeName >> damageTypeName >> power >> accuracy >> powerPoint;
    return {std::move(name), TypeMap.at(typeName), DamageTypeMap.at(damageTypeName),
            power, accuracy, powerPoint, statusName.empty() ? Status::NONE : StatusMap.at(statusName.substr(1))};
}

const std::string &Move::getName() const {
    return name;
}

Type Move::getType() const {
    return type;
}

DamageType Move::getDamageType() const {
    return damageType;
}

int Move::getPower() const {
    return power;
}

int Move::getAccuracy() const {
    return accuracy;
}

int Move::getPowerPoint() const {
    return powerPoint;
}

const Status &Move::getAdditionalEffect() const {
    return additionalEffect;
}

int Move::calcBaseDamage(const Pokemon &attacker, const Pokemon &defender) const {
    if (damageType == DamageType::STATUS) {
        return 0;
    }

    const int attack = damageType == DamageType::PHYSICAL ? attacker.getAttack() : attacker.getSpecialAttack();
    const int defense = damageType == DamageType::PHYSICAL ? defender.getDefense() : attacker.getSpecialDefense();
    return static_cast<int>(((attacker.getLevel() << 1) + 10) * power * attack / 250.0 / defense) + 2;
}

double Move::calcSTAB(const std::set<Type> &defenderTypeList) const {
    return defenderTypeList.find(type) != defenderTypeList.cend() ? 1.5 : 1.0;
}

double Move::calcTypeEffect(const std::set<Type> &defenderTypeList) const {
    const double *effectRow = TypeEffect[static_cast<size_t>(type)];
    double effect = 1.0;
    for (const Type defType: defenderTypeList) {
        effect *= effectRow[static_cast<size_t>(defType)];
    }
    return effect;
}

bool Move::canUse() const {
    return powerPoint > 0;
}

void Move::use() {
    if (powerPoint <= 0) {
        throw PowerPointError(name);
    }
    --powerPoint;
}
