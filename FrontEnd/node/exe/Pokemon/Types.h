#pragma once

#include <string>
#include <map>

enum class Status {
    PARALYSIS,
    BURN,
    POISON,
    NONE
};

const std::map<std::string, Status> StatusMap = {
        {"PAR", Status::PARALYSIS},
        {"BRN", Status::BURN},
        {"PSN", Status::POISON}
};

const char StatusName[3][4] = {"PAR", "BRN", "PSN"};

enum class Type {
    NORMAL,
    FIRE,
    WATER,
    ELECTRIC,
    GRASS,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
    FAIRY,
    NONE
};

const size_t TYPE_COUNT = 18;

const std::map<std::string, Type> TypeMap = {
        {"Normal",   Type::NORMAL},
        {"Fire",     Type::FIRE},
        {"Water",    Type::WATER},
        {"Electric", Type::ELECTRIC},
        {"Grass",    Type::GRASS},
        {"Ice",      Type::ICE},
        {"Fighting", Type::FIGHTING},
        {"Poison",   Type::POISON},
        {"Ground",   Type::GROUND},
        {"Flying",   Type::FLYING},
        {"Psychic",  Type::PSYCHIC},
        {"Bug",      Type::BUG},
        {"Rock",     Type::ROCK},
        {"Ghost",    Type::GHOST},
        {"Dragon",   Type::DRAGON},
        {"Dark",     Type::DARK},
        {"Steel",    Type::STEEL},
        {"Fairy",    Type::FAIRY},
};

const double TypeEffect[TYPE_COUNT][TYPE_COUNT] = {
        {1, 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0.5, 0,   1,   1,   0.5, 1},
        {1, 0.5, 0.5, 1,   2,   2,   1,   1,   1,   1,   1,   2,   0.5, 1,   0.5, 1,   2,   1},
        {1, 2,   0.5, 1,   0.5, 1,   1,   1,   2,   1,   1,   1,   2,   1,   0.5, 1,   1,   1},
        {1, 1,   2,   0.5, 0.5, 1,   1,   1,   0,   2,   1,   1,   1,   1,   0.5, 1,   1,   1},
        {1, 0.5, 2,   1,   0.5, 1,   1,   0.5, 2,   0.5, 1,   0.5, 2,   1,   0.5, 1,   0.5, 1},
        {1, 0.5, 0.5, 1,   2,   0.5, 1,   1,   2,   2,   1,   1,   1,   1,   2,   1,   0.5, 1},
        {2, 1,   1,   1,   1,   2,   1,   0.5, 1,   0.5, 0.5, 0.5, 2,   0,   1,   2,   2,   0.5},
        {1, 1,   1,   1,   2,   1,   1,   0.5, 0.5, 1,   1,   1,   0.5, 0.5, 1,   1,   0,   2},
        {1, 2,   1,   2,   0.5, 1,   1,   2,   1,   0,   1,   0.5, 2,   1,   1,   1,   2,   1},
        {1, 1,   1,   0.5, 2,   1,   2,   1,   1,   1,   1,   2,   0.5, 1,   1,   1,   0.5, 1},
        {1, 1,   1,   1,   1,   1,   2,   2,   1,   1,   0.5, 1,   1,   1,   1,   0,   0.5, 1},
        {1, 0.5, 1,   1,   2,   1,   0.5, 0.5, 1,   0.5, 2,   1,   1,   0.5, 1,   2,   0.5, 0.5},
        {1, 2,   1,   1,   1,   2,   0.5, 1,   0.5, 2,   1,   2,   1,   1,   1,   1,   0.5, 1},
        {0, 1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   1,   1,   2,   1,   0.5, 1,   1},
        {1, 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   1,   0.5, 0},
        {1, 1,   1,   1,   1,   1,   0.5, 1,   1,   1,   2,   1,   1,   2,   1,   0.5, 1,   0.5},
        {1, 0.5, 0.5, 0.5, 1,   2,   1,   1,   1,   1,   1,   1,   2,   1,   1,   1,   0.5, 2},
        {1, 0.5, 1,   1,   1,   1,   2,   0.5, 1,   1,   1,   1,   1,   1,   2,   2,   0.5, 1}
};

enum class DamageType {
    PHYSICAL,
    SPECIAL,
    STATUS
};

const std::map<std::string, DamageType> DamageTypeMap = {
        {"Physical", DamageType::PHYSICAL},
        {"Special",  DamageType::SPECIAL},
        {"Status",   DamageType::STATUS},
};

const std::map<std::string, int> PotionMap {
        {"Potion",      20},
        {"SuperPotion", 60},
        {"HyperPotion", 120},
        {"MaxPotion",   1000},
};
