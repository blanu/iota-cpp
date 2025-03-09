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

#include "../Connection.h"
#include "../types.h"
#include "../squeeze.h"

#include "../nouns/noun.h"

// MixedArray
// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(bytes x, int o)
{
  return maybe<Storage>(Storage(0, StorageType::WORD, 0));
}

// Encodes a MixedArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x to_bytes} over join)
maybe<bytes> MixedArray::to_bytes(const Storage& i) {
  if (std::holds_alternative<mixed>(i.i)) {
    mixed ii = std::get<mixed>(i.i);

    bytes r = bytes();

    int size = ii.size();
    bytes sizeBytes = squeeze_int(size);

    r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

    for (Storage y : ii) {
      bytes valueBytes = Noun::to_bytes(y);
      r.insert(r.end(), valueBytes.begin(), valueBytes.end());
    }

    return maybe<bytes>(r);
  } else {
    return std::nullopt;
  }
}

maybe<Storage> MixedArray::from_conn(const Connection& conn, int o) {
  varint varsize = expand_conn(conn);
  if (std::holds_alternative<int>(varsize)) {
    int size = std::get<int>(varsize);

    mixed i = mixed();

    for (int y = 0; y < size; y++) {
      if (maybe<Storage> maybeStorage = Noun::from_conn(conn)) {
        i.push_back(*maybeStorage);
      } else {
        return std::nullopt;
      }
    }

    return MixedArray::make(i, o);
  } else {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void MixedArray::to_conn(const Connection& conn, const Storage& x) {
  if (std::holds_alternative<mixed>(x.i)) {
    mixed i = std::get<mixed>(x.i);

    // Always include type in to_conn implementation
    conn.write({ static_cast<char>(x.t), static_cast<char>(x.o) });

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for (Storage y : i) {
      Noun::to_conn(conn, y);
    }
  }
}

Storage MixedArray::make(mixed x, int o) {
  return Storage(o, StorageType::MIXED_ARRAY, x);
}
