//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include "testing_effects_provider.h"
#include "../effects_provider.h"

#include "log/log.h"

#include <storage/storage.h>

#include "../../nouns/noun.h"
#include "../effects.h"
#include <storage/mixed_array.h>
#include <storage/word_array.h>
#include "random/random.h"
#include "state/state.h"

TestingEffectsProvider::TestingEffectsProvider()
{
  Log::initialize(this);
  Random::initialize(this);

  // Initialize system effects
  // Random
  // Log: Nilads
  Noun::registerNilad((effects::families::log << 8) | effects::log::timestamp, Log::timestamp_impl);

  // Log: Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, (effects::families::log << 8) | effects::log::level, Log::level_impl);

  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, (effects::families::log << 8) | effects::log::critical, Log::critical_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, (effects::families::log << 8) | effects::log::error, Log::error_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, (effects::families::log << 8) | effects::log::warning, Log::warning_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, (effects::families::log << 8) | effects::log::info, Log::info_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, (effects::families::log << 8) | effects::log::debug, Log::debug_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, (effects::families::log << 8) | effects::log::trace, Log::trace_impl);

  // Random
  // Random: Nilads
  Noun::registerNilad((effects::families::random << 8) | effects::random::random, Random::random_impl);

  // Random: Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, (effects::families::random << 8) | effects::random::roll, Random::roll_impl);

  // Random : Dyads
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, (effects::families::random << 8) | effects::random::rolls, StorageType::WORD, NounType::INTEGER, Random::rolls_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, (effects::families::random << 8) | effects::random::deal, StorageType::WORD, NounType::INTEGER, Random::deal_impl);

  // State
  // State: Nilads
  Noun::registerNilad((effects::families::state << 8) | effects::state::get, State::get_impl);

  // State: Monads
  Noun::registerMonad(StorageType::ANY, NounType::ANY, (effects::families::state << 8) | effects::state::put, State::put_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::EXPRESSION, (effects::families::state << 8) | effects::state::modify, State::modify_impl);
}

Storage TestingEffectsProvider::getEffectState()
{
  auto results = mixed();

  // Effects: Log
  Storage logEffects = Log::getEffectState();
  results.push_back(logEffects);

  // Effects: Relation
  Storage relationEffects = WordArray::nil();
  results.push_back(relationEffects);

  // Effects: Random
  Storage randomEffects = WordArray::nil();
  results.push_back(randomEffects);

  // Effects: State
  Storage stateEffects = State::getEffectState();
  results.push_back(stateEffects);

  return MixedArray::make(results);
}
