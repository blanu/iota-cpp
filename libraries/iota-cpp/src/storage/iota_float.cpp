//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "iota_float.h"

#include "../types.h"
#include "../squeeze.h"

#include "../storage/storage.h"

#include <Connection.h>

// Float
// Storage::from_bytes decodes a byte array into a Float object
// Be careful with this function, it moves x.
maybe<Storage> Float::from_bytes(bytes x, const int o)
{
  if(const maybe<floating> maybeFloating = expand_floating(std::move(x)))
  {
    float f;
    if(std::holds_alternative<float>(*maybeFloating))
    {
      f = std::get<float>(*maybeFloating);
    }
    else
    {
      const double d = static_cast<float>(std::get<double>(*maybeFloating));
      f = static_cast<float>(d);
    }

    return {Float::make(f, o)};
  }
  else
  {
    return std::nullopt;
  }
}

// Encodes a Float into a byte array
// Format: IEEE Float
maybe<bytes> Float::to_bytes(const Storage& i)
{
  if(std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);

    return {squeeze_floating(floating(f))};
  }
  else
  {
    return std::nullopt;
  }
}

maybe<Storage> Float::from_conn(Connection& conn, const int objectType)
{
  if(const maybe<floating> maybeFloating = expand_conn_floating(conn))
  {
    if(std::holds_alternative<float>(*maybeFloating))
    {
      const float f = std::get<float>(*maybeFloating);

      return {Float::make(f, objectType)};
    }
    else
    {
      const double d = std::get<double>(*maybeFloating);

      return {Float::make(static_cast<float>(d), objectType)};
    }
  }
  else
  {
    return std::nullopt;
  }
}

void Float::to_conn(Connection& conn, const Storage& i)
{
  if(std::holds_alternative<float>(i.i))
  {
    // Always include type in to_conn implementation
    std::vector<char> typeBytes = {static_cast<char>(i.t), static_cast<char>(i.o)};
    conn.write(typeBytes);

    float f = std::get<float>(i.i);

    const bytes result = squeeze_floating(floating(f));
    conn.write(result);
  }
}

Storage Float::make(float x, int o)
{
  return {o, StorageType::FLOAT, x};
}

