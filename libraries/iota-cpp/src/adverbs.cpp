//
// Created by Dr. Brandon Wiley on 3/23/25.
//

#include "adverbs.h"

#include <nouns/symbol.h>
#include "storage/word.h"

Storage MonadicAdverb::make(const int i)
{
  return Word::make(i, NounType::MONADIC_ADVERB);
}

void MonadicAdverb::initialize()
{
  INTERN_VERB(iota, MonadicAdverb, converge);
  INTERN_VERB(iota, MonadicAdverb, each);
  INTERN_VERB(iota, MonadicAdverb, eachPair);
  INTERN_VERB(iota, MonadicAdverb, over);
  INTERN_VERB(iota, MonadicAdverb, scanConverging);
  INTERN_VERB(iota, MonadicAdverb, scanOver);
}


Storage DyadicAdverb::make(const int i)
{
  return Word::make(i, NounType::DYADIC_ADVERB);
}

void DyadicAdverb::initialize()
{
  INTERN_VERB(iota, MonadicAdverb, each2);
  INTERN_VERB(iota, MonadicAdverb, eachLeft);
  INTERN_VERB(iota, MonadicAdverb, eachRight);
  INTERN_VERB(iota, MonadicAdverb, overNeutral);
  INTERN_VERB(iota, MonadicAdverb, iterate);
  INTERN_VERB(iota, MonadicAdverb, scanIterating);
  INTERN_VERB(iota, MonadicAdverb, scanOverNeutral);
  INTERN_VERB(iota, MonadicAdverb, scanWhileOne);
  INTERN_VERB(iota, MonadicAdverb, whileOne);
}