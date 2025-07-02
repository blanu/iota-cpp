//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#ifndef TESTING_STATE_H
#define TESTING_STATE_H

#include "../../../types.h"

#include "../../effects_provider.h"

#include "../../../storage/storage.h"

class State
{
  public:
    static void initialize(EffectsProvider* effects_register);

    // Nilads
    static Storage get_impl();

    // Monads
    static Storage put_impl(const Storage& i);
    static Storage modify_impl(const Storage& i);

    static Storage getEffectState();

  private:
    static maybe<Storage> state;
};

#endif //TESTING_STATE_H
