//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_H
#define EFFECTS_H

#include "effect_symbols.h"

#include "../storage/storage.h"

class NiladicEffect
{
  public:
    static Storage make(int f, int e);
};

class MonadicEffect
{
  public:
    static Storage make(int f, int e);
};

class DyadicEffect
{
  public:
    static Storage make(int f, int e);
};

namespace iota // Effects
{
  // Effect: Log
  // Effect: Log: Monads
  inline Storage level = MonadicEffect::make(effects::families::log, effects::log::level);
  inline Storage critical = MonadicEffect::make(effects::families::log, effects::log::critical);
  inline Storage error = MonadicEffect::make(effects::families::log, effects::log::error);
  inline Storage warning = MonadicEffect::make(effects::families::log, effects::log::warning);
  inline Storage info = MonadicEffect::make(effects::families::log, effects::log::info);
  inline Storage debug = MonadicEffect::make(effects::families::log, effects::log::debug);
  inline Storage trace = MonadicEffect::make(effects::families::log, effects::log::trace);
  inline Storage timestamp = MonadicEffect::make(effects::families::log, effects::log::timestamp);

  // Effect: Random
  // Effect: Random: Nilads
  inline Storage random = NiladicEffect::make(effects::families::random, effects::random::random);

  // Effect: Random: Monads
  inline Storage roll = MonadicEffect::make(effects::families::random, effects::random::roll);

  // Effect: Random: Dyads
  inline Storage rolls = DyadicEffect::make(effects::families::random, effects::random::rolls);
  inline Storage deal = DyadicEffect::make(effects::families::random, effects::random::deal);

  // Effect: Relations
  // Effect: Relations: Monads
  inline Storage makeTable = MonadicEffect::make(effects::families::relation, effects::relation::makeTable);
  inline Storage copyTable = MonadicEffect::make(effects::families::relation, effects::relation::copyTable);
  inline Storage free = MonadicEffect::make(effects::families::relation, effects::relation::freeTable);
  inline Storage flatten = MonadicEffect::make(effects::families::relation, effects::relation::flatten);

  // Effect: Relations: Dyads
  inline Storage insert = DyadicEffect::make(effects::families::relation, effects::relation::insert);
  inline Storage remove = DyadicEffect::make(effects::families::relation, effects::relation::remove);
  inline Storage iunion = DyadicEffect::make(effects::families::relation, effects::relation::iunion);
  inline Storage project = DyadicEffect::make(effects::families::relation, effects::relation::project);
  inline Storage difference = DyadicEffect::make(effects::families::relation, effects::relation::difference);
  inline Storage rename = DyadicEffect::make(effects::families::relation, effects::relation::rename);
  inline Storage crossProduct = DyadicEffect::make(effects::families::relation, effects::relation::crossProduct);
  inline Storage restrict = DyadicEffect::make(effects::families::relation, effects::relation::restrict);
  inline Storage intersection = DyadicEffect::make(effects::families::relation, effects::relation::intersection);

  // Effect: State
  // Effect: State: Nilads
  inline Storage put = NiladicEffect::make(effects::families::state, effects::state::put);

  // Effect: State: Monads
  inline Storage get = MonadicEffect::make(effects::families::state, effects::state::get);
  inline Storage modify = MonadicEffect::make(effects::families::state, effects::state::modify);

} // namespace iota

#endif //EFFECTS_H
