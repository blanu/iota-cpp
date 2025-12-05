//
// Created by Dr. Brandon Wiley on 10/29/25.
//

#include "I2CEffects.h"

#include <storage/word_array.h>
#include "nouns/integer.h"

#include <Arduino.h>
#include <Wire.h>

Storage I2CEffects::initialize()
{

}

Storage I2CEffects::get(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<I2CPorts>(ii))
    {
      case I2CPorts::I2C0:
        return Integer::make(ii); // FIXME - should be a I2CPort NounType

      case I2CPorts::I2C1: // FIXME - should be a I2CPort NounType
        return Integer::make(ii);

      case I2CPorts::I2C2: // FIXME - should be a I2CPort NounType
        return Integer::make(ii);

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::setClock(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      switch(static_cast<I2CPorts>(ii))
      {
        case I2CPorts::I2C0:
          Wire.setClock(oi);
          return i;

        case I2CPorts::I2C1: // FIXME - should be a I2CPort NounType
          Wire1.setClock(oi);
          return i;

        case I2CPorts::I2C2: // FIXME - should be a I2CPort NounType
          Wire2.setClock(oi);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::available(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<I2CPorts>(ii))
    {
      case I2CPorts::I2C0:
        int result = Wire.available();
        return Integer::make(result);

      case I2CPorts::I2C1:
        int result = Wire1.available();
        return Integer::make(result);

      case I2CPorts::I2C2:
        int result = Wire2.available();
        return Integer::make(result);

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::begin(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<I2CPorts>(ii))
    {
      case I2CPorts::I2C0:
        Wire.begin();
        return i;

      case I2CPorts::I2C1:
        Wire1.begin();
        return i;

      case I2CPorts::I2C2:
        Wire2.begin();
        return i;

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::beginWithAddress(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      switch(static_cast<I2CPorts>(ii))
      {
        case I2CPorts::I2C0:
          Wire.begin(oi);
          return i;

        case I2CPorts::I2C1:
          Wire1.begin(oi);
          return i;

        case I2CPorts::I2C2:
          Wire2.begin(oi);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::end(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<I2CPorts>(ii))
    {
      case I2CPorts::I2C0:
        Wire.end();
        return i;

      case I2CPorts::I2C1:
        Wire1.end();
        return i;

      case I2CPorts::I2C2:
        Wire2.end();
        return i;

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::read(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<I2CPorts>(ii))
    {
      case I2CPorts::I2C0:
        int result = Wire.read();
        return Integer::make(result);

      case I2CPorts::I2C1:
        int result = Wire1.read();
        return Integer::make(result);

      case I2CPorts::I2C2:
        int result = Wire2.read();
        return Integer::make(result);

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::beginTransmission(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      switch(static_cast<I2CPorts>(ii))
      {
        case I2CPorts::I2C0:
          Wire.beginTransmission(oi);
          return i;

        case I2CPorts::I2C1:
          Wire.beginTransmission(oi);
          return i;

        case I2CPorts::I2C2:
          Wire.beginTransmission(oi);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::endTransmission(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<I2CPorts>(ii))
    {
      case I2CPorts::I2C0:
        Wire.endTransmission();
        return i;

      case I2CPorts::I2C1:
        Wire1.endTransmission();
        return i;

      case I2CPorts::I2C2:
        Wire2.endTransmission();
        return i;

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::endTransmissionSendStop(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o.i);

      switch(static_cast<I2CPorts>(ii))
      {
        case I2CPorts::I2C0:
          Wire.endTransmission(oi);
          return i;

        case I2CPorts::I2C1:
          Wire1.endTransmission(oi);
          return i;

        case I2CPorts::I2C2:
          Wire2.endTransmission(oi);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage I2CEffects::write(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(o.i))
    {
      maybe<std::vector<uint8_t>> maybeBytes = Data::toBytes(o);
      if(maybeBytes)
      {
        std::vector<uint8_t> bytes = *maybeBytes;

        switch(static_cast<I2CPorts>(ii))
        {
          case I2CPorts::I2C0:
            Wire.write(bytes);

          case I2CPorts::I2C1:
            Wire1.write(bytes);

          case I2CPorts::I2C2:
            Wire2.write(bytes);

          default:
            return WordArray::nil();
        }
      }
    }
  }

  return WordArray::nil();
}