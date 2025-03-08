#ifndef STORAGE_H_
#define STORAGE_H_

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "Connection.h"
#include "types.h"

// StorageType
class StorageType
{
  public:
    static constexpr int WORD = 0;
    static constexpr int FLOAT = 1;
    static constexpr int WORD_ARRAY = 2;  // all integers
    static constexpr int FLOAT_ARRAY = 3; // all floats
    static constexpr int MIXED_ARRAY = 4; // array of storage types
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
};

class SymbolType
{
  public:
    static constexpr int i = 0;
    static constexpr int x = 1;
    static constexpr int y = 2;
    static constexpr int z = 3;
    static constexpr int f = 4;
    static constexpr int undefined = 5; // If adding new symbols, undefined must also be the last symbol as it marks the end of the list of builtin symbols.
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

    // Be careful with this constructor, it moves the i value, so only use it as the final use of the i.
    Storage(int o, int t, I i) : o(o), t(t), i(std::move(i)) {}

    [[nodiscard]] int truth() const;

    bool operator==(const Storage& other) const;
};

template<>
struct std::hash<Storage>
{
  std::size_t operator()(const Storage& i) const noexcept
  {
    std::size_t ht = std::hash<int>()(i.t);
    std::size_t ho = std::hash<int>()(i.o);
    std::size_t hi = 0;

    if(std::holds_alternative<int>(i.i))
    {
      int ii = std::get<int>(i.i);
      hi = std::hash<int>()(ii);
    }
    else if(std::holds_alternative<float>(i.i))
    {
      float ii = std::get<float>(i.i);
      hi = std::hash<float>()(ii);
    }
    else if(std::holds_alternative<ints>(i.i))
    {
      ints ii = std::get<ints>(i.i);
      hi = ii.size();
      for(int y : ii)
      {
        hi ^= std::hash<int>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats ii = std::get<floats>(i.i);
      hi = ii.size();
      for(float y : ii)
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

class Word
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(const Storage& i);

    static maybe<Storage> from_conn(const Connection& conn, int objectType);
    static void to_conn(const Connection& conn, const Storage& i);

    static Storage make(int x, int o = NounType::INTEGER);
};

class Float
{
  public:
    static constexpr float tolerance = 1e-14f; // for match
    static constexpr float precision = 6; // for format

    static maybe<Storage> from_bytes(bytes x, int o);
    static maybe<bytes> to_bytes(const Storage& i);

    static maybe<Storage> from_conn(const Connection& conn, int objectType);
    static void to_conn(const Connection& conn, const Storage& i);

    static Storage make(float x, int o = NounType::REAL);
};

class WordArray
{
  public:
    static Storage nil();
    static Storage nil1(const Storage& i);
    static Storage nil2(const Storage& i, const Storage& x);

    static maybe<Storage> from_bytes(const bytes& data, int o);
    static bytes to_bytes(const Storage &storage);

    static maybe<Storage> from_conn(const Connection& conn, int objectType);
    static void to_conn(const Connection& conn, const Storage& i);

    static Storage make(ints x, int o = NounType::LIST);
};

class FloatArray
{
  public:
    static maybe<Storage> from_bytes(const bytes& data, int o);
    static bytes to_bytes(const Storage& i);

    static maybe<Storage> from_conn(const Connection& conn, int objectType);
    static void to_conn(const Connection& conn, const Storage& i);

    static Storage make(floats x, int o = NounType::LIST);
};

// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API

#endif