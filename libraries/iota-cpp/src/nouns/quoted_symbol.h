//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef QUOTED_SYMBOL_H
#define QUOTED_SYMBOL_H

#include "../Connection.h"

#include "../storage/storage.h"

class QuotedSymbol
{
  public:
    static void initialize();

    static Storage make(const ints &i);
    static Storage undefined();

    // Monads
    static Storage format_impl(const Storage& i);
    static Storage undefined_impl(const Storage& i);
};

#endif //QUOTED_SYMBOL_H
