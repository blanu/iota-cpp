//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include "log.h"

#include <chrono>

#include "../../../storage/storage.h"
#include "../../../storage/word_array.h"
#include "../../../storage/mixed_array.h"

#include "../../../nouns/integer.h"

void Log::initialize(EffectsRegister* effects_register)
{
  logLevel = Levels::warning;
  logs = std::queue<Storage>();
  timestamps = ints();
}

// Nilad Sinks
void Log::timestamp_impl()
{
  auto now = std::chrono::system_clock::now();
  int integer = static_cast<int>(std::chrono::system_clock::to_time_t(now));
  timestamps.push_back(integer);
}

// Monads
void Log::level_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int newLevel = std::get<int>(i.i);
    logLevel = newLevel;
  }
}

void Log::critical_impl(const Storage& i)
{
  write(Levels::critical, i);
}

void Log::error_impl(const Storage& i)
{
  write(Levels::error, i);
}

void Log::warning_impl(const Storage& i)
{
  write(Levels::warning, i);
}

void Log::info_impl(const Storage& i)
{
  write(Levels::info, i);
}

void Log::debug_impl(const Storage& i)
{
  write(Levels::debug, i);
}

void Log::trace_impl(const Storage& i)
{
  write(Levels::trace, i);
}

Storage Log::getEffectState()
{
  auto results = mixed();

  results.push_back(Integer::make(logLevel));
  results.push_back(getTimestamps());
  results.push_back(getLogs());

  return MixedArray::make(results);
}

Storage Log::getLogs()
{
  auto results = mixed();
  std::queue<Storage> temp = logs; // This makes a copy.
  results.reserve(temp.size());

  while (!temp.empty())
  {
    results.push_back(temp.front());
    temp.pop();
  }

  return MixedArray::make(results);
}

Storage Log::getTimestamps()
{
  auto results = ints();
  results.reserve(timestamps.size());

  for(int timestamp : timestamps)
  {
    results.push_back(timestamp);
  }

  return WordArray::make(results);
}

int Log::logLevel;
std::queue<Storage> Log::logs;
ints Log::timestamps;

void Log::write(const int level, const Storage& i)
{
  if(level <= logLevel)
  {
    logs.push(i);
  }
}
