//
// Created by Dr. Brandon Wiley on 4/24/25.
//

#ifndef TESTING_RANDOM_H
#define TESTING_RANDOM_H

#include <random>

#include "../../effects_provider.h"

#include <storage/storage.h>

class Random
{
  public:
    static void initialize(EffectsProvider* effects_register);

    // Nilads
    static Storage random_impl();

    // Monads
    static Storage roll_impl(const Storage& i);

    // Dyads
    static Storage rolls_impl(const Storage& i, const Storage& x);
    static Storage deal_impl(const Storage& i, const Storage& x);

  private:
    static std::mt19937 generator;
};

#endif //TESTING_RANDOM_H
