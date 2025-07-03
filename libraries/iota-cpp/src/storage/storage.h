#ifndef STORAGE_H_
#define STORAGE_H_

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "../types.h"

// StorageType
class StorageType
{
  public:
    static constexpr int WORD = 0;
    static constexpr int FLOAT = 1;
    static constexpr int WORD_ARRAY = 2;  // all integers
    static constexpr int FLOAT_ARRAY = 3; // all floats
    static constexpr int MIXED_ARRAY = 4; // array of storage types
    static constexpr int ANY = 255;
};

class NounType
{
  public:
    static constexpr int INTEGER = 0;
    static constexpr int REAL = 1;
    static constexpr int CHARACTER = 2;
    static constexpr int STRING = 3;
    static constexpr int LIST = 4;
    static constexpr int DICTIONARY = 5;
    static constexpr int BUILTIN_SYMBOL = 6;
    static constexpr int BUILTIN_MONAD = 7;
    static constexpr int BUILTIN_DYAD = 8;
    static constexpr int BUILTIN_TRIAD = 9;
    static constexpr int MONADIC_ADVERB = 10;
    static constexpr int DYADIC_ADVERB = 11;
    static constexpr int USER_SYMBOL = 12;
    static constexpr int USER_MONAD = 13;
    static constexpr int USER_DYAD = 14;
    static constexpr int USER_TRIAD = 15;
    static constexpr int ERROR = 16;
    static constexpr int EXPRESSION = 17;
    static constexpr int TYPE = 18;
    static constexpr int CONDITIONAL = 19;
    static constexpr int QUOTED_SYMBOL = 20;
    static constexpr int EFFECT_TYPE = 21;
    static constexpr int RESOURCE = 22;
    static constexpr int CONTINGENCY = 23;
    static constexpr int SIGNAL = 24;
    static constexpr int SEQUENCE = 25;
    static constexpr int DEPENDENCY = 26;
    static constexpr int EFFECT_EXPRESSION = 27;
    static constexpr int LENS = 28;
    static constexpr int EFFECT_CHAIN = 29;
    static constexpr int NILADIC_EFFECT = 30;
    static constexpr int MONADIC_EFFECT = 31;
    static constexpr int DYADIC_EFFECT = 32;
    static constexpr int CONJUNCTION = 33;
    static constexpr int ANY = 255;
};

class SymbolType
{
  public:
    static constexpr int i = 0;
    static constexpr int x = 1;
    static constexpr int y = 2;
    static constexpr int z = 3;
    static constexpr int f = 4;
    static constexpr int causing = 5;
    static constexpr int undefined = 6; // If adding new symbols, undefined must always be the last symbol as it marks the end of the SymbolType sequence.
};

class Storage;

using mixed = std::vector<Storage>;
using I = std::variant<int, float, ints, floats, mixed>;

class Storage
{
  public:
    int o;
    int t;
    I i;

    static Storage identity(const Storage& i);

    bool operator==(const Storage& other) const;

    // Be careful with this constructor, it moves the i value, so only use it as the final use of the i.
    Storage(const int o, const int t, I i) : o(o), t(t), i(std::move(i)) {}

    // Copy constructor
    // Be careful with this constructor, it moves the x.i value, so only use it as the final use of the x.
    Storage(const Storage& x) = default; // o(x.o), t(x.t), i(x.i)

    [[nodiscard]] int truth() const;
    void print();
};

template<>
struct std::hash<Storage>
{
  std::size_t operator()(const Storage& i) const noexcept // NOLINT
  {
    const std::size_t ht = std::hash<int>()(i.t);
    const std::size_t ho = std::hash<int>()(i.o);
    std::size_t hi = 0;

    if(std::holds_alternative<int>(i.i))
    {
      const int ii = std::get<int>(i.i);
      hi = std::hash<int>()(ii);
    }
    else if(std::holds_alternative<float>(i.i))
    {
      const float ii = std::get<float>(i.i);
      hi = std::hash<float>()(ii);
    }
    else if(std::holds_alternative<ints>(i.i))
    {
      const ints ii = std::get<ints>(i.i);
      hi = ii.size();
      for(const int y : ii)
      {
        hi ^= std::hash<int>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      const floats ii = std::get<floats>(i.i);
      hi = ii.size();
      for(const float y : ii)
      {
        hi ^= std::hash<float>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      const mixed ii = std::get<mixed>(i.i);
      for(const Storage& y : ii)
      {
        hi ^= std::hash<Storage>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
      }
    }

    return ht ^ (ho << 1) ^ (hi << 2);
  }
};

#endif