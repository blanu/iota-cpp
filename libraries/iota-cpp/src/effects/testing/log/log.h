//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#ifndef TESTING_LOG_H
#define TESTING_LOG_H

#include <queue>

#include "../../effects_register.h"

#include "../../../storage/storage.h"

class Log
{
  public:
    static void initialize(EffectsRegister* effects_register);

    // Monads
    static void info_impl(const Storage& i);

    static Storage getLogs();

  private:
    static std::queue<Storage> logs;
};

#endif //TESTING_LOG_H
