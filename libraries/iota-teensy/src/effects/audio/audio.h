//
// Created by Dr. Brandon Wiley on 7/6/25.
//

#ifndef AUDIO_H
#define AUDIO_H

#include <Audio.h>

#include <map>

#include <storage/storage.h>

#include <nouns/symbol.h>

class TeensyAudio
{
  public:
    // Input
    AudioInputI2S *input_i2s;

    // Output
    AudioOutputI2S *output_i2s;

    // Synth
    std::vector<AudioSynthToneSweep *> synths_sweep;

    // Effect
    std::vector<AudioEffectReverb *> effects_reverb;

    // Filter
    std::vector<AudioFilterLadder *> filters_ladder;

    // Analyze
    std::vector<AudioAnalyzeFFT1024 *> analyzers_fft1024;

    // Control
    AudioControlSGTL5000 *control_sgtl5000;

    // Play
    std::vector<AudioPlayMemory *> plays_memory;

    // Record
    std::vector<AudioRecordQueue *> records_queue;

    // Mixer
    std::vector<AudioMixer4 *> mixers;

    // Connections
    static std::map<int, AudioConnection *> edges;

    static void initialize();
};

namespace effects::audio
{
  static constexpr int input   =  1;
  static constexpr int output  =  2;
  static constexpr int synth   =  3;
  static constexpr int effect  =  4;
  static constexpr int filter  =  5;
  static constexpr int analyze =  6;
  static constexpr int control =  7;
  static constexpr int play    =  8;
  static constexpr int record  =  9;
  static constexpr int mixer   = 10;
  static constexpr int to      = 11;
  static constexpr int set     = 12;
  static constexpr int get     = 13;
  static constexpr int read    = 14;
  static constexpr int start   = 15;
  static constexpr int stop    = 16;
  static constexpr int clear   = 17;
  static constexpr int channel = 18;
}

namespace effects::audio::ios
{
  static constexpr int i2s   =  3;
  static constexpr int i2s2  =  4;
  static constexpr int i2s6  =  5;
  static constexpr int i2s8  =  6;
  static constexpr int spdif =  8;
  static constexpr int tdm   =  9;
  static constexpr int tdm2  = 10;
}

namespace effects::audio::inputs
{
  static constexpr int adc   =  1;
  static constexpr int adcs  =  2;
  static constexpr int pdm   =  7;
}

namespace effects::audio::outputs
{
  static constexpr int adat   =  1;
  static constexpr int dac    =  2;
  static constexpr int dacs   =  3;
  static constexpr int mqs    =  9;
  static constexpr int pt8211 = 10;
  static constexpr int pwm    = 11;
}

namespace effects::audio::synths
{
  static constexpr int dc        =  1;
  static constexpr int string    =  2;
  static constexpr int pink      =  3;
  static constexpr int pwm       =  4;
  static constexpr int drum      =  5;
  static constexpr int sine      =  6;
  static constexpr int sweep     =  7;
  static constexpr int waveform  =  8;
  static constexpr int wavetable =  9;
  static constexpr int noise     = 10;
}

namespace effects::audio::audioEffects
{
  static constexpr int crush = 1;
  static constexpr int chorus = 2;
  static constexpr int combine = 3;
  static constexpr int delay = 4;
  static constexpr int envelope = 5;
  static constexpr int fade = 6;
  static constexpr int flange = 7;
  static constexpr int freeverb = 8;
  static constexpr int granular = 9;
  static constexpr int midside = 10;
  static constexpr int multiply = 11;
  static constexpr int rectifier = 12;
  static constexpr int reverb = 13;
  static constexpr int wavefolder = 14;
  static constexpr int waveshaper = 15;
}

namespace effects::audio::filters
{
  static constexpr int biquad = 1;
  static constexpr int fir = 2;
  static constexpr int ladder = 3;
  static constexpr int variable = 4;
}

namespace effects::audio::analyzers
{
  static constexpr int fft   = 1;
  static constexpr int note  = 2;
  static constexpr int peak  = 3;
  static constexpr int print = 4;
  static constexpr int rms   = 5;
  static constexpr int tone  = 6;
}

namespace effects::audio::controllers
{
  static constexpr int sgtl5000 = 1;
}

namespace effects::audio::players
{
  static constexpr int memory = 1;
  static constexpr int queue = 2;
  static constexpr int raw = 3;
  static constexpr int wav = 4;
  static constexpr int flash = 5;
}

namespace effects::audio::properties
{
  static constexpr int playing   = 1;
  static constexpr int duration  = 2;
  static constexpr int frequency = 3;
  static constexpr int resonance = 4;
  static constexpr int octave    = 5;
  static constexpr int gain      = 6;
  static constexpr int drive     = 7;
  static constexpr int method    = 8;
  static constexpr int available = 9;
  static constexpr int volume    = 10;
  static constexpr int level     = 11;
  static constexpr int mute      = 12;
  static constexpr int port      = 13;
  static constexpr int position  = 14;
  static constexpr int length    = 15;
}

namespace effects::audio::interpolation
{
  static constexpr int linear = 1;
  static constexpr int poly   = 2;
}

namespace effects::audio::inputPort
{
  static constexpr int mic  = 1;
  static constexpr int line = 2;
}

namespace effects::audio::outputPort
{
  static constexpr int headphone = 1;
  static constexpr int line      = 2;
}

namespace iota
{
  inline Storage input = Monad::make(effects::audio::input);
  inline Storage output = Monad::make(effects::audio::output);
  inline Storage to = Dyad::make(effects::audio::to);

  inline Storage i2s = Symbol::make(effects::audio::ios::i2s);
}

#endif //AUDIO_H
