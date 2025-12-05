//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "verbs.h"

#include "nouns/iota_string.h"
#include "nouns/noun.h"
#include "nouns/symbol.h"
#include "storage/word.h"

Storage Nilad::make(int i)
{
  return Word::make(i, NounType::BUILTIN_NILAD);
}

void Nilad::initialize()
{
}

void Nilad::print(const Storage& i)
{
  if(i.o == NounType::BUILTIN_DYAD)
  {
    if(std::holds_alternative<int>(i.i))
    {
      int integer = std::get<int>(i.i);

      ints integers = Symbol::integerToString[integer];
      const Storage& is = IotaString::make(integers);
      std::string s = IotaString::toString(is);
      printf("%s", s.c_str());
    }
  }
}

Storage Monad::make(int i)
{
  return Word::make(i, NounType::BUILTIN_MONAD);
}

void Monad::initialize()
{
  INTERN_VERB(iota, Monad, atom);
  INTERN_VERB(iota, Monad, ichar);
  INTERN_VERB(iota, Monad, enclose);
  INTERN_VERB(iota, Monad, enumerate);
  INTERN_VERB(iota, Monad, expand);
  INTERN_VERB(iota, Monad, first);
  INTERN_VERB(iota, Monad, floor);
  INTERN_VERB(iota, Monad, format);
  INTERN_VERB(iota, Monad, gradeDown);
  INTERN_VERB(iota, Monad, gradeUp);
  INTERN_VERB(iota, Monad, group);
  INTERN_VERB(iota, Monad, negate);
  INTERN_VERB(iota, Monad, inot);
  INTERN_VERB(iota, Monad, reciprocal);
  INTERN_VERB(iota, Monad, reverse);
  INTERN_VERB(iota, Monad, shape);
  INTERN_VERB(iota, Monad, size);
  INTERN_VERB(iota, Monad, transpose);
  INTERN_VERB(iota, Monad, unique);
  INTERN_VERB(iota, Monad, undefined);

  // Extension Monads
  INTERN_VERB(iota, Monad, evaluate);
  INTERN_VERB(iota, Monad, erase);
  INTERN_VERB(iota, Monad, truth);
  INTERN_VERB(iota, Monad, lift);
  INTERN_VERB(iota, Monad, occurs);
}


Storage Dyad::make(int i)
{
  return Word::make(i, NounType::BUILTIN_DYAD);
}

void Dyad::initialize()
{
  INTERN_VERB(iota, Dyad, amend);
  INTERN_VERB(iota, Dyad, cut);
  INTERN_VERB(iota, Dyad, divide);
  INTERN_VERB(iota, Dyad, drop);
  INTERN_VERB(iota, Dyad, equal);
  INTERN_VERB(iota, Dyad, find);
  INTERN_VERB(iota, Dyad, form);
  INTERN_VERB(iota, Dyad, format2);
  INTERN_VERB(iota, Dyad, index);
  INTERN_VERB(iota, Dyad, integerDivide);
  INTERN_VERB(iota, Dyad, join);
  INTERN_VERB(iota, Dyad, less);
  INTERN_VERB(iota, Dyad, match);
  INTERN_VERB(iota, Dyad, max);
  INTERN_VERB(iota, Dyad, min);
  INTERN_VERB(iota, Dyad, minus);
  INTERN_VERB(iota, Dyad, more);
  INTERN_VERB(iota, Dyad, plus);
  INTERN_VERB(iota, Dyad, power);
  INTERN_VERB(iota, Dyad, remainder);
  INTERN_VERB(iota, Dyad, reshape);
  INTERN_VERB(iota, Dyad, rotate);
  INTERN_VERB(iota, Dyad, split);
  INTERN_VERB(iota, Dyad, take);
  INTERN_VERB(iota, Dyad, times);

  // Lens
  INTERN_VERB(iota, Dyad, retrieve);
}

void Dyad::print(const Storage& i)
{
  if(i.o == NounType::BUILTIN_DYAD)
  {
    if(std::holds_alternative<int>(i.i))
    {
      int integer = std::get<int>(i.i);

      ints integers = Symbol::integerToString[integer];
      const Storage& is = IotaString::make(integers);
      std::string s = IotaString::toString(is);
      printf("%s", s.c_str());
    }
  }
}

void Triad::initialize()
{
  INTERN_VERB(iota, Triad, store);
}

Storage Triad::make(int i)
{
  return Word::make(i, NounType::BUILTIN_TRIAD);
}

void Triad::print(const Storage& i)
{
  if(i.o == NounType::BUILTIN_DYAD)
  {
    if(std::holds_alternative<int>(i.i))
    {
      int integer = std::get<int>(i.i);

      ints integers = Symbol::integerToString[integer];
      const Storage& is = IotaString::make(integers);
      std::string s = IotaString::toString(is);
      printf("%s", s.c_str());
    }
  }
}