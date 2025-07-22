//
// Created by Dr. Brandon Wiley on 3/21/25.
//

#ifndef ADVERBS_H
#define ADVERBS_H

#include "symbols.h"

#include <storage/storage.h>

class MonadicAdverb
{
  public:
    static Storage make(int i);
};

class DyadicAdverb
{
  public:
    static Storage make(int i);
};

namespace iota
{
  // Monadic Adverbs
  inline Storage converge = MonadicAdverb::make(MonadicAdverbs::converge);
  inline Storage each = MonadicAdverb::make(MonadicAdverbs::each);
  inline Storage eachPair = MonadicAdverb::make(MonadicAdverbs::eachPair);
  inline Storage over = MonadicAdverb::make(MonadicAdverbs::over);
  inline Storage scanConverging = MonadicAdverb::make(MonadicAdverbs::scanConverging);
  inline Storage scanOver = MonadicAdverb::make(MonadicAdverbs::scanOver);

  // Dyadic Adverbs
  inline Storage each2 = DyadicAdverb::make(DyadicAdverbs::each2);
  inline Storage eachLeft = DyadicAdverb::make(DyadicAdverbs::eachLeft);
  inline Storage eachRight = DyadicAdverb::make(DyadicAdverbs::eachRight);
  inline Storage overNeutral = DyadicAdverb::make(DyadicAdverbs::overNeutral);
  inline Storage iterate = DyadicAdverb::make(DyadicAdverbs::iterate);
  inline Storage scanIterating = DyadicAdverb::make(DyadicAdverbs::scanIterating);
  inline Storage scanOverNeutral = DyadicAdverb::make(DyadicAdverbs::scanOverNeutral);
  inline Storage scanWhileOne = DyadicAdverb::make(DyadicAdverbs::scanWhileOne);
  inline Storage whileOne = DyadicAdverb::make(DyadicAdverbs::whileOne);
}

#endif //ADVERBS_H
