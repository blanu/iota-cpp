//
// Created by Dr. Brandon Wiley on 10/27/25.
//

#ifndef IOTA_CPP_GPIOEFFECTS_H
#define IOTA_CPP_GPIOEFFECTS_H

#include <storage/storage.h>

// FIXME - register a GPIOPin Noun type

class GPIOEffects
{
  public:
    static Storage get(const Storage& i);
    static Storage mode(const Storage& i, const Storage& o);
    static Storage readBit(const Storage& i);
    static Storage writeBit(const Storage& i, const Storage& o);
    static Storage readInt(const Storage& i);
    static Storage writeInt(const Storage& i, const Storage& o);
    static Storage startSquareWave(const Storage& i, const Storage& o);
    static Storage stopSquareWave(const Storage& i);
    static Storage readShortPulse(const Storage& i, const Storage& o);
    static Storage readLongPulse(const Storage& i, const Storage& o);
    static Storage readShift(const Storage& i, const Storage& o);
    static Storage writeShift(const Storage& i, const Storage& o);
};


#endif //IOTA_CPP_GPIOEFFECTS_H