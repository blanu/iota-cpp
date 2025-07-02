//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects.h"

#include "../nouns/noun.h"

#include "../storage/storage.h"
#include "../storage/word.h"
#include "../storage/word_array.h"

Storage NiladicEffect::make(int f, int e)
{
  return WordArray::make(ints{f, e}, NounType::NILADIC_EFFECT);
}

Storage MonadicEffect::make(int f, int e)
{
  return WordArray::make(ints{f, e}, NounType::MONADIC_EFFECT);
}

Storage DyadicEffect::make(int f, int e)
{
  return WordArray::make(ints{f, e}, NounType::DYADIC_EFFECT);
}
