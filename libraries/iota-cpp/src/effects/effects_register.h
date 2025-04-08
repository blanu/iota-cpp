//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_REGISTER_H
#define EFFECTS_REGISTER_H

#include "../storage/storage.h"

class EffectsRegister
{
  public:
    static void initialize();

    EffectsRegister() {}

    Storage eval(const Storage& s);
};

#endif //EFFECTS_REGISTER_H
