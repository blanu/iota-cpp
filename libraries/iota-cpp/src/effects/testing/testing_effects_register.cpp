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

TestingEffectsRegister::TestingEffectsRegister()
{
  Log::initialize(this);

  // Initialize system effects
  registerMonadicEffect(StorageType::WORD, NounType::INTEGER, effects::families::log, effects::log::level, Log::level_impl);
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::critical, Log::critical_impl);
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::error, Log::error_impl);
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::warning, Log::warning_impl);
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::info, Log::info_impl);
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::debug, Log::debug_impl);
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::trace, Log::trace_impl);
}

Storage TestingEffectsRegister::getEffectState() const
{
  return Log::getLogs();
}
