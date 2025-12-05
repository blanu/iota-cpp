// SPIEffects.cpp
//
// Created by Dr. Brandon Wiley on 10/30/25.
//

#include "SPIEffects.h"

#include <storage/word_array.h>
#include "nouns/integer.h"
#include "nouns/data.h"

#include <Arduino.h>
#include <SPI.h>

void SPIEffects::initialize()
{
}

Storage SPIEffects::get(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<SPIPorts>(ii))
    {
      case SPIPorts::SPI0:
        return Integer::make(ii); // FIXME - should be a SPIPort NounType

      case SPIPorts::SPI1:
        return Integer::make(ii); // FIXME - should be a SPIPort NounType

      case SPIPorts::SPI2:
        return Integer::make(ii); // FIXME - should be a SPIPort NounType

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::begin(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<SPIPorts>(ii))
    {
      case SPIPorts::SPI0:
        SPI.begin();
        return i;

      case SPIPorts::SPI1:
        SPI1.begin();
        return i;

      case SPIPorts::SPI2:
        SPI2.begin();
        return i;

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::end(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<SPIPorts>(ii))
    {
      case SPIPorts::SPI0:
        SPI.end();
        return i;

      case SPIPorts::SPI1:
        SPI1.end();
        return i;

      case SPIPorts::SPI2:
        SPI2.end();
        return i;

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::beginTransaction(const Storage& i, const Storage& settings)
{
  // settings should be a MixedArray or Array with [clock, bitOrder, dataMode]
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(settings.i))
    {
      auto elements = std::get<ints>(settings.i);
      if(elements.size() >= 3)
      {
        uint32_t clock = static_cast<uint32_t>(elements[0]);
        uint8_t bitOrder = static_cast<uint8_t>(elements[1]);
        uint8_t dataMode = static_cast<uint8_t>(elements[2]);

        SPISettings spiSettings(clock, bitOrder, dataMode);

        switch(static_cast<SPIPorts>(ii))
        {
          case SPIPorts::SPI0:
            SPI.beginTransaction(spiSettings);
            return i;

          case SPIPorts::SPI1:
            SPI1.beginTransaction(spiSettings);
            return i;

          case SPIPorts::SPI2:
            SPI2.beginTransaction(spiSettings);
            return i;

          default:
            return WordArray::nil();
        }
      }
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::endTransaction(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    switch(static_cast<SPIPorts>(ii))
    {
      case SPIPorts::SPI0:
        SPI.endTransaction();
        return i;

      case SPIPorts::SPI1:
        SPI1.endTransaction();
        return i;

      case SPIPorts::SPI2:
        SPI2.endTransaction();
        return i;

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::transferByte(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      uint8_t data = static_cast<uint8_t>(std::get<int>(o.i));
      uint8_t result;

      switch(static_cast<SPIPorts>(ii))
      {
        case SPIPorts::SPI0:
          result = SPI.transfer(data);
          return Integer::make(result);

        case SPIPorts::SPI1:
          result = SPI1.transfer(data);
          return Integer::make(result);

        case SPIPorts::SPI2:
          result = SPI2.transfer(data);
          return Integer::make(result);

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::transfer(const Storage& i, const Storage& o)
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

        switch(static_cast<SPIPorts>(ii))
        {
          case SPIPorts::SPI0:
            SPI.transfer(bytes.data(), bytes.size());
            return Data::make(bytes);

          case SPIPorts::SPI1:
            SPI1.transfer(bytes.data(), bytes.size());
            return Data::make(bytes);

          case SPIPorts::SPI2:
            SPI2.transfer(bytes.data(), bytes.size());
            return Data::make(bytes);

          default:
            return WordArray::nil();
        }
      }
    }
  }

  return WordArray::nil();
}

Storage SPIEffects::transfer16(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i))
    {
      uint16_t data = static_cast<uint16_t>(std::get<int>(o.i));
      uint16_t result;

      switch(static_cast<SPIPorts>(ii))
      {
        case SPIPorts::SPI0:
          result = SPI.transfer16(data);
          return Integer::make(result);

        case SPIPorts::SPI1:
          result = SPI1.transfer16(data);
          return Integer::make(result);

        case SPIPorts::SPI2:
          result = SPI2.transfer16(data);
          return Integer::make(result);

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}