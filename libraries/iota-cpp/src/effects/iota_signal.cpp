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