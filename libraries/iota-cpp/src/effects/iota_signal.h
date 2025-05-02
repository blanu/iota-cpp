//
// Created by Dr. Brandon Wiley on 3/28/25.
//

#ifndef SIGNAL_H
#define SIGNAL_H

#include "../storage/storage.h"

class Signal
{
  public:
    static void initialize();

    static Storage make(const Storage& i, const Storage& x);

    static Storage lift_impl(const Storage& i);
    static Storage then_impl(const Storage& i);
    static Storage bind_impl(const Storage& i);
};

class Sequence
{
  public:
    static void initialize();

    static Storage make(const Storage& i, const Storage& x);

    static Storage then_impl(const Storage& i);
};

class Contingency
{
  public:
    static void initialize();

    static Storage make(const Storage& i, const Storage& x);

    static Storage bind_impl(const Storage& i, const Storage& x);
};

#endif //SIGNAL_H
