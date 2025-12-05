//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_H
#define EFFECTS_H

#include "effect_symbols.h"

#include <storage/storage.h>

class NiladicEffect
{
  public:
    static Storage make(int f);
};

class MonadicEffect
{
  public:
    static Storage make(int f);
};

class DyadicEffect
{
  public:
    static Storage make(int f);
};

class TriadicEffect
{
  public:
    static Storage make(int f);
};

namespace iota // Effects
{
  // Effect: Log
  // Effect: Log: Monads
  inline Storage level = MonadicEffect::make(effects::log::level);
  inline Storage critical = MonadicEffect::make(effects::log::critical);
  inline Storage error = MonadicEffect::make(effects::log::error);
  inline Storage warning = MonadicEffect::make(effects::log::warning);
  inline Storage info = MonadicEffect::make(effects::log::info);
  inline Storage debug = MonadicEffect::make(effects::log::debug);
  inline Storage trace = MonadicEffect::make(effects::log::trace);
  inline Storage timestamp = NiladicEffect::make(effects::log::timestamp);

  // Effect: Random
  // Effect: Random: Nilads
  inline Storage random = NiladicEffect::make(effects::random::random);

  // Effect: Random: Monads
  inline Storage roll = MonadicEffect::make(effects::random::roll);

  // Effect: Random: Dyads
  inline Storage rolls = DyadicEffect::make(effects::random::rolls);
  inline Storage deal = DyadicEffect::make(effects::random::deal);

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
