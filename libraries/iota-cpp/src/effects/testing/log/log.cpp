//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include "log.h"

#include "../../effect_symbols.h"

#include "../../../storage/storage.h"
#include "../../../storage/mixed_array.h"

void Log::initialize(EffectsRegister* effects_register)
{
}

// Monads
// This moves i.i.
void Log::info_impl(const Storage& i)
{
  logs.push(i);
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

std::queue<Storage> Log::logs;
