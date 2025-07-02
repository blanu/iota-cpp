//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_PROVIDER_H
#define EFFECTS_PROVIDER_H

#include "../storage/storage.h"

class EffectsProvider
{
  public:
    static Storage then_impl(const Storage& i, const Storage& x);

    EffectsProvider();
};

#endif //EFFECTS_PROVIDER_H
