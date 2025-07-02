//
// Created by Dr. Brandon Wiley on 5/5/25.
//

#include "lens.h"

#include "../api.h"
#include "error.h"

#include "../storage/storage.h"
#include "../storage/word_array.h"
#include "../storage/mixed_array.h"

#include "../nouns/noun.h"
#include "../nouns/integer.h"
#include "../nouns/real.h"

// Lens
void Lens::initialize()
{
  // Lens
  // Monads
  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::retrieve, StorageType::WORD_ARRAY, NounType::LENS, retrieve_impl);
  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::retrieve, StorageType::MIXED_ARRAY, NounType::LENS, retrieve_impl);

  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::mutate, StorageType::MIXED_ARRAY, NounType::LENS, mutate_impl);
}

Storage Lens::make(int i)
{
  Storage results = Noun::mix(WordArray::make({i}));
  results.o = NounType::LENS;
  return results;
}

Storage Lens::make(ints i)
{
  Storage results = Noun::mix(WordArray::make(i));
  results.o = NounType::LENS;
  return results;
}

Storage Lens::make(mixed i)
{
  return MixedArray::make(i, NounType::LENS);
}

Storage Lens::retrieve_impl(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= iis.size())
        {
          int result = iis[xi - 1];
          return Integer::make(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        int firstIndex = xis[0];
        ints rest = ints(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, Integer::make(firstIndex)});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          return retrieve_impl(*nextLevel, WordArray::make(rest));
        }
      }
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        Storage xi = xis[0];
        if(std::holds_alternative<int>(xi.i))
        {
          int xii = std::get<int>(xi.i);
          if(xii >= 1 && xii <= iis.size())
          {
            int result = iis[xii - 1];
            return Integer::make(result);
          }
          else
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        Storage firstIndex = xis[0];
        mixed rest = mixed(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, firstIndex});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          return retrieve_impl(*nextLevel, MixedArray::make(rest));
        }
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= iis.size())
        {
          float result = iis[xi - 1];
          return Real::make(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        int firstIndex = xis[0];
        ints rest = ints(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, Integer::make(firstIndex)});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          return retrieve_impl(*nextLevel, WordArray::make(rest));
        }
      }
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        Storage xi = xis[0];
        if(std::holds_alternative<int>(xi.i))
        {
          int xii = std::get<int>(xi.i);
          if(xii >= 1 && xii <= iis.size())
          {
            float result = iis[xii - 1];
            return Real::make(result);
          }
          else
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        Storage firstIndex = xis[0];
        mixed rest = mixed(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, firstIndex});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          return retrieve_impl(*nextLevel, MixedArray::make(rest));
        }
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= iis.size())
        {
          Storage result = iis[xi - 1];
          return Noun::simplify(MixedArray::make({result}));
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        int firstIndex = xis[0];
        ints rest = ints(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, Integer::make(firstIndex)});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          return retrieve_impl(*nextLevel, WordArray::make(rest));
        }
      }
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        Storage xi = xis[0];
        if(std::holds_alternative<int>(xi.i))
        {
          int xii = std::get<int>(xi.i);
          if(xii >= 1 && xii <= iis.size())
          {
            Storage result = iis[xii - 1];
            return result;
          }
          else
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        Storage firstIndex = xis[0];
        mixed rest = mixed(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, firstIndex});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          return retrieve_impl(*nextLevel, MixedArray::make(rest));
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Lens::mutate_impl(const Storage& i, const Storage& x)
{
  // FIXME
  return WordArray::nil();
}