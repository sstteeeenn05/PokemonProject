//
// Created by tomjojo on 2023/5/30.
//

#pragma once

#include<map>
#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<stdlib.h>
#include<algorithm>

using namespace std;

enum Status{
    PARALYSIS,
    BURN,
    POISON,
};

//map<string, Stat> toStatus = {
//    { "PAR", PARALYSIS },
//    { "BRN", BURN },
//    { "PSN", POISON }
//};

enum Type{
    Normal,
    Fire,
    Water,
    Electric,
    Grass,
    Ice,
    Fighting,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dragon,
    Dark,
    Steel,
    Fairy,
    TYPE_COUNT
};
