//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effect_type.h"

#include "../storage/word_array.h"

Storage EffectType::make(int category, int type)
{
  return WordArray::make({category, type}, NounType::EFFECT_TYPE);
}