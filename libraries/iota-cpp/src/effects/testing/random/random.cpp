//
// Created by Dr. Brandon Wiley on 4/24/25.
//

#include "random.h"

#include "../../../api.h"
#include "../../../nouns/error.h"
#include "../../../verbs.h"

#include "../../../storage/storage.h"
#include "../../../storage/word.h"
#include "../../../storage/word_array.h"
#include "../../../storage/float_array.h"
#include "../../../storage/mixed_array.h"

#include "../../../nouns/noun.h"
#include "../../../nouns/integer.h"
#include "../../../nouns/real.h"

void Random::initialize(EffectsProvider* effects_register)
{
  //std::random_device rd;
  //generator = std::mt19937(rd());

  generator = std::mt19937(123456789); // NOLINT, Use a static seed for the testing version of the random number generator. Obviously, do not do this in the production random number generator.
}

Storage Random::random_impl()
{
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  const float result = dist(generator);
  return Real::make(result);
}

Storage Random::roll_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    if(ii > 0)
    {
      if(ii == 1)
      {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        const float result = dist(generator);
        return Real::make(result);
      }
      else
      {
        std::uniform_int_distribution<int> dist(1, ii);
        const int result = dist(generator);
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
    const int xi = std::get<int>(x.i);

    if(std::holds_alternative<int>(i.i))
    {
      auto results = ints();

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
      auto results = floats();

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

Storage Random::deal_impl(const Storage& i, const Storage& x)
{
  using namespace iota;

  Storage isize = eval({i, size});
  if(isize.o == NounType::ERROR)
  {
    return isize;
  }

  if(isize.o == NounType::INTEGER && std::holds_alternative<int>(isize.i))
  {
    int is = std::get<int>(isize.i);

    if(is == 0)
    {
      return WordArray::nil();
    }
    else if(is > 0)
    {
      auto results = mixed();

      for(int offset = 0; offset < is; offset++)
      {
        Storage choice = roll_impl(isize);
        Storage result = eval({i, iota::index, choice});
        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

std::mt19937 Random::generator; // NOLINT
