//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "word_array.h"
#include "storage.h"

#include "../squeeze.h"

// WordArray
Storage WordArray::nil()
{
  return WordArray::make(ints(), NounType::LIST);
}

Storage WordArray::nil1(const Storage& i)
{
  return WordArray::make(ints(), NounType::LIST);
}

Storage WordArray::nil2(const Storage& i, const Storage& x)
{
  return WordArray::make(ints(), NounType::LIST);
}

// Storage::from_bytes decodes a byte array into a WordArray object
maybe<Storage> WordArray::from_bytes(const bytes& data, int o)
{
  // FIXME
  return {Storage(0, StorageType::WORD, 0)};
}

// Encodes a WordArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x squeeze} over join)
bytes WordArray::to_bytes(const Storage &storage)
{
  if(std::holds_alternative<ints>(storage.i))
  {
    auto result = bytes();

    const auto i = std::get<ints>(storage.i);

    const int length = static_cast<int>(i.size());
    bytes lengthBytes = squeeze_int(length);

    result.insert(result.begin(), lengthBytes.begin(), lengthBytes.end());

    for(const int integer : i)
    {
      bytes integerBytes = squeeze_int(integer);
      result.insert(result.end(), integerBytes.begin(), integerBytes.end());
    }

    return result;
  }
  else
  {
    return {};
  }
}

maybe<Storage> WordArray::from_conn(Connection& conn, const int objectType)
{
  varint varsize = expand_conn(conn); // NOLINT
  if(std::holds_alternative<int>(varsize))
  {
    const int size = std::get<int>(varsize);

    auto i = ints();

    for(int y=0; y<size; y++)
    {
      varint varinteger = expand_conn(conn); // NOLINT
      if(std::holds_alternative<int>(varinteger))
      {
        int integer = std::get<int>(varinteger);
        i.push_back(integer);
      }
      else
      {
        // Varint elements in Word arrays not yet supported
        return std::nullopt;
      }
    }

    return WordArray::make(i, objectType);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void WordArray::to_conn(Connection& conn, const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    // Always include type in to_conn implementation
    std::vector<char> typeBytes = {static_cast<char>(i.t), static_cast<char>(i.o)};
    conn.write(typeBytes);

    const auto integers = std::get<ints>(i.i);

    const int length = static_cast<int>(integers.size());
    const bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for(const int integer : integers)
    {
      const bytes integerBytes = squeeze_int(integer);
      conn.write(integerBytes);
    }
  }
}

Storage WordArray::make(ints x, int o)
{
  return {o, StorageType::WORD_ARRAY, x};
}

