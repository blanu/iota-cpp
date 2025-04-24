//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_REGISTER_H
#define EFFECTS_REGISTER_H

#include <map>
#include <functional>

#include "../storage/storage.h"
#include "../nouns/noun.h"

class EffectsRegister
{
  public:
    static Storage cause_impl(const Storage& i, const Storage& x);
    static Storage then_impl(const Storage& i, const Storage& x);

    EffectsRegister();

    void registerMonadicEffect(Type it, Type io, Type f, Type e, std::function<void(Storage)>);
    void registerDyadicEffect(Type it, Type io, Type f, Type e, Type xt, Type xo, void (*d)(const Storage&, const Storage&));

    void dispatchMonadicEffect(const Storage& i, const Storage& fe);
    void dispatchDyadicEffect(const Storage& i, const Storage& fe, const Storage& x);

    Storage eval(const Storage& s);
    void eval_effect_expression(const Storage& s);

  private:
    std::map<Specialization4, std::function<void(Storage)>> monads;
    std::map<Specialization6, std::function<void(Storage,Storage)>> dyads;
};

#endif //EFFECTS_REGISTER_H
