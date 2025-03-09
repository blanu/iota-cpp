#ifndef NOUN_H_
#define NOUN_H_

#include <map>
#include <functional>
#include <vector>
#include <tuple>

#include "../storage/storage.h"
#include "../Connection.h"

using Type = int;
using Specialization3 = std::tuple<Type, Type, Type>;
using Specialization5 = std::tuple<Type, Type, Type, Type, Type>;
using Monad = std::function<Storage(Storage)>;
using Dyad = std::function<Storage(Storage,Storage)>;
using Triad = std::function<Storage(Storage,Storage,Storage)>;
using MonadicAdverb = std::function<Storage(Storage,Storage)>;
using DyadicAdverb = std::function<Storage(Storage,Storage,Storage)>;

class Noun
{
  public:
    static constexpr int maximumConvergeIterations = 1000;

    static void initialize();

    static Storage dispatchMonad(const Storage& i, const Storage& f);
    static Storage dispatchDyad(const Storage& i, const Storage& f, const Storage& x);
    static Storage dispatchTriad(const Storage& i, const Storage& f, const Storage& x, const Storage& y);
    static Storage dispatchMonadicAdverb(const Storage& i, const Storage& f, const Storage& g);
    static Storage dispatchDyadicAdverb(const Storage& i, const Storage& f, const Storage& g, const Storage& x);

    static void registerMonad(Type it, Type io, Type f, Storage (*m)(const Storage&));
    static void registerDyad(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&));
    static void registerTriad(Type it, Type io, Type f, Type xt, Type xo, Storage (*t)(const Storage&, const Storage&, const Storage&));
    static void registerMonadicAdverb(Type it, Type io, Type f, Storage (*a)(const Storage&, const Storage&));
    static void registerDyadicAdverb(Type it, Type io, Type f, Type xt, Type xo, Storage (*a)(const Storage&, const Storage&, const Storage&));

    // Monads
    static Storage enclose_impl(const Storage& i);
    static Storage shape_scalar(const Storage& i);

    // Extension Monads
    static Storage evaluate_expression(const Storage& e);
    static Storage mix(const Storage& i);
    static Storage simplify(const Storage& i);

    static Storage true0();
    static Storage true1(const Storage& i);
    static Storage true2(const Storage& i, const Storage& x);
    static Storage false0();
    static Storage false1(const Storage& i);
    static Storage false2(const Storage& i, const Storage& x);
    static Storage identity1(const Storage& i);

    // Extension Dyads
    static Storage join_scalar(const Storage& i, const Storage& x);
    static Storage prepend(const Storage& i, const Storage& x);
    static Storage append(const Storage& i, const Storage& x);
    static Storage join_mixed(const Storage& i, const Storage& x);
    static Storage join_mix_left(const Storage& i, const Storage& x);
    static Storage join_mix_right(const Storage& i, const Storage& x);
    static Storage join_mix_enclose(const Storage& i, const Storage& x);
    static Storage join_enclose_mix(const Storage& i, const Storage& x);
    static Storage identity2(const Storage& i, const Storage& x);
    static Storage enclose2(const Storage& i, const Storage& x);

    // Monadic Adverbs
    static Storage converge_impl(const Storage& i, const Storage& f);
    static Storage scanConverging_impl(const Storage& i, const Storage& f);

    // Dyadic Adverbs
    // each2
    static Storage each2_impl(const Storage& i, const Storage& f, const Storage& x);
    static Storage eachLeft_impl(const Storage& i, const Storage& f, const Storage& x);
    static Storage eachRight_impl(const Storage& i, const Storage& f, const Storage& x);
    static Storage overNeutral_impl(const Storage& i, const Storage& f, const Storage& x);
    static Storage iterate_integer(const Storage& i, const Storage& f, const Storage& x);
    static Storage scanIterating_integer(const Storage& i, const Storage& f, const Storage& x);
    static Storage scanOverNeutral_impl(const Storage& i, const Storage& f, const Storage& x);
    static Storage scanWhileOne_impl(const Storage& i, const Storage& f, const Storage& g);
    static Storage whileOne_impl(const Storage& i, const Storage& f, const Storage& g);

    // General serialization
    static maybe<Storage> from_bytes(bytes data);
    static bytes to_bytes(const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn);
    static void to_conn(const Connection& conn, const Storage& x);

    private:
      static std::map<Specialization3, Monad> monads;
      static std::map<Specialization5, Dyad> dyads;
      static std::map<Specialization5, Triad> triads;
      static std::map<Specialization3, MonadicAdverb> monadicAdverbs;
      static std::map<Specialization5, DyadicAdverb> dyadicAdverbs;
};


#endif