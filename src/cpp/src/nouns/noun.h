#ifndef NOUN_H_
#define NOUN_H_

#include <map>
#include <functional>
#include <vector>
#include <tuple>

#include <storage/storage.h>

#include <Connection.h>
#include <logger.h>

// Import noun.h before storage/mixed_array.h to get advanced noun serialization override
#define NOUN_TO_BYTES(i) Noun::to_bytes(i)
#define NOUN_FROM_CONN(conn) Noun::from_conn(conn)
#define NOUN_TO_CONN(conn, i, logger) Noun::to_conn(conn, i, logger)

using Type = int;
using Specialization1 = std::tuple<Type>;
using Specialization2 = std::tuple<Type, Type>;
using Specialization3 = std::tuple<Type, Type, Type>;
using Specialization5 = std::tuple<Type, Type, Type, Type, Type>;
using Specialization7 = std::tuple<Type, Type, Type, Type, Type, Type, Type>;

using NiladicSourceFunction = std::function<Storage()>;
using MonadicSourceFunction = std::function<Storage(Storage)>;
using DyadicSourceFunction = std::function<Storage(Storage,Storage)>;
using TriadicSourceFunction = std::function<Storage(Storage,Storage,Storage)>;

using NiladicSinkFunction = std::function<void()>;
using MonadicSinkFunction = std::function<void(Storage)>;
using DyadicSinkFunction = std::function<void(Storage,Storage)>;
using TriadicSinkFunction = std::function<void(Storage,Storage,Storage)>;

using MonadicAdverbFunction = std::function<Storage(Storage,Storage)>;
using DyadicAdverbFunction = std::function<Storage(Storage,Storage,Storage)>;

using ConjunctionFunction = std::function<Storage(Storage,Storage)>;

class Noun
{
  public:
    static constexpr int maximumConvergeIterations = 1000;

    static void initialize();

    static Storage dispatchNilad(const Storage& f);
    static Storage dispatchMonad(const Storage& i, const Storage& f);
    static Storage dispatchDyad(const Storage& i, const Storage& f, const Storage& x);
    static Storage dispatchTriad(const Storage& i, const Storage& f, const Storage& x, const Storage& y);
    static Storage dispatchMonadicAdverb(const Storage& i, const Storage& f, const Storage& g);
    static Storage dispatchDyadicAdverb(const Storage& i, const Storage& f, const Storage& g, const Storage& x);
    static Storage dispatchNiladicEffect(const Storage& f);
    static Storage dispatchMonadicEffect(const Storage& i, const Storage& f);
    static Storage dispatchDyadicEffect(const Storage& i, const Storage& f, const Storage& x);
    static Storage dispatchTriadicEffect(const Storage& i, const Storage& f, const Storage& x, const Storage& y);
    static Storage dispatchConjunction(const Storage& i, const Storage& f, const Storage& x);

    static void registerNilad(Type f, Storage (*m)());
    static void registerMonad(Type it, Type io, Type f, Storage (*m)(const Storage&));
    static void registerDyad(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&));
    static void registerTriad(Type it, Type io, Type f, Type xt, Type xo, Type yt, Type yo, Storage (*t)(const Storage&, const Storage&, const Storage&));
    static void registerMonadicAdverb(Type it, Type io, Type f, Storage (*a)(const Storage&, const Storage&));
    static void registerDyadicAdverb(Type it, Type io, Type f, Type xt, Type xo, Storage (*a)(const Storage&, const Storage&, const Storage&));
    static void registerConjunction(Type f, Storage (*c)(const Storage&, const Storage&));

    static void printDyad(const Storage &i, const Storage& f, const Storage& x);

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
    static maybe<Storage> from_conn(Connection& conn, Logger* logger = nullptr);
    static void to_conn(Connection& conn, const Storage& x);

    static std::map<Specialization5, DyadicSourceFunction> dyadSources;

    static void setLogger(Logger *newLogger);

    private:
      static Logger *logger;

      static std::map<Specialization1, NiladicSourceFunction> niladSources;
      static std::map<Specialization3, MonadicSourceFunction> monadSources;
      static std::map<Specialization7, TriadicSourceFunction> triadSources;

      static std::map<Specialization2, NiladicSourceFunction> niladSinks;
      static std::map<Specialization3, MonadicSourceFunction> monadSinks;
      static std::map<Specialization5, DyadicSourceFunction> dyadSinks;
      static std::map<Specialization7, TriadicSourceFunction> triadSinks;

      static std::map<Specialization3, MonadicAdverbFunction> monadicAdverbs;
      static std::map<Specialization5, DyadicAdverbFunction> dyadicAdverbs;

      static std::map<Specialization1, ConjunctionFunction> conjunctions;
};


#endif