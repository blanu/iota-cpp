//
// Created by Dr. Brandon Wiley on 12/1/25.
//

#ifndef IOTA_CPP_STATE_H
#define IOTA_CPP_STATE_H

#include "../effects_provider.h"

#include <storage/storage.h>

#include "storage/word_array.h"

namespace iota
{
  inline Storage get = WordArray::nil();
  inline Storage put = WordArray::nil();
  inline Storage modify = WordArray::nil();

  inline Storage pull = WordArray::nil();
  inline Storage push = WordArray::nil();
  inline Storage replace = WordArray::nil();
  inline Storage transform = WordArray::nil();
}

class State
{
  public:
    inline static int get;
    inline static int put;
    inline static int modify;

    static inline int pull;
    static inline int push;
    static inline int replace;
    static inline int transform;

    static void initialize(EffectsProvider* effects_register);

    // Monads
    static Storage pull_impl(const Storage& i);

    // Dyads
    static Storage push_impl(const Storage& i, const Storage& x);
    static Storage replace_impl(const Storage& i, const Storage& f);

    // Triads
    static Storage transform_impl(const Storage& i, const Storage& f, const Storage& y);
};

#endif //IOTA_CPP_STATE_H