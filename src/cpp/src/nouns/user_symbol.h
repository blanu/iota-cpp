//
// Created by Dr. Brandon Wiley on 12/12/25.
//

#ifndef IOTA_CPP_USER_SYMBOL_H
#define IOTA_CPP_USER_SYMBOL_H
#include <string>

#include "storage/storage.h"

class UserSymbol
{
  public:
    static void initialize();

    static Storage make(const std::string&);
};

#endif //IOTA_CPP_USER_SYMBOL_H