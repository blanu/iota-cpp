//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects.h"

#include "relation/relation.h"

#include "../symbols.h"
#include "../error.h"

#include "../nouns/noun.h"

#include "../storage/storage.h"
#include "../storage/word.h"

Storage MonadicEffect::make(int i)
{
  return Word::make(i, NounType::EFFECT_TYPE);
}

Storage DyadicEffect::make(int i)
{
  return Word::make(i, NounType::EFFECT_TYPE);
}

std::map<Specialization3, MonadicFunction> Effects::monads;
std::map<Specialization5, DyadicFunction> Effects::dyads;

void Effects::initialize()
{
  // Install support for effects in the function dispatch table
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cause, StorageType::MIXED_ARRAY, NounType::EFFECT_TYPE, Effects::cause_impl);

  // Initialize system effects
  Relation::initialize();
}

void Effects::registerMonadicEffect(Type it, Type io, Type f, Storage (*m)(const Storage&))
{
  Effects::monads[Specialization3(it, io, f)] = m;
}

void Effects::registerDyadicEffect(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&))
{
  Effects::dyads[Specialization5(it, io, f, xt, xo)] = d;
}

Storage Effects::dispatchMonadicEffect(const Storage& i, const Storage& f)
{
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monads.find(specialization) == monads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  MonadicFunction verb = monads[specialization];
  return verb(i);
}

Storage Effects::dispatchDyadicEffect(const Storage& i, const Storage& f, const Storage& x)
{
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyads.find(specialization) == dyads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  DyadicFunction verb = dyads[specialization];
  return verb(i, x);
}

void Effects::processEffects()
{

}

Storage Effects::cause_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed ms = std::get<mixed>(x.i);

    if(ms.empty())
    {
      return Word::make(EMPTY, NounType::ERROR);
    }

    switch(ms.size())
    {
      case 2:
      {
        // FIXME
        Storage mods = ms[0];
        Storage es = ms[1];
        break;
      }

      case 3:
      {
        Storage mods = ms[0];
        Storage es = ms[1];
        Storage xs = ms[2];
        break;
      }

      default:
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}