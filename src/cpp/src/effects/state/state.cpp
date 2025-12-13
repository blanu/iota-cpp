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

  INTERN_INT(restore);
  INTERN_EFFECT(iota, Monad, restore);

  INTERN_INT(save);
  INTERN_EFFECT(iota, Dyad, save);

  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LENS, pull, pull_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LENS, pull, pull_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::USER_SYMBOL, restore, restore_impl);

  Noun::registerDyad(StorageType::ANY, NounType::ANY, push, StorageType::WORD_ARRAY, NounType::LENS, push_impl);
  Noun::registerDyad(StorageType::ANY, NounType::ANY, push, StorageType::MIXED_ARRAY, NounType::LENS, push_impl);
  Noun::registerDyad(StorageType::ANY, NounType::ANY, save, StorageType::WORD_ARRAY, NounType::SYMBOL_DEFINITION, save_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LENS, replace, StorageType::WORD, NounType::BUILTIN_MONAD, replace_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LENS, replace, StorageType::WORD, NounType::BUILTIN_MONAD, replace_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LENS, replace, StorageType::WORD, NounType::USER_MONAD, replace_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LENS, replace, StorageType::WORD, NounType::USER_MONAD, replace_impl);

  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::WORD_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::WORD_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::USER_MONAD, StorageType::WORD_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::USER_MONAD, StorageType::WORD_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::BUILTIN_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::WORD_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::USER_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, transform_impl);
  Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::LENS, transform, StorageType::WORD, NounType::USER_MONAD, StorageType::MIXED_ARRAY, NounType::LENS, transform_impl);
}

// Get a value out of a the state structure with a lens
// i: lens for getting
Storage State::pull_impl(const Storage& i)
{
  using namespace iota;
  using iota::get;
  using iota::retrieve;

  return evalExpressionCppToIota({get, retrieve, i});
}

// Put a value into a the state structure with a lens
// i: new value
// x: lens for putting
Storage State::push_impl(const Storage& i, const Storage& x)
{
  using namespace iota;
  using iota::get;
  using iota::put;
  using iota::store;

  return evalExpressionCppToIota({get, store, i, x, put});
}

// Get a value out of the state structure with a lens, apply a function to it, and then put it back in with the same lens
// i: lens for getting and putting
// f: function to apply
Storage State::replace_impl(const Storage& i, const Storage& f)
{
  using namespace iota;
  using iota::pull;
  using iota::push;

  return evalExpressionCppToIota({i, pull, f, push, i});
}

// Take a value out of a structure with a lens, apply a function to it, and put it back in with a different lens
// i: lens for getting
// f: function to apply
// x: lens for putting
Storage State::transform_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;
  using iota::pull;
  using iota::push;

  return evalExpressionCppToIota({i, pull, f, push, x});
}

Storage State::save_impl(const Storage& i, const Storage& x)
{
  using namespace iota;
  using iota::getBindings;
  using iota::bind;
  using iota::putBindings;

  Storage oldBindings = evalExpressionCppToIota({getBindings});
  Storage newBindings = evalExpressionCppToIota({oldBindings, bind, i, x});
  evalExpressionCppToIota({newBindings, putBindings});

  return i;
}

Storage State::restore_impl(const Storage& i)
{
  using namespace iota;
  using iota::getBindings;
  using iota::resolve;

  return evalExpressionCppToIota({getBindings, resolve, i});
}