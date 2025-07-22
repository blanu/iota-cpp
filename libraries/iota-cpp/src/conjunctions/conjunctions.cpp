//
// Created by Dr. Brandon Wiley on 7/3/25.
//

#include "conjunctions.h"

#include <storage/word.h>

#include "../nouns/noun.h"

Storage Conjunction::make(const int i)
{
  return Word::make(i, NounType::CONJUNCTION);
}

void Conjunctions::initialize()
{
  Noun::registerConjunction(Conjunctions::then, then_impl);
}

// then ignores i and return x
// This is also known as KI, Kite, false, zero, or second (snd) in functional combinator languages.
Storage Conjunctions::then_impl(const Storage& i, const Storage& x)
{
  return x;
}