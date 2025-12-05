//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <cmath> // This is needed for std::abs, even if the compiler doesn't realize it.
#include <variant>
#include <vector>

#include "character.h"
#include "integer.h"
#include "noun.h"

#include "error.h"
#include <squeeze.h>
#include "../symbols.h"

#include <storage/mixed_array.h>
#include <storage/word.h>
#include <storage/word_array.h>

// Character
void Character::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::ichar, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::enclose, Character::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::format, Character::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::inot, Noun::false1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::size, Character::size_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::evaluate, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::CHARACTER, Monads::evaluate, Noun::identity1);

  // Dyads
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::equal, StorageType::WORD, NounType::CHARACTER, Character::equal_impl);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD, NounType::INTEGER, Character::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::FLOAT, NounType::REAL, Character::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Character::join_character);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Character::prepend_string);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD, NounType::CHARACTER, Character::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::CHARACTER, MonadicAdverbs::converge, Noun::converge_impl);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::CHARACTER, MonadicAdverbs::each, Noun::dispatchMonad);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::CHARACTER, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::USER_MONAD, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage Character::make(const int i)
{
  return Word::make(i, NounType::CHARACTER);
}

Storage Character::make(char c)
{
  return Word::make(static_cast<int>(c), NounType::CHARACTER);
}

Storage Character::make(std::string i) {
  // Parse UTF-8 string to get the UTF-32 codepoint
  if (i.empty()) {
    // Handle error - empty string
    return WordArray::nil(); // or however you want to handle errors
  }

  uint32_t codepoint = 0;
  const unsigned char* bytes = reinterpret_cast<const unsigned char*>(i.c_str());

  if ((bytes[0] & 0x80) == 0) {
    // 1-byte UTF-8 (ASCII)
    codepoint = bytes[0];
  }
  else if ((bytes[0] & 0xE0) == 0xC0) {
    // 2-byte UTF-8
    codepoint = ((bytes[0] & 0x1F) << 6) | (bytes[1] & 0x3F);
  }
  else if ((bytes[0] & 0xF0) == 0xE0) {
    // 3-byte UTF-8
    codepoint = ((bytes[0] & 0x0F) << 12) |
                ((bytes[1] & 0x3F) << 6) |
                (bytes[2] & 0x3F);
  }
  else if ((bytes[0] & 0xF8) == 0xF0) {
    // 4-byte UTF-8
    codepoint = ((bytes[0] & 0x07) << 18) |
                ((bytes[1] & 0x3F) << 12) |
                ((bytes[2] & 0x3F) << 6) |
                (bytes[3] & 0x3F);
  }

  return Word::make(static_cast<int>(codepoint), NounType::CHARACTER);
}

maybe<std::string> Character::to_string(const Storage& i) {
  if(std::holds_alternative<int>(i.i))
  {
    // Get the UTF-32 codepoint from storage
    uint32_t codepoint = static_cast<uint32_t>(std::get<int>(i.i));

    std::string result;

    if (codepoint <= 0x7F) {
      // 1-byte UTF-8 (ASCII range)
      result += static_cast<char>(codepoint);
    }
    else if (codepoint <= 0x7FF) {
      // 2-byte UTF-8
      result += static_cast<char>(0xC0 | (codepoint >> 6));
      result += static_cast<char>(0x80 | (codepoint & 0x3F));
    }
    else if (codepoint <= 0xFFFF) {
      // 3-byte UTF-8
      result += static_cast<char>(0xE0 | (codepoint >> 12));
      result += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
      result += static_cast<char>(0x80 | (codepoint & 0x3F));
    }
    else if (codepoint <= 0x10FFFF) {
      // 4-byte UTF-8
      result += static_cast<char>(0xF0 | (codepoint >> 18));
      result += static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F));
      result += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
      result += static_cast<char>(0x80 | (codepoint & 0x3F));
    }

    return result;
  }

  return std::nullopt;
}

Storage Character::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      const int xi = std::get<int>(x.i);

      return Word::make(ii == xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::enclose_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return WordArray::make({ integer }, NounType::STRING);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Character::size_impl(const Storage& i)
{
  if (std::holds_alternative<int>(i.i))
  {
    const int integer = std::get<int>(i.i);
    return Word::make(std::abs(integer), NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads


// Join
Storage Character::join_scalar(const Storage& i, const Storage& x)
{
  const auto results = mixed({i, x});

  return MixedArray::make(results, NounType::LIST);
}

Storage Character::join_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      const auto results = ints({ii, xi});

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::join_list(const Storage& i, const Storage& x)
{
  const Storage mx = Noun::mix(x);
  if(std::holds_alternative<mixed>(mx.i))
  {
    auto results = std::get<mixed>(mx.i);
    results.insert(results.begin(), i);

    return MixedArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::prepend_string(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      const ints xis = std::get<ints>(x.i);

      ints results(xis);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      const int xi = std::get<int>(x.i);

      if(ii == xi)
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

// Serialization
maybe<Storage> Character::from_bytes(const bytes& bs, const int t) {
  if(t == StorageType::WORD)
  {
    return Word::from_bytes(bs, NounType::CHARACTER);
  }
  else
  {
    return std::nullopt;
  }
}

maybe<bytes> Character::to_bytes(const Storage& i) {
  if (i.o != NounType::CHARACTER) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if (std::holds_alternative<ints>(i.i)) {
        const ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      } else {
        return std::nullopt;
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Character::from_conn(Connection& conn, const int t) {
  if(t == StorageType::WORD)
  {
    return Word::from_conn(conn, NounType::CHARACTER, nullptr);

    // FIXME - add support for StorageType::WORD_ARRAY to represent grapheme clusters
  }
  else
  {
    return std::nullopt;
  }
}

void Character::to_conn(Connection& conn, const Storage& i) {
  if (i.o != NounType::CHARACTER) {
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
          const ints integers = std::get<ints>(i.i);
          const bytes intBytes = squeeze_bigint(integers);

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
