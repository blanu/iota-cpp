//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#ifndef TESTING_STATE_H
#define TESTING_STATE_H

#include <types.h>

#include <storage/storage.h>

#include "effects/effects_provider.h"

class TestingState
{
  public:
    inline static int get;
    inline static int put;
    inline static int modify;

    static void initialize(EffectsProvider* effects_register);

    // Nilads
    static Storage get_impl();

    // Monads
    static Storage put_impl(const Storage& i);
    static Storage modify_impl(const Storage& f);

    static Storage getEffectState();

  private:
    static Storage state;
};

#endif //TESTING_STATE_H
