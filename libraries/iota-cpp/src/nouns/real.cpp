//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <vector>
#include <variant>
#include <string>
#include <limits>
#include <cmath>

#include "real.h"
#include "noun.h"
#include "integer.h"
#include "iota_string.h"
#include "quoted_symbol.h"

#include "../squeeze.h"
#include "../symbols.h"
#include "../error.h"
#include "../verbs.h"

#include "../storage/word.h"
#include "../storage/iota_float.h"
#include "../storage/word_array.h"
#include "../storage/float_array.h"
#include "../storage/mixed_array.h"

// Real
// Registration
void Real::initialize() {
  // Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::enclose, Real::enclose_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::floor, Real::floor_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::format, Real::format_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::negate, Real::negate_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::inot, Real::not_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::reciprocal, Real::reciprocal_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::size, Real::size_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::evaluate, Noun::identity1);

  // Dyads
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::WORD, NounType::INTEGER, Real::divide_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::FLOAT, NounType::REAL, Real::divide_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Real::divide_integers);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Real::divide_reals);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Real::divide_mixed);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_scalar);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::FLOAT, NounType::REAL, Real::join_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Real::prepend_to_reals);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::format2, StorageType::WORD, NounType::INTEGER, Real::format2_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::format2, StorageType::FLOAT, NounType::REAL, Real::format2_impl);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::WORD, NounType::INTEGER, Real::less_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::FLOAT, NounType::REAL, Real::less_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, Real::less_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, Real::less_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, Real::less_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD, NounType::INTEGER, Real::match_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::FLOAT, NounType::REAL, Real::match_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::WORD, NounType::INTEGER, Real::max_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::FLOAT, NounType::REAL, Real::max_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Real::max_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Real::max_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Real::max_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::WORD, NounType::INTEGER, Real::min_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::FLOAT, NounType::REAL, Real::min_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Real::min_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Real::min_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Real::min_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::WORD, NounType::INTEGER, Real::minus_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::FLOAT, NounType::REAL, Real::minus_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Real::minus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Real::minus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Real::minus_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::WORD, NounType::INTEGER, Real::more_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::FLOAT, NounType::REAL, Real::more_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Real::more_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Real::more_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Real::more_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::WORD, NounType::INTEGER, Real::plus_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::FLOAT, NounType::REAL, Real::plus_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, Real::plus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, Real::plus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, Real::plus_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::WORD, NounType::INTEGER, Real::power_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::FLOAT, NounType::REAL, Real::power_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, Real::power_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, Real::power_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, Real::power_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::WORD, NounType::INTEGER, Real::times_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::FLOAT, NounType::REAL, Real::times_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, Real::times_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, Real::times_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, Real::times_list);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::each, Noun::dispatchMonad);
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::eachPair, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::over, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::scanOver, Noun::enclose2);

  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage Real::make(float i)
{
  return Float::make(i, NounType::REAL);
}

Storage Real::zero()
{
  return Real::make(0.0);
}

Storage Real::one()
{
  return Real::make(1.0);
}

Storage Real::enclose_impl(const Storage& i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);
    return FloatArray::make(floats({ f }), NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::floor_impl(const Storage& i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);
    int result = (int)std::floor(f);

    return Word::make(result, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::format_impl(const Storage& i)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    // This code prints a float with the minimum number of digits necessary to not lose precision
    std::vector<char> buffer = std::vector<char>(256);
    int formattedLength = std::snprintf(buffer.data(), buffer.size(), "%.*g", std::numeric_limits<double>::max_digits10, fi);
    std::string s = std::string(buffer.data());

    ints results = ints();
    int needDecimal = 1;
    for(char c : s)
    {
      results.push_back(static_cast<int>(c));
      if(c == '.')
      {
        needDecimal = 0;
      }
    }

    if(needDecimal)
    {
      results.push_back(static_cast<int>('.'));
      results.push_back(static_cast<int>('0'));
    }

    return IotaString::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::negate_impl(const Storage& i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(-f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::not_impl(const Storage& i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);

    if(abs(f) < Float::tolerance)
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

Storage Real::reciprocal_impl(const Storage& i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(1.0 / f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::size_impl(const Storage& i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(abs(f), NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
// Floating-point division with a float and an integer
Storage Real::divide_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      float fx = static_cast<float>(xi);

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with two floats
Storage Real::divide_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

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

Storage Real::divide_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(int y : xis)
      {
        if(y == 0)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fy = static_cast<float>(y);
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

Storage Real::divide_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

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

Storage Real::divide_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(Storage y : xis)
      {
        Storage result = divide(Float::make(fi, NounType::REAL), y);

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

Storage Real::format2_impl(const Storage& i, const Storage& x)
{
  Storage formatted = format(i);
  if(formatted.o == NounType::ERROR)
  {
    return formatted;
  }

  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(xi == 0)
    {
      return formatted;
    }
    else if(xi > 0)
    {
      if(std::holds_alternative<ints>(formatted.i))
      {
        ints characters = std::get<ints>(formatted.i);

        if(xi <= characters.size())
        {
          return formatted;
        }
        else
        {
          int difference = xi - characters.size();
          for(int index = 0; index < difference; index++)
          {
            characters.push_back((int)' ');
          }

          return IotaString::make(characters);
        }
      }
    }
    else if(xi < 0)
    {
      xi = -xi;

      if(std::holds_alternative<ints>(formatted.i))
      {
        ints characters = std::get<ints>(formatted.i);

        if(xi <= characters.size())
        {
          return formatted;
        }
        else
        {
          int difference = xi - characters.size();
          for(int index = 0; index < difference; index++)
          {
            characters.insert(characters.begin(), (int)' ');
          }

          return IotaString::make(characters);
        }
      }
    }
  }
  else if(std::holds_alternative<float>(x.i))
  {
    float fi = std::get<float>(x.i);

    // We can ignore the sign on float format parameters
    int negative = 0;
    if(fi < 0)
    {
      fi = -fi;
      negative = 1;
    }

    int integerPartTarget = static_cast<int>(fi);
    int fractionalPartTarget = static_cast<int>((fi - integerPartTarget) * powf(10, Float::precision));
    while((fractionalPartTarget != 0) && (fractionalPartTarget % 10 == 0))
    {
      fractionalPartTarget = fractionalPartTarget / 10;
    }

    if((integerPartTarget == 0) && (fractionalPartTarget == 0))
    {
      return formatted;
    }
    else if(fractionalPartTarget == 0)
    {
      if(negative)
      {
        return format2(i, Integer::make(-integerPartTarget));
      }
      else
      {
        return format2(i, Integer::make(integerPartTarget));
      }
    }

    if(std::holds_alternative<ints>(formatted.i))
    {
      ints characters = std::get<ints>(formatted.i);

      int decimalIndex = -1;
      for(int index = 0; index < characters.size(); index++)
      {
        int character = characters[index];
        if(character == static_cast<int>('.'))
        {
          decimalIndex = index;
          break;
        }
      }

      if(decimalIndex == -1)
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
      }

      ints integerPart = ints(characters.begin(), characters.begin() + decimalIndex);
      ints fractionalPart = ints(characters.begin() + decimalIndex + 1, characters.end());

      if(integerPart.size() < integerPartTarget)
      {
        int difference = integerPartTarget - integerPart.size();
        for(int index = 0; index < difference; index++)
        {
          integerPart.insert(integerPart.begin(), static_cast<int>(' '));
        }
      }

      if(fractionalPart.size() < fractionalPartTarget)
      {
        int difference = fractionalPartTarget - fractionalPart.size();
        for(int index = 0; index < difference; index++)
        {
          fractionalPart.push_back(static_cast<int>('0'));
        }
      }

      ints results = ints();
      results.insert(results.end(), integerPart.begin(), integerPart.end());
      results.insert(results.end(), static_cast<int>('.'));
      results.insert(results.end(), fractionalPart.begin(), fractionalPart.end());

      return IotaString::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage Real::join_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results = floats({ii, xi});

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::prepend_to_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xi = std::get<floats>(x.i);

      floats results(xi);
      results.insert(results.begin(), ii);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::less_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

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

  return Noun::false1(i);
}

Storage Real::less_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

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

  return Noun::false1(i);
}

Storage Real::less_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

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
    else if(std::holds_alternative<floats>(x.i))
    {
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
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
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

Storage Real::max_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

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

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::max_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

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

  return Noun::false1(i);
}

Storage Real::max_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(Word::make(y));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(fy);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
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

Storage Real::min_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

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

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::min_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

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

  return Noun::false1(i);
}

Storage Real::min_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(Word::make(y));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(fy);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
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

Storage Real::minus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi - fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::minus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi - fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::minus_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
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
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = minus(si, y);
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

Storage Real::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(abs(fi - fx) < Float::tolerance)
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

Storage Real::more_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

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

  return Noun::false1(i);
}

Storage Real::more_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

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

  return Noun::false1(i);
}

Storage Real::more_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

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
    else if(std::holds_alternative<floats>(x.i))
    {
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
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
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

Storage Real::plus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi + fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::plus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi + fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::plus_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
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
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = plus(si, y);
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

Storage Real::power_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(powf(fi, fx));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::power_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(powf(fi, fx));
    }
  }

  return Noun::false1(i);
}

Storage Real::power_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
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
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = power(si, y);
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

Storage Real::times_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi * fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::times_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi * fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::times_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi * fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
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
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = times(si, y);
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
maybe<Storage> Real::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::FLOAT:
      return Float::from_bytes(bs, NounType::REAL);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Real::to_bytes(const Storage& i) {
  if (i.o != NounType::REAL) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::FLOAT:
      return Float::to_bytes(i);

    default:
      return std::nullopt;
  }
}

maybe<Storage> Real::from_conn(const Connection& conn, int t) {
  switch (t) {
    case StorageType::FLOAT:
      return Float::from_conn(conn, NounType::REAL);

    default:
      return std::nullopt;
  }
}

void Real::to_conn(const Connection& conn, const Storage& i) {
  if (i.o != NounType::REAL) {
    return;
  }

  switch (i.t) {
    case StorageType::FLOAT:
      {
        // No need to include type here because it is provided by Float::to_conn
        return Float::to_conn(conn, i);
      }

    default:
      return;
  }
}
