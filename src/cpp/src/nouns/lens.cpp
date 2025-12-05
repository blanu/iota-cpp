//
// Created by Dr. Brandon Wiley on 5/5/25.
//

#include "lens.h"

#include "../api.h"
#include "error.h"
#include "../symbols.h"

#include <storage/storage.h>
#include <storage/word_array.h>
#include <storage/float_array.h>
#include <storage/mixed_array.h>

#include "../nouns/noun.h"
#include "../nouns/integer.h"
#include "../nouns/real.h"

// Lens
void Lens::initialize()
{
  // Lens

  // Dyads
  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::retrieve, StorageType::WORD_ARRAY, NounType::LENS, retrieve_impl);
  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::retrieve, StorageType::MIXED_ARRAY, NounType::LENS, retrieve_impl);

  // Triads
  Noun::registerTriad(StorageType::ANY, NounType::ANY, Triads::store, StorageType::ANY, NounType::ANY, StorageType::WORD_ARRAY, NounType::LENS, store_impl);
  Noun::registerTriad(StorageType::ANY, NounType::ANY, Triads::store, StorageType::ANY, NounType::ANY, StorageType::MIXED_ARRAY, NounType::LENS, store_impl);
}

Storage Lens::make(int i)
{
  Storage results = Noun::mix(WordArray::make({i}));
  results.o = NounType::LENS;
  return results;
}

Storage Lens::make(const ints& i)
{
  Storage results = Noun::mix(WordArray::make(i));
  results.o = NounType::LENS;
  return results;
}

Storage Lens::make(const mixed& i)
{
  return MixedArray::make(i, NounType::LENS);
}

Storage Lens::make(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    return make(std::get<int>(i.i));
  }
  else if(std::holds_alternative<ints>(i.i))
  {
    return make(std::get<ints>(i.i));
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    return make(std::get<mixed>(i.i));
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Lens::retrieve_impl(const Storage& i, const Storage& x) // NOLINT
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    auto iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      auto xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= static_cast<int>(iis.size()))
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
        auto rest = ints(xis.begin() + 1, xis.end());

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
      auto xis = std::get<mixed>(x.i);

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
          if(xii >= 1 && xii <= static_cast<int>(iis.size()))
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
        auto rest = mixed(xis.begin() + 1, xis.end());

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
    auto iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      auto xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= static_cast<int>(iis.size()))
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
        auto rest = ints(xis.begin() + 1, xis.end());

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
      auto xis = std::get<mixed>(x.i);

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
          if(xii >= 1 && xii <= static_cast<int>(iis.size()))
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
        auto rest = mixed(xis.begin() + 1, xis.end());

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
    auto iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      auto xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return i;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= static_cast<int>(iis.size()))
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
        auto rest = ints(xis.begin() + 1, xis.end());

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
      auto xis = std::get<mixed>(x.i);

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
          if(xii >= 1 && xii <= static_cast<int>(iis.size()))
          {
            const Storage& result = iis[xii - 1];
            return result; // FIXME - variable reference may escape scope warning
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
        auto rest = mixed(xis.begin() + 1, xis.end());

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

// store a value inside of a structure
// i: target structure
// x: new value
// y: lens
Storage Lens::store_impl(const Storage& i, const Storage& x, const Storage& y)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    auto iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(y.i))
    {
      auto xis = std::get<ints>(y.i);

      if(xis.empty())
      {
        return x;  // Replace entire structure
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= static_cast<int>(iis.size()))
        {
          auto result = iis;
          if(std::holds_alternative<int>(x.i))
          {
            result[xi - 1] = std::get<int>(x.i);
            return WordArray::make(result);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        int firstIndex = xis[0];
        auto rest = ints(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, Integer::make(firstIndex)});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          Storage updatedNext = store_impl(*nextLevel, WordArray::make(rest), x);
          if(updatedNext.o == NounType::ERROR)
          {
            return updatedNext;
          }

          auto result = iis;
          // Need to convert updatedNext back to int for storage
          if(std::holds_alternative<int>(updatedNext.i))
          {
            result[firstIndex - 1] = std::get<int>(updatedNext.i);
            return WordArray::make(result);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }
      }
    }
    else if(std::holds_alternative<mixed>(y.i))
    {
      auto xis = std::get<mixed>(y.i);

      if(xis.empty())
      {
        return x;
      }
      else if(xis.size() == 1)
      {
        Storage xi = xis[0];
        if(std::holds_alternative<int>(xi.i))
        {
          int xii = std::get<int>(xi.i);
          if(xii >= 1 && xii <= static_cast<int>(iis.size()))
          {
            auto result = iis;
            if(std::holds_alternative<int>(x.i))
            {
              result[xii - 1] = std::get<int>(x.i);
              return WordArray::make(result);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
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
        auto rest = mixed(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, firstIndex});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          Storage updatedNext = store_impl(*nextLevel, MixedArray::make(rest), x);
          if(updatedNext.o == NounType::ERROR)
          {
            return updatedNext;
          }

          auto result = iis;
          if(std::holds_alternative<int>(updatedNext.i))
          {
            result[std::get<int>(firstIndex.i) - 1] = std::get<int>(updatedNext.i);
            return WordArray::make(result);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    auto iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(y.i))
    {
      auto xis = std::get<ints>(y.i);

      if(xis.empty())
      {
        return x;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= static_cast<int>(iis.size()))
        {
          auto result = iis;
          if(std::holds_alternative<float>(x.i))
          {
            result[xi - 1] = std::get<float>(x.i);
            return FloatArray::make(result);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        int firstIndex = xis[0];
        auto rest = ints(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, Integer::make(firstIndex)});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          Storage updatedNext = store_impl(*nextLevel, WordArray::make(rest), x);
          if(updatedNext.o == NounType::ERROR)
          {
            return updatedNext;
          }

          auto result = iis;
          if(std::holds_alternative<float>(updatedNext.i))
          {
            result[firstIndex - 1] = std::get<float>(updatedNext.i);
            return FloatArray::make(result);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }
      }
    }
    else if(std::holds_alternative<mixed>(y.i))
    {
      auto xis = std::get<mixed>(y.i);

      if(xis.empty())
      {
        return x;
      }
      else if(xis.size() == 1)
      {
        Storage xi = xis[0];
        if(std::holds_alternative<int>(xi.i))
        {
          int xii = std::get<int>(xi.i);
          if(xii >= 1 && xii <= static_cast<int>(iis.size()))
          {
            auto result = iis;
            if(std::holds_alternative<float>(x.i))
            {
              result[xii - 1] = std::get<float>(x.i);
              return FloatArray::make(result);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
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
        auto rest = mixed(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, firstIndex});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          Storage updatedNext = store_impl(*nextLevel, MixedArray::make(rest), x);
          if(updatedNext.o == NounType::ERROR)
          {
            return updatedNext;
          }

          auto result = iis;
          if(std::holds_alternative<float>(updatedNext.i))
          {
            result[std::get<int>(firstIndex.i) - 1] = std::get<float>(updatedNext.i);
            return FloatArray::make(result);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    auto iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(y.i))
    {
      auto xis = std::get<ints>(y.i);

      if(xis.empty())
      {
        return x;
      }
      else if(xis.size() == 1)
      {
        int xi = xis[0];
        if(xi >= 1 && xi <= static_cast<int>(iis.size()))
        {
          auto result = iis;
          result[xi - 1] = x;
          return MixedArray::make(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }
      else
      {
        int firstIndex = xis[0];
        auto rest = ints(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, Integer::make(firstIndex)});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          Storage updatedNext = store_impl(*nextLevel, WordArray::make(rest), x);
          if(updatedNext.o == NounType::ERROR)
          {
            return updatedNext;
          }

          auto result = iis;
          result[firstIndex - 1] = updatedNext;
          return MixedArray::make(result);
        }
      }
    }
    else if(std::holds_alternative<mixed>(y.i))
    {
      auto xis = std::get<mixed>(y.i);

      if(xis.empty())
      {
        return x;
      }
      else if(xis.size() == 1)
      {
        Storage xi = xis[0];
        if(std::holds_alternative<int>(xi.i))
        {
          int xii = std::get<int>(xi.i);
          if(xii >= 1 && xii <= static_cast<int>(iis.size()))
          {
            auto result = iis;
            result[xii - 1] = x;
            return MixedArray::make(result);
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
        auto rest = mixed(xis.begin() + 1, xis.end());

        maybe<Storage> nextLevel = eval({i, iota::index, firstIndex});
        if(nextLevel)
        {
          if(nextLevel->o == NounType::ERROR)
          {
            return *nextLevel;
          }

          Storage updatedNext = store_impl(*nextLevel, MixedArray::make(rest), x);
          if(updatedNext.o == NounType::ERROR)
          {
            return updatedNext;
          }

          auto result = iis;
          result[std::get<int>(firstIndex.i) - 1] = updatedNext;
          return MixedArray::make(result);
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}