//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "quoted_symbol.h"
#include "noun.h"
#include "iota_string.h"
#include "symbol.h"
#include "integer.h"

#include "../symbols.h"
#include "error.h"

#include "../storage/word.h"
#include "../storage/word_array.h"

void QuotedSymbol::initialize()
{
  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::evaluate, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::format, QuotedSymbol::format_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::undefined, QuotedSymbol::undefined_impl);

  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::truth, Noun::true1);

  // Dyads
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::MIXED_ARRAY, NounType::DICTIONARY, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, IotaString::match_impl);
}

Storage QuotedSymbol::make(const ints &i)
{
  return WordArray::make(i, NounType::QUOTED_SYMBOL);
}

Storage QuotedSymbol::undefined()
{
  ints name = Symbol::integerToString[SymbolType::undefined];
  return QuotedSymbol::make(name);
}

Storage QuotedSymbol::format_impl(const Storage& i)
{
  int unicode_colon = static_cast<int>(':');

  if(std::holds_alternative<ints>(i.i))
  {
    ints result = ints(std::get<ints>(i.i));
    result.insert(result.begin(), unicode_colon);
    return IotaString::make(result);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage QuotedSymbol::undefined_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    ints name = Symbol::integerToString[SymbolType::undefined];

    if(integers == name)
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}
