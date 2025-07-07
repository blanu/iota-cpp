#include <cstring> // only for std::memcpy, we never use C strings
#include <variant>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

#include "squeeze.h"
#include "types.h"

// int

// Encode an integer in the fewest number of bytes, plus a 1-byte length to tell us how many bytes that is.
bytes squeeze_int(int value)
{
  // Allocate the result
  bytes r;

  // The only case where the length can be zero is for the number 0.
  if(value == 0)
  {
    r.push_back(0);
    return r;
  }

  // Remember if the integer was positive or negative. If negative, we will make the length negative later.
  // Regardless, we end up with a positive integer for encoding.
  // Positive integers are more straightforward to encode.
  int negative = 0;
  if(value < 0)
  {
    negative = 1;
    value = -value;
  }

  // Determine how many bytes we need to encode the integer by removing zero bytes from the top end.
  // Note that this algorithm does not care about endianness and accommodates any word size.
  while(value != 0)
  {
    // Get each byte of the integer separately so that we can count how many bytes we need.
    r.insert(r.begin(), static_cast<char>(value & 0xFF));
    value = value >> 8;
  }

  char length = static_cast<char>(r.size());

  // If the integer is negative, we make the length byte negative as well
  // The length byte goes at the beginning of the encoding
  if(negative)
  {
    length = static_cast<char>(length | 0x80);
  }

  r.insert(r.begin(), length);

  return r;
}

bytes squeeze_bigint(ints value)
{
  // Allocate the result
  bytes r;

  // Remember if the integer was positive or negative. If negative, we will make the length negative later.
  // Regardless, we end up with a positive integer for encoding.
  // Positive integers are more straightforward to encode.
  const int negative = value.at(0);
  value.erase(value.begin());

  for(const int signedInteger : value)
  {
    auto unsignedInteger = static_cast<unsigned int>(signedInteger);

    auto integerBytes = bytes();
    for(int offset=0; offset<sizeof(unsignedInteger); offset++)
    {
      // Get each byte of the integer separately, encoding all bytes, including zeros
      integerBytes.insert(integerBytes.begin(), static_cast<char>(unsignedInteger & 0xFF));
      unsignedInteger = unsignedInteger >> 8;
    }

    r.insert(r.end(), integerBytes.begin(), integerBytes.end());
  }

  char length = static_cast<char>(r.size());

  // If the integer is negative, we make the length byte negative as well
  // The length byte goes at the beginning of the encoding
  if(negative)
  {
    length = static_cast<char>(length | 0x80);
  }

  r.insert(r.begin(), length);

  return r;
}

bytes squeeze_varint(const varint &value)
{
  if(std::holds_alternative<int>(value))
  {
    const int integer = std::get<int>(value);
    return squeeze_int(integer);
  }
  else
  {
    const auto integers = std::get<ints>(value);
    return squeeze_ints(integers);
  }
}

std::tuple<varint, bytes> expand_int(bytes value)
{
  // If input vector is empty, we have nothing to parse
  if(value.empty())
  {
    return std::make_tuple(0, bytes());
  }

  // The first byte of the input array is the length at the beginning of the array with the integer for us to parse, the rest of the array is extra
  int integerLength = static_cast<unsigned char>(value.front());

  // The only case where the length can be zero is for the number 0.
  if(integerLength == 0)
  {
    bytes rest(value.begin() + 1, value.end());
    return std::make_tuple(0, rest);
  }

  // We encode if the integer is positive or negative by using a positive or negative length
  int negative = 0;
  if(integerLength & 0x80) // Check the sign bit & 0b10000000
  {
    negative = 1;
    integerLength = integerLength & 0x7F; // Clear the sign bit & 0b01111111
  }

  if(value.size() < 1 + integerLength)
  {
    return std::make_tuple(0, bytes());
  }

  const bytes integerData(value.begin() + 1, value.begin() + 1 + integerLength);
  bytes rest(value.begin() + 1 + integerLength, value.end());

  varint i = expand_int_from_bytes(integerData);
  if(negative)
  {
    if(std::holds_alternative<int>(i))
    {
      const int integer = std::get<int>(i);
      i = varint(-integer);
    }
    else
    {
      auto integers = std::get<ints>(i);
      integers.at(0) = -integers.at(0);
      i = varint(integers);
    }
  }

  return std::make_tuple(i, rest);
}

varint expand_conn(Connection& conn)
{
  int length = static_cast<unsigned char>(conn.readOne());

  if(length == 0)
  {
    return {0};
  }

  int negative = 0;
  if(length & 0x80)
  {
    length = length & 0x7F;
    negative = 1;
  }

  const bytes integerBytes = conn.read(length);

  varint i = expand_int_from_bytes(integerBytes);

  if(std::holds_alternative<int>(i))
  {
    if(negative)
    {
      const int integer = std::get<int>(i);
      i = varint(-integer);
    }
  }
  else
  {
    auto integers = std::get<ints>(i);

    if(negative)
    {
      integers.insert(integers.begin(), 1);
    }
    else
    {
      integers.insert(integers.begin(), 0);
    }

    i = varint(integers);
  }

  return i;
}

varint expand_int_from_bytes(const bytes &bytes)
{
  // We have to use an unsigned int here because in the base that we end up with a bigint, all the limbs should be unsigned.
  // If we use a (signed) int, we will lose the top bit.
  auto integers = ints();
  for(int count = 1; count <= bytes.size(); count++)
  {
    // We ran out of bytes in the queued integers
    if(count % sizeof(int) == 1)
    {
      integers.insert(integers.begin(), 0);
    }

    // Shift all the integers one byte left
    for(int index = 0; index < static_cast<int>(integers.size()); index++)
    {
      if(index == integers.size() - 1)
      {
        integers.at(index) = static_cast<int>((static_cast<unsigned int>(integers.at(index)) << 8) | static_cast<unsigned int>(bytes.at(count - 1)));
      }
      else
      {
        const auto current = static_cast<unsigned int>(integers.at(index));
        const auto next = static_cast<unsigned int>(integers.at(index + 1));

        constexpr int shift = (sizeof(int) - 1) * 8;
        const unsigned int nextHighByte = (next >> shift) & 0xFF;

        integers.at(index) = static_cast<int>((current << 8) | nextHighByte);
      }
    }
  }

  // In this special case, we might have a valid max size (signed) int, or we might have a max size unsigned int that is too big to fit into a signed int because of the sign bit.
  if(integers.size() == 1)
  {
    const auto unsignedInteger = static_cast<unsigned int>(integers.at(0)); // NOLINT

    if(unsignedInteger <= std::numeric_limits<int>::max())
    {
      return {static_cast<int>(unsignedInteger)};
    }
  }

  return {integers};
}

// float

bool isLittleEndian()
{
    int num = 0x1; // A number where the least significant byte is non-zero
    const char* bytePtr = reinterpret_cast<char*>(&num);

    // Check the value of the first byte
    return (*bytePtr == 0x1);
}

bytes squeeze_floating(const std::variant<float, double> value)
{
  if(std::holds_alternative<float>(value))
  {
    const float f = std::get<float>(value);

    if(f == 0.0)
    {
      return bytes({0});
    }

    auto result = bytes();
    result.insert(result.end(), (char)sizeof(float));

    bytes floatBytes(sizeof(float));
    std::memcpy(floatBytes.data(), &f, sizeof(float));

    if(isLittleEndian())
    {
      std::reverse(floatBytes.begin(), floatBytes.end());
    }

    result.insert(result.end(), floatBytes.begin(), floatBytes.end());

    return result;
  }
  else
  {
    const double d = std::get<double>(value);

    if(d == 0.0)
    {
      return bytes({0});
    }

    auto result = bytes();
    result.insert(result.end(), (char)sizeof(double));

    bytes floatBytes(sizeof(double));
    std::memcpy(floatBytes.data(), &d, sizeof(double));

    if(isLittleEndian())
    {
      std::reverse(floatBytes.begin(), floatBytes.end());
    }

    result.insert(result.end(), floatBytes.begin(), floatBytes.end());

    return result;
  }
}

maybe<floating> expand_floating(bytes value)
{
  const int length = static_cast<unsigned char>(value.at(0));

  if(length == 0)
  {
    return {0.0};
  }

  bytes floatBytes(value.begin() + 1, value.begin() + 1 + length);
  bytes rest(value.begin() + 1 + length, value.end());

  if(isLittleEndian())
  {
    std::reverse(floatBytes.begin(), floatBytes.end());
  }

  switch(length)
  {
    case 4:      
      float f;
    std::memcpy(&f, floatBytes.data(), length);
    return {f};

    case 8:
      double d;
    std::memcpy(&d, floatBytes.data(), length);
    return {d};

    default:
      return std::nullopt;
  }
}

maybe<floating> expand_conn_floating(Connection& conn)
{
  const int length = static_cast<unsigned char>(conn.readOne());

  if(length == 0)
  {
    return {0.0};
  }

  bytes floatBytes = conn.read(length);

  if(isLittleEndian())
  {
    std::reverse(floatBytes.begin(), floatBytes.end());
  }

  switch(length)
  {
    case sizeof(float):
    {
      float f;
      memcpy(&f, floatBytes.data(), floatBytes.size());

      return {floating(f)};
    }

    case sizeof(double):
    {
      double d;
      memcpy(&d, floatBytes.data(), floatBytes.size());

      return {floating(d)};
    }

    default:
      return std::nullopt;
  }
}

// ints

// Encode an array of integers in the fewest number of bytes, plus an encoded integer length to tell us how many bytes that is.
bytes squeeze_ints(const ints &value)
{
  // The only case where the length can be zero is for the number 0.
  if(value.empty())
  {
    return bytes({0});
  }

  // Allocate the result
  auto r = bytes();

  const int size = static_cast<int>(value.size());
  bytes sizeBytes = squeeze_int(size);

  r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

  for(const int integer : value)
  {    
    bytes valueBytes = squeeze_int(integer);
    r.insert(r.end(), valueBytes.begin(), valueBytes.end());
  }

  return r;
}

std::tuple<ints, bytes> expand_ints(const bytes& value)
{
  // If input vector is empty, we have nothing to parse
  if(value.empty())
  {
    return std::make_tuple(ints(), value);
  }

  auto integers = ints();

  // The first byte of the input array is the length at the beginning of the array with the integer for us to parse, the rest of the array is extra
  const std::tuple<varint, bytes> sizeResult = expand_int(value);
  const varint varsize = std::get<0>(sizeResult);
  bytes rest = std::get<1>(sizeResult);

  if(std::holds_alternative<int>(varsize))
  {
    const int size = std::get<int>(varsize);

    // The only case where the length can be zero is for empty array [].
    if(size == 0)
    {
      return std::make_tuple(ints(), rest);
    }

    for(int count=0; count<size; count++)
    {
      std::tuple<varint, bytes> intResult = expand_int(rest);
      varint varinteger = std::get<0>(intResult);
      rest = std::get<1>(intResult);

      if(std::holds_alternative<int>(varinteger))
      {
        int integer = std::get<int>(varinteger);
        integers.push_back(integer);
      }
      else
      {
        // varint elements in integer arrays are not yet fully implemented
        return std::make_tuple<ints, bytes>(ints(), bytes());
      }
    }

    return std::make_tuple(integers, rest);
  }
  else
  {
    // varint sizes are not yet fully implemented
    return std::make_tuple<ints, bytes>(ints(), bytes());
  }
}

// floats

// Encode an array of floats in the fewest number of bytes, plus an encoded integer length to tell us how many bytes that is.
bytes squeeze_floats(const floats& value)
{
  // The only case where the length can be zero is for the number 0.
  if(value.empty())
  {
    return bytes({0});
  }

  // Allocate the result
  auto r = bytes();

  const int size = static_cast<int>(value.size());
  bytes sizeBytes = squeeze_int(size);

  r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

  for(float f : value)
  {
    bytes valueBytes = squeeze_floating(floating(f));
    r.insert(r.end(), valueBytes.begin(), valueBytes.end());
  }

  return r;
}
