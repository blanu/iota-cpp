//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "float_array.h"

#include "../types.h"
#include "../squeeze.h"

#include <Connection.h>

// FloatArray
maybe<Storage> FloatArray::from_bytes(const bytes& data, int o)
{
  // FIXME
  return std::nullopt;
}

// Encodes a FloatArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x IEEE<32|64>} over join)
bytes FloatArray::to_bytes(const Storage& i)
{
  if(std::holds_alternative<floats>(i.i))
  {
    auto result = bytes();

    const floats fs = std::get<floats>(i.i);

    const int length = static_cast<int>(fs.size());
    bytes lengthBytes = squeeze_int(length);

    result.insert(result.begin(), lengthBytes.begin(), lengthBytes.end());

    for(float f : fs)
    {
      bytes integerBytes = squeeze_floating(floating(f));
      result.insert(result.end(), integerBytes.begin(), integerBytes.end());
    }

    return result;
  }
  else
  {
    return {};
  }
}

maybe<Storage> FloatArray::from_conn(Connection& conn, const int objectType)
{
  varint varsize = expand_conn(conn); // NOLINT
  if(std::holds_alternative<int>(varsize))
  {
    const int size = std::get<int>(varsize);

    auto fs = floats();

    for(int y=0; y<size; y++)
    {
      if(maybe<floating> maybeFloating = expand_conn_floating(conn))
      {
        if(std::holds_alternative<float>(*maybeFloating))
        {
          float f = std::get<float>(*maybeFloating);
          fs.push_back(f);
        }
        else
        {
          const double d = std::get<double>(*maybeFloating);
          fs.push_back(static_cast<float>(d));
        }
      }
      else
      {
        return std::nullopt;
      }
    }

    return FloatArray::make(fs, objectType);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void FloatArray::to_conn(Connection& conn, const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    const ints integers = std::get<ints>(i.i);

    // Always include type in to_conn implementation
    std::vector<char> typeBytes = {static_cast<char>(i.t), static_cast<char>(i.o)};
    conn.write(typeBytes);

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

Storage FloatArray::make(floats x, int o)
{
  return {o, StorageType::FLOAT_ARRAY, x};
}
