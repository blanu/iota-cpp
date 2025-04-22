//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#ifndef TESTING_EFFECTS_REGISTER_H
#define TESTING_EFFECTS_REGISTER_H

#include "../effects_register.h"

#include "../../storage/storage.h"

class TestingEffectsRegister : public EffectsRegister
{
  public:
    TestingEffectsRegister();

    Storage getEffectState() const;
};

#endif //TESTING_EFFECTS_REGISTER_H
