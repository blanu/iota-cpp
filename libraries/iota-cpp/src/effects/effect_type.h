//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECT_H
#define EFFECT_H

#include "../storage/storage.h"

class EffectType
{
  public:
    static Storage make(int category, int type);
};

#endif //EFFECT_H
