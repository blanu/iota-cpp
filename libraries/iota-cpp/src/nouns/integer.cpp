//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <cmath> // This is necessary for std::abs, even if the compiler doesn't realize it.
#include <numeric>
#include <tuple>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>

#include "error.h"
#include <squeeze.h>
#include "../symbols.h"
#include "../verbs.h"
#include "../adverbs.h"
#include "../api.h"

#include <storage/float_array.h>
#include <storage/ion_float.h>
#include <storage/mixed_array.h>
#include <storage/storage.h>
#include <storage/word.h>
#include <storage/word_array.h>

#include "integer.h"
#include "iota_string.h"
#include "list.h"
#include "noun.h"
#include "quoted_symbol.h"
#include "real.h"

#include <Connection.h>
#include <functional>

#include <iostream> // FIXME - remove, for debugging
#include <BigNumber.h>

// Integer
void Integer::initialize()
{
  BigNumber::begin();

  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::ichar, Integer::char_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enclose, Integer::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::expand, Integer::expand_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enumerate, Integer::enumerate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::format, Integer::format_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::INTEGER, Monads::format, Integer::format_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::floor, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::negate, Integer::negate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::inot, Integer::not_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::reciprocal, Integer::reciprocal_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::size, Integer::size_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::evaluate, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::INTEGER, Monads::evaluate, Noun::identity1);

  // Dyads
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, Integer::cut_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::cut_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::MIXED_ARRAY, NounType::LIST, Integer::cut_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD, NounType::INTEGER, Integer::divide_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::divide, StorageType::WORD, NounType::INTEGER, Integer::divide_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::divide_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::divide, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::divide_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT, NounType::REAL, Integer::divide_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Integer::divide_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::divide_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Integer::divide_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::equal, StorageType::WORD, NounType::INTEGER, Integer::equal_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::equal, StorageType::WORD, NounType::INTEGER, Integer::equal_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::equal, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::equal_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::equal, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::equal_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD, NounType::INTEGER, Integer::integerDivide_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD, NounType::INTEGER, Integer::integerDivide_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::integerDivide_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::integerDivide_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::INTEGER, Integer::join_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::prepend_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD, NounType::INTEGER, Integer::less_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::less, StorageType::WORD, NounType::INTEGER, Integer::less_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::less_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::less, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::less_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::FLOAT, NounType::REAL, Integer::less_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, Integer::less_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::less_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, Integer::less_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD, NounType::INTEGER, Integer::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::FLOAT, NounType::REAL, Integer::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD, NounType::INTEGER, Integer::max_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::max, StorageType::WORD, NounType::INTEGER, Integer::max_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::max_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::max, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::max_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT, NounType::REAL, Integer::max_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Integer::max_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::min, StorageType::WORD, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::min, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT, NounType::REAL, Integer::min_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Integer::min_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::minus, StorageType::WORD, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::minus, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT, NounType::REAL, Integer::minus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::minus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::more, StorageType::WORD, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::more, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT, NounType::REAL, Integer::more_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Integer::more_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD, NounType::INTEGER, Integer::plus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::plus, StorageType::WORD, NounType::INTEGER, Integer::plus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::plus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::plus, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::plus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::FLOAT, NounType::REAL, Integer::plus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, Integer::plus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::plus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::plus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::WORD, NounType::INTEGER, Integer::power_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::FLOAT, NounType::REAL, Integer::power_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, Integer::power_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::power_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, Integer::power_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::WORD, NounType::INTEGER, Integer::remainder_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::remainder, StorageType::WORD, NounType::INTEGER, Integer::remainder_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::remainder_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::remainder, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::remainder_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, Integer::remainder_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, Integer::remainder_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::WORD, NounType::INTEGER, Integer::reshape_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, Integer::reshape_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, Integer::reshape_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::WORD, NounType::INTEGER, Integer::times_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::times, StorageType::WORD, NounType::INTEGER, Integer::times_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::times_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::INTEGER, Dyads::times, StorageType::WORD_ARRAY, NounType::INTEGER, Integer::times_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::FLOAT, NounType::REAL, Integer::times_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, Integer::times_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::times_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, Integer::times_list);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::each, Noun::dispatchMonad);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::eachPair, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::over, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::scanOver, Noun::enclose2);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage Integer::make(int i)
{
  return Word::make(i, NounType::INTEGER);
}

Storage Integer::make(uint64_t i)
{
  // Check if it fits in int range (signed 32-bit)
  if (i <= static_cast<uint64_t>(INT_MAX))
  {
    return Word::make(static_cast<int>(i), NounType::INTEGER);
  }

  // Convert to WordArray representation
  // Determine how many 32-bit chunks we need
  ints chunks;

  // Sign bit (always 0 for unsigned)
  chunks.push_back(0);

  // Extract 32-bit chunks in big-endian order
  if (i > 0xFFFFFFFF)
  {
    // Need 2 chunks (high and low 32 bits)
    uint32_t high = static_cast<uint32_t>(i >> 32);
    uint32_t low = static_cast<uint32_t>(i & 0xFFFFFFFF);

    // Reinterpret unsigned as signed to preserve bit pattern
    chunks.push_back(static_cast<int>(high));
    chunks.push_back(static_cast<int>(low));
  }
  else
  {
    // Only need 1 chunk (low 32 bits)
    uint32_t low = static_cast<uint32_t>(i);
    chunks.push_back(static_cast<int>(low));
  }

  return WordArray::make(chunks, NounType::INTEGER);
}

// In integer.cpp
Storage Integer::make(unsigned long i)
{
  // Convert unsigned long to uint64_t and use existing logic
  return Integer::make(static_cast<uint64_t>(i));
}

Storage Integer::makeHex(std::string s)
{
  if(s.empty())
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  // Handle negative sign
  bool negative = (s[0] == '-');
  size_t start = negative ? 1 : 0;

  // Remove 0x or 0X prefix if present
  if(s.length() > start + 2 && s[start] == '0' &&
      (s[start + 1] == 'x' || s[start + 1] == 'X'))
  {
    start += 2;
  }

  if(start >= s.length())
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  std::string hex = s.substr(start);

  // Convert hex string to array of nibbles (4-bit values)
  std::vector<uint8_t> nibbles;
  for(char c : hex)
  {
    uint8_t value;
    if(c >= '0' && c <= '9')
    {
      value = c - '0';
    }
    else if(c >= 'A' && c <= 'F')
    {
      value = c - 'A' + 10;
    }
    else if(c >= 'a' && c <= 'f')
    {
      value = c - 'a' + 10;
    }
    else
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }
    nibbles.push_back(value);
  }

  // Determine how many nibbles fit in a platform int
  // Each nibble is 4 bits, int has sizeof(int) * 8 bits
  const int nibbles_per_chunk = (sizeof(int) * 8) / 4;

  // Group nibbles into int-sized chunks
  // Process from right to left to maintain big-endian word order
  typedef unsigned int uint_t;
  std::vector<uint_t> chunks;

  int num_nibbles = static_cast<int>(nibbles.size());
  for(int i = num_nibbles; i > 0; i -= nibbles_per_chunk)
  {
    uint_t chunk = 0;
    int start_idx = (i >= nibbles_per_chunk) ? (i - nibbles_per_chunk) : 0;
    int count = i - start_idx;

    // Build chunk from nibbles using arithmetic (no bit operations)
    for(int j = 0; j < count; j++)
    {
      chunk = chunk * 16 + nibbles[start_idx + j];
    }

    chunks.insert(chunks.begin(), chunk); // Insert at front for big-endian order
  }

  // Check if the result fits in a platform int
  if(chunks.size() == 1)
  {
    uint_t value = chunks[0];

    // Check if it fits in the platform's int type
    if(!negative && value <= static_cast<uint_t>(INT_MAX))
    {
      return Word::make(static_cast<int>(value), NounType::INTEGER);
    }
    else if(negative && value <= static_cast<uint_t>(-(static_cast<int64_t>(INT_MIN))))
    {
      if(value == static_cast<uint_t>(-(static_cast<int64_t>(INT_MIN))))
      {
        return Word::make(INT_MIN, NounType::INTEGER);
      }
      else
      {
        return Word::make(-static_cast<int>(value), NounType::INTEGER);
      }
    }
  }

  // Build WordArray (bigint representation)
  ints result;

  // First element: sign bit (0 = positive, 1 = negative)
  result.push_back(negative ? 1 : 0);

  // Remaining elements: int-sized chunks in big-endian word order
  // Reinterpret uint_t as int to preserve bit pattern
  for(uint_t chunk : chunks)
  {
    result.push_back(static_cast<int>(chunk));
  }

  return WordArray::make(result, NounType::INTEGER);
}

Storage Integer::make(const BigNumber& bn)
{
    // Check if it's zero
    if (bn.isZero())
    {
        return Integer::make(0);
    }

    // Check if negative
    bool negative = bn.isNegative();

    // Try to fit in regular int first
    char* decimal_cstr = bn.toString();
    if (decimal_cstr == nullptr)
    {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    std::string decimal_str(decimal_cstr);
    free(decimal_cstr);

    // Remove minus sign for length check
    std::string abs_str = decimal_str;
    if (negative && abs_str.length() > 0 && abs_str[0] == '-')
    {
        abs_str = abs_str.substr(1);
    }

    // If 10 digits or less, try to fit in regular int
    if (abs_str.length() <= 10)
    {
        long long temp = std::stoll(decimal_str);
        if (temp >= INT_MIN && temp <= INT_MAX)
        {
            return Integer::make(static_cast<int>(temp));
        }
        // Falls through to WordArray if out of range
    }

    // For large numbers, convert to WordArray format
    // Format: [sign_bit, chunk1, chunk2, ...] where chunks are 32-bit in big-endian order

    ints chunks;
    chunks.push_back(negative ? 1 : 0); // sign bit

    // Create a working copy to modify
    BigNumber working = bn;
    if (negative)
    {
        working = BigNumber(0) - working; // Make positive
    }

    // Build 2^32 as divisor: "4294967296"
    BigNumber base("4294967296");

    std::vector<uint32_t> temp_chunks;

    while (!working.isZero())
    {
        BigNumber quotient, remainder;
        working.divMod(base, quotient, remainder);

        // Convert remainder to uint32_t
        // Get string representation and parse it
        char* rem_cstr = remainder.toString();
        if (rem_cstr == nullptr)
        {
            return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        unsigned long long rem_val = std::stoull(rem_cstr);
        free(rem_cstr);

        if (rem_val > 0xFFFFFFFFULL)
        {
            return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        temp_chunks.push_back(static_cast<uint32_t>(rem_val));

        working = quotient;
    }

    // Handle empty case (shouldn't happen, but be safe)
    if (temp_chunks.empty())
    {
        return Integer::make(0);
    }

    // Chunks are in little-endian order, reverse for big-endian
    std::reverse(temp_chunks.begin(), temp_chunks.end());

    for (uint32_t chunk : temp_chunks)
    {
        chunks.push_back(static_cast<int>(chunk));
    }

    return WordArray::make(chunks, NounType::INTEGER);
}

Storage Integer::makeDecimal(std::string decimal_str)
{
  using namespace iota;

  Storage s = IotaString::makeString(decimal_str);
  return evalExpressionCppToIota({s, form, Integer::zero()});
}

std::string Integer::toDecimalString(const Storage& i)
{
  Storage s = Integer::format_impl(i);
  return IotaString::toString(s);
}

// In integer.h, add this declaration:
static BigNumber toBigNumber(const Storage& i);

// In integer.cpp, add this implementation:
BigNumber Integer::toBigNumber(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    // WORD case - simple conversion
    int val = std::get<int>(i.i);
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", val);
    return BigNumber(buf);
  }
  else if(std::holds_alternative<ints>(i.i))
  {
    // WORD_ARRAY case - convert chunks to BigNumber
    const ints& chunks = std::get<ints>(i.i);

    if(chunks.empty())
    {
      return BigNumber(0);
    }

    bool negative = (chunks[0] == 1);

    // Check if all chunks are zero
    bool all_zero = true;
    for(size_t idx = 1; idx < chunks.size(); idx++)
    {
      if(chunks[idx] != 0)
      {
        all_zero = false;
        break;
      }
    }

    if(all_zero)
    {
      return BigNumber(0);
    }

    // Build result by processing chunks from least to most significant
    BigNumber result(0);
    BigNumber multiplier(1);

    // Build base = 2^(sizeof(int)*8)
    BigNumber base(1);
    const int BITS_PER_CHUNK = sizeof(int) * 8;
    for(int j = 0; j < BITS_PER_CHUNK; j++)
    {
      base = base + base;
    }

    // Process chunks from right to left (least to most significant)
    for(size_t idx = chunks.size() - 1; idx >= 1; idx--)
    {
      // Reinterpret chunk as unsigned
      const auto chunk_unsigned = static_cast<const unsigned int>(chunks[idx]);

      // Convert to string to avoid sign issues
      char chunk_str[32];
      snprintf(chunk_str, sizeof(chunk_str), "%u", chunk_unsigned);
      BigNumber chunk_bn(chunk_str);

      result = result + (chunk_bn * multiplier);
      multiplier = multiplier * base;

      if(idx == 1) break; // Avoid underflow
    }

    if(negative)
    {
      result = BigNumber(0) - result;
    }

    return result;
  }

  // Fallback
  return BigNumber(0);
}

uint64_t* Integer::toUInt64(const Storage& i)
{
  if (std::holds_alternative<int>(i.i))
  {
    // Word case - convert int to uint64_t
    int value = std::get<int>(i.i);
    if (value < 0)
    {
      return nullptr; // Cannot convert negative Word to uint64_t
    }

    auto* result = new uint64_t;
    *result = static_cast<uint64_t>(value);
    return result;
  }
  else if (std::holds_alternative<ints>(i.i))
  {
    // WordArray case - reconstruct from 32-bit chunks
    const ints& list = std::get<ints>(i.i);

    if (list.empty())
    {
      return nullptr; // Empty WordArray
    }

    // First element is sign bit
    bool isNegative = (list[0] == 1);
    if (isNegative)
    {
      return nullptr; // Cannot convert negative WordArray to uint64_t
    }

    // Check we don't have too many chunks for uint64_t
    // Need at most 2 chunks (plus sign bit) = 3 elements total
    if (list.size() > 3)
    {
      return nullptr; // Too many chunks for uint64_t
    }

    uint64_t result = 0;

    // Process subsequent items as 32-bit chunks in big-endian order
    for (size_t idx = 1; idx < list.size(); idx++)
    {
      // Reinterpret signed int as unsigned to preserve bit pattern
      uint32_t chunk = static_cast<uint32_t>(list[idx]);

      result = (result << 32) | static_cast<uint64_t>(chunk);
    }

    auto* ptr = new uint64_t;
    *ptr = result;
    return ptr;
  }
  else
  {
    return nullptr; // Cannot convert to uint64_t: invalid storage type
  }
}

int Integer::toInt(const Storage& i)
{
  if (std::holds_alternative<int>(i.i))
  {
    return std::get<int>(i.i);
  }
  else if (std::holds_alternative<ints>(i.i))
  {
    // WordArray case - reconstruct from 32-bit chunks
    const ints& list = std::get<ints>(i.i);

    if(list.empty())
    {
      return 0;
    }

    if(list.size() == 2)
    {
      bool isNegative = (list[0] == 1);
      int value = list[1];
      return isNegative ? -value : value;
    }
  }

  return 0;
}

unsigned long* Integer::toUnsignedLong(const Storage& i)
{
  uint64_t* result64 = Integer::toUInt64(i);

  if (result64 == nullptr)
  {
    return nullptr;
  }

  uint64_t value = *result64;
  delete result64;

  // Check if it fits in unsigned long
  if (value > static_cast<uint64_t>(ULONG_MAX))
  {
    return nullptr; // Value too large for unsigned long
  }

  auto* result = new unsigned long;
  *result = static_cast<unsigned long>(value);
  return result;
}

std::string Integer::toHexString(const Storage& i)
{
  // Handle regular int (WORD)
  if(std::holds_alternative<int>(i.i))
  {
    int value = std::get<int>(i.i);
    bool negative = (value < 0);

    // Convert to unsigned to handle negative values safely
    typedef unsigned int uint_t;
    uint_t abs_value;
    if(negative)
    {
      // Careful handling of INT_MIN
      if(value == INT_MIN)
      {
        abs_value = static_cast<uint_t>(-(static_cast<long long>(INT_MIN)));
      }
      else
      {
        abs_value = static_cast<uint_t>(-value);
      }
    }
    else
    {
      abs_value = static_cast<uint_t>(value);
    }

    // Convert to hex using arithmetic (no bit operations)
    if(abs_value == 0)
    {
      return "0";
    }

    std::string result;
    const char hex_digits[] = "0123456789ABCDEF";

    while(abs_value > 0)
    {
      uint_t digit = abs_value % 16;
      result = hex_digits[digit] + result;
      abs_value = abs_value / 16;
    }

    return negative ? ("-" + result) : result;
  }

  // Handle bigint (WORD_ARRAY)
  if(std::holds_alternative<ints>(i.i))
  {
    const ints& bigint = std::get<ints>(i.i);

    if(bigint.empty())
    {
      return "0";
    }

    // First element is sign bit
    bool negative = (bigint[0] == 1);

    // Check if all chunks are zero
    bool all_zero = true;
    for(size_t idx = 1; idx < bigint.size(); idx++)
    {
      if(bigint[idx] != 0)
      {
        all_zero = false;
        break;
      }
    }

    if(all_zero)
    {
      return "0";
    }

    std::string result;
    const char hex_digits[] = "0123456789ABCDEF";

    // Calculate how many hex digits per chunk based on platform int size
    const int nibbles_per_chunk = (sizeof(int) * 8) / 4;

    // Process each int-sized chunk in big-endian word order
    bool started = false; // Skip leading zeros

    for(size_t idx = 1; idx < bigint.size(); idx++)
    {
      // Reinterpret int as unsigned int to preserve bit pattern
      typedef unsigned int uint_t;
      uint_t chunk = static_cast<uint_t>(bigint[idx]);

      // Convert chunk to hex digits using arithmetic
      char chunk_hex[17]; // Max 16 hex digits for 64-bit int + null terminator
      for(int pos = nibbles_per_chunk - 1; pos >= 0; pos--)
      {
        uint_t digit = chunk % 16;
        chunk_hex[pos] = hex_digits[digit];
        chunk = chunk / 16;
      }
      chunk_hex[nibbles_per_chunk] = '\0';

      if(!started)
      {
        // First non-zero chunk - skip leading zeros
        if(static_cast<uint_t>(bigint[idx]) == 0)
        {
          continue;
        }

        // Find first non-zero digit
        int first_nonzero = 0;
        while(first_nonzero < nibbles_per_chunk && chunk_hex[first_nonzero] == '0')
        {
          first_nonzero++;
        }

        result += &chunk_hex[first_nonzero];
        started = true;
      }
      else
      {
        // Subsequent chunks - include all digits (with leading zeros)
        result += chunk_hex;
      }
    }

    if(result.empty())
    {
      return "0";
    }

    return negative ? ("-" + result) : result;
  }

  return "";
}

Storage Integer::zero()
{
  return Integer::make(0);
}

Storage Integer::one()
{
  return Integer::make(1);
}

// Monads
Storage Integer::char_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(integer, NounType::CHARACTER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::enclose_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return WordArray::make(ints({ integer }), NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::enumerate_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);

    ints results(integer);
    std::iota(results.begin(), results.end(), 1);  // iota here refers to the C++/STL version of enumerate

    return WordArray::make(results, NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::expand_impl(const Storage& i)
{
  if (std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    ints results = ints();
    for(int index = 0; index < integer; index++)
    {
      results.push_back(0);
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::format_impl(const Storage& i)
{
  using namespace iota;

  int unicode_minus = static_cast<int>('-');
  int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.

  const Storage zero = Integer::zero();
  const Storage ten = Integer::make(10);
  const Storage offset = Integer::make(unicode_zero);

  if(eval({i, equal, zero}).truth())
  {
    return IotaString::make({unicode_zero});
  }

  ints results = ints();
  Storage working = i;

  bool negative = eval({i, less, zero}).truth();
  if(negative)
  {
    results.push_back(unicode_minus);
    working = eval({i, negate});
  }

  while(eval({working, more, zero}).truth())
  {
    auto digit = eval({working, iota::remainder, ten});
    auto numeral = eval({digit, plus, offset});
    results.insert(results.begin(), Integer::toInt(numeral));
    working = eval({working, integerDivide, ten});
  }

  return IotaString::make(results);
}

Storage Integer::negate_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(-integer, NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::not_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(integer == 0)
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::reciprocal_impl(const Storage& i)
{
  if (std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);
    return Real::make(1.0f / static_cast<float>(integer));
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::size_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(abs(integer), NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
Storage Integer::cut_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints integers = std::get<ints>(x.i);

      if(integer == 0)
      {
        if(integers.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= static_cast<int>(integers.size()))
      {
        ints left = ints(integers.begin(), integers.begin() + integer);
        ints right = ints(integers.begin() + integer, integers.end());

        mixed results = mixed();
        results.insert(results.end(), WordArray::make(left, NounType::LIST));
        results.insert(results.end(), WordArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::cut_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats list = std::get<floats>(x.i);

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
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= static_cast<int>(list.size()))
      {
        floats left = floats(list.begin(), list.begin() + integer);
        floats right = floats(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), FloatArray::make(left, NounType::LIST));
        results.insert(results.end(), FloatArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::cut_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed list = std::get<mixed>(x.i);

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
          results.push_back(x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= static_cast<int>(list.size()))
      {
        mixed left = mixed(list.begin(), list.begin() + integer);
        mixed right = mixed(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), MixedArray::make(left, NounType::LIST));
        results.insert(results.end(), MixedArray::make(right, NounType::LIST));
        return Noun::simplify(MixedArray::make(results, NounType::LIST));
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with two integer arguments
Storage Integer::divide_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      auto fx = static_cast<float>(xi);

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with an integer and a float
Storage Integer::divide_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fx < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int y : xis)
      {
        auto fy = static_cast<float>(y);

        if(y == 0)
        {
        return QuotedSymbol::undefined();
        }

        results.insert(results.end(), fi / fy);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<floats>(x.i))
    {
      floats fis = std::get<floats>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(float fy : fis)
      {
        if(fy < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float result = fi / fy;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({Real::make(fi), divide, y});

        if(result.o == NounType::ERROR)
        {
          return result;
        }
        else if(result.o == NounType::QUOTED_SYMBOL) // :undefined
        {
          mixedResults.push_back(result);
        }
        else if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.push_back(fr);
          mixedResults.push_back(Real::make(fr));
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      return Word::make(ii == xi, NounType::INTEGER);
    }
  }

  const BigNumber bi = Integer::toBigNumber(i);
  const BigNumber bx = Integer::toBigNumber(x);
  return Word::make(bi == bx, NounType::INTEGER);
}

Storage Integer::format2_impl(const Storage& i, const Storage& x)
{
  using namespace iota;

  int xi = 0;
  if(std::holds_alternative<int>(x.i))
  {
    xi = std::get<int>(x.i);
  }
  else if(std::holds_alternative<float>(x.i))
  {
    float fi = std::get<float>(x.i);
    xi = static_cast<int>(fi);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Storage formatted = eval({i, format});
  if(formatted.o == NounType::ERROR)
  {
    return formatted;
  }

  if(xi == 0)
  {
    return formatted;
  }
  else if(xi > 0)
  {
    if(std::holds_alternative<ints>(formatted.i))
    {
      ints characters = std::get<ints>(formatted.i);

      if(xi <= static_cast<int>(characters.size()))
      {
        return formatted;
      }
      else
      {
        int difference = xi - static_cast<int>(characters.size());
        for(int index = 0; index < difference; index++)
        {
          characters.push_back(static_cast<int>(' '));
        }

        return IotaString::make(characters);
      }
    }
  }
  else // xi < 0
  {
    xi = -xi;

    if(std::holds_alternative<ints>(formatted.i))
    {
      ints characters = std::get<ints>(formatted.i);

      if(xi <= static_cast<int>(characters.size()))
      {
        return formatted;
      }
      else
      {
        int difference = xi - static_cast<int>(characters.size());
        for(int index = 0; index < difference; index++)
        {
          characters.insert(characters.begin(), static_cast<int>(' '));
        }

        return IotaString::make(characters);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::integerDivide_impl(const Storage& i, const Storage& x)
{
  // Handle division by zero
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);
    if(xi == 0)
    {
      return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
    }
  }
  else if(std::holds_alternative<ints>(x.i))
  {
    const ints& chunks = std::get<ints>(x.i);
    if(chunks.empty())
    {
      return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
    }

    bool all_zero = true;
    for(size_t idx = 1; idx < chunks.size(); idx++)
    {
      if(chunks[idx] != 0)
      {
        all_zero = false;
        break;
      }
    }

    if(all_zero)
    {
      return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
    }
  }

  // Simple case: both are regular ints and no overflow
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    // Special case: INT_MIN / -1 would overflow
    if(ii == INT_MIN && xi == -1)
    {
      // Fall through to BigNumber
    }
    else
    {
      return Word::make(ii / xi);
    }
  }

  // Use BigNumber for multi-precision or overflow cases
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  // Perform division
  BigNumber quotient = bn_i / bn_x;

  // Convert result back (Integer::make will downgrade to Word if it fits)
  return Integer::make(quotient);
}

// Join
Storage Integer::join_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints({ii, xi});

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::prepend_to_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xi = std::get<ints>(x.i);

      ints results(xi);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::less_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii < xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  BigNumber bi = Integer::toBigNumber(i);
  BigNumber bx = Integer::toBigNumber(x);
  return Word::make(bi < bx ? 1 : 0, NounType::INTEGER);
}

Storage Integer::less_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false0();
}

Storage Integer::less_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii < y)
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
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
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
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, less, y});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
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
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii == xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);
      auto fi = static_cast<float>(ii);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::max_integer(const Storage& i, const Storage& x)
{
  // Simple case: both are regular ints
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    if(ii < xi)
    {
      return x;
    }
    else
    {
      return i;
    }
  }

  // Use BigNumber for comparison with bigints
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  if(bn_i < bn_x)
  {
    return x;
  }
  else
  {
    return i;
  }
}

Storage Integer::max_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false0();
}

Storage Integer::max_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii < y)
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(Float::make(fy));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, less, y});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::min_integer(const Storage& i, const Storage& x)
{
  // Simple case: both are regular ints
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    if(ii > xi)
    {
      return x;
    }
    else
    {
      return i;
    }
  }

  // Use BigNumber for comparison with bigints
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  if(bn_i > bn_x)
  {
    return x;
  }
  else
  {
    return i;
  }
}

Storage Integer::min_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false0();
}

Storage Integer::min_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii > y)
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(Float::make(fy));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, more, y});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::minus_integer(const Storage& i, const Storage& x)
{
  // Simple case: both are regular ints and no overflow
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    // Check for overflow
    int result = ii - xi;

    bool overflow = false;
    if(ii > 0 && xi < 0 && result <= 0) overflow = true;  // positive - negative = overflow positive
    if(ii < 0 && xi > 0 && result >= 0) overflow = true;  // negative - positive = overflow negative

    if(!overflow)
    {
      return Word::make(result);
    }

    // Overflow - fall through to BigNumber
  }

  // Use BigNumber for multi-precision subtraction
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  // Perform subtraction
  BigNumber result = bn_i - bn_x;

  // Convert result back (Integer::make will downgrade to Word if it fits)
  return Integer::make(result);
}

Storage Integer::minus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi - fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::minus_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii - y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, minus, y});
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

Storage Integer::more_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii > xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  BigNumber bi = Integer::toBigNumber(i);
  BigNumber bx = Integer::toBigNumber(x);
  return Word::make(bi > bx ? 1 : 0, NounType::INTEGER);
}

Storage Integer::more_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false0();
}

Storage Integer::more_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii > y)
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
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
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
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, more, y});
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
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
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::plus_integer(const Storage& i, const Storage& x)
{
  // Simple case: both are regular ints and no overflow
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    // Check for overflow by checking if signs match but result sign doesn't
    int result = ii + xi;

    // No overflow if: same signs and result has same sign, or different signs
    bool overflow = false;
    if(ii > 0 && xi > 0 && result <= 0) overflow = true;
    if(ii < 0 && xi < 0 && result >= 0) overflow = true;

    if(!overflow)
    {
      return Word::make(result);
    }

    // Overflow - fall through to BigNumber
  }

  // Use BigNumber for multi-precision addition
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  // Perform addition
  BigNumber result = bn_i + bn_x;

  // Convert result back (Integer::make will downgrade to Word if it fits)
  return Integer::make(result);
}

Storage Integer::plus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi + fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::plus_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii + y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, plus, y});
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

Storage Integer::power_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      auto fi = static_cast<float>(ii);
      auto fx = static_cast<float>(xi);

      float result = powf(fi, fx);
      return Float::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::power_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = powf(fi, fx);
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::power_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      auto fi = static_cast<float>(ii);

      for(int y : xis)
      {
        auto fy = static_cast<float>(y);

        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, power, y});
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

Storage Integer::remainder_integer(const Storage& i, const Storage& x)
{
  // Check for division by zero first
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);
    if(xi == 0)
    {
      return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
    }
  }
  else if(std::holds_alternative<ints>(x.i))
  {
    const ints& chunks = std::get<ints>(x.i);
    if(chunks.empty())
    {
      return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
    }

    bool all_zero = true;
    for(size_t idx = 1; idx < chunks.size(); idx++)
    {
      if(chunks[idx] != 0)
      {
        all_zero = false;
        break;
      }
    }

    if(all_zero)
    {
      return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
    }
  }

  // Simple case: both are regular ints
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    return Word::make(ii % xi);
  }

  // Use BigNumber for multi-precision remainder
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  // Perform remainder operation
  BigNumber result = bn_i % bn_x;

  // Convert result back (Integer::make will downgrade to Word if it fits)
  return Integer::make(result);
}

Storage Integer::remainder_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    // Check for any zeros in the list
    for(int y : xis)
    {
      if(y == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }
    }

    // If i is a simple int, we can optimize
    if(std::holds_alternative<int>(i.i))
    {
      int ii = std::get<int>(i.i);

      ints results = ints();
      for(int y : xis)
      {
        results.push_back(ii % y);
      }

      return WordArray::make(results, NounType::LIST);
    }

    // Otherwise i is a bigint, use BigNumber for each operation
    BigNumber bn_i = Integer::toBigNumber(i);

    ints results = ints();
    for(int y : xis)
    {
      BigNumber bn_y(y);
      BigNumber bn_result = bn_i % bn_y;

      // Convert result back to int (remainder should fit in int if divisor is int)
      Storage result_storage = Integer::make(bn_result);
      if(std::holds_alternative<int>(result_storage.i))
      {
        results.push_back(std::get<int>(result_storage.i));
      }
      else
      {
        // Remainder is too large? This shouldn't happen with int divisor
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::remainder_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, iota::remainder, y});
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

Storage Integer::reshape_integer(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi == -1)
      {
        xi = getInteger(eval({eval({i, size}), integerDivide, Word::make(2)}));
      }

      if(xi > 0)
      {
        ints results = ints();

        for(int index = 0; index < xi; index++)
        {
          results.push_back(ii);
        }

        return WordArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::reshape_integers(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
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

        if(xi == -1)
        {
          lengths.push_back(halfSize);
        }

        // else xi > 0
        lengths.push_back(xi);
      }

      if(lengths.size() == 1)
      {
        int xi = lengths[0];
        Storage sx = Word::make(xi);

        return eval({i, reshape, sx});
      }
      else // xi.size() > 1
      {
        Storage sl = WordArray::make(lengths);
        Storage total = eval({sl, over, times});
        ints rest(lengths.begin(), lengths.end() - 1);

        Storage working = eval({i, reshape, total});

        for(int index = static_cast<int>(rest.size()) - 1; index >= 0; index--)
        {
          int y = rest[index];
          working = eval({working, split, Word::make(y)});
        }

        return working;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::reshape_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      if(!xis.empty())
      {
        if(xis.size() == 1)
        {
          const Storage& xi = xis[0];

          return eval({i, reshape, xi});
        }
        else // xi.size() > 1
        {
          Storage first = xis.front();
          mixed rest(xis.begin() + 1, xis.end());

          Storage result = eval({i, reshape, MixedArray::make(rest)});
          return eval({first, reshape, result});
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::times_integer(const Storage& i, const Storage& x)
{
  // Simple case: both are regular ints and no overflow
  if(std::holds_alternative<int>(i.i) && std::holds_alternative<int>(x.i))
  {
    int ii = std::get<int>(i.i);
    int xi = std::get<int>(x.i);

    // Check for overflow
    // Special cases
    if(ii == 0 || xi == 0)
    {
      return Integer::make(0);
    }

    // Check if multiplication would overflow
    bool overflow = false;

    if(ii > 0 && xi > 0)
    {
      if(ii > INT_MAX / xi) overflow = true;
    }
    else if(ii < 0 && xi < 0)
    {
      if(ii < INT_MAX / xi) overflow = true;
    }
    else if(ii > 0 && xi < 0)
    {
      if(xi < INT_MIN / ii) overflow = true;
    }
    else // ii < 0 && xi > 0
    {
      if(ii < INT_MIN / xi) overflow = true;
    }

    if(!overflow)
    {
      return Word::make(ii * xi);
    }

    // Overflow - fall through to BigNumber
  }

  // Use BigNumber for multi-precision multiplication
  BigNumber bn_i = Integer::toBigNumber(i);
  BigNumber bn_x = Integer::toBigNumber(x);

  // Perform multiplication
  BigNumber result = bn_i * bn_x;

  // Convert result back (Integer::make will downgrade to Word if it fits)
  return Integer::make(result);
}

Storage Integer::times_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    auto fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi * fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::times_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii * y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      auto fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi * fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(const Storage& y : xis)
      {
        Storage result = eval({si, times, y});
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

// Serialization
maybe<Storage> Integer::from_bytes(const bytes& bs, int t) {
  if(t == StorageType::WORD)
  {
    return Word::from_bytes(bs, NounType::INTEGER);
  }
  else
  {
    return std::nullopt;
  }
}

maybe<bytes> Integer::to_bytes(const Storage& i) {
  if (i.o != NounType::INTEGER) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if (std::holds_alternative<ints>(i.i)) {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      } else {
        return std::nullopt;
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Integer::from_conn(Connection& conn, int t) {
  if(t == NounType::INTEGER)
  {
    return Word::from_conn(conn, NounType::INTEGER, nullptr);
  }
  else
  {
    return std::nullopt;
  }
}

void Integer::to_conn(Connection& conn, const Storage& i) {
  if (i.o != NounType::INTEGER) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD:
      {
        // No need to include type here because it is provided by Word::to_conn
        return Word::to_conn(conn, i);
      }

    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          bytes intBytes = squeeze_bigint(integers);

          // Note that we always send NounType::INTEGER and StorageType::WORD, even if we internally represent them as StorageType::WORD_ARRAYs.
          std::vector<char> typeBytes = { static_cast<char>(StorageType::WORD), static_cast<char>(i.o) };
          conn.write(typeBytes);
          conn.write(intBytes);
        } else {
          return;
        }
      }

    default:
      return;
  }
}