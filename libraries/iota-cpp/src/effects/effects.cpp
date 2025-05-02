//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects.h"

#include "relation/relation.h"

#include "../symbols.h"
#include "../error.h"

#include "../nouns/noun.h"

#include "../storage/storage.h"
#include "../storage/word.h"
#include "../storage/word_array.h"

Storage NiladicEffect::make(int f, int e)
{
  return WordArray::make(ints{f, e}, NounType::EFFECT_TYPE);
}

Storage MonadicEffect::make(int f, int e)
{
  return WordArray::make(ints{f, e}, NounType::EFFECT_TYPE);
}

Storage DyadicEffect::make(int f, int e)
{
  return WordArray::make(ints{f, e}, NounType::EFFECT_TYPE);
}
