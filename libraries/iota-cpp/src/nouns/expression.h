//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../storage/storage.h"

class Expression
{
  public:
    // Initialize dispatch table
    static void initialize();
    static Storage make(const mixed& e);

    static Storage truth(const Storage& i);
};

#endif //EXPRESSION_H
