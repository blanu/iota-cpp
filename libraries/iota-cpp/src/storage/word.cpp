//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "word.h"
#include "storage.h"
#include "word_array.h"

#include "../squeeze.h"
#include "../types.h"

#include <Connection.h>

// Word
// Storage::from_bytes decodes a byte array into a Word object
maybe<Storage> Word::from_bytes(const bytes& data, const int o)
{
  varint varinteger = expand_int_from_bytes(data); // NOLINT
  if(std::holds_alternative<int>(varinteger))
  {
    const int integer = std::get<int>(varinteger);
    return Word::make(integer, o);
  }
  else
  {
    // varint results for Words are not yet fully implemented
    return std::nullopt;
  }
}

// Encodes a Word into a byte array
// Format: int:i.squeeze
bytes Word::to_bytes(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int integer = std::get<int>(i.i);
    bytes result = squeeze_int(integer);
    return result;
  }
  else
  {
    return {};
  }
}

maybe<Storage> Word::from_conn(Connection& conn, const int objectType)
{
  varint varinteger = expand_conn(conn); // NOLINT

  if(std::holds_alternative<int>(varinteger))
  {
    const int integer = std::get<int>(varinteger);
    return {Word::make(integer, objectType)};
  }
  else
  {
    const ints integers = std::get<ints>(varinteger);
    return {WordArray::make(integers, objectType)};
  }
}

void Word::to_conn(Connection& conn, const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    // Always include type in to_conn implementation
    std::vector<char> typeBytes = {static_cast<char>(i.t), static_cast<char>(i.o)};
    conn.write(typeBytes);

    const int integer = std::get<int>(i.i);
    const bytes result = squeeze_int(integer);

    conn.write(result);
  }
}

Storage Word::make(int x, int o)
{
  return {o, StorageType::WORD, x};
}

