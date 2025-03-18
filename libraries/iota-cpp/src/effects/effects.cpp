//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects.h"

#include "relation/relation.h"

#include "../error.h"

#include "../storage/storage.h"
#include "../storage/word.h"

std::map<Specialization3, Monad> Effects::monads;
std::map<Specialization5, Dyad> Effects::dyads;

static void initialize()
{
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

  Monad verb = monads[specialization];
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

  Dyad verb = dyads[specialization];
  return verb(i, x);
}

void Effects::processEffects()
{

}