//
// Created by Dr. Brandon Wiley on 7/6/25.
//

#include "audio.h"

#include <Audio.h>

// Input
static AudioInputI2S *TeensyAudio::input_i2s;

// Output
static AudioOutputI2S *TeensyAudio::output_i2s;

// Synth
static std::vector<AudioSynthToneSweep *> TeensyAudio::synths_sweep;

// Effect
static std::vector<AudioEffectReverb *> TeensyAudio::effects_reverb;

// Filter
static std::vector<AudioFilterLadder *> TeensyAudio::filters_ladder;

// Analyze
static std::vector<AudioAnalyzeFFT1024 *> TeensyAudio::analyzers_fft1024;

// Control
static AudioControlSGTL5000 *TeensyAudio::control_sgtl5000;

// Play
static std::vector<AudioPlayMemory *> TeensyAudio::plays_memory;

// Record
static std::vector<AudioRecordQueue *> TeensyAudio::records_queue;

// Mixer
static std::vector<AudioMixer4 *> TeensyAudio::mixers;

// Connections
static std::map<int, AudioConnection *> TeensyAudio::edges;

void TeensyAudio::initialize();