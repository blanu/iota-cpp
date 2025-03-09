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
maybe<Storage> WordArray::from_bytes(const bytes& x, int o)
{
  // FIXME
  return {Storage(0, StorageType::WORD, 0)};
}

// Encodes a WordArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x squeeze} over join)
bytes WordArray::to_bytes(const Storage &x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    bytes result = bytes();

    ints i = std::get<ints>(x.i);

    int length = static_cast<int>(i.size());
    bytes lengthBytes = squeeze_int(length);

    result.insert(result.begin(), lengthBytes.begin(), lengthBytes.end());

    for(int integer : i)
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

maybe<Storage> WordArray::from_conn(const Connection& conn, int o)
{
  varint varsize = expand_conn(conn);
  if(std::holds_alternative<int>(varsize))
  {
    int size = std::get<int>(varsize);

    ints i = ints();

    for(int y=0; y<size; y++)
    {
      varint varinteger = expand_conn(conn);
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

    return WordArray::make(i, o);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void WordArray::to_conn(const Connection& conn, const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    // Always include type in to_conn implementation
    conn.write({static_cast<char>(i.t), static_cast<char>(i.o)});

    ints integers = std::get<ints>(i.i);

    int length = static_cast<int>(integers.size());
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for(int integer : integers)
    {
      bytes integerBytes = squeeze_int(integer);
      conn.write(integerBytes);
    }
  }
}

Storage WordArray::make(ints x, int o)
{
  return {o, StorageType::WORD_ARRAY, x};
}

