//
// Created by Dr. Brandon Wiley on 12/12/25.
//

#ifndef IOTA_CPP_SYMBOL_DEFINITION_H
#define IOTA_CPP_SYMBOL_DEFINITION_H

#include <string>

#include "types.h"
#include "storage/storage.h"

class SymbolDefinition
{
  public:
    static void initialize();

    static Storage make(const std::string&);

    static std::string toString(const Storage&);
};

#endif //IOTA_CPP_SYMBOL_DEFINITION_H