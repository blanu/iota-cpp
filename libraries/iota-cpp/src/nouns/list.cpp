//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <algorithm>
#include <cmath> // This is required for std::floor, even if the compiler doesn't realize it.
#include <unordered_set>
#include <variant>
#include <vector>

#include "list.h"
#include "integer.h"
#include "iota_string.h"
#include "noun.h"
#include "quoted_symbol.h"
#include "real.h"

#include "error.h"
#include <squeeze.h>
#include "../symbols.h"
#include "../verbs.h"
#include "../adverbs.h"
#include "../api.h"

#include <storage/float_array.h>
#include <storage/ion_float.h>
#include <storage/mixed_array.h>
#include <storage/word.h>
#include <storage/word_array.h>

// List
void List::initialize() {
  // WordArray
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::expand, List::expand_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::floor, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::format, List::format_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::group, List::group_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::amend, StorageType::WORD_ARRAY, NounType::LIST, List::amend_integers_integers);
  // Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, List::amend_integers_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::equal, StorageType::WORD_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::equal, StorageType::FLOAT_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::equal, StorageType::MIXED_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::equal, StorageType::WORD_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::equal, StorageType::FLOAT_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::equal, StorageType::MIXED_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::equal, StorageType::WORD_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::equal, StorageType::FLOAT_ARRAY, NounType::LIST, List::equal_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::equal, StorageType::MIXED_ARRAY, NounType::LIST, List::equal_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_integers_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_integers_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::CHARACTER, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, WordArray::nil2);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::format2, StorageType::WORD, NounType::INTEGER, List::format2_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::format2, StorageType::FLOAT, NounType::REAL, List::format2_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, List::append_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, List::join_integers_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::join_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_mixed);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_mix_left);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_enclose);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD, NounType::INTEGER, List::remainder_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, List::remainder_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, List::remainder_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD, NounType::INTEGER, List::reshape_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, List::reshape_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, List::reshape_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::rotate, StorageType::WORD, NounType::INTEGER, List::rotate_integer);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD, NounType::INTEGER, List::split_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, List::split_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::take, StorageType::WORD, NounType::INTEGER, List::take_integer);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD, NounType::INTEGER, List::times_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT, NounType::REAL, List::times_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, List::times_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, List::times_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, List::times_mixed);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::each, List::each_integers);
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::eachPair, List::eachPair_integers);
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::over, List::over_integers);

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::scanOver, List::scanOver_integers);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);

  // FloatArray
  // Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::floor, List::floor_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::format, List::format_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::group, List::group_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::amend, StorageType::WORD_ARRAY, NounType::LIST, List::amend_floats_integers);
  // Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, List::amend_floats_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_reals_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_reals_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::CHARACTER, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, WordArray::nil2);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::format2, StorageType::WORD, NounType::INTEGER, List::format2_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::format2, StorageType::FLOAT, NounType::REAL, List::format2_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, List::append_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mixed);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, List::join_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_mix_left);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_enclose);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::rotate, StorageType::WORD, NounType::INTEGER, List::rotate_integer);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD, NounType::INTEGER, List::split_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, List::split_integers);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::take, StorageType::WORD, NounType::INTEGER, List::take_integer);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD, NounType::INTEGER, List::times_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT, NounType::REAL, List::times_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, List::times_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, List::times_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, List::times_mixed);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::each, List::each_reals);
  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::eachPair, List::eachPair_reals);
  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::over, List::over_reals);

  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::scanOver, List::scanOver_reals);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);

  // MixedArray
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::floor, List::floor_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::format, List::format_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::group, List::group_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::transpose, List::transpose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, List::amend_floats);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::CHARACTER, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, List::find_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::format2, StorageType::WORD, NounType::INTEGER, List::format2_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::format2, StorageType::FLOAT, NounType::REAL, List::format2_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, List::join_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_right);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD, NounType::INTEGER, List::remainder_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, List::remainder_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, List::remainder_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD, NounType::INTEGER, List::reshape_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, List::reshape_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, List::reshape_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::rotate, StorageType::WORD, NounType::INTEGER, List::rotate_integer);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD, NounType::INTEGER, List::split_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, List::split_integers);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::take, StorageType::WORD, NounType::INTEGER, List::take_integer);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD, NounType::INTEGER, List::times_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT, NounType::REAL, List::times_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, List::times_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, List::times_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, List::times_mixed);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::each, List::each_mixed);
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::eachPair, List::eachPair_mixed);
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::over, List::over_mixed);

  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::scanOver, List::scanOver_mixed);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage List::make(const ints& i)
{
  return WordArray::make(i, NounType::LIST);  // Changed from NounType::INTEGER to NounType::LIST
}

Storage List::make(const std::vector<uint64_t>& i)
{
  // Convert each uint64_t to Storage
  std::vector<Storage> storageList;
  storageList.reserve(i.size());

  for (uint64_t value : i)
  {
    storageList.push_back(Integer::make(value));
  }

  // Check if all are Words (can use WordArray) or if any are WordArrays (need MixedArray)
  bool allWords = true;
  for (const Storage& storage : storageList)
  {
    if (!std::holds_alternative<int>(storage.i))
    {
      allWords = false;
      break;
    }
  }

  if (allWords)
  {
    // All are Words, extract the int values and use WordArray
    ints intList;
    intList.reserve(storageList.size());

    for (const Storage& storage : storageList)
    {
      intList.push_back(std::get<int>(storage.i));
    }

    return WordArray::make(intList, NounType::LIST);
  }
  else
  {
    // At least one is a WordArray, use MixedArray
    return Storage(NounType::LIST, StorageType::MIXED_ARRAY, storageList);
  }
}

ints List::toInts(const Storage& i)
{
    // Verify it's a LIST type
    if (i.o != NounType::LIST)
    {
        return {}; // Return empty vector for invalid type
    }

    if (std::holds_alternative<ints>(i.i))
    {
        // WordArray case - direct return
        return std::get<ints>(i.i);
    }
    else if (std::holds_alternative<mixed>(i.i))
    {
        // MixedArray case - convert each Storage element to int
        const mixed& list = std::get<mixed>(i.i);
        ints result;
        result.reserve(list.size());

        for (const Storage& storage : list)
        {
            if (std::holds_alternative<int>(storage.i))
            {
                result.push_back(std::get<int>(storage.i));
            }
            else
            {
                return {}; // Return empty if any element can't convert to int
            }
        }

        return result;
    }
    else
    {
        return {}; // Invalid storage type
    }
}

std::vector<uint64_t> List::toUInt64s(const Storage& i)
{
    // Verify it's a LIST type
    if (i.o != NounType::LIST)
    {
        return {}; // Return empty vector for invalid type
    }

    if (std::holds_alternative<ints>(i.i))
    {
        // WordArray case - convert each int to uint64_t
        const ints& list = std::get<ints>(i.i);
        std::vector<uint64_t> result;
        result.reserve(list.size());

        for (int value : list)
        {
            if (value < 0)
            {
                return {}; // Return empty for negative values
            }
            result.push_back(static_cast<uint64_t>(value));
        }

        return result;
    }
    else if (std::holds_alternative<mixed>(i.i))
    {
        // MixedArray case - convert each Storage element to uint64_t
        const mixed& list = std::get<mixed>(i.i);
        std::vector<uint64_t> result;
        result.reserve(list.size());

        for (const Storage& storage : list)
        {
            uint64_t* value = Integer::toUInt64(storage);
            if (value == nullptr)
            {
                return {}; // Return empty if any element can't convert
            }
            result.push_back(*value);
            delete value;
        }

        return result;
    }
    else
    {
        return {}; // Invalid storage type
    }
}

Storage List::atom_impl(const Storage& i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);
    if (integers.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);
    if (fs.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);
    if (ms.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else {
    return Noun::false0();
  }
}

Storage List::char_impl(const Storage& i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);

    if (integers.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed ms = mixed();
    for (int y : integers) {
      ms.insert(ms.end(), Word::make(y, NounType::CHARACTER));
    }
    return MixedArray::make(ms, NounType::LIST);
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);

    if (fs.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    } else {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);

    if (ms.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    } else {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::expand_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return WordArray::nil();
    }

    ints results = ints();

    for(int index = 0; index < static_cast<int>(integers.size()); index++)
    {
      int count = integers[index];

      for(int y = 0; y < count; y++)
      {
        results.push_back(index);
      }
    }

    return WordArray::make(results);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::first_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    int integer = integers.front();

    return Word::make(integer, NounType::INTEGER);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    float f = fs.front();

    return Float::make(f, NounType::REAL);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    const Storage& result = ms.front();

    return result;
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::floor_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    return i;
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    ints results = ints();
    for(float y : fs)
    {
      results.insert(results.end(), static_cast<int>(std::floor(y)));
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    ints results = ints();
    mixed mixedResults = mixed();
    for(const Storage& y : ms)
    {
      Storage result = eval({y, iota::floor});
      mixedResults.push_back(result);

      if(result.o == NounType::INTEGER)
      {
        if(std::holds_alternative<int>(result.i))
        {
          int integer = std::get<int>(result.i);
          results.push_back(integer);
        }
      }
    }

    if(mixedResults.size() > results.size())
    {
      return MixedArray::make(mixedResults, NounType::LIST);
    }
    else
    {
      return WordArray::make(results, NounType::LIST);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::format_impl(const Storage& i)
{
  using namespace iota;

  Storage mi = Noun::mix(i);
  if(std::holds_alternative<mixed>(mi.i))
  {
    mixed ms = std::get<mixed>(mi.i);

    if(ms.empty())
    {
      return IotaString::make(ints({static_cast<int>('['), static_cast<int>(']')}));
    }

    mixed results = mixed();

    for(const Storage& y : ms)
    {
      results.push_back(eval({y, format}));
    }

    return MixedArray::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::gradeDown_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());

    for (int index = 0; index < static_cast<int>(results.size()); ++index)
    {
        results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
        return integers[x] > integers[y];
    });

    for (int & result : results)
    {
        result = result + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return i;
    }

    ints results(fs.size());

    for (int resultsIndex = 0; resultsIndex < static_cast<int>(results.size()); ++resultsIndex)
    {
        results[resultsIndex] = resultsIndex;
    }

    std::sort(results.begin(), results.end(), [&fs](int x, int y)
    {
        if(fs[x] > fs[y])
        {
          float difference = fs[x] - fs[y];
          if(difference > Float::tolerance)
          {
            return 1; // x > y
          }
          else
          {
            return 0; // x ~= y
          }
        }
        else
        {
          return 0; // x <= y
        }
    });

    for (int & result : results)
    {
        result = result + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return i;
    }

    ints results(ms.size());

    for (int resultsIndex = 0; resultsIndex < static_cast<int>(results.size()); ++resultsIndex)
    {
        results[resultsIndex] = resultsIndex;
    }

    std::sort(results.begin(), results.end(), [&ms](int x, int y)
    {
        Storage result = eval({ms[x], more, ms[y]});
        switch(result.t)
        {
          case NounType::INTEGER:
            if(std::holds_alternative<int>(result.i))
            {
              return std::get<int>(result.i);
            }

          default:
            return 0;
        }

        return 0;
    });

    for (int & result : results)
    {
        result = result + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::gradeUp_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());

    for (int index = 0; index < static_cast<int>(results.size()); ++index)
    {
        results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
        return integers[x] < integers[y];
    });

    for (int & result : results)
    {
        result = result + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return i;
    }

    ints results(fs.size());

    for (int resultsIndex = 0; resultsIndex < static_cast<int>(results.size()); ++resultsIndex)
    {
        results[resultsIndex] = resultsIndex;
    }

    std::sort(results.begin(), results.end(), [&fs](int x, int y)
    {
        if(fs[x] < fs[y])
        {
          float difference = fs[y] - fs[x];
          if(difference > Float::tolerance)
          {
            return 1; // y < x
          }
          else
          {
            return 0; // y ~= x
          }
        }
        else
        {
          return 0; // y >= x
        }
    });

    for (int & result : results)
    {
        result = result + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return i;
    }

    ints results(ms.size());

    for (int resultsIndex = 0; resultsIndex < static_cast<int>(results.size()); ++resultsIndex)
    {
        results[resultsIndex] = resultsIndex;
    }

    std::sort(results.begin(), results.end(), [&ms](int x, int y)
    {
        Storage result = eval({ms[x], less, ms[y]});
        switch(result.t)
        {
          case NounType::INTEGER:
            if(std::holds_alternative<int>(result.i))
            {
              int integer = std::get<int>(result.i);
              return integer;
            }

          default:
            return 0;
        }

        return 0;
    });

    for (int & result : results)
    {
        result = result + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::group_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints items = std::get<ints>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<int, int> firsts=std::unordered_map<int, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();

    for (int index = 0; index < static_cast<int>(items.size()); index++)
    {
      // Get each item in the list
      int item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto & pair : groups)
    {
      ints group = pair.second;
      results.push_back(WordArray::make(group));
    }

    return MixedArray::make(results);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats items = std::get<floats>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<float, int> firsts=std::unordered_map<float, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();

    for (int index = 0; index < static_cast<int>(items.size()); index++)
    {
      // Get each item in the list
      float item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto & pair : groups)
    {
      ints group = pair.second;
      results.push_back(WordArray::make(group));
    }

    return MixedArray::make(results);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed items = std::get<mixed>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<Storage, int> firsts=std::unordered_map<Storage, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();

    for (int index = 0; index < static_cast<int>(items.size()); index++)
    {
      // Get each item in the list
      Storage item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto & pair : groups)
    {
      ints group = pair.second;
      results.push_back(WordArray::make(group));
    }

    return MixedArray::make(results);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::negate_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    ints results = ints();
    for(int y : integers)
    {
      results.insert(results.end(), -y);
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats();
    for(float y : fs)
    {
      results.insert(results.end(), -y);
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed();
    for(const Storage& y : ms)
    {
      results.push_back(eval({y, negate}));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::not_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if (integers.empty())
    {
      return Noun::true0();
    }

    ints results = ints();
    for (int y : integers)
    {
      if(y == 0)
      {
        results.push_back(1);
      }
      else
      {
        results.push_back(0);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if (std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if (fs.empty())
    {
      return Noun::true0();
    }

    ints results = ints();
    for (float y : fs)
    {
      if(abs(y) < Float::tolerance)
      {
        results.push_back(1);
      }
      else
      {
        results.push_back(0);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if (std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if (ms.empty())
    {
      return Noun::true0();
    }

    ints results = ints();
    mixed mixedResults = mixed();
    for (const Storage& y : ms)
    {
      Storage result = eval({y, inot});
      mixedResults.push_back(result);

      if(result.o == NounType::INTEGER)
      {
        if(std::holds_alternative<int>(result.i))
        {
          int integer = std::get<int>(result.i);
          results.push_back(integer);
        }
      }
    }

    if(mixedResults.size() > results.size())
    {
      return MixedArray::make(mixedResults, NounType::LIST);
    }
    else
    {
      return WordArray::make(results, NounType::LIST);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::reciprocal_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    floats results = floats();
    for(int y : integers)
    {
      results.insert(results.end(), 1.0f / static_cast<float>(y));
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats();
    for(float y : fs)
    {
      results.insert(results.end(), 1.0f / y);
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    floats results = floats();
    mixed mixedResults = mixed();
    for(const Storage& y : ms)
    {
      Storage result = eval({Real::make(1.0), divide, y});
      mixedResults.push_back(result);

      if(result.o == NounType::REAL)
      {
        if(std::holds_alternative<float>(result.i))
        {
          float f = std::get<float>(result.i);

          results.push_back(f);
        }
      }
    }

    if(mixedResults.size() > results.size())
    {
      return MixedArray::make(mixedResults, NounType::LIST);
    }
    else
    {
      return FloatArray::make(results, NounType::LIST);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::reverse_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    ints results = ints(integers);
    std::reverse(results.begin(), results.end());

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);



    if(fs.empty())
    {
      return i;
    }

    floats results = floats(fs);
    std::reverse(results.begin(), results.end());

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed(ms);
    std::reverse(results.begin(), results.end());

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::shape_impl(const Storage& i)
{
  using namespace iota;

  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    ints results = ints({static_cast<int>(integers.size())});
    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    ints results = ints({static_cast<int>(fs.size())});
    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    mixed shapes = mixed();
    for(const Storage& y : ms)
    {
      shapes.push_back(eval({y, shape}));
    }

    Storage firstShape = shapes.front();
    if(firstShape.o == NounType::LIST && firstShape.t == StorageType::WORD_ARRAY && std::holds_alternative<ints>(firstShape.i))
    {
      ints firstShapeIntegers = std::get<ints>(firstShape.i);

      for(const Storage& y : shapes)
      {
        Storage nextShape = eval({y, shape});
        if(nextShape.o == NounType::LIST && nextShape.t == StorageType::WORD_ARRAY && std::holds_alternative<ints>(nextShape.i))
        {
          ints nextShapeIntegers = std::get<ints>(nextShape.i);

          if(firstShapeIntegers != nextShapeIntegers)
          {
            return WordArray::make(ints({static_cast<int>(shapes.size())}), NounType::LIST);
          }
        }
      }

      ints results = ints(firstShapeIntegers);
      results.insert(results.begin(), static_cast<int>(shapes.size()));

      return WordArray::make(results, NounType::LIST);
    }
    else
    {
      return WordArray::make(ints({static_cast<int>(ms.size())}), NounType::LIST);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::size_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    return Word::make(static_cast<int>(integers.size()), NounType::INTEGER);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    return Word::make(static_cast<int>(fs.size()), NounType::INTEGER);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    return Word::make(static_cast<int>(ms.size()), NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// We can only transpose 2D arrays, which means a mixed array of either all words or all floats, where all subarrays are the same size
// FIXME - support 2D arrays of mixed words and floats
// FIXME - support 2D arrays of bigints
Storage List::transpose_impl(const Storage& i)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }
    else
    {
      int all_word_arrays = 1;
      int all_float_arrays = 1;
      for(const Storage& y : ms)
      {
        if(y.t == StorageType::WORD_ARRAY)
        {
          all_float_arrays = 0;
        }
        else if(y.t == StorageType::FLOAT_ARRAY)
        {
          all_word_arrays = 0;
        }
        else
        {
          all_word_arrays = 0;
          all_float_arrays = 0;
          break;
        }
      }

      if(all_word_arrays)
      {
        Storage first = ms.front();
        if(std::holds_alternative<ints>(first.i))
        {
          ints firstIntegers = std::get<ints>(first.i);

          int rows = static_cast<int>(ms.size());
          int columns = static_cast<int>(firstIntegers.size());

          std::vector<ints> source(rows);
          for (int j = 0; j < rows; ++j)
          {
            Storage subarray = ms[j];
            if(std::holds_alternative<ints>(subarray.i))
            {
              source[j] = std::get<ints>(subarray.i);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
          }

          std::vector<ints> transposed(columns, ints(rows));
          for (int j = 0; j < rows; ++j)
          {
            for (int k = 0; k < columns; ++k)
            {
                transposed[k][j] = source[j][k];  // Swap row and column indices
            }
          }

          mixed results = mixed();
          for (int k = 0; k < columns; ++k)
          {
            results.insert(results.end(), WordArray::make(transposed[k], NounType::LIST));
          }

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(all_float_arrays)
      {
        Storage first = ms.front();
        if(std::holds_alternative<floats>(first.i))
        {
          floats firstFloats = std::get<floats>(first.i);

          int rows = static_cast<int>(ms.size());
          int columns = static_cast<int>(firstFloats.size());

          std::vector<floats> source(rows);
          for (int j = 0; j < rows; ++j)
          {
            Storage subarray = ms[j];
            if(std::holds_alternative<floats>(subarray.i))
            {
              source[j] = std::get<floats>(subarray.i);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
          }

          std::vector<floats> transposed(columns, floats(rows));
          for (int j = 0; j < rows; ++j)
          {
            for (int k = 0; k < columns; ++k)
            {
                transposed[k][j] = source[j][k];  // Swap row and column indices
            }
          }

          mixed results = mixed();
          for (int k = 0; k < columns; ++k)
          {
            results.insert(results.end(), FloatArray::make(transposed[k], NounType::LIST));
          }

          return Noun::simplify(MixedArray::make(results, NounType::LIST));
        }
      }
      else // mixed
      {
        mixed results = mixed();

        Storage first = ms.front();

        int columnSize = static_cast<int>(ms.size());
        int rowSize = getInteger(eval({first, size}));

        for(int rowOffset = 0; rowOffset < rowSize; ++rowOffset)
        {
          results.push_back(MixedArray::make(mixed()));
        }

        for(int columnOffset = 0; columnOffset < columnSize; ++columnOffset)
        {
          Storage column = ms[columnOffset];
          for(int rowOffset = 0; rowOffset < rowSize; ++rowOffset)
          {
            Storage element = eval({column, iota::index, Integer::make(rowOffset + 1)});
            results[rowOffset] = eval({results[rowOffset], join, element});
          }
        }

        return Noun::simplify(MixedArray::make(results, NounType::LIST));
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::unique_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    std::unordered_set<int> set = std::unordered_set<int>();
    ints results = ints();

    for(int y : integers)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    std::unordered_set<float> set = std::unordered_set<float>();
    floats results = floats();

    for(float y : fs)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    std::unordered_set<Storage> set = std::unordered_set<Storage>();
    mixed results = mixed();

    for(const Storage& y : ms)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// List Dyads
// Storage List::amend_integers_integer(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<ints>(i.i))
//   {
//     ints integers = std::get<ints>(i.i);
//
//     if(integers.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<ints>(x.i))
//     {
//       ints indices = std::get<ints>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       ints results = ints(integers);
//
//       int replacement = indices.front();
//       for(int offset = 1; offset < indices.size(); offset++)
//       {
//         int index = indices[offset] - 1;
//         if(index < 0)
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//
//         if(index < static_cast<int>(results.size()))
//         {
//           results[index] = replacement;
//         }
//         else if(index == results.size())
//         {
//           results.push_back(replacement);
//         }
//         else
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//       }
//
//       return WordArray::make(results);
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_integers_mixed(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<ints>(i.i))
//   {
//     ints integers = std::get<ints>(i.i);
//
//     if(integers.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<mixed>(x.i))
//     {
//       mixed mixedIndices = std::get<mixed>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       ints results = ints(integers);
//
//       Storage replacement = mixedIndices.front();
//       Storage simplifiedIndices = simplify(drop(x, Integer::one()));
//
//       for(int offset = 1; offset < indices.size(); offset++)
//       {
//         int index = indices[offset] - 1;
//         if(index < 0)
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//
//         if(index < static_cast<int>(results.size()))
//         {
//           results[index] = replacement;
//         }
//         else if(index == results.size())
//         {
//           results.push_back(replacement);
//         }
//         else
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//       }
//
//       return WordArray::make(results);
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_floats_integer(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<floats>(i.i))
//   {
//     floats iis = std::get<floats>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<ints>(x.i))
//     {
//       ints indices = std::get<ints>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = Integer::make(indices.front());
//
//       if(std::holds_alternative<float>(mixedReplacement))
//       {
//         float replacement = std::get<float>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < static_cast<int>(results.size()))
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < static_cast<int>(results.size()))
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_floats_mixed(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<floats>(i.i))
//   {
//     floats iis = std::get<floats>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<mixed>(x.i))
//     {
//       mixed indices = std::get<mixed>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = indices.front();
//
//       if(std::holds_alternative<float>(mixedReplacement))
//       {
//         float replacement = std::get<float>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < static_cast<int>(results.size()))
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < static_cast<int>(results.size()))
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_mixed_integer(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<mixed>(i.i))
//   {
//     mixed iis = std::get<mixed>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<ints>(x.i))
//     {
//       ints indices = std::get<ints>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = Integer::make(indices.front());
//
//       if(std::holds_alternative<float>(mixedReplacement))
//       {
//         float replacement = std::get<float>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < static_cast<int>(results.size()))
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < static_cast<int>(results.size()))
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_mixed(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<mixed>(i.i))
//   {
//     mixed iis = std::get<mixed>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<mixed>(x.i))
//     {
//       mixed indices = std::get<mixed>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = indices.front();
//
//       if(std::holds_alternative<int>(mixedReplacement))
//       {
//         int replacement = std::get<int>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < static_cast<int>(results.size()))
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < static_cast<int>(results.size()))
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }

Storage List::cut_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int integer = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints list = std::get<ints>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == static_cast<int>(list.size()))
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < static_cast<int>(list.size()))
      {
        ints left = ints(list.begin(), list.begin() + integer);
        ints right = ints(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), WordArray::make(left, NounType::LIST));
        results.insert(results.end(), WordArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats list = std::get<floats>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == static_cast<int>(list.size()))
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < static_cast<int>(list.size()))
      {
        floats left = floats(list.begin(), list.begin() + integer);
        floats right = floats(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), FloatArray::make(left, NounType::LIST));
        results.insert(results.end(), FloatArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed list = std::get<mixed>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return Noun::simplify(MixedArray::make(results, NounType::LIST));
        }
        else
        {
          mixed results = mixed();
          results.push_back(WordArray::nil());
          results.push_back(i);

          return Noun::simplify(MixedArray::make(results, NounType::LIST));
        }
      }
      else if(integer == static_cast<int>(list.size()))
      {
          mixed results = mixed();
          results.push_back(i);
          results.push_back(WordArray::nil());

          return Noun::simplify(MixedArray::make(results, NounType::LIST));
      }
      else if(integer > 0 && integer < static_cast<int>(list.size()))
      {
        mixed left = mixed(list.begin(), list.begin() + integer);
        mixed right = mixed(list.begin() + integer, list.end());

        mixed results = mixed();
        results.push_back(MixedArray::make(left, NounType::LIST));
        results.push_back(MixedArray::make(right, NounType::LIST));
        return Noun::simplify(MixedArray::make(results, NounType::LIST));
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::cut_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints integers = std::get<ints>(x.i);

    // If no indices where specified, we always return [i]
    if(integers.empty())
    {
      mixed results = mixed({i});
      return MixedArray::make(results, NounType::LIST);
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints list = std::get<ints>(i.i);

      // Indices are non-empty, so the source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > static_cast<int>(list.size()))
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonically increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == static_cast<int>(list.size()))
            {
              // Capture the rest of the list that wasn't in any previous slice
              ints slice = ints(list.begin() + last, list.end());
              results.insert(results.end(), WordArray::make(slice, NounType::LIST));

              // Also insert nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              ints slice = ints(list.begin() + last, list.begin() + y);
              results.insert(results.end(), WordArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < static_cast<int>(list.size()))
        {
          ints slice = ints(list.begin() + last, list.end());
          results.insert(results.end(), WordArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats list = std::get<floats>(i.i);

      // Indices are non-empty, so the source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > static_cast<int>(list.size()))
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonically increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == static_cast<int>(list.size()))
            {
              // Capture the rest of the list that wasn't in any previous slice
              floats slice = floats(list.begin() + last, list.end());
              results.insert(results.end(), FloatArray::make(slice, NounType::LIST));

              // Also insert nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              floats slice = floats(list.begin() + last, list.begin() + y);
              results.insert(results.end(), FloatArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < static_cast<int>(list.size()))
        {
          ints slice = ints(list.begin() + last, list.end());
          results.insert(results.end(), WordArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed list = std::get<mixed>(i.i);

      // Indices are non-empty, so the source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > static_cast<int>(list.size()))
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonically increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == static_cast<int>(list.size()))
            {
              // Capture the rest of the list that wasn't in any previous slice
              mixed slice = mixed(list.begin() + last, list.end());
              results.insert(results.end(), MixedArray::make(slice, NounType::LIST));

              // Also insert nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              mixed slice = mixed(list.begin() + last, list.begin() + y);
              results.insert(results.end(), MixedArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < static_cast<int>(list.size()))
        {
          mixed slice = mixed(list.begin() + last, list.end());
          results.insert(results.end(), MixedArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      floats results = floats();
      for(int y : iis)
      {
        auto fy = static_cast<float>(y);
        auto fxi = static_cast<float>(xi);
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      auto fxi = static_cast<float>(xi);

      floats results = floats();
      for(float fy : fis)
      {
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed mis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      auto fxi = static_cast<float>(xi);

      floats results = floats();
      mixed mixedResults = mixed();

      for(const Storage& y : mis)
      {
        Storage result = eval({y, divide, Real::make(fxi)});
        if(result.o == NounType::QUOTED_SYMBOL)
        {
          mixedResults.push_back(result);
        }
        else if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.push_back(fr);
          mixedResults.push_back(result);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      if(mixedResults.size() > results.size())
      {
        return MixedArray::make(mixedResults);
      }
      else
      {
        return FloatArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      if(xi < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      floats results = floats();
      for(int y : iis)
      {
        auto fy = static_cast<float>(y);
        auto fxi = static_cast<float>(xi);
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fxi = std::get<float>(x.i);

      if(fxi < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      floats results = floats();
      for(float fy : fis)
      {
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed mis = std::get<mixed>(i.i);

    mixed results = mixed();

    for(const Storage& y : mis)
    {
      Storage result = eval({y, divide, x});
      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        if(xis[index] == 0)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          auto fi = static_cast<float>(iis[index]);
          auto fx = static_cast<float>(xis[index]);

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() > results.size())
      {
        return MixedArray::make(mixedResults);
      }
      else
      {
        return FloatArray::make(results);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        if(xis[index] == 0)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fi = iis[index];
          auto fx = static_cast<float>(xis[index]);

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() > results.size())
      {
        return MixedArray::make(mixedResults);
      }
      else
      {
        return FloatArray::make(results);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        Storage sx = Word::make(xis[index], NounType::INTEGER);
        Storage result = eval({si, divide, sx});

        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results, NounType::LIST));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          auto fi = static_cast<float>(iis[index]);
          float fx = xis[index];

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() > results.size())
      {
        return MixedArray::make(mixedResults);
      }
      else
      {
        return FloatArray::make(results);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fi = iis[index];
          float fx = xis[index];

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() > results.size())
      {
        return MixedArray::make(mixedResults);
      }
      else
      {
        return FloatArray::make(results);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        Storage sx = Float::make(xis[index], NounType::REAL);

        Storage result = eval({si, divide, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results, NounType::LIST));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        const Storage& sx = xis[index];

        Storage result = eval({si, divide, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results));
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        const Storage& sx = xis[index];

        Storage result = eval({si, divide, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results));
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, divide, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return Noun::simplify(MixedArray::make(results, NounType::LIST));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// FIXME - drop for strings
Storage List::drop_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          return WordArray::nil();
        }

        ints results(iis.begin() + xi, iis.end());
        return WordArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= static_cast<int>(iis.size()))
        {
          return WordArray::nil();
        }

        ints results(iis.begin(), iis.end() - xi);
        return WordArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          return WordArray::nil();
        }

        floats results(iis.begin() + xi, iis.end());
        return FloatArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= static_cast<int>(iis.size()))
        {
          return WordArray::nil();
        }

        floats results(iis.begin(), iis.end() - xi);
        return FloatArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          return WordArray::nil();
        }

        mixed results(iis.begin() + xi, iis.end());
        return MixedArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= static_cast<int>(iis.size()))
        {
          return WordArray::nil();
        }

        mixed results(iis.begin(), iis.end() - xi);
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::equal_impl(const Storage& i, const Storage& x)
{
  using namespace iota;

  int is = getInteger(eval({i, size}));
  int xs = getInteger(eval({x, size}));

  if(is != xs)
  {
    return Word::make(SHAPE_MISMATCH, NounType::ERROR);
  }

  if(is == 0)
  {
    return WordArray::nil();
  }

  mixed results = mixed();
  for(int offset = 1; offset <= is; offset++)
  {
    Storage y = eval({i, iota::index, Integer::make(offset)});
    Storage z = eval({x, iota::index, Integer::make(offset)});
    Storage result = eval({y, equal, z});
    results.push_back(result);
  }

  return Noun::simplify(MixedArray::make(results));
}

Storage List::find_integers_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Word::make(xi, NounType::INTEGER);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_integers_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Float::make(fx, NounType::REAL);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_reals_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      Storage sx = Word::make(xi, NounType::INTEGER);

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);

        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_reals_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = Float::make(xi, NounType::REAL);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    ints results = ints();

    for(int index = 0; index < static_cast<int>(iis.size()); index++)
    {
      const Storage& si = iis[index];
        Storage matched = eval({si, match, x});
      if(matched.o == NounType::ERROR)
      {
        return matched;
      }

      if(matched.truth())
      {
        results.push_back(index + 1);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::format2_impl(const Storage& i, const Storage& x)
{
  using namespace iota;

  Storage mi = Noun::mix(i);
  if(std::holds_alternative<mixed>(mi.i))
  {
    mixed ms = std::get<mixed>(mi.i);

    if(ms.empty())
    {
      return QuotedSymbol::undefined();
    }

    mixed results = mixed();

    for(const Storage& y : ms)
    {
      results.push_back(eval({y, format2, x}));
    }

    return MixedArray::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::index_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= static_cast<int>(iis.size()))
      {
        int result = iis[xi - 1];
        return Word::make(result, NounType::INTEGER);
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= static_cast<int>(iis.size()))
        {
          int result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= static_cast<int>(iis.size()))
      {
        float result = iis[xi - 1];
        return Float::make(result, NounType::REAL);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= static_cast<int>(iis.size()))
        {
          float result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= static_cast<int>(iis.size()))
      {
        return iis[xi - 1];
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= static_cast<int>(iis.size()))
        {
          results.push_back(iis[xi - 1]);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage List::append_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results(iis);
      results.push_back(xi);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::append_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results(iis);
      results.push_back(xi);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::prepend_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(xis);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::prepend_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results(iis);
      results.insert(results.begin(), xi);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(iis);

      for(int y : xis)
      {
        results.push_back(y);
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_integers_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(int y : iis)
      {
        results.push_back(Word::make(y, NounType::INTEGER));
      }

      for(float y : xis)
      {
        results.push_back(Float::make(y, NounType::REAL));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results(iis);

      for(float y : xis)
      {
        results.push_back(y);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_reals_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(float y : iis)
      {
        results.push_back(Float::make(y, NounType::REAL));
      }

      for(int y : xis)
      {
        results.push_back(Word::make(y, NounType::INTEGER));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : iis)
      {
        results.push_back(y);
      }

      for(const Storage& y : xis)
      {
        results.push_back(y);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();


      for(int y : iis)
      {
        if(y < xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      ints results = ints();

      for(float fy : fs)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, less, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        if((fy < fx) && ((fx - fy ) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      ints results = ints();

      for(float fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, less, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        if(ii < xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y > xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      ints results = ints();

      for(float fy : fs)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, more, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      ints results = ints();

      for(float fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, more, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        if(ii > xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::match_impl(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        if(iis[index] != xis[index])
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        auto fi = static_cast<float>(iis[index]);
        float fx = xis[index];
        if(abs(fi - fx) >= Float::tolerance)
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        const Storage& sx = xis[index];
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(static_cast<int>(fs.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(fs.size()); index++)
      {
        Storage si = Real::make(fs[index]);
        Storage sx = Integer::make(xis[index]);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(static_cast<int>(fs.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(fs.size()); index++)
      {
        Storage si = Real::make(fs[index]);
        Storage sx = Real::make(xis[index]);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(static_cast<int>(fs.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(fs.size()); index++)
      {
        Storage si = Real::make(fs[index]);
        const Storage& sx = xis[index];
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        Storage sx = Word::make(xis[index], NounType::INTEGER);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        Storage sx = Float::make(xis[index], NounType::REAL);
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Noun::false0();
      }

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];
        Storage matched = eval({si, match, sx});
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y < xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(y);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      mixed results = mixed();

      for(float fy : fs)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Real::make(fy));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, less, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        if((fy < fx) && ((fx - fy ) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(y));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fy);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, less, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        if(ii < xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(Word::make(xi));
        }
        else
        {
          results.push_back(Float::make(fi));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(Float::make(fx));
        }
        else
        {
          results.push_back(Word::make(ii));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, less, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y > xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(y);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      mixed results = mixed();

      for(float fy : fs)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Real::make(fy));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, more, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(y));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fy);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, more, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        if(ii > xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(Word::make(xi));
        }
        else
        {
          results.push_back(Float::make(fi));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(Float::make(fx));
        }
        else
        {
          results.push_back(Word::make(ii));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y - xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      floats results = floats();

      for(float fy : fs)
      {
        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, minus, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);


    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, minus, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii - xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, minus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, minus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, minus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, minus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y + xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      floats results = floats();

      for(float fy : fs)
      {
        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, plus, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, plus, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii + xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, plus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();


      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, more, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, plus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, plus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, plus, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);
    auto fx = static_cast<float>(xi);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : fs)
      {
        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, power, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, power, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        int xi = xis[index];

        auto fi = static_cast<float>(ii);
        auto fx = static_cast<float>(xi);

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fi = iis[index];

        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();


      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, power, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, power, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, power, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, power, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, power, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::remainder_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);


      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y % xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, iota::remainder, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::remainder_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        int xi = xis[index];

        results.push_back(ii % xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, iota::remainder, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::remainder_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, iota::remainder, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, iota::remainder, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::reshape_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(xi == 0)
    {
      return i;
    }

    if(xi < -1)
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    if(xi == -1)
    {
      xi = getInteger(eval({eval({i, size}), divide, Word::make(2)}));
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int index = 0; index < xi; index++)
      {
        int cyclingIndex = index % static_cast<int>(iis.size());
        results.push_back(iis[cyclingIndex]);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(int index = 0; index < xi; index++)
      {
        int cyclingIndex = index % static_cast<int>(iis.size());
        results.push_back(iis[cyclingIndex]);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(int index = 0; index < xi; index++)
      {
        int cyclingIndex = index % static_cast<int>(iis.size());
        results.push_back(iis[cyclingIndex]);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::reshape_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  int halfSize = getInteger(eval({eval({i, size}), integerDivide, Word::make(2)}));

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(xis.empty())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    ints lengths = ints();
    for(int xi : xis)
    {
      if(xi == 0 || xi < -1)
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
      else if(xi == -1)
      {
        lengths.push_back(halfSize);
      }
      else
      {
        // else xi > 0
        lengths.push_back(xi);
      }
    }

    if(lengths.size() == 1)
    {
      int xi = lengths[0];
      Storage sx = Word::make(xi);

      return eval({i, reshape, sx});
    }
    else // lengths.size() > 1
    {
      Storage sl = WordArray::make(lengths);
      Storage totals = eval({sl, scanOver, times, reverse});

      Storage working = eval({i, reshape, eval({totals, iota::index, Integer::zero()})});

      return eval({working, overNeutral, split, totals});
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::reshape_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, reshape, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, reshape, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::rotate_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return WordArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % static_cast<int>(iis.size());

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return WordArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        floats results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return FloatArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % static_cast<int>(iis.size());

        floats results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return FloatArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        mixed results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return MixedArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % static_cast<int>(iis.size());

        mixed results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::split_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        ints result = ints();
        for(int ii : iis)
        {
          result.push_back(ii);

          if(static_cast<int>(result.size()) == xi)
          {
            results.push_back(WordArray::make(result));
            result = ints();
          }
        }

        if(!result.empty())
        {
          results.push_back(WordArray::make(result));
        }

        return MixedArray::make(results);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        floats result = floats();
        for(float ii : iis)
        {
          result.push_back(ii);

          if(static_cast<int>(result.size()) == xi)
          {
            results.push_back(FloatArray::make(result));
            result = floats();
          }
        }

        if(!result.empty())
        {
          results.push_back(FloatArray::make(result));
        }

        return MixedArray::make(results);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        mixed result = mixed();
        for(const auto & ii : iis)
        {
          result.push_back(ii);

          if(static_cast<int>(result.size()) == xi)
          {
            results.push_back(MixedArray::make(result));
            result = mixed();
          }
        }

        if(!result.empty())
        {
          results.push_back(MixedArray::make(result));
        }

        return MixedArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::split_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(xis.empty())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < static_cast<int>(iis.size()))
      {
        int y = xis[index++ % static_cast<int>(xis.size())]; // cycle

        if(count + y > static_cast<int>(iis.size()))
        {
          ints result(iis.begin() + count, iis.end());
          results.push_back(WordArray::make(result));
          break;
        }
        else
        {
          ints result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(WordArray::make(result));
        }

        count = count + y;
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < static_cast<int>(iis.size()))
      {
        int y = xis[index++ % static_cast<int>(xis.size())]; // cycle

        if(count + y > static_cast<int>(iis.size()))
        {
          floats result(iis.begin(), iis.end());
          results.push_back(FloatArray::make(result));
          break;
        }
        else
        {
          floats result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(FloatArray::make(result));
        }

        count = count + y;
      }

      if(count < static_cast<int>(iis.size()))
      {
          floats result(iis.begin() + count, iis.end());
          results.push_back(FloatArray::make(result));
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);
      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < static_cast<int>(iis.size()))
      {
        int y = xis[index++ % static_cast<int>(xis.size())]; // cycle

        if(count + y > static_cast<int>(static_cast<int>(iis.size())))
        {
          mixed result(iis.begin(), iis.end());
          results.push_back(MixedArray::make(result));
          break;
        }
        else
        {
          mixed result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(MixedArray::make(result));
        }

        count = count + y;
      }

      if(count < static_cast<int>(iis.size()))
      {
          mixed result(iis.begin() + count, iis.end());
          results.push_back(MixedArray::make(result));
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::take_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return WordArray::nil();
      }
      else if(xi > 0)
      {
        ints results = ints();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % static_cast<int>(iis.size())]); // cycle through iis
        }

        return WordArray::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        ints results = ints();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % static_cast<int>(iis.size());
          results.push_back(iis[index]);
        }

        return WordArray::make(results);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return WordArray::nil();
      }

      if(xi > 0)
      {
        floats results = floats();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % static_cast<int>(iis.size())]); // cycle through iis
        }

        return FloatArray::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        floats results = floats();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % static_cast<int>(iis.size());
          results.push_back(iis[index]);
        }

        return FloatArray::make(results);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return WordArray::nil();
      }

      if(xi > 0)
      {
        mixed results = mixed();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % static_cast<int>(iis.size())]); // cycle through iis
        }

        return MixedArray::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        mixed results = mixed();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % static_cast<int>(iis.size());
          results.push_back(iis[index]);
        }

        return MixedArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y * xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats fs = std::get<floats>(i.i);
      auto fx = static_cast<float>(xi);

      floats results = floats();

      for(float fy : fs)
      {
        results.push_back(fy * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, times, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_real(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        auto fy = static_cast<float>(y);

        results.push_back(fy * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(const Storage& sy : iis)
      {
        Storage result = eval({sy, times, x});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii * xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        auto fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, times, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_reals(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        auto fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        const Storage& sy = iis[index];

        Storage result = eval({sy, times, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, times, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        const Storage& sx = xis[index];

        Storage result = eval({si, times, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      auto iis = std::get<mixed>(i.i);

      if(static_cast<int>(iis.size()) != static_cast<int>(xis.size()))
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        const Storage& si = iis[index];
        const Storage& sx = xis[index];

        Storage result = eval({si, times, sx});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Monadic Adverbs
Storage List::each_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();
    for(int y : iis)
    {
      Storage result = Noun::dispatchMonad(Integer::make(y), f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::each_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    mixed results = mixed();
    for(float y : fs)
    {
      Storage result = Noun::dispatchMonad(Real::make(y), f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::each_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    mixed results = mixed();
    for(const Storage& y : iis)
    {
      Storage result = Noun::dispatchMonad(y, f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::eachPair_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();
    for(int index = 0; index < static_cast<int>(iis.size()) - 1; index++)
    {
      int y = iis[index];
      int z = iis[index+1];
      Storage result = Noun::dispatchDyad(Word::make(y), f, Word::make(z));

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::eachPair_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    mixed results = mixed();
    for(int index = 0; index < static_cast<int>(iis.size()) - 1; index++)
    {
      float y = iis[index];
      float z = iis[index+1];
      Storage result = Noun::dispatchDyad(Float::make(y), f, Float::make(z));

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::eachPair_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    mixed results = mixed();
    for(int index = 0; index < static_cast<int>(iis.size()) - 1; index++)
    {
      const Storage& y = iis[index];
      const Storage& z = iis[index+1];
      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::over_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(static_cast<int>(iis.size()) == 1)
    {
      int result = iis[0];
      return Word::make(result);
    }

    // else static_cast<int>(iis.size()) > 1

    Storage y = Word::make(iis[0]);

    for(int index = 1; index < static_cast<int>(iis.size()); index++)
    {
      Storage z = Word::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;
    }

    return y;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::over_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(static_cast<int>(iis.size()) == 1)
    {
      float result = iis[0];
      return Float::make(result);
    }

    // else static_cast<int>(iis.size()) > 1

    Storage y = Float::make(iis[0]);

    for(int index = 1; index < static_cast<int>(iis.size()); index++)
    {
      Storage z = Float::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;
    }

    return y;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::over_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(static_cast<int>(iis.size()) == 1)
    {
      return iis[0];
    }

    // else static_cast<int>(iis.size()) > 1

    Storage y = iis[0];

    for(int index = 1; index < static_cast<int>(iis.size()); index++)
    {
      const Storage& z = iis[index];

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;
    }

    return y;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::scanOver_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(static_cast<int>(iis.size()) == 1)
    {
      return i;
    }

    // else static_cast<int>(iis.size()) > 1

    Storage y = Word::make(iis[0]);
    mixed results = mixed({y});

    for(int index = 1; index < static_cast<int>(iis.size()); index++)
    {
      Storage z = Word::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;

      results.push_back(y);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::scanOver_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(static_cast<int>(iis.size()) == 1)
    {
      return i;
    }

    // else static_cast<int>(iis.size()) > 1

    Storage y = Float::make(iis[0]);
    mixed results = mixed({y});

    for(int index = 1; index < static_cast<int>(iis.size()); index++)
    {
      Storage z = Float::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;

      results.push_back(y);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::scanOver_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(static_cast<int>(iis.size()) == 1)
    {
      return i;
    }

    // else static_cast<int>(iis.size()) > 1

    Storage y = iis[0];
    mixed results = mixed({y});

    for(int index = 1; index < static_cast<int>(iis.size()); index++)
    {
      const Storage& z = iis[index];

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;

      results.push_back(y);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

maybe<Storage> List::from_bytes(const bytes &bs, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_bytes(bs, NounType::LIST);

    case StorageType::FLOAT_ARRAY:
      return FloatArray::from_bytes(bs, NounType::LIST);

    case StorageType::MIXED_ARRAY:
      return MixedArray::from_bytes(bs, NounType::LIST);

    default:
      return std::nullopt;
  }
}

maybe<bytes> List::to_bytes(const Storage& i) {
  // Don't include type, that is handled by Noun::to_bytes

  if (i.o != NounType::LIST) {
    return std::nullopt;
  }

  bytes result = bytes();

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          return squeeze_ints(integers);
        } else {
          return std::nullopt;
        }
      }

    case StorageType::FLOAT_ARRAY:
      {
        if (std::holds_alternative<floats>(i.i)) {
          floats fs = std::get<floats>(i.i);
          return squeeze_floats(fs);
        } else {
          return std::nullopt;
        }
      }

    case StorageType::MIXED_ARRAY:
      {
        return MixedArray::to_bytes(i);
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> List::from_conn(Connection& conn, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_conn(conn, NounType::LIST);

    case StorageType::FLOAT_ARRAY:
      return FloatArray::from_conn(conn, NounType::LIST);

    case StorageType::MIXED_ARRAY:
      return MixedArray::from_conn(conn, NounType::LIST);

    default:
      return std::nullopt;
  }
}

void List::to_conn(Connection& conn, const Storage& i) {
  if (i.o != NounType::LIST) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          // Always include type in to_conn implementation
          std::vector<char> typeBytes = { static_cast<char>(i.t), static_cast<char>(i.o) };
          conn.write(typeBytes);

          ints integers = std::get<ints>(i.i);
          bytes bs = squeeze_ints(integers);

          conn.write(bs);
        }
        return;
      }

    case StorageType::FLOAT_ARRAY:
      {
        // Always include type in to_conn implementation
        std::vector<char> typeBytes = { static_cast<char>(i.t), static_cast<char>(i.o) };
        conn.write(typeBytes);

        floats fs = std::get<floats>(i.i);
        bytes bs = squeeze_floats(fs);

        conn.write(bs);
      }

    case StorageType::MIXED_ARRAY:
      {
        // No need to include type here, because it is provided by MixedArray::to_conn
        MixedArray::to_conn(conn, i);
      }

    default:
      return;
  }
}
