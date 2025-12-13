//
// Created by Dr. Brandon Wiley on 12/9/25.
//

#include "bindings.h"

#include <algorithm>

#include "error.h"
#include "noun.h"
#include "symbols.h"
#include "verbs.h"
#include "effects/effects.h"

#include "storage/word_array.h"
#include "storage/mixed_array.h"

void Bindings::initialize()
{
  INTERN_INT(resolve);
  INTERN_EFFECT(iota, Dyad, resolve);

  INTERN_INT(bind);
  INTERN_EFFECT(iota, Triad, bind);

  // Dyads
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::BINDINGS, Dyads::resolve, StorageType::MIXED_ARRAY, NounType::USER_SYMBOL, resolve_impl);

  // Triads
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::BINDINGS, Triads::bind, StorageType::ANY, NounType::ANY, StorageType::WORD_ARRAY, NounType::SYMBOL_DEFINITION, bind_impl);
}

Storage Bindings::empty()
{
  auto keys = WordArray::make({});
  auto values = MixedArray::make({});

  return MixedArray::make({keys, values}, NounType::BINDINGS);
}

Storage Bindings::make(const mixed& i)
{
  return MixedArray::make(i, NounType::BINDINGS);
}

Storage Bindings::make(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    return MixedArray::make(ms, NounType::BINDINGS);
  }
  else
  {
    return makeError(UNSUPPORTED_OBJECT);
  }
}

// bind: associations a symbol with a value in a bindings
// i: Bindings
// x: Any
// y: SymbolDefinition
// returns: Bindings
Storage Bindings::bind_impl(const Storage& i, const Storage& x, const Storage& y)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.size() == 2)
    {
      const Storage& keys = ms[0];
      const Storage& values = ms[1];

      if(std::holds_alternative<ints>(keys.i))
      {
        ints ks = std::get<ints>(keys.i);

        if(std::holds_alternative<mixed>(values.i))
        {
          mixed vs = std::get<mixed>(values.i);

          int key = Symbol::toInteger(y);

          // Bad key
          if(key == -1)
          {
            return makeError(UNSUPPORTED_OBJECT);
          }

          auto found = std::find(ks.begin(), ks.end(), key);
          if(found != ks.end())
          {
            // Key found
            size_t index = std::distance(ks.begin(), found);

            if(index < vs.size())
            {
              // Corresponding value for the key found
              vs[index] = x;
            }
            else
            {
              // Corresponding value for the key not found, keys and values are out of sync
              return makeError(UNSUPPORTED_OBJECT);
            }
          }
          else
          {
            // Key wasn't found, add it
            ks.push_back(key);
            vs.push_back(x);
          }

          const auto result = mixed({WordArray::make(ks), MixedArray::make(vs)});
          return MixedArray::make(result, NounType::BINDINGS);
        }
      }
    }
  }

  return makeError(UNSUPPORTED_OBJECT);
}

// resolve: retrieves the value associated from a symbol from a bindings
// i: Bindings
// x: UserSymbol
// returns: Any
Storage Bindings::resolve_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.size() == 2)
    {
      const Storage& keys = ms[0];
      const Storage& values = ms[1];

      if(std::holds_alternative<ints>(keys.i))
      {
        ints ks = std::get<ints>(keys.i);

        if(std::holds_alternative<mixed>(values.i))
        {
          mixed vs = std::get<mixed>(values.i);

          int key = Symbol::toInteger(x);

          auto found = std::find(ks.begin(), ks.end(), key);
          if(found != ks.end())
          {
            size_t index = std::distance(ks.begin(), found);

            if(index < vs.size())
            {
              auto& result = vs[index];
              return result;
            }
          }
        }
      }
    }
  }

  return makeError(UNSUPPORTED_OBJECT);
}
