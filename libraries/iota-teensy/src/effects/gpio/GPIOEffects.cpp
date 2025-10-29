//
// Created by Dr. Brandon Wiley on 10/27/25.
//

#include "GPIOEffects.h"

#include <storage/word_array.h>
#include <nouns/integer.h>

#include "api.h"

#include <Arduino.h>

Storage GPIOEffects::get(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    return Word::make(ii); // FIXME - NounType should be GPIOPin
  }

  return WordArray::nil();
}

Storage GPIOEffects::mode(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      if(oi == 0 || oi == 1)
      {
        pinMode(static_cast<uint8_t>(ii), static_cast<uint8_t>(oi));

        return i;
      }
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::readBit(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    int result = digitalRead(static_cast<uint8_t>(ii));

    return Integer::make(result);
  }

  return WordArray::nil();
}

Storage GPIOEffects::writeBit(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      digitalWrite(static_cast<uint8_t>(ii), static_cast<uint8_t>(oi));

      return i;
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::readInt(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    int result = analogRead(static_cast<uint8_t>(ii));

    return Integer::make(result);
  }

  return WordArray::nil();
}

Storage GPIOEffects::writeInt(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      analogWrite(static_cast<uint8_t>(ii), oi);

      return i;
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::startSquareWave(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      tone(static_cast<uint8_t>(ii), static_cast<unsigned int>(oi));

      return i;
    }
    else if(std::holds_alternative<ints>(o.i))
    {
      ints ois = std::get<ints>(o.i);
      if(ois.size() == 2)
      {
        int frequency = ois[0];
        int duration = ois[1];

        tone(static_cast<uint8_t>(ii), static_cast<unsigned int>(frequency), static_cast<unsigned long>(duration));

        return i;
      }
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::stopSquareWave(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    noTone(static_cast<uint8_t>(ii));

    return i;
  }

  return WordArray::nil();
}

Storage GPIOEffects::readShortPulse(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      unsigned long result = pulseIn(static_cast<uint8_t>(ii), static_cast<uint8_t>(oi));

      return Integer::make(static_cast<int>(result)); // FIXME promote to a bigint if too big for an int
    }
    else if(std::holds_alternative<ints>(o.i))
    {
      ints ois = std::get<ints>(o.i);
      if(ois.size() == 2)
      {
        int value = ois[0];
        int timeout = ois[1];

        unsigned long result = pulseIn(static_cast<uint8_t>(ii), static_cast<uint8_t>(value), static_cast<unsigned long>(timeout));

        return Integer::make(static_cast<int>(result)); // FIXME promote to a bigint if too big for an int
      }
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::readLongPulse(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      unsigned long result = pulseInLong(static_cast<uint8_t>(ii), static_cast<uint8_t>(oi));

      return Integer::make(static_cast<int>(result)); // FIXME promote to a bigint if too big for an int
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::writeShift(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.size() == 4)
    {
      int dataPin = iis[0];
      int clockPin = iis[1];
      int bitOrder = iis[2];
      int value = iis[3];

      shiftOut(static_cast<uint8_t>(dataPin), static_cast<uint8_t>(clockPin), static_cast<uint8_t>(bitOrder), static_cast<uint8_t>(value));
    }
  }

  return WordArray::nil();
}

Storage GPIOEffects::readShift(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.size() == 3)
    {
      int dataPin = iis[0];
      int clockPin = iis[1];
      int bitOrder = iis[2];

      int result = static_cast<int>(shiftIn(static_cast<uint8_t>(dataPin), static_cast<uint8_t>(clockPin), static_cast<uint8_t>(bitOrder)));

      return Integer::make(result);
    }
  }

  return WordArray::nil();
}