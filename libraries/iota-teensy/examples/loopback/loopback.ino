#include "iota-teensy.h"

void setup()
{
  using namespace iota;

  AudioMemory(40);

  EvalRegister::initialize();
  TeensyEffectsProvider();

  evalExpression({ {i2s, input}, to, {i2s, output} });
}

void loop()
{
}