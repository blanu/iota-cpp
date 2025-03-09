//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef MIXED_ARRAY_H
#define MIXED_ARRAY_H

#include <map>
#include <functional>
#include <vector>
#include <tuple>
#include <string>

#include "storage.h"
#include "Connection.h"

class MixedArray
{
public:
  static maybe<Storage> from_bytes(bytes data, int o);
  static maybe<bytes> to_bytes(const Storage& storage);

  static maybe<Storage> from_conn(const Connection& conn, int objectType);
  static void to_conn(const Connection& conn, const Storage& i);

  static Storage make(mixed x, int o = NounType::LIST);
};

#endif //MIXED_ARRAY_H
