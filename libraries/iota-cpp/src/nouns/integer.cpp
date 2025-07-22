//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <cmath> // This is necessary for std::abs, even if the compiler doesn't realize it.
#include <numeric>
#include <tuple>
#include <vector>

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

// Integer
void Integer::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::ichar, Integer::char_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enclose, Integer::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::expand, Integer::expand_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enumerate, Integer::enumerate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::format, Integer::format_impl);
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
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT, NounType::REAL, Integer::divide_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Integer::divide_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::divide_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Integer::divide_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::equal, StorageType::WORD, NounType::INTEGER, Integer::equal_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD, NounType::INTEGER, Integer::integerDivide_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::INTEGER, Integer::join_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::prepend_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD, NounType::INTEGER, Integer::less_integer);
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
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT, NounType::REAL, Integer::max_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Integer::max_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT, NounType::REAL, Integer::min_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Integer::min_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT, NounType::REAL, Integer::minus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::minus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT, NounType::REAL, Integer::more_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Integer::more_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD, NounType::INTEGER, Integer::plus_integer);
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
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, Integer::remainder_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, Integer::remainder_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::WORD, NounType::INTEGER, Integer::reshape_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, Integer::reshape_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, Integer::reshape_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::WORD, NounType::INTEGER, Integer::times_integer);
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
  int unicode_minus = static_cast<int>('-');
  int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.

  if (std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(integer == 0)
    {
      return IotaString::make({unicode_zero});
    }

    ints results = ints();

    int negative = 0;
    if(integer < 0)
    {
      integer = -integer;
      negative = 1;
    }

    while(integer > 0)
    {
      int digit = integer % 10;
      // Unicode value is located at x + 45 for all x '0' to '9'
      results.insert(results.begin(), digit + unicode_zero);
      integer = integer / 10;
    }

    if(negative)
    {
      results.insert(results.begin(), unicode_minus);
    }

    return IotaString::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      return Word::make(ii / xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
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
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
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
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii - xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii + xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      return Word::make(ii % xi);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::remainder_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii % y);
      }

      return WordArray::make(results, NounType::LIST);
    }
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
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii * xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
    return Word::from_conn(conn, NounType::INTEGER);
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
