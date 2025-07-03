//
// Created by Dr. Brandon Wiley on 5/5/25.
//

#ifndef LENS_H
#define LENS_H

#include "../storage/storage.h"

class Lens
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(int i);
    static Storage make(const ints& i);
    static Storage make(const mixed& i);

    // Monads
    static Storage retrieve_impl(const Storage& i, const Storage& x);
    static Storage mutate_impl(const Storage& i, const Storage& x);
};

#endif //LENS_H
