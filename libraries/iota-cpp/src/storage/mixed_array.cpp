//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "mixed_array.h"
#include "storage.h"

#include "../types.h"
#include "../squeeze.h"

#include "../nouns/noun.h"

#include <Connection.h>

// MixedArray
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(const bytes& data, const int o)
{
  return {Storage(o, StorageType::WORD, 0)};
}

// Encodes a MixedArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x to_bytes} over join)
maybe<bytes> MixedArray::to_bytes(const Storage& storage) {
  if (std::holds_alternative<mixed>(storage.i)) {
    const mixed ii = std::get<mixed>(storage.i);

    auto r = bytes();

    const int size = static_cast<int>(ii.size());
    bytes sizeBytes = squeeze_int(size);

    r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

    for (const Storage& y : ii) {
      bytes valueBytes = Noun::to_bytes(y);
      r.insert(r.end(), valueBytes.begin(), valueBytes.end());
    }

    return {r};
  }
  else
  {
    return std::nullopt;
  }
}

maybe<Storage> MixedArray::from_conn(Connection& conn, const int objectType)
{
  varint varsize = expand_conn(conn); // NOLINT
  if (std::holds_alternative<int>(varsize))
  {
    const int size = std::get<int>(varsize);

    auto i = mixed();

    for(int y = 0; y < size; y++)
    {
      if(maybe<Storage> maybeStorage = Noun::from_conn(conn))
      {
        i.push_back(*maybeStorage);
      }
      else
      {
        return std::nullopt;
      }
    }

    return MixedArray::make(i, objectType);
  }

  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void MixedArray::to_conn(Connection& conn, const Storage& i)
{
  if (std::holds_alternative<mixed>(i.i))
  {
    const mixed ms = std::get<mixed>(i.i);

    // Always include type in to_conn implementation
    std::vector<char> typeBytes = { static_cast<char>(i.t), static_cast<char>(i.o) };
    conn.write(typeBytes);

    const int length = static_cast<int>(ms.size());
    const bytes lengthBytes = squeeze_int(static_cast<int>(length));

    conn.write(lengthBytes);

    for (const Storage& y : ms)
    {
      Noun::to_conn(conn, y);
    }
  }
}

Storage MixedArray::make(mixed x, int o)
{
  return {o, StorageType::MIXED_ARRAY, x};
}
