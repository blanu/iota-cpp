//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef PRINT_EFFECT_REGISTER_H
#define PRINT_EFFECT_REGISTER_H

#include <storage/storage.h>

class PrintEffectRegister
{
  static void initialize();

  static void handle_impl(Storage i);
};

#endif //PRINT_EFFECT_REGISTER_H
