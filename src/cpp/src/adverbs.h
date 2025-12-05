//
// Created by Dr. Brandon Wiley on 3/21/25.
//

#ifndef ADVERBS_H
#define ADVERBS_H

#include <storage/word_array.h>

#include <storage/storage.h>

class MonadicAdverb
{
  public:
    static Storage make(int i);

    static void initialize();
};

class DyadicAdverb
{
  public:
    static Storage make(int i);

    static void initialize();
};

namespace iota
{
  // Monadic Adverbs
  inline Storage converge = WordArray::nil();
  inline Storage each = WordArray::nil();
  inline Storage eachPair = WordArray::nil();
  inline Storage over = WordArray::nil();
  inline Storage scanConverging = WordArray::nil();
  inline Storage scanOver = WordArray::nil();

  // Dyadic Adverbs
  inline Storage each2 = WordArray::nil();
  inline Storage eachLeft = WordArray::nil();
  inline Storage eachRight = WordArray::nil();
  inline Storage overNeutral = WordArray::nil();
  inline Storage iterate = WordArray::nil();
  inline Storage scanIterating = WordArray::nil();
  inline Storage scanOverNeutral = WordArray::nil();
  inline Storage scanWhileOne = WordArray::nil();
  inline Storage whileOne = WordArray::nil();
}

#endif //ADVERBS_H
