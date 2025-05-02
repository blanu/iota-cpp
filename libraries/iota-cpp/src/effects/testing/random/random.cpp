//
// Created by Dr. Brandon Wiley on 4/24/25.
//

#include "random.h"

#include "../../../error.h"

#include "../../../storage/storage.h"
#include "../../../storage/word.h"
#include "../../../storage/word_array.h"
#include "../../../storage/float_array.h"

#include "../../../nouns/integer.h"
#include "../../../nouns/real.h"

void Random::initialize(EffectsRegister* effects_register)
{
  std::random_device rd;
  generator = std::mt19937(rd());
}

Storage Random::roll_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(ii > 0)
    {
      if(ii == 1)
      {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        float result = dist(generator);
        return Real::make(result);
      }
      else
      {
        std::uniform_int_distribution<int> dist(1, ii);
        int result = dist(generator);
        return Integer::make(result);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Random::rolls_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<int>(i.i))
    {
      ints results = ints();

      for(int offset = 0; offset < xi; offset++)
      {
        Storage result = roll_impl(i);
        if(result.o == NounType::INTEGER && std::holds_alternative<int>(result.i))
        {
          results.push_back(std::get<int>(result.i));
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<float>(i.i))
    {
      floats results = floats();

      for(int offset = 0; offset < xi; offset++)
      {
        Storage result = roll_impl(i);
        if(result.o == NounType::REAL && std::holds_alternative<float>(result.i))
        {
          results.push_back(std::get<float>(result.i));
        }
      }

      return FloatArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// FIXME
Storage Random::deal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<int>(i.i))
    {
      ints results = ints();

      for(int offset = 0; offset < xi; offset++)
      {
        Storage result = roll_impl(i);
        if(result.o == NounType::INTEGER && std::holds_alternative<int>(result.i))
        {
          results.push_back(std::get<int>(result.i));
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<float>(i.i))
    {
      floats results = floats();

      for(int offset = 0; offset < xi; offset++)
      {
        Storage result = roll_impl(i);
        if(result.o == NounType::REAL && std::holds_alternative<float>(result.i))
        {
          results.push_back(std::get<float>(result.i));
        }
      }

      return FloatArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

std::mt19937 Random::generator;
