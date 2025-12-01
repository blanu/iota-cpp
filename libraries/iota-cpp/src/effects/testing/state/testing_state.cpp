//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#include "testing_state.h"

#include "../../../api.h"

#include <storage/storage.h>
#include <storage/word.h>
#include <storage/word_array.h>

#include <nouns/noun.h>

#include <effects/state/state.h>

Storage TestingState::state = WordArray::nil();

void TestingState::initialize(EffectsProvider* effects_register)
{
  State::initialize(effects_register);

  // Monolithic state
  Noun::registerNilad(State::get, get_impl);

  Noun::registerMonad(StorageType::ANY, NounType::ANY, State::put, put_impl);

  Noun::registerMonad(StorageType::WORD, NounType::BUILTIN_MONAD, State::modify, modify_impl);
  Noun::registerMonad(StorageType::WORD, NounType::USER_MONAD, State::modify, modify_impl);

  // Lensed state
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