//
// Created by Dr. Brandon Wiley on 10/28/25.
//

#ifndef IOTA_CPP_TIMEEFFECTS_H
#define IOTA_CPP_TIMEEFFECTS_H

#include <storage/storage.h>

class TimeEffects
{
  public:
    static void initialize();

    static Storage ticksInMilliseconds();
    static Storage ticksInMicroseconds();
    static Storage waitMilliseconds(const Storage& i);
    static Storage waitMicroseconds(const Storage& i);
};


#endif //IOTA_CPP_TIMEEFFECTS_H