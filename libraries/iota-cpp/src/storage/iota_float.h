//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef FLOAT_H
#define FLOAT_H

#include "../types.h"

#include "../storage/storage.h"

#include <Connection.h>

class Float
{
  public:
    static constexpr float tolerance = 1e-14f; // for match
    static constexpr float precision = 6; // for format

    static maybe<Storage> from_bytes(bytes x, int o);
    static maybe<bytes> to_bytes(const Storage& i);

    static maybe<Storage> from_conn(Connection& conn, int objectType);
    static void to_conn(Connection& conn, const Storage& i);

    static Storage make(float x, int o = NounType::REAL);
};

#endif //FLOAT_H
