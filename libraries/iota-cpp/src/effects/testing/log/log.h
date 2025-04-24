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
    class Levels
    {
      public:
        static constexpr int critical = 0;
        static constexpr int error = 1;
        static constexpr int warning = 2;
        static constexpr int info = 3;
        static constexpr int debug = 4;
        static constexpr int trace = 5;

    };

    static void initialize(EffectsRegister* effects_register);

    // Monads
    static void level_impl(const Storage& i);
    static void critical_impl(const Storage& i);
    static void error_impl(const Storage& i);
    static void warning_impl(const Storage& i);
    static void info_impl(const Storage& i);
    static void debug_impl(const Storage& i);
    static void trace_impl(const Storage& i);

    static Storage getLogs();

  private:
    static int logLevel;
    static std::queue<Storage> logs;

    static void write(int level, const Storage& i);
};

#endif //TESTING_LOG_H
