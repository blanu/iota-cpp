//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef FLOAT_ARRAY_H
#define FLOAT_ARRAY_H

#include "../types.h"

#include "../storage/storage.h"

#include <Connection.h>

class FloatArray
{
public:
  static maybe<Storage> from_bytes(const bytes& data, int o);
  static bytes to_bytes(const Storage& i);

  static maybe<Storage> from_conn(Connection& conn, int objectType);
  static void to_conn(Connection& conn, const Storage& i);

  static Storage make(floats x, int o = NounType::LIST);
};

#endif //FLOAT_ARRAY_H
