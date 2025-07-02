//
// Created by Dr. Brandon Wiley on 3/21/25.
//

#ifndef EFFECT_SYMBOLS_H
#define EFFECT_SYMBOLS_H

#include "log/log_symbols.h" // NOLINT
#include "relation/relation_symbols.h" // NOLINT
#include "random/random_symbols.h" // NOLINT
#include "state/state_symbols.h" // NOLINT"

namespace effects::families
{
  static constexpr int log = 1;
  static constexpr int relation = 2;
  static constexpr int random = 3;
  static constexpr int state = 4;
}

#endif //EFFECT_SYMBOLS_H
