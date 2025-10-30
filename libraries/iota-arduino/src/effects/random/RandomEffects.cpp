//
// Created by Dr. Brandon Wiley on 10/30/25.
//

#include "RandomEffects.h"

#include <Arduino.h>
#include <variant>

#include <storage/word_array.h>
#include "nouns/integer.h"

void RandomEffects::initialize()
{

}

Storage RandomEffects::seed(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    randomSeed(ii);
  }

  return WordArray::nil();
}

Storage RandomEffects::randomMax(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    int result = random(ii);
    return Integer::make(result);
  }

  return WordArray::nil();
}

Storage RandomEffects::randomRange(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      int result = random(ii, oi);
      return Integer::make(result);
    }
  }

  return WordArray::nil();
}
