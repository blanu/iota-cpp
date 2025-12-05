//
// Created by Dr. Brandon Wiley on 7/3/25.
//

#ifndef CONJUNCTIONS_H
#define CONJUNCTIONS_H

#include <storage/storage.h>

class Conjunction
{
  public:
    static Storage make(int i);
};

class Conjunctions
{
  public:
    static constexpr int then = 0;

    static void initialize();

    static Storage then_impl(const Storage& i, const Storage& x);
};

namespace iota
{
  inline Storage then = Conjunction::make(Conjunctions::then);
}

#endif //CONJUNCTIONS_H
