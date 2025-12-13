//
// Created by Dr. Brandon Wiley on 12/9/25.
//

#ifndef IOTA_CPP_BINDINGS_H
#define IOTA_CPP_BINDINGS_H
#include "storage/storage.h"

class Bindings
{
  public:
    static inline int bind;
    static inline int resolve;

    static void initialize();

    static Storage empty();
    static Storage make(const mixed& i);
    static Storage make(const Storage& i);

    static Storage bind_impl(const Storage& i, const Storage& x, const Storage& y);
    static Storage resolve_impl(const Storage& i, const Storage& x);
};

#endif //IOTA_CPP_BINDINGS_H