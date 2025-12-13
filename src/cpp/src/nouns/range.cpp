//
// Created by Dr. Brandon Wiley on 12/9/25.
//

#include "range.h"

#include "api.h"
#include "error.h"
#include "symbols.h"
#include "types.h"
#include "storage/word_array.h"

#include "nouns/noun.h"
#include "nouns/integer.h"
#include "storage/mixed_array.h"

void Range::initialize()
{
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::RANGE, MonadicAdverbs::each, each_impl);
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::RANGE, MonadicAdverbs::each, each_impl);
}

Storage Range::make(const ints& i)
{
  return WordArray::make(i, NounType::RANGE);
}

Storage Range::make(int x, int y)
{
  return WordArray::make(ints({ x, y }), NounType::RANGE);
}


Storage Range::make(int x, BigNumber y)
{
  return MixedArray::make({Integer::make(x), Integer::make(y)}, NounType::RANGE);
}

Storage Range::make(BigNumber x, int y)
{
  return MixedArray::make({Integer::make(x), Integer::make(y)}, NounType::RANGE);
}

Storage Range::make(const mixed& i)
{
  return MixedArray::make(i, NounType::RANGE);
}

Storage Range::make(BigNumber x, BigNumber y)
{
  return MixedArray::make({Integer::make(x), Integer::make(y)}, NounType::RANGE);
}

Storage Range::make(const Storage& x, const Storage& y)
{
  if(x.o == NounType::INTEGER && y.o == NounType::INTEGER)
  {
    return MixedArray::make({x, y}, NounType::RANGE);
  }

  return makeError(UNSUPPORTED_OBJECT);
}

ints Range::toIntegers(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    return std::get<ints>(i.i);
  }
  else
  {
    return {};
  }
}

std::tuple<int, int> Range::toIntegerTuple(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints list = std::get<ints>(i.i);

    if(list.size() == 2)
    {
      return std::make_tuple(list[0], list[1]);
    }
  }

  return std::make_tuple(0, 0);
}

Storage Range::toMixedArray(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    return MixedArray::make(std::get<mixed>(i.i));
  }

  return makeError(UNSUPPORTED_OBJECT);
}

std::tuple<BigNumber, BigNumber> Range::toBigNumberTuple(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.size() == 2)
    {
      BigNumber ba = Integer::toBigNumber(ms[0]);
      BigNumber bb = Integer::toBigNumber(ms[1]);

      return std::make_tuple(ba, bb);
    }
  }

  return std::make_tuple(BigNumber(-1), BigNumber(-1));
}

Storage Range::each_impl(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints list = std::get<ints>(i.i);

    if(list.size() == 2)
    {
      const int start = list[0];
      const int end = list[1];

      auto results = mixed();
      for(int x = start; x <= end; x++)
      {
        Storage result = eval({Integer::make(x), f});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results));
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    const mixed list = std::get<mixed>(i.i);

    if(list.size() == 2)
    {
      const Storage start = list[0];
      const Storage end = list[1];

      const BigNumber bstart = Integer::toBigNumber(start);
      const BigNumber bend = Integer::toBigNumber(end);

      auto results = mixed();
      for(BigNumber x = bstart; x <= bend; ++x)
      {
        Storage result = eval({Integer::make(x), f});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results));
    }
  }

  return makeError(UNSUPPORTED_OBJECT);
}

// FIXME
// Storage Range::over_impl(const Storage& i, const Storage& f)
// {
//
// }
//
// Storage Range::overNeutral_impl(const Storage& i, const Storage& f)
// {
//
// }
//
// Storage Range::scanOver_impl(const Storage& i, const Storage& f)
// {
//
// }
