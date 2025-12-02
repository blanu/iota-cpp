//
// Created by Dr. Brandon Wiley on 12/1/25.
//

#include "state.h"

#include "api.h"
#include "verbs.h"
#include "../../verbs.h"

#include "nouns/noun.h"
#include "nouns/symbol.h"

void State::initialize(EffectsProvider* effects_register)
{
  INTERN_INT(pull);
  INTERN_EFFECT(iota, Monad, pull);

  INTERN_INT(push);
  INTERN_EFFECT(iota, Dyad, push);

  INTERN_INT(replace);
  INTERN_EFFECT(iota, Dyad, replace);

  INTERN_INT(transform);
  INTERN_EFFECT(iota, Triad, transform);

  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LENS, State::pull, State::pull_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LENS, State::pull, State::pull_impl);

  Noun::registerDyad(StorageType::ANY, NounType::ANY, State::push, StorageType::WORD_ARRAY, NounType::LENS, State::push_impl);
  Noun::registerDyad(StorageType::ANY, NounType::ANY, State::push, StorageType::MIXED_ARRAY, NounType::LENS, State::push_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LENS, State::replace, StorageType::WORD, NounType::BUILTIN_MONAD, State::replace_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LENS, State::replace, StorageType::WORD, NounType::BUILTIN_MONAD, State::replace_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LENS, State::replace, StorageType::WORD, NounType::USER_MONAD, State::replace_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LENS, State::replace, StorageType::WORD, NounType::USER_MONAD, State::replace_impl);

  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::WORD_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::WORD_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::USER_MONAD, StorageType::WORD_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::USER_MONAD, StorageType::WORD_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::USER_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, State::transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, State::transform, StorageType::WORD, NounType::USER_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, State::transform_impl);
}

Storage State::pull_impl(const Storage& i)
{
  using namespace iota;
  using iota::get;
  using iota::retrieve;

  return evalExpressionCppToIota({get, retrieve, i});
}

Storage State::push_impl(const Storage& i, const Storage& x)
{
  using namespace iota;
  using iota::get;
  using iota::put;
  using iota::store;

  return evalExpressionCppToIota({get, store, i, x, put});
}

Storage State::replace_impl(const Storage& i, const Storage& f)
{
  using namespace iota;
  using iota::get;
  using iota::put;
  using iota::retrieve;
  using iota::store;

  return evalExpressionCppToIota({get, store, i, {get, retrieve, i, f}, put});
}

Storage State::transform_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;
  using iota::get;
  using iota::put;
  using iota::retrieve;
  using iota::store;

  return evalExpressionCppToIota({get, store, x, {get, retrieve, i, f}, put});
}