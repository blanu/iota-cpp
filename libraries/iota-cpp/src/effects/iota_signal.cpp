//
// Created by Dr. Brandon Wiley on 3/28/25.
//

#include "iota_signal.h"

#include "effect_type.h"

#include "../storage/mixed_array.h"

Storage Signal::make(Storage value, Storage i, Storage e)
{
  mixed results = {value, i, e};

  return MixedArray::make(results, NounType::SIGNAL);
}

Storage Signal::make(Storage value, Storage i, Storage e, Storage x)
{
  mixed results = {value, i, e, x};

  return MixedArray::make(results, NounType::SIGNAL);
}
