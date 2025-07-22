//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <utility>
#include <vector>
#include <variant>
#include <algorithm>

#include "iota_string.h"
#include "noun.h"
#include "list.h"
#include "integer.h"
#include "character.h"
#include "quoted_symbol.h"

#include <squeeze.h>
#include "../symbols.h"
#include "error.h"
#include "../verbs.h"
#include "../api.h"
#include "../adverbs.h"

#include <storage/word.h>
#include <storage/ion_float.h>
#include <storage/word_array.h>
#include <storage/mixed_array.h>

// String
void IotaString::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::atom, IotaString::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::first, IotaString::first_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::format, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::gradeDown, IotaString::gradeDown_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::gradeUp, IotaString::gradeUp_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::group, IotaString::group_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::inot, IotaString::not_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::reverse, IotaString::reverse_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::size, IotaString::size_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, IotaString::amend_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::equal, StorageType::WORD_ARRAY, NounType::STRING, IotaString::equal_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::find, StorageType::WORD, NounType::CHARACTER, IotaString::find_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, IotaString::find_string);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD, NounType::INTEGER, IotaString::form_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::FLOAT, NounType::REAL, IotaString::form_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD_ARRAY, NounType::LIST, IotaString::form_list);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::FLOAT_ARRAY, NounType::LIST, IotaString::form_list);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::MIXED_ARRAY, NounType::LIST, IotaString::form_list);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD, NounType::CHARACTER, IotaString::form_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD_ARRAY, NounType::STRING, Noun::identity2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, IotaString::form_quoted_symbol);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::index, StorageType::WORD, NounType::INTEGER, IotaString::index_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, IotaString::index_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD, NounType::CHARACTER, IotaString::append_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, IotaString::join_string);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, IotaString::match_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::rotate, StorageType::WORD, NounType::INTEGER, IotaString::rotate_integer);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::split, StorageType::WORD, NounType::INTEGER, IotaString::split_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, IotaString::split_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::take, StorageType::WORD, NounType::INTEGER, IotaString::take_integer);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, MonadicAdverbs::each, IotaString::each_impl);

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::USER_MONAD, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

// Be careful with this function, it moves i.
Storage IotaString::make(ints i)
{
  return WordArray::make(std::move(i), NounType::STRING);
}

Storage IotaString::makeEmpty()
{
  return WordArray::make(ints(), NounType::STRING);
}

Storage IotaString::atom_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    const ints chars = std::get<ints>(i.i);

    if (chars.empty())
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

Storage IotaString::first_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    const ints chars = std::get<ints>(i.i);

    if (chars.empty())
    {
      return Word::make(EMPTY, NounType::ERROR);
    }

    const int c = chars.front();

    return Word::make(c, NounType::CHARACTER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::gradeDown_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    auto integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());

    for (int index = 0; index < static_cast<int>(results.size()); ++index)
    {
      results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](const int x, const int y)
    {
      return integers[x] > integers[y];
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

Storage IotaString::gradeUp_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    auto integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());

    for (int index = 0; index < static_cast<int>(results.size()); ++index)
    {
      results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](const int x, const int y)
    {
      return integers[x] < integers[y];
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

Storage IotaString::not_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    const ints integers = std::get<ints>(i.i);

    if (integers.empty())
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

Storage IotaString::reverse_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers);
    std::reverse(results.begin(), results.end());

    return WordArray::make(results, NounType::STRING);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::size_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints integers = std::get<ints>(i.i);

    const int result = static_cast<int>(integers.size());

    return Word::make(result, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::group_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    const ints items = std::get<ints>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    auto firsts=std::unordered_map<int, int>();

    // Groups sorted by the first index in each group
    auto groups=std::map<int, ints>();

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
        const auto group = ints({index + 1});

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

    auto results = mixed();
    for (auto &[fst, snd] : groups)
    {
      const ints group = snd;
      results.push_back(WordArray::make(group));
    }

    return MixedArray::make(results);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
Storage IotaString::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      const ints xis = std::get<ints>(x.i);

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
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::find_character(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    auto results = ints();

    for(int index = 0; index < static_cast<int>(iis.size()); index++)
    {
      Storage si = Character::make(iis[index]);
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

Storage IotaString::find_string(const Storage& i, const Storage& x)
{
  using namespace iota;

  if(std::holds_alternative<ints>(i.i))
  {
    auto iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      auto xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        Storage si = Integer::make(1 + static_cast<int>(iis.size()));
        return eval({si, enumerate});
      }

      auto results = ints();

      for(int index = 0; index < static_cast<int>(iis.size()); index++)
      {
        int found = true;
        for(int xindex = 0; xindex < static_cast<int>(xis.size()); xindex++)
        {
          int offset = index + xindex;
          if(offset >= static_cast<int>(iis.size()))
          {
            found = false;
            break;
          }

          Storage si = Character::make(iis[offset]);
          Storage sx = Character::make(xis[xindex]);
          Storage matched = eval({si, match, sx});
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::form_integer(const Storage& i, const Storage& x)
{
  constexpr int unicode_minus = static_cast<int>('-');
  constexpr int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.

  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    int first = 1;
    int negative = 0;
    int result = 0;
    for(const int y : iis)
    {
      if(first)
      {
        first = 0;

        if(y == unicode_minus)
        {
          negative = 1;
          continue;
        }
      }

      const int digit = y - unicode_zero;
      if((digit >= 0) && (digit <= 9))
      {
        result = result * 10;
        result = result + digit;
      }
      else
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
    }

    if(negative)
    {
      return Integer::make(-result);
    }
    else
    {
      return Integer::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::form_real(const Storage& i, const Storage& x)
{
  constexpr int unicode_minus = static_cast<int>('-');
  constexpr int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.
  constexpr int unicode_period = static_cast<int>('.');

  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    int first = 1;
    int negative = 0;
    int decimalFound = 0;
    int integerPart = 0;
    int fractionalPart = 0;
    float fractionalPower = 1;
    for(const int y : iis)
    {
      if(first)
      {
        first = 0;

        if(y == unicode_minus)
        {
          negative = 1;
          continue;
        }
      }

      if(y == unicode_period)
      {
        if(decimalFound)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }
        else
        {
          decimalFound = 1;
          continue;
        }
      }

      const int digit = y - unicode_zero;
      if((digit >= 0) && (digit <= 9))
      {
        if(decimalFound)
        {
          fractionalPart = fractionalPart * 10;
          fractionalPart = fractionalPart + digit;

          fractionalPower = fractionalPower * 10.0f;
        }
        else
        {
          integerPart = integerPart * 10;
          integerPart = integerPart + digit;
        }
      }
      else
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
    }

    const auto integerFloat = static_cast<float>(integerPart);
    const auto fractionalFloat = static_cast<float>(fractionalPart);
    float result = integerFloat + (fractionalFloat / fractionalPower);

    if(negative)
    {
      result = -result;
    }

    return Float::make(result);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}


Storage IotaString::form_list(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({Noun::mix(x), eachRight, form, i});
}

Storage IotaString::form_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(static_cast<int>(iis.size()) == 1)
    {
      const int result = iis[0];
      return Character::make(result);
    }
    else
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::form_quoted_symbol(const Storage& i, const Storage& x)
{
  constexpr int unicode_colon = static_cast<int>(':');

  if(std::holds_alternative<ints>(i.i))
  {
    auto result = ints(std::get<ints>(i.i));
    if(result.front() == unicode_colon)
    {
      result.erase(result.begin());
    }

    return QuotedSymbol::make(result);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::index_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      const int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= static_cast<int>(iis.size()))
      {
        const int result = iis[xi - 1];
        return Word::make(result, NounType::CHARACTER);
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      const ints xis = std::get<ints>(x.i);

      auto results = ints();
      for(const int xi : xis)
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

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage IotaString::append_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      const int xi = std::get<int>(x.i);

      ints results(iis);
      results.insert(results.end(), xi);

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::join_string(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      auto xis = std::get<ints>(x.i);

      ints results(iis);
      results.insert(results.end(), xis.begin(), xis.end());

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      const ints xis = std::get<ints>(x.i);

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
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::rotate_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    auto iis = std::get<ints>(i.i);

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
        const int offset = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return IotaString::make(results);
      }
      else // x < 0
      {
        xi = -xi;

        const int offset = xi % static_cast<int>(iis.size());

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return IotaString::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::split_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    const int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      const ints iis = std::get<ints>(i.i);

      if(xi > 0)
      {
        if(xi >= static_cast<int>(iis.size()))
        {
          auto results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        auto results = mixed();

        auto result = ints();
        for(int ii : iis)
        {
          result.push_back(ii);

          if(result.size() == xi)
          {
            results.push_back(IotaString::make(result));
            result = ints();
          }
        }

        if(!result.empty())
        {
          results.push_back(IotaString::make(result));
        }

        return MixedArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::split_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    const ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      auto iis = std::get<ints>(i.i);

      auto results = mixed();

      int count = 0;
      int index = 0;
      while(count < static_cast<int>(iis.size()))
      {
        const int y = xis[index++ % static_cast<int>(xis.size())]; // cycle

        if(count + y > static_cast<int>(iis.size()))
        {
          const ints result(iis.begin(), iis.end());
          results.push_back(IotaString::make(result));
          break;
        }
        else
        {
          const ints result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(IotaString::make(result));
        }

        count = count + y;
      }

      if(count < static_cast<int>(iis.size()))
      {
        const ints result(iis.begin() + count, iis.end());
        results.push_back(IotaString::make(result));
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::take_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      const ints iis = std::get<ints>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return IotaString::makeEmpty();
      }

      if(xi > 0)
      {
        auto results = ints();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % static_cast<int>(iis.size())]); // cycle through iis
        }

        return IotaString::make(results);
      }
      else // xi < 0
      {
        xi = -xi;
        const int start = static_cast<int>(iis.size()) - (xi % static_cast<int>(iis.size()));

        auto results = ints();
        for(int offset = 0; offset < xi; offset++)
        {
          const int index = (start + offset) % static_cast<int>(iis.size());
          results.push_back(iis[index]);
        }

        return IotaString::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Monadic Adverbs
Storage IotaString::each_impl(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints iis = std::get<ints>(i.i);

    auto results = mixed();
    for(const int y : iis)
    {
      Storage result = Noun::dispatchMonad(Character::make(y), f);

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

// Serialization
maybe<Storage> IotaString::from_bytes(const bytes& bs, const int t) {
  if(t == StorageType::WORD_ARRAY)
  {
    return WordArray::from_bytes(bs, NounType::STRING);
  }
  else
  {
    return std::nullopt;
  }
}

maybe<bytes> IotaString::to_bytes(const Storage& i) {
  if (i.o != NounType::STRING) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      return WordArray::to_bytes(i);

    default:
      return std::nullopt;
  }
}

maybe<Storage> IotaString::from_conn(Connection& conn, const int t) {
  if(t == StorageType::WORD_ARRAY)
  {
    return WordArray::from_conn(conn, NounType::STRING);
  }
  else
  {
    return std::nullopt;
  }
}

void IotaString::to_conn(Connection& conn, const Storage& i) {
  if (i.o != NounType::STRING) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        // No need to include type here because it is provided by Word::to_conn
        return WordArray::to_conn(conn, i);
      }

    default:
      return;
  }
}
