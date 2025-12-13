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
    inline static int putBindings;
    inline static int getBindings;

    static void initialize(EffectsProvider* effects_register);

    // Nilads
    static Storage get_impl();
    static Storage getBindings_impl();

    // Monads
    static Storage put_impl(const Storage& i);
    static Storage modify_impl(const Storage& f);
    static Storage putBindings_impl(const Storage& i);

    static Storage getEffectState();
    static Storage getBindingsState();

  private:
    static Storage state;
    static Storage bindings;
};

#endif //TESTING_STATE_H
