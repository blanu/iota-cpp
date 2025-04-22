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
  // Initialize system effects
  registerMonadicEffect(StorageType::WORD_ARRAY, NounType::STRING, effects::families::log, effects::log::info, Log::info_impl);
}

Storage TestingEffectsRegister::getEffectState() const
{
  return Log::getLogs();
}
