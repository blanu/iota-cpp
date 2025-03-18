//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECT_H
#define EFFECT_H

#include <unordered_map>

#include "storage/storage.h"

class Effect
{
  public:
    int effectType;
    mixed parameters;
    std::unordered_map<Storage, Storage> handlers;
};

#endif //EFFECT_H
