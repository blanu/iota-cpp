//
// Created by Dr. Brandon Wiley on 7/7/25.
//

#include "teensy_effects_provider.h"

#include <storage/storage.h>
#include <nouns/noun.h>
#include <effects/effects.h>

#include "effects/audio/audio.h"

TeensyEffectsProvider::TeensyEffectsProvider()
{
  // Audio
  Audio::initialize();

  Noun::registerMonad(StorageType::WORD, Audio::AUDIO_IO, (effects::families::audio << 8) | effects::audio::input, Audio::input_impl);
  Noun::registerMonad(StorageType::WORD, Audio::AUDIO_IO, (effects::families::audio << 8) | effects::audio::output, Audio::output_impl);
  Noun::registerDyad(StorageType::WORD, Audio::AUDIO_NODE, (effects::families::audio << 8) | effects::audio::to, StorageType::WORD, Audio::AUDIO_NODE, Audio::to_impl);
}