//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#ifndef TESTING_EFFECTS_PROVIDER_H
#define TESTING_EFFECTS_PROVIDER_H

#include "../effects_provider.h"

#include "../../storage/storage.h"

class TestingEffectsProvider : public EffectsProvider
{
  public:
    TestingEffectsProvider();

    [[nodiscard]] static Storage getEffectState();
};

#endif //TESTING_EFFECTS_PROVIDER_H
