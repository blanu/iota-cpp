//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include "log.h"

#include "../../../storage/storage.h"
#include "../../../storage/mixed_array.h"

void Log::initialize(EffectsRegister* effects_register)
{
  logLevel = Levels::warning;
  logs = std::queue<Storage>();
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

int Log::logLevel;
std::queue<Storage> Log::logs;

void Log::write(const int level, const Storage& i)
{
  if(level <= logLevel)
  {
    logs.push(i);
  }
}
