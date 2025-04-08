//
// Created by Dr. Brandon Wiley on 3/28/25.
//

#ifndef SIGNAL_H
#define SIGNAL_H

#include "../storage/storage.h"

class Signal
{
  public:
    static Storage make(Storage value, Storage i, Storage e);
    static Storage make(Storage value, Storage i, Storage e, Storage x);
};

#endif //SIGNAL_H
