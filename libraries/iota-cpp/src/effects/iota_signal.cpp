//
// Created by Dr. Brandon Wiley on 3/28/25.
//

#include "iota_signal.h"

#include "../storage/mixed_array.h"

#include "../nouns/noun.h"
#include "../verbs.h"

void Signal::initialize()
{
  Noun::registerMonad(StorageType::ANY, NounType::ANY, Monads::lift, lift_impl);
}

Storage Signal::make(const Storage& i, const Storage& x)
{
  const mixed results = {i, x};

  return MixedArray::make(results, NounType::SIGNAL);
}

Storage Signal::lift_impl(const Storage& i)
{
  return make(i, MixedArray::make());
}

void Contingency::initialize()
{
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, Dyads::bind, StorageType::MIXED_ARRAY, NounType::EXPRESSION, bind_impl);
}

Storage Contingency::make(const Storage& i, const Storage& x)
{
  mixed results = {i, x};
  return MixedArray::make(results, NounType::CONTINGENCY);
}

Storage Contingency::bind_impl(const Storage& i, const Storage& x)
{
  return make(i, x);
}
