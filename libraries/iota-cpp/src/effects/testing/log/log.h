//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#ifndef TESTING_LOG_H
#define TESTING_LOG_H

#include <queue>

#include "../../effects_provider.h"

#include <storage/storage.h>

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

    static inline int timestamp;
    static inline int level;
    static inline int critical;
    static inline int error;
    static inline int warning;
    static inline int info;
    static inline int debug;
    static inline int trace;

    static void initialize(EffectsProvider* effects_provider);

    // Nilad Sinks
    static Storage timestamp_impl();

    // Monads
    static Storage level_impl(const Storage& i);
    static Storage critical_impl(const Storage& i);
    static Storage error_impl(const Storage& i);
    static Storage warning_impl(const Storage& i);
    static Storage info_impl(const Storage& i);
    static Storage debug_impl(const Storage& i);
    static Storage trace_impl(const Storage& i);

    static Storage getEffectState();
    static Storage getLogs();
    static Storage getTimestamps();

  private:
    static int logLevel;
    static std::queue<Storage> logs;
    static ints timestamps;

    static void write(int level, const Storage& i);
};

#endif //TESTING_LOG_H
