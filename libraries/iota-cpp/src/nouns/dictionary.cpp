//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <vector>

#include "dictionary.h"
#include "noun.h"
#include "integer.h"
#include "list.h"
#include "quoted_symbol.h"

#include "../squeeze.h"
#include "../symbols.h"
#include "../error.h"
#include "../verbs.h"

#include "../storage/storage.h"
#include "../storage/word.h"
#include "../storage/mixed_array.h"

// Dictionary
void Dictionary::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::inot, Noun::false1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::shape, Noun::false1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::undefined, Noun::false1);

  // Dyads
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD, NounType::INTEGER, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::FLOAT, NounType::REAL, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD, NounType::CHARACTER, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dictionary::find_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dictionary::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Noun::false2);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);
}

Storage Dictionary::make(const mixed &i)
{
  return MixedArray::make(i, NounType::DICTIONARY);
}

Storage Dictionary::makeEmpty()
{
  return MixedArray::make(mixed(), NounType::DICTIONARY);
}

Storage Dictionary::find_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.size() == 2)
    {
      const Storage& keys = ms[0];
      const Storage& values = ms[1];

      Storage indices = find(keys, x);

      if(std::holds_alternative<ints>(indices.i))
      {
        ints integerIndices = std::get<ints>(indices.i);

        if(integerIndices.empty())
        {
          return QuotedSymbol::undefined();
        }
        else if(integerIndices.size() == 1)
        {
          int valueIndex = integerIndices.front();

          Storage result = index(values, Integer::make(valueIndex));

          if(result.o == NounType::ERROR)
          {
            return QuotedSymbol::undefined();
          }

          return result;
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Dictionary::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage matched = match(iis[index], xis[index]);
        if(matched.truth())
        {
          continue;
        }
        else
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

maybe<Storage> Dictionary::from_bytes(const bytes& bs, int t)
{
  if(t == StorageType::MIXED_ARRAY)
  {
    return MixedArray::from_bytes(bs, NounType::DICTIONARY);
  }
  else
  {
    return std::nullopt;
  }
}

maybe<bytes> Dictionary::to_bytes(const Storage& i)
{
  // Don't include type, that is handled by Noun::to_bytes

  if (i.o != NounType::LIST)
  {
    return std::nullopt;
  }

  bytes result = bytes();

  switch (i.t)
  {
    case StorageType::MIXED_ARRAY:
    {
      return MixedArray::to_bytes(i);
    }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Dictionary::from_conn(const Connection& conn, int t)
{
  if(t == StorageType::MIXED_ARRAY)
  {
    return MixedArray::from_conn(conn, NounType::DICTIONARY);
  }
  else
  {
    return std::nullopt;
  }
}

void Dictionary::to_conn(const Connection& conn, const Storage& i)
{
  if (i.o != NounType::LIST)
  {
    return;
  }

  switch (i.t)
  {
    case StorageType::MIXED_ARRAY:
    {
      // No need to include type here, because it is provided by MixedArray::to_conn
      MixedArray::to_conn(conn, i);
    }

    default:
      return;
  }
}
