//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "float_array.h"

#include "../Connection.h"
#include "../types.h"
#include "../squeeze.h"

// FloatArray
maybe<Storage> FloatArray::from_bytes(const bytes& x, int o)
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
    bytes result = bytes();

    floats fs = std::get<floats>(i.i);

    int length = static_cast<int>(fs.size());
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

maybe<Storage> FloatArray::from_conn(const Connection& conn, int o)
{
  varint varsize = expand_conn(conn);
  if(std::holds_alternative<int>(varsize))
  {
    int size = std::get<int>(varsize);

    floats fs = floats();

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
          double d = std::get<double>(*maybeFloating);
          fs.push_back(static_cast<float>(d));
        }
      }
      else
      {
        return std::nullopt;
      }
    }

    return FloatArray::make(fs, o);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void FloatArray::to_conn(const Connection& conn, const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    // Always include type in to_conn implementation
    conn.write({static_cast<char>(i.t), static_cast<char>(i.o)});

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

Storage FloatArray::make(floats x, int o)
{
  return {o, StorageType::FLOAT_ARRAY, x};
}
