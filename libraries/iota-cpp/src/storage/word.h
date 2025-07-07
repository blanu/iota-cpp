//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef WORD_H
#define WORD_H

#include "word.h"
#include "storage.h"

#include "../types.h"

#include <Connection.h>

class Word
{
  public:
    static maybe<Storage> from_bytes(const bytes& data, int o);
    static bytes to_bytes(const Storage& i);

    static maybe<Storage> from_conn(Connection& conn, int objectType);
    static void to_conn(Connection& conn, const Storage& i);

    static Storage make(int x, int o = NounType::INTEGER);
};

#endif //WORD_H
