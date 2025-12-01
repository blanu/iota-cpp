//
// Created by Dr. Brandon Wiley on 12/1/25.
//

#include "state.h"

#include "api.h"
#include "verbs.h"
#include "../effects.h"
#include "nouns/symbol.h"

void State::initialize(EffectsProvider* effects_register)
{
  INTERN_INT(get);
  INTERN_EFFECT(iota, Nilad, get);

  INTERN_INT(put);
  INTERN_EFFECT(iota, Monad, put);

  INTERN_INT(modify);
  INTERN_EFFECT(iota, Monad, modify);

  INTERN_INT(pull);
  INTERN_EFFECT(iota, Monad, pull);

  INTERN_INT(push);
  INTERN_EFFECT(iota, Dyad, push);

  INTERN_INT(replace);
  INTERN_EFFECT(iota, Dyad, replace);

  INTERN_INT(transform);
  INTERN_EFFECT(iota, Triad, transform);
}

Storage State::pull_impl(const Storage& i)
{
  using namespace iota;
  using iota::get;

  return evalExpressionCppToIota({get, retrieve, i});
}

Storage State::push_impl(const Storage& i, const Storage& x)
{
  using namespace iota;
  using iota::get;
  using iota::put;

  return evalExpressionCppToIota({get, mutate, i, x, put});
}

Storage State::replace_impl(const Storage& i, const Storage& f)
{
  using namespace iota;
  using iota::get;
  using iota::put;

  return evalExpressionCppToIota({get, mutate, i, {get, retrieve, i, f}, put});
}

Storage State::transform_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;
  using iota::get;
  using iota::put;

  return evalExpressionCppToIota({get, mutate, x, {get, retrieve, i, f}, put});
}