//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects_provider.h"

#include "../api.h"

#include "../storage/storage.h"
#include "../nouns/noun.h"

EffectsProvider::EffectsProvider()
{
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::then, StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, then_impl);
}

// then ignores i and return x
// This is also known as KI, Kite, false, zero, or second (snd) in functional combinator languages.
Storage EffectsProvider::then_impl(const Storage& i, const Storage& x)
{
  return x;
}