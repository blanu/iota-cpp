//
// Created by Dr. Brandon Wiley on 7/6/25.
//

#include "audio.h"

#include <Audio.h>

#include <storage/word.h>
#include <storage/word_array.h>

#include "../../../../iota-cpp/src/nouns/error.h"

// Input
AudioInputI2S Audio::input_i2s;
AudioInputUSB Audio::input_usb;

// Output
AudioOutputI2S Audio::output_i2s;
AudioOutputUSB Audio::output_usb;

// Control
AudioControlSGTL5000* Audio::control_sgtl5000;

// Synth
std::vector<AudioSynthToneSweep*> Audio::synths_sweep;
AudioSynthNoiseWhite Audio::synth_noise;

// Effect
std::vector<AudioEffectReverb*> Audio::effects_reverb;

// Filter
std::vector<AudioFilterLadder*> Audio::filters_ladder;

// Analyze
std::vector<AudioAnalyzeFFT1024*> Audio::analyzers_fft1024;

// Play
std::vector<AudioPlayMemory*> Audio::plays_memory;

// Record
std::vector<AudioRecordQueue*> Audio::records_queue;

// Mixer
std::vector<AudioMixer4*> Audio::mixers;

// Connections
std::vector<AudioConnection*> Audio::edges;
AudioConnection Audio::noiseToI2S(synth_noise, 0, output_i2s, 0);

void Audio::initialize()
{
  control_sgtl5000 = new AudioControlSGTL5000();

  synths_sweep = std::vector<AudioSynthToneSweep*>();
  effects_reverb = std::vector<AudioEffectReverb*>();
  filters_ladder = std::vector<AudioFilterLadder*>();
  analyzers_fft1024 = std::vector<AudioAnalyzeFFT1024*>();
  plays_memory = std::vector<AudioPlayMemory*>();
  records_queue = std::vector<AudioRecordQueue*>();
  mixers = std::vector<AudioMixer4*>();
  edges = std::vector<AudioConnection*>();

  control_sgtl5000->enable();
  control_sgtl5000->inputSelect(AUDIO_INPUT_MIC);
  control_sgtl5000->volume(0.5);

  synth_noise.amplitude(0.0f);
}

Storage Audio::input_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(ii)
    {
      case effects::audio::ios::i2s:
      {
        return AudioNode::make(input_i2s_id);
      }

      case effects::audio::ios::usb:
      {
        return AudioNode::make(input_usb_id);
      }

      default:
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Audio::output_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(ii)
    {
      case effects::audio::ios::i2s:
      {
        return AudioNode::make(output_i2s_id);
      }

      case effects::audio::ios::usb:
      {
        return AudioNode::make(output_usb_id);
      }

      default:
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Audio::to_impl(const Storage& i, const Storage& x)
{
  AudioStream* a = Audio::findNode(i);
  AudioStream* b = Audio::findNode(x);

  if(a == nullptr || b == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  AudioNoInterrupts();
  AudioConnection* conn0 = new AudioConnection(*a, 0, *b, 0);
  AudioConnection* conn1 = new AudioConnection(*b, 1, *a, 1);
  AudioInterrupts();

  edges.push_back(conn0);
  edges.push_back(conn1);

  return AudioLink::make(i, 0, x, 0);
}

// Audio private
AudioStream* Audio::findNode(Storage i)
{
  if(i.o != Audio::AUDIO_NODE)
  {
    return nullptr;
  }

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(ii)
    {
      case Audio::input_i2s_id:
        return &input_i2s;

      case Audio::output_i2s_id:
        return &output_i2s;

      default:
        return nullptr;
    }
  }

  return nullptr;
}

// end Audio private

Storage AudioIO::make(int i)
{
  return Word::make(i, Audio::AUDIO_IO);
}

Storage AudioNode::make(int i)
{
  return Word::make(i, Audio::AUDIO_NODE);
}

Storage AudioLink::make(int i, int x)
{
  return WordArray::make({i, x}, Audio::AUDIO_LINK);
}

Storage AudioLink::make(int i, int ic, int x, int xc)
{
  return WordArray::make({i, ic, x, xc}, Audio::AUDIO_LINK);
}

Storage AudioLink::make(Storage i, int ic, Storage x, int xc)
{
  return WordArray::make({std::get<int>(i.i), ic, std::get<int>(x.i), xc}, Audio::AUDIO_LINK);
}

Storage AudioLink::make(Storage i, Storage x)
{
  return WordArray::make({std::get<int>(i.i), std::get<int>(x.i)}, Audio::AUDIO_LINK);
}
