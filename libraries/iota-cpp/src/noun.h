#ifndef NOUN_H_
#define NOUN_H_

#include <map>
#include <functional>
#include <vector>
#include <tuple>
#include <string>

#include "storage.h"
#include "Connection.h"

// Monads
Storage atom(const Storage& i);
Storage ichar(const Storage& i);
Storage enclose(const Storage& i);
Storage enumerate(const Storage& i);
Storage expand(const Storage& i);
Storage first(const Storage& i);
Storage floor(const Storage& i);
Storage format(const Storage& i);
Storage gradeDown(const Storage& i);
Storage gradeUp(const Storage& i);
Storage group(const Storage& i);
Storage negate(const Storage& i);
Storage reciprocal(const Storage& i);
Storage reverse(const Storage& i);
Storage shape(const Storage& i);
Storage size(const Storage& i);
Storage transpose(const Storage& i);
Storage unique(const Storage& i);
Storage inot(const Storage& i);
Storage undefined(const Storage& i);

// Extension Monads

Storage evaluate(const Storage& i);
Storage erase(const Storage& i);
Storage truth(const Storage& i);

// Dyads
Storage amend(const Storage& i, const Storage& x);
Storage cut(const Storage& i, const Storage& x);
Storage divide(const Storage& i, const Storage& x);
Storage drop(const Storage& i, const Storage& x);
Storage equal(const Storage& i, const Storage& x);
Storage find(const Storage& i, const Storage& x);
Storage form(const Storage& i, const Storage& x);
Storage format2(const Storage& i, const Storage& x);
Storage index(const Storage& i, const Storage& x);
Storage join(const Storage& i, const Storage& x);
Storage less(const Storage& i, const Storage& x);
Storage match(const Storage& i, const Storage& x);
Storage max(const Storage& i, const Storage& x);
Storage min(const Storage& i, const Storage& x);
Storage minus(const Storage& i, const Storage& x);
Storage more(const Storage& i, const Storage& x);
Storage plus(const Storage& i, const Storage& x);
Storage power(const Storage& i, const Storage& x);
Storage remainder(const Storage& i, const Storage& x);
Storage reshape(const Storage& i, const Storage& x);
Storage rotate(const Storage& i, const Storage& x);
Storage split(const Storage& i, const Storage& x);
Storage take(const Storage& i, const Storage& x);
Storage times(const Storage& i, const Storage& x);

// Monadic Adverbs
Storage converge(const Storage& i, const Storage& f);
Storage each(const Storage& i, const Storage& f);
Storage eachPair(const Storage& i, const Storage& f);
Storage over(const Storage& i, const Storage& f);
Storage scanConverging(const Storage& i, const Storage& f);
Storage scanOver(const Storage& i, const Storage& f);

// Dyadic Adverbs
Storage each2(const Storage& i, const Storage& f, const Storage& x);
Storage eachLeft(const Storage& i, const Storage& f, const Storage& x);
Storage eachRight(const Storage& i, const Storage& f, const Storage& x);
Storage overNeutral(const Storage& i, const Storage& f, const Storage& x);
Storage iterate(const Storage& i, const Storage& f, const Storage& x);
Storage scanIterating(const Storage& i, const Storage& f, const Storage& x);
Storage scanOverNeutral(const Storage& i, const Storage& f, const Storage& x);
Storage scanWhileOne(const Storage& i, const Storage& f, const Storage& x);
Storage whileOne(const Storage& i, const Storage& f, const Storage& x);

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

class Integer
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(int i);
    static Storage zero();
    static Storage one();

    // Monads
    static Storage char_impl(const Storage& i);    
    static Storage enclose_impl(const Storage& i);    
    static Storage enumerate_impl(const Storage& i);
    static Storage expand_impl(const Storage& i);    
    static Storage floor_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage negate_impl(const Storage& i);    
    static Storage not_impl(const Storage& i);
    static Storage reciprocal_impl(const Storage& i);    
    static Storage reverse_impl(const Storage& i);    
    static Storage size_impl(const Storage& i);    

    // Dyads
    static Storage cut_integers(const Storage& i, const Storage& x);
    static Storage cut_reals(const Storage& i, const Storage& x);
    static Storage cut_mixed(const Storage& i, const Storage& x);
    static Storage divide_integer(const Storage& i, const Storage& x);
    static Storage divide_real(const Storage& i, const Storage& x);
    static Storage divide_integers(const Storage& i, const Storage& x);
    static Storage divide_reals(const Storage& i, const Storage& x);
    static Storage divide_mixed(const Storage& i, const Storage& x);
    static Storage equal_impl(const Storage& i, const Storage& x);
    static Storage format2_impl(const Storage& i, const Storage& x);
    static Storage integerDivide_impl(const Storage& i, const Storage& x);
    static Storage join_integer(const Storage& i, const Storage& x);
    static Storage prepend_to_integers(const Storage& i, const Storage& x);
    static Storage less_integer(const Storage& i, const Storage& x);
    static Storage less_real(const Storage& i, const Storage& x);
    static Storage less_list(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage max_integer(const Storage& i, const Storage& x);
    static Storage max_real(const Storage& i, const Storage& x);
    static Storage max_list(const Storage& i, const Storage& x);
    static Storage min_integer(const Storage& i, const Storage& x);
    static Storage min_real(const Storage& i, const Storage& x);
    static Storage min_list(const Storage& i, const Storage& x);
    static Storage minus_integer(const Storage& i, const Storage& x);
    static Storage minus_real(const Storage& i, const Storage& x);
    static Storage minus_list(const Storage& i, const Storage& x);
    static Storage more_integer(const Storage& i, const Storage& x);
    static Storage more_real(const Storage& i, const Storage& x);
    static Storage more_list(const Storage& i, const Storage& x);
    static Storage plus_integer(const Storage& i, const Storage& x);
    static Storage plus_real(const Storage& i, const Storage& x);
    static Storage plus_list(const Storage& i, const Storage& x);
    static Storage power_integer(const Storage& i, const Storage& x);
    static Storage power_real(const Storage& i, const Storage& x);
    static Storage power_list(const Storage& i, const Storage& x);
    static Storage remainder_integer(const Storage& i, const Storage& x);
    static Storage remainder_integers(const Storage& i, const Storage& x);
    static Storage remainder_mixed(const Storage& i, const Storage& x);
    static Storage reshape_integer(const Storage& i, const Storage& x);
    static Storage reshape_integers(const Storage& i, const Storage& x);
    static Storage reshape_mixed(const Storage& i, const Storage& x);
    static Storage times_integer(const Storage& i, const Storage& x);
    static Storage times_real(const Storage& i, const Storage& x);
    static Storage times_list(const Storage& i, const Storage& x);

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

class Real
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(float i);
    static Storage zero();
    static Storage one();

    static Storage enclose_impl(const Storage& i);    
    static Storage floor_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage negate_impl(const Storage& i);    
    static Storage not_impl(const Storage& i);
    static Storage reciprocal_impl(const Storage& i);    
    static Storage reverse_impl(const Storage& i);    
    static Storage size_impl(const Storage& i);    

    // Dyads
    static Storage divide_integer(const Storage& i, const Storage& x);
    static Storage divide_real(const Storage& i, const Storage& x);
    static Storage divide_integers(const Storage& i, const Storage& x);
    static Storage divide_reals(const Storage& i, const Storage& x);
    static Storage divide_mixed(const Storage& i, const Storage& x);
    static Storage format2_impl(const Storage& i, const Storage& x);
    static Storage join_real(const Storage& i, const Storage& x);
    static Storage prepend_to_reals(const Storage& i, const Storage& x);
    static Storage less_integer(const Storage& i, const Storage& x);
    static Storage less_real(const Storage& i, const Storage& x);
    static Storage less_list(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage max_integer(const Storage& i, const Storage& x);
    static Storage max_real(const Storage& i, const Storage& x);
    static Storage max_list(const Storage& i, const Storage& x);
    static Storage min_integer(const Storage& i, const Storage& x);
    static Storage min_real(const Storage& i, const Storage& x);
    static Storage min_list(const Storage& i, const Storage& x);
    static Storage minus_integer(const Storage& i, const Storage& x);
    static Storage minus_real(const Storage& i, const Storage& x);
    static Storage minus_list(const Storage& i, const Storage& x);
    static Storage more_integer(const Storage& i, const Storage& x);
    static Storage more_real(const Storage& i, const Storage& x);
    static Storage more_list(const Storage& i, const Storage& x);
    static Storage plus_integer(const Storage& i, const Storage& x);
    static Storage plus_real(const Storage& i, const Storage& x);
    static Storage plus_list(const Storage& i, const Storage& x);
    static Storage power_integer(const Storage& i, const Storage& x);
    static Storage power_real(const Storage& i, const Storage& x);
    static Storage power_list(const Storage& i, const Storage& x);
    static Storage reshape_integer(const Storage& i, const Storage& x);
    static Storage reshape_integers(const Storage& i, const Storage& x);
    static Storage reshape_mixed(const Storage& i, const Storage& x);
    static Storage times_integer(const Storage& i, const Storage& x);
    static Storage times_real(const Storage& i, const Storage& x);
    static Storage times_list(const Storage& i, const Storage& x);

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

class List
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Monads
    static Storage atom_impl(const Storage& i);    
    static Storage char_impl(const Storage& i);    
    static Storage enclose_impl(const Storage& i);    
    static Storage expand_impl(const Storage& i);    
    static Storage first_impl(const Storage& i);
    static Storage floor_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage gradeDown_impl(const Storage& i);
    static Storage gradeUp_impl(const Storage& i);
    static Storage group_impl(const Storage& i);
    static Storage negate_impl(const Storage& i);    
    static Storage not_impl(const Storage& i);
    static Storage reciprocal_impl(const Storage& i);    
    static Storage reverse_impl(const Storage& i);    
    static Storage shape_impl(const Storage& i);    
    static Storage size_impl(const Storage& i);    
    static Storage transpose_impl(const Storage& i);    
    static Storage unique_impl(const Storage& i);    

    // Dyads
    // static Storage amend_integers_integer(const Storage& i, const Storage& x);
    // static Storage amend_integers_mixed(const Storage& i, const Storage& x);
    // static Storage amend_floats_integer(const Storage& i, const Storage& x);
    // static Storage amend_floats_mixed(const Storage& i, const Storage& x);
    // static Storage amend_mixed_integer(const Storage& i, const Storage& x);
    // static Storage amend_mixed_mixed(const Storage& i, const Storage& x);

    static Storage cut_integer(const Storage& i, const Storage& x);
    static Storage cut_integers(const Storage& i, const Storage& x);

    static Storage divide_integer(const Storage& i, const Storage& x);
    static Storage divide_real(const Storage& i, const Storage& x);
    static Storage divide_integers(const Storage& i, const Storage& x);
    static Storage divide_reals(const Storage& i, const Storage& x);
    static Storage divide_mixed(const Storage& i, const Storage& x);

    static Storage drop_impl(const Storage& i, const Storage& x);
    static Storage equal_impl(const Storage& i, const Storage& x);

    static Storage find_integers_integer(const Storage& i, const Storage& x);
    static Storage find_integers_real(const Storage& i, const Storage& x);
    static Storage find_reals_integer(const Storage& i, const Storage& x);
    static Storage find_reals_real(const Storage& i, const Storage& x);
    static Storage find_mixed(const Storage& i, const Storage& x);

    static Storage format2_impl(const Storage& i, const Storage& x);
    static Storage index_impl(const Storage& i, const Storage& x);

    // Join
    static Storage append_integer(const Storage& i, const Storage& x);
    static Storage append_real(const Storage& i, const Storage& x);
    static Storage prepend_integer(const Storage& i, const Storage& x);
    static Storage prepend_real(const Storage& i, const Storage& x);
    static Storage join_integers(const Storage& i, const Storage& x);
    static Storage join_integers_reals(const Storage& i, const Storage& x);
    static Storage join_reals(const Storage& i, const Storage& x);
    static Storage join_reals_integers(const Storage& i, const Storage& x);
    static Storage join_mixed(const Storage& i, const Storage& x);

    static Storage less_integer(const Storage& i, const Storage& x);
    static Storage less_real(const Storage& i, const Storage& x);
    static Storage less_integers(const Storage& i, const Storage& x);
    static Storage less_reals(const Storage& i, const Storage& x);
    static Storage less_mixed(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage max_integer(const Storage& i, const Storage& x);
    static Storage max_real(const Storage& i, const Storage& x);
    static Storage max_integers(const Storage& i, const Storage& x);
    static Storage max_reals(const Storage& i, const Storage& x);
    static Storage max_mixed(const Storage& i, const Storage& x);
    static Storage min_integer(const Storage& i, const Storage& x);
    static Storage min_real(const Storage& i, const Storage& x);
    static Storage min_integers(const Storage& i, const Storage& x);
    static Storage min_reals(const Storage& i, const Storage& x);
    static Storage min_mixed(const Storage& i, const Storage& x);
    static Storage minus_integer(const Storage& i, const Storage& x);
    static Storage minus_real(const Storage& i, const Storage& x);
    static Storage minus_integers(const Storage& i, const Storage& x);
    static Storage minus_reals(const Storage& i, const Storage& x);
    static Storage minus_mixed(const Storage& i, const Storage& x);
    static Storage more_integer(const Storage& i, const Storage& x);
    static Storage more_real(const Storage& i, const Storage& x);
    static Storage more_integers(const Storage& i, const Storage& x);
    static Storage more_reals(const Storage& i, const Storage& x);
    static Storage more_mixed(const Storage& i, const Storage& x);
    static Storage plus_integer(const Storage& i, const Storage& x);
    static Storage plus_real(const Storage& i, const Storage& x);
    static Storage plus_integers(const Storage& i, const Storage& x);
    static Storage plus_reals(const Storage& i, const Storage& x);
    static Storage plus_mixed(const Storage& i, const Storage& x);
    static Storage power_integer(const Storage& i, const Storage& x);
    static Storage power_real(const Storage& i, const Storage& x);
    static Storage power_integers(const Storage& i, const Storage& x);
    static Storage power_reals(const Storage& i, const Storage& x);
    static Storage power_mixed(const Storage& i, const Storage& x);
    static Storage remainder_integer(const Storage& i, const Storage& x);
    static Storage remainder_integers(const Storage& i, const Storage& x);
    static Storage remainder_mixed(const Storage& i, const Storage& x);
    static Storage reshape_integer(const Storage& i, const Storage& x);
    static Storage reshape_integers(const Storage& i, const Storage& x);
    static Storage reshape_mixed(const Storage& i, const Storage& x);
    static Storage rotate_integer(const Storage& i, const Storage& x);
    static Storage split_integer(const Storage& i, const Storage& x);
    static Storage split_integers(const Storage& i, const Storage& x);
    static Storage take_integer(const Storage& i, const Storage& x);
    static Storage times_integer(const Storage& i, const Storage& x);
    static Storage times_real(const Storage& i, const Storage& x);
    static Storage times_integers(const Storage& i, const Storage& x);
    static Storage times_reals(const Storage& i, const Storage& x);
    static Storage times_mixed(const Storage& i, const Storage& x);

    // Monadic Adverbs
    static Storage each_integers(const Storage& i, const Storage& f);
    static Storage each_reals(const Storage& i, const Storage& f);
    static Storage each_mixed(const Storage& i, const Storage& f);
    static Storage eachPair_integers(const Storage& i, const Storage& f);
    static Storage eachPair_reals(const Storage& i, const Storage& f);
    static Storage eachPair_mixed(const Storage& i, const Storage& f);
    static Storage over_integers(const Storage& i, const Storage& f);
    static Storage over_reals(const Storage& i, const Storage& f);
    static Storage over_mixed(const Storage& i, const Storage& f);
    static Storage scanOver_integers(const Storage& i, const Storage& f);
    static Storage scanOver_reals(const Storage& i, const Storage& f);
    static Storage scanOver_mixed(const Storage& i, const Storage& f);

    // Dyadic Adverbs

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes &bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

class Character
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(int i);

    // Monads
    static Storage enclose_impl(const Storage& i);    
    static Storage format_impl(const Storage& i);
    static Storage reverse_impl(const Storage& i);    
    static Storage size_impl(const Storage& i);    

    // Dyads
    static Storage equal_impl(const Storage& i, const Storage& x);

    // Join
    static Storage join_scalar(const Storage& i, const Storage& x);
    static Storage join_character(const Storage& i, const Storage& x);
    static Storage join_list(const Storage& i, const Storage& x);
    static Storage prepend_string(const Storage& i, const Storage& x);

    static Storage less_character(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage more_character(const Storage& i, const Storage& x);

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

class IotaString
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(ints i);
    static Storage makeEmpty();

    // Monads
    static Storage atom_impl(const Storage& i);    
    static Storage enclose_impl(const Storage& i);    
    static Storage first_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage gradeDown_impl(const Storage& i);
    static Storage gradeUp_impl(const Storage& i);
    static Storage group_impl(const Storage& i);
    static Storage not_impl(const Storage& i);
    static Storage reverse_impl(const Storage& i);    
    static Storage size_impl(const Storage& i);    

    // Dyads
    static Storage amend_impl(const Storage& i, const Storage& x);
    static Storage equal_impl(const Storage& i, const Storage& x);

    static Storage find_character(const Storage& i, const Storage& x);
    static Storage find_string(const Storage& i, const Storage& x);

    static Storage form_integer(const Storage& i, const Storage& x);
    static Storage form_real(const Storage& i, const Storage& x);
    static Storage form_list(const Storage& i, const Storage& x);
    static Storage form_character(const Storage& i, const Storage& x);
    static Storage form_quoted_symbol(const Storage& i, const Storage& x);

    static Storage less_string(const Storage& i, const Storage& x);
    static Storage index_impl(const Storage& i, const Storage& x);
    
    // Join
    static Storage append_character(const Storage& i, const Storage& x);
    static Storage join_string(const Storage& i, const Storage& x);

    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage more_string(const Storage& i, const Storage& x);
    static Storage rotate_integer(const Storage& i, const Storage& x);

    static Storage split_integer(const Storage& i, const Storage& x);
    static Storage split_integers(const Storage& i, const Storage& x);
    static Storage take_integer(const Storage& i, const Storage& x);

    // Monadic Adverbs
    static Storage each_impl(const Storage& i, const Storage& f);
    static Storage eachPair_impl(const Storage& i, const Storage& f);
    static Storage over_impl(const Storage& i, const Storage& f);
    static Storage scanOver_impl(const Storage& i, const Storage& f);

    // Dyadic Adverbs

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes& bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

class Dictionary
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(const mixed &i);
    static Storage makeEmpty();

    // Monads

    // // Dyads
    // static Storage drop_impl(const Storage& i, const Storage& x);
    // static Storage equal_impl(const Storage& i, const Storage& x);
    static Storage find_impl(const Storage& i, const Storage& x);
    // static Storage join_impl(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    
    // // Monadic Adverbs
    // static Storage each_impl(const Storage& i, const Storage& f);

    // // Dyadic Adverbs

    // // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

class Expression
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage truth(const Storage& i);
};

class Conditional
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(const mixed &i);

    static Storage evaluate_impl(const Storage& i);
    static Storage truth_impl(const Storage& i);
};

class Symbol
{
  public:
    static std::unordered_map<int, ints> integerToString;
    static std::unordered_map<ints, int, IntsHash> stringToInteger;
    static std::unordered_map<int, Storage> values;

    // Initialize dispatch table and symbol tables
    static void initialize();

    static Storage match_impl(const Storage& i, const Storage& x);

    static Storage evaluate_impl(const Storage& i);
    static Storage truth_impl(const Storage& i);

    static ints asciiToUTF32(const std::string& ascii);
};

class QuotedSymbol
{
  public:
    static void initialize();

    static Storage make(const ints &i);
    static Storage undefined();

    // Monads
    static Storage format_impl(const Storage& i);
    static Storage undefined_impl(const Storage& i);
};

// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
class MixedArray
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static maybe<bytes> to_bytes(const Storage& storage);

    static maybe<Storage> from_conn(const Connection& conn, int objectType);
    static void to_conn(const Connection& conn, const Storage& i);

    static Storage make(mixed x, int o = NounType::LIST);
};

#endif