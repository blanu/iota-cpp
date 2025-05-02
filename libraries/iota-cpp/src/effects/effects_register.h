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
    static Storage because_impl(const Storage& i, const Storage& x);
    static Storage cause_impl(const Storage& i, const Storage& x);
    static Storage then_impl(const Storage& i, const Storage& x);

    static Storage bind_monad(const Storage& i, const Storage& x);
    static Storage bind_expression(const Storage& i, const Storage& x);

    EffectsRegister();

    void registerNiladicSinkEffect(Type f, Type e, const std::function<void()>&);
    void registerMonadicSinkEffect(Type it, Type io, Type f, Type e, const std::function<void(Storage)>&);
    void registerDyadicSinkEffect(Type it, Type io, Type f, Type e, Type xt, Type xo, const std::function<void(const Storage&, const Storage&)>&);

    void registerNiladicSourceEffect(Type f, Type e, const std::function<Storage()>&);
    void registerMonadicSourceEffect(Type it, Type io, Type f, Type e, const std::function<Storage (const Storage&)>&);
    void registerDyadicSourceEffect(Type it, Type io, Type f, Type e, Type xt, Type xo, const std::function<Storage (const Storage&, const Storage&)>&);

    void dispatchNiladicSinkEffect(const Storage& fe);
    void dispatchMonadicSinkEffect(const Storage& i, const Storage& fe);
    void dispatchDyadicSinkEffect(const Storage& i, const Storage& fe, const Storage& x);

    Storage dispatchNiladicSourceEffect(const Storage& fe);
    Storage dispatchMonadicSourceEffect(const Storage& i, const Storage& fe);
    Storage dispatchDyadicSourceEffect(const Storage& i, const Storage& fe, const Storage& x);

    Storage eval(const Storage& s);
    void eval_effect_expression(const Storage& s);

  private:
    std::map<Specialization2, std::function<void()>> niladSinks;
    std::map<Specialization4, std::function<void(Storage)>> monadSinks;
    std::map<Specialization6, std::function<void(Storage,Storage)>> dyadSinks;

    std::map<Specialization2, std::function<Storage()>> niladSources;
    std::map<Specialization4, std::function<Storage(Storage)>> monadSources;
    std::map<Specialization6, std::function<Storage(Storage,Storage)>> dyadSources;
};

#endif //EFFECTS_REGISTER_H
