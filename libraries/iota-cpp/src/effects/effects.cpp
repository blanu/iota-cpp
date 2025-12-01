//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects.h"

#include "../nouns/noun.h"

#include <storage/storage.h>
#include <storage/word.h>
#include <storage/word_array.h>

Storage NiladicEffect::make(const int f)
{
  return Word::make(f, NounType::NILADIC_EFFECT);
}

Storage MonadicEffect::make(const int f)
{
  return Word::make(f, NounType::MONADIC_EFFECT);
}

Storage DyadicEffect::make(const int f)
{
  return Word::make(f, NounType::DYADIC_EFFECT);
}

Storage TriadicEffect::make(const int f)
{
  return Word::make(f, NounType::TRIADIC_EFFECT);
}