//
// Created by Dr. Brandon Wiley on 5/27/25.
//

#include "error.h"

#include <storage/storage.h>
#include <storage/word.h>
#include <storage/mixed_array.h>

#include <nouns/integer.h>
#include <nouns/iota_string.h>

Storage Error::make(const int i)
{
  return Word::make(i, NounType::ERROR);
}

Storage Error::make(int type, const char* file, int line, const char* func)
{
  mixed ms = {Integer::make(type), IotaString::makeCString(file), Integer::make(line), IotaString::makeCString(func)};
  return MixedArray::make(ms, NounType::ERROR);
}
