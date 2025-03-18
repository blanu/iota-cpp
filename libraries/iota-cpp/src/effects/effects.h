//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_H
#define EFFECTS_H

#include <queue>
#include <unordered_map>

#include "../storage/storage.h"

#include "../nouns/noun.h"

class Effects
{
  public:
    static void initialize();

    static void registerMonadicEffect(Type it, Type io, Type f, Storage (*m)(const Storage&));
    static void registerDyadicEffect(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&));

    static Storage dispatchMonadicEffect(const Storage& i, const Storage& f);
    static Storage dispatchDyadicEffect(const Storage& i, const Storage& f, const Storage& x);

    static void processEffects();

  private:
    static std::map<Specialization3, Monad> monads;
    static std::map<Specialization5, Dyad> dyads;
};

#endif //EFFECTS_H
