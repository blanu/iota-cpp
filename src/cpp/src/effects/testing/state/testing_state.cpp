//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#include "testing_state.h"

#include "../../../api.h"

#include <storage/storage.h>
#include <storage/word.h>
#include <storage/word_array.h>

#include <nouns/noun.h>
#include <nouns/symbol.h>

#include <effects/state/state.h>

Storage TestingState::state = WordArray::nil();

void TestingState::initialize(EffectsProvider* effects_register)
{
  State::initialize(effects_register);

  INTERN_INT(get);
  INTERN_EFFECT(iota, Nilad, get);

  INTERN_INT(put);
  INTERN_EFFECT(iota, Monad, put);

  INTERN_INT(modify);
  INTERN_EFFECT(iota, Monad, modify);

  Noun::registerNilad(get, get_impl);

  Noun::registerMonad(StorageType::ANY, NounType::ANY, put, put_impl);

  Noun::registerMonad(StorageType::WORD, NounType::BUILTIN_MONAD, modify, modify_impl);
  Noun::registerMonad(StorageType::WORD, NounType::USER_MONAD, modify, modify_impl);
}

// Monads
Storage TestingState::get_impl()
{
  return state;
}

// Dyads
Storage TestingState::put_impl(const Storage& i)
{
  state = i;

  return i;
}

Storage TestingState::modify_impl(const Storage& f)
{
  Storage result = eval({state, f});
  state = result;
  return result;
}

Storage TestingState::getEffectState()
{
  return state;
}