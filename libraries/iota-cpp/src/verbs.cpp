//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "verbs.h"

#include "nouns/noun.h"
#include "storage/word.h"

Storage Monad::make(int i)
{
  return Word::make(i, NounType::BUILTIN_MONAD);
}

Storage Dyad::make(int i)
{
  return Word::make(i, NounType::BUILTIN_DYAD);
}