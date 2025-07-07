//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef INTEGER_ARRAY_H
#define INTEGER_ARRAY_H

#include <vector>
#include <optional>

#include "word_array.h"
#include "storage.h"

#include "../types.h"

#include <Connection.h>

class WordArray
{
public:
  static Storage nil();
  static Storage nil1(const Storage& i);
  static Storage nil2(const Storage& i, const Storage& x);

  static maybe<Storage> from_bytes(const bytes& data, int o);
  static bytes to_bytes(const Storage &storage);

  static maybe<Storage> from_conn(Connection& conn, int objectType);
  static void to_conn(Connection& conn, const Storage& i);

  static Storage make(ints x, int o = NounType::LIST);
};

#endif //INTEGER_ARRAY_H
