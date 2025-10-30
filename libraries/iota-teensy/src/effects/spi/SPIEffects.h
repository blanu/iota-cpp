// SPIEffects.h
//
// Created by Dr. Brandon Wiley on 10/30/25.
//

#ifndef IOTA_CPP_SPIEFFECTS_H
#define IOTA_CPP_SPIEFFECTS_H

#include <storage/storage.h>

enum class SPIPorts : int
{
  SPI0 = 0,
  SPI1 = 1,
  SPI2 = 2
};

class SPIEffects
{
  public:
    static void initialize();
    static Storage get(const Storage& i);
    static Storage begin(const Storage& i);
    static Storage end(const Storage& i);
    static Storage beginTransaction(const Storage& i, const Storage& settings);
    static Storage endTransaction(const Storage& i);
    static Storage transferByte(const Storage& i, const Storage& o);
    static Storage transfer(const Storage& i, const Storage& o);
    static Storage transfer16(const Storage& i, const Storage& o);
};

#endif //IOTA_CPP_SPIEFFECTS_H