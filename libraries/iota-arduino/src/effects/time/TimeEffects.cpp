//
// Created by Dr. Brandon Wiley on 10/28/25.
//

#include "TimeEffects.h"

#include <Arduino.h>

#include <storage/storage.h>
#include <storage/word_array.h>
#include <nouns/integer.h>

static void initialize()
{

}

static Storage ticksInMilliseconds()
{
  unsigned long result = millis();
  return Integer::make(result);
}

static Storage ticksInMicroseconds()
{
  unsigned long result = micros();
  return Integer::make(result);
}

static Storage waitMilliseconds(const Storage& i)
{
  unsigned long* duration = Integer::toUnsignedLong(i);
  if(duration)
  {
    delay(*duration);
  }

  return WordArray::nil();
}

static Storage waitMicroseconds(const Storage& i)
{
  unsigned long* duration = Integer::toUnsignedLong(i);
  if(duration)
  {
    delayMicroseconds(*duration);
  }

  return WordArray::nil();
}