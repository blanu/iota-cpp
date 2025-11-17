//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "symbol.h"
#include "noun.h"

#include "../symbols.h"
#include "error.h"
#include "../verbs.h"
#include "../api.h"

#include <storage/storage.h>
#include <storage/word.h>
#include <storage/mixed_array.h>
#include <nouns/nouns.h>

// Symbol
std::unordered_map<int, ints> Symbol::integerToString;
std::unordered_map<ints, int> Symbol::stringToInteger;
std::unordered_map<int, Storage> Symbol::values;

void Symbol::initialize()
{
  // Nilads
  Noun::registerNilad(Nilads::symbols, Symbol::symbols_impl);

  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::BUILTIN_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::BUILTIN_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::USER_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::USER_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);

  Noun::registerMonad(StorageType::WORD, NounType::BUILTIN_SYMBOL, Monads::truth, Symbol::truth_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::BUILTIN_SYMBOL, Monads::truth, Symbol::truth_impl);
  Noun::registerMonad(StorageType::WORD, NounType::USER_SYMBOL, Monads::truth, Symbol::truth_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::USER_SYMBOL, Monads::truth, Symbol::truth_impl);

  // Symbol tables
  integerToString[SymbolType::x] = asciiToUTF32("x");
  stringToInteger[asciiToUTF32("x")] = SymbolType::x;

  integerToString[SymbolType::y]=asciiToUTF32("y");
  stringToInteger[asciiToUTF32("y")] = SymbolType::y;

  integerToString[SymbolType::z]=asciiToUTF32("z");
  stringToInteger[asciiToUTF32("z")] = SymbolType::z;

  integerToString[SymbolType::f]=asciiToUTF32("f");
  stringToInteger[asciiToUTF32("f")] = SymbolType::f;

  integerToString[SymbolType::undefined]=asciiToUTF32("undefined");
  stringToInteger[asciiToUTF32("undefined")] = SymbolType::undefined;
}

Storage Symbol::make(int i)
{
  return Word::make(i, NounType::USER_SYMBOL);
}

Storage Symbol::make(std::string s)
{
  int nextId = integerToString.size();
  ints utf32 = asciiToUTF32(s);

  integerToString[nextId] = utf32;
  stringToInteger[utf32] = nextId;

  const Storage symbol = MixedArray::make({Integer::make(nextId), IotaString::make(utf32)});
  values.insert({nextId, symbol});

  return symbol;
}

int Symbol::toInteger(const Storage& s)
{
  if(s.t == StorageType::WORD)
  {
    if(std::holds_alternative<int>(s.i))
    {
      return std::get<int>(s.i);
    }
  }
  else if(s.t == StorageType::MIXED_ARRAY)
  {
    if(std::holds_alternative<mixed>(s.i))
    {
      mixed si = std::get<mixed>(s.i);

      if(si.size() == 2)
      {
        const Storage entry = si[0];
        if(std::holds_alternative<int>(entry.i))
        {
          return std::get<int>(entry.i);
        }
      }
    }
  }

  return -1;
}

std::string Symbol::toString(const Storage& s)
{
  if(s.t == StorageType::MIXED_ARRAY)
  {
    if(std::holds_alternative<mixed>(s.i))
    {
      mixed si = std::get<mixed>(s.i);

      if(si.size() == 2)
      {
        const Storage entry = si[1];
        if(std::holds_alternative<ints>(entry.i))
        {
          ints is = std::get<ints>(entry.i);

        }
      }
    }
  }

  return "";
}


Storage Symbol::symbols_impl()
{
  auto results = mixed();
  for(const auto& [fst, snd] : values)
  {
    results.push_back(snd);
  }

  return MixedArray::make(results);
}

Storage Symbol::evaluate_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    const auto pair = values.find(ii);
    if(pair == values.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    return pair->second;
  }
  else if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(stringToInteger.find(iis) == stringToInteger.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    const int integer = stringToInteger[iis];

    const auto pair = values.find(integer);
    if(pair == values.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    return pair->second;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Symbol::truth_impl(const Storage& i)
{
  using namespace iota;

  return eval({i, evaluate, truth});
}