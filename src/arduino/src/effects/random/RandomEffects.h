//
// Created by Dr. Brandon Wiley on 10/30/25.
//

#ifndef IOTA_CPP_RANDOMEFFECTS_H
#define IOTA_CPP_RANDOMEFFECTS_H

#include <storage/storage.h>

class RandomEffects
{
  public:
    static void initialize();

    static Storage randomMax(const Storage& i);
    static Storage randomRange(const Storage& i, const Storage& o);
    static Storage seed(const Storage& i);
};


#endif //IOTA_CPP_RANDOMEFFECTS_H