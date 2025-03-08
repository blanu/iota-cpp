#include <Arduino.h>
#include "debug.h"

void d(char b)
{
  Serial.write((char)0x80);
  Serial.write(b);
}
