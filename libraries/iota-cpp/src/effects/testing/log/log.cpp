//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include "log.h"

#include <chrono>

#include "../../../storage/storage.h"
#include "../../../storage/word_array.h"
#include "../../../storage/mixed_array.h"

#include "../../../nouns/integer.h"

void Log::initialize(EffectsProvider* effects_provider)
{
  logLevel = Levels::warning;
  logs = std::queue<Storage>();
  timestamps = ints();
}

// Nilad Sinks
Storage Log::timestamp_impl()
{
  auto now = std::chrono::system_clock::now();
  int integer = static_cast<int>(std::chrono::system_clock::to_time_t(now));
  timestamps.push_back(integer);

  return WordArray::nil();
}

// Monads
Storage Log::level_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int newLevel = std::get<int>(i.i);
    logLevel = newLevel;
  }

  return WordArray::nil();
}

Storage Log::critical_impl(const Storage& i)
{
  write(Levels::critical, i);

  return WordArray::nil();
}

Storage Log::error_impl(const Storage& i)
{
  write(Levels::error, i);

  return WordArray::nil();
}

Storage Log::warning_impl(const Storage& i)
{
  write(Levels::warning, i);

  return WordArray::nil();
}

Storage Log::info_impl(const Storage& i)
{
  write(Levels::info, i);

  return WordArray::nil();
}

Storage Log::debug_impl(const Storage& i)
{
  write(Levels::debug, i);

  return WordArray::nil();
}

Storage Log::trace_impl(const Storage& i)
{
  write(Levels::trace, i);

  return WordArray::nil();
}

Storage Log::getEffectState()
{
  auto results = mixed();

  results.push_back(getTimestamps());
  results.push_back(Integer::make(logLevel));
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
