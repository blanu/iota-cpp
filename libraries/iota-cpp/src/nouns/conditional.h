//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Connection.h"
#include "../storage/storage.h"

class Conditional
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(const mixed &i);

    static Storage evaluate_impl(const Storage& i);
    static Storage truth_impl(const Storage& i);
};

#endif //CONDITIONAL_H
