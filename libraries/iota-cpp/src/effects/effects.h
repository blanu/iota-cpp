//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_H
#define EFFECTS_H

#include <queue>

#include "effect_symbols.h"

#include "../storage/storage.h"

#include "../nouns/noun.h"

class Effects
{
  public:
    static constexpr int relation = 0;

    static void initialize();

    static void registerMonadicEffect(Type it, Type io, Type f, Storage (*m)(const Storage&));
    static void registerDyadicEffect(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&));

    static Storage dispatchMonadicEffect(const Storage& i, const Storage& f);
    static Storage dispatchDyadicEffect(const Storage& i, const Storage& f, const Storage& x);

    static void processEffects();

    static Storage cause_impl(const Storage& i, const Storage& x);

  private:
    static std::map<Specialization3, MonadicFunction> monads;
    static std::map<Specialization5, DyadicFunction> dyads;
};

class MonadicEffect
{
  public:
    static Storage make(int i);
};

class DyadicEffect
{
  public:
    static Storage make(int i);
};

namespace iota
{
  // Effects
  // Effect: Relations
  // Effect: Relations: Monads
  inline Storage makeTable = MonadicEffect::make(effects::relation::makeTable);
  inline Storage copyTable = MonadicEffect::make(effects::relation::copyTable);
  inline Storage free = MonadicEffect::make(effects::relation::freeTable);
  inline Storage flatten = MonadicEffect::make(effects::relation::flatten);

  // Effect: Relations: Dyads
  inline Storage insert = DyadicEffect::make(effects::relation::insert);
  inline Storage remove = DyadicEffect::make(effects::relation::remove);
  inline Storage iunion = DyadicEffect::make(effects::relation::iunion);
  inline Storage project = DyadicEffect::make(effects::relation::project);
  inline Storage difference = DyadicEffect::make(effects::relation::difference);
  inline Storage rename = DyadicEffect::make(effects::relation::rename);
  inline Storage crossProduct = DyadicEffect::make(effects::relation::crossProduct);
  inline Storage restrict = DyadicEffect::make(effects::relation::restrict);
  inline Storage intersection = DyadicEffect::make(effects::relation::intersection);
} // namespace iota

#endif //EFFECTS_H
