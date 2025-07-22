#include <Arduino.h>
#include <Audio.h>
#include <iota-teensy.h>

//AudioInputUSB input;
//AudioOutputUSB output;
//AudioConnection i2o0(input, 0, output, 0);
//AudioConnection i2o1(input, 1, output, 1);

void setup()
{
  using namespace iota;

  Serial.begin(9600);

  AudioMemory(40);

  EvalRegister::initialize();
  TeensyEffectsProvider();

  evalExpression({ {usb, input}, to, {usb, output} });
}

void loop()
{
  Serial.println('.');
}