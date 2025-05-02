//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include "testing_effects_register.h"
#include "../effects_register.h"

#include "log/log.h"

#include "../../storage/storage.h"

#include "../../nouns/noun.h"
#include "../../verbs.h"
#include "../effects.h"
#include "random/random.h"

TestingEffectsRegister::TestingEffectsRegister()
{
  Log::initialize(this);
  Random::initialize(this);

  // Initialize system effects
  // Random
  // Log: Nilads
  registerNiladicSinkEffect(effects::families::log, effects::log::timestamp, Log::timestamp_impl);

  // Log: Monads
  registerMonadicSinkEffect(StorageType::WORD, NounType::INTEGER, effects::families::log, effects::log::level, Log::level_impl);

  registerMonadicSinkEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::critical, Log::critical_impl);
  registerMonadicSinkEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::error, Log::error_impl);
  registerMonadicSinkEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::warning, Log::warning_impl);
  registerMonadicSinkEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::info, Log::info_impl);
  registerMonadicSinkEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::debug, Log::debug_impl);
  registerMonadicSinkEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::trace, Log::trace_impl);

  // Random
  // Random: Nilads
  registerNiladicSourceEffect(effects::families::random, effects::random::random, Random::random_impl);

  // Random: Monads
  registerMonadicSourceEffect(StorageType::WORD, NounType::INTEGER, effects::families::random, effects::random::roll, Random::roll_impl);

  // Random : Dyads
  registerDyadicSourceEffect(StorageType::WORD, NounType::INTEGER, effects::families::random, effects::random::rolls, StorageType::WORD, NounType::INTEGER, Random::rolls_impl);

  registerDyadicSourceEffect(StorageType::WORD_ARRAY, NounType::LIST, effects::families::random, effects::random::deal, StorageType::WORD, NounType::INTEGER, Random::deal_impl);
}

Storage TestingEffectsRegister::getEffectState() const
{
  return Log::getEffectState();
}
