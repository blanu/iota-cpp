//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "symbol.h"
#include "noun.h"

#include "../symbols.h"
#include "../error.h"
#include "../verbs.h"
#include "../api.h"

#include "../storage/storage.h"
#include "../storage/word.h"

// Symbol
std::unordered_map<int, ints> Symbol::integerToString;
std::unordered_map<ints, int> Symbol::stringToInteger;
std::unordered_map<int, Storage> Symbol::values;

void Symbol::initialize()
{
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

Storage Symbol::evaluate_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    auto pair = values.find(ii);
    if(pair == values.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    return pair->second;
  }
  else if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(stringToInteger.find(iis) == stringToInteger.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    int integer = stringToInteger[iis];

    auto pair = values.find(integer);
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

ints Symbol::asciiToUTF32(const std::string& ascii)
{
  ints results = ints();

  for(char y : ascii)
  {
    results.push_back(static_cast<int>(y));
  }

  return results;
}

