//
// Created by Dr. Brandon Wiley on 3/23/25.
//

#include "adverbs.h"

#include "storage/word.h"

Storage MonadicAdverb::make(const int i)
{
  return Word::make(i, NounType::MONADIC_ADVERB);
}

Storage DyadicAdverb::make(const int i)
{
  return Word::make(i, NounType::DYADIC_ADVERB);
}
