#include <Arduino.h>

#include "IotaTeensy.h"

#include <eval_register.h>
#include <types.h>
#include <api.h>

#include "effects/audio/audio.h"

void setup()
{
  using namespace iota;

  EvalRegister::initialize();
  TeensyAudio::initialize();

  eval({ {i2s, input}, to, {i2s, output} });
}

void loop()
{
}