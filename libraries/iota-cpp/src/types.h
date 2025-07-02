#ifndef TYPES_H_
#define TYPES_H_

#include <vector>
#include <optional>
#include <variant>

using bytes = std::vector<char>;
using ints = std::vector<int>;
using floats = std::vector<float>;

template<>
struct std::hash<ints>
{
  std::size_t operator()(const std::vector<int>& integers) const noexcept
  {
    std::size_t hash = 0;

    for (int integer : integers) {
      std::hash<int> hasher;
      hash ^= hasher(integer) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }

    return hash;
  }
};

template<>
struct std::hash<floats>
{
  std::size_t operator()(const std::vector<float>& fs) const noexcept
  {
    std::size_t hash = 0;

    for (float f : fs) {
      std::hash<float> hasher;
      hash ^= hasher(f) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }

    return hash;
  }
};

using varint = std::variant<int, ints>;

template <typename T>
using maybe = std::optional<T>;

using floating = std::variant<float, double>;

#endif