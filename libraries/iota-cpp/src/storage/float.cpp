//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "float.h"

#include "../Connection.h"
#include "../types.h"
#include "../squeeze.h"

#include "../storage/storage.h"

// Float
// Storage::from_bytes decodes a byte array into a Float object
// Be careful with this function, it moves x.
maybe<Storage> Float::from_bytes(bytes x, int o)
{
  if(maybe<floating> maybeFloating = expand_floating(std::move(x)))
  {
    float f;
    if(std::holds_alternative<float>(*maybeFloating))
    {
      f = std::get<float>(*maybeFloating);
    }
    else
    {
      double d = static_cast<float>(std::get<double>(*maybeFloating));
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

maybe<Storage> Float::from_conn(const Connection& conn, int o)
{
  if(maybe<floating> maybeFloating = expand_conn_floating(conn))
  {
    if(std::holds_alternative<float>(*maybeFloating))
    {
      float f = std::get<float>(*maybeFloating);

      return {Float::make(f, o)};
    }
    else
    {
      double d = std::get<double>(*maybeFloating);

      return {Float::make(static_cast<float>(d), o)};
    }
  }
  else
  {
    return std::nullopt;
  }
}

void Float::to_conn(const Connection& conn, const Storage& i)
{
  if(std::holds_alternative<float>(i.i))
  {
    // Always include type in to_conn implementation
    conn.write({static_cast<char>(i.t), static_cast<char>(i.o)});

    float f = std::get<float>(i.i);

    bytes result = squeeze_floating(floating(f));
    conn.write(result);
  }
}

Storage Float::make(float x, int o)
{
  return {o, StorageType::FLOAT, x};
}

