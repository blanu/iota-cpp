#ifndef API_H_
#define API_H_

#include <variant>
#include <vector>
#include <string>
#include <type_traits>

#include "verbs.h" // NOLINT, included for convenience for users of api.h
#include "adverbs.h" // NOLINT, included for convenience for users of api.h
#include "effects/effects.h" // NOLINT, included for convenience for users of api.h
#include "conjunctions/conjunctions.h" // NOLINT, included for convenience for users of api.h

#include <storage/storage.h>
#include "storage/word.h"
#include <storage/ion_float.h>

#include "nouns/error.h"

struct cppValue;
using cppValueVariant = std::variant<std::vector<cppValue>, int, float, char, std::string, Error, Storage>;
struct cppValue : cppValueVariant
{
  using cppValueVariant::cppValueVariant;

  bool operator==(const cppValue& other) const
  {
    if(std::holds_alternative<std::vector<cppValue>>(*this))
    {
      auto i = std::get<std::vector<cppValue>>(*this);
      auto x = std::get<std::vector<cppValue>>(other);
      if(i.size() != x.size())
      {
        return false;
      }

      return std::equal(i.begin(), i.end(), x.begin());
    }
    else if(std::holds_alternative<int>(*this))
    {
      if(std::holds_alternative<int>(other))
      {
        return std::get<int>(*this) == std::get<int>(other);
      }
    }
    else if(std::holds_alternative<float>(*this))
    {
      if(std::holds_alternative<float>(other))
      {
        return std::abs(std::get<float>(*this) - std::get<float>(other)) < Float::precision;
      }
    }
    else if(std::holds_alternative<char>(*this))
    {
      if(std::holds_alternative<char>(other))
      {
        return std::get<char>(*this) == std::get<char>(other);
      }
    }
    else if(std::holds_alternative<std::string>(*this))
    {
      if(std::holds_alternative<std::string>(other))
      {
        return std::get<std::string>(*this) == std::get<std::string>(other);
      }
    }
    else if(std::holds_alternative<Error>(*this))
    {
      if(std::holds_alternative<Error>(other))
      {
        return std::get<Error>(*this) == std::get<Error>(other);
      }
    }
    else if(std::holds_alternative<Storage>(*this))
    {
      if(std::holds_alternative<Storage>(other))
      {
        return std::get<Storage>(*this) == std::get<Storage>(other);
      }
    }

    return false;
  }

  cppValue() : cppValueVariant(std::vector<cppValue>()) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
  cppValue(std::initializer_list<cppValue> values) : cppValueVariant(std::vector<cppValue>(values)) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
};

using cppValues = std::vector<cppValue>;
using a = cppValues; // alias for convenience
const cppValue nil = {};

class CppValue
{
  public:
    static cppValue t;
    static cppValue f;

    static bool all_ints(const cppValues& values);
    static bool all_floats(const cppValues& values);
};

template <typename T>
T variant_cast(const cppValue& value) {
  return std::get<T>(value);
}

template <typename T>
std::enable_if_t<!std::is_same_v<T, cppValue>, bool>
operator==(const cppValue& left, const T& right) {
  if (std::holds_alternative<T>(left)) {
    return std::get<T>(left) == right;
  }
  return false;
}

template <typename T>
std::enable_if_t<!std::is_same_v<T, cppValue>, bool>
operator==(const T& left, const cppValue& right) {
  return right == left; // Use the overload above
}

template <typename T>
bool operator==(const std::vector<T>& left, const std::vector<T>& right)
{
  if(left.size() != right.size())
  {
    return false;
  }

  for(int i = 0; i < static_cast<int>(left.size()); i++)
  {
    if(left[i] == right[i])
    {
      continue;
    }
    else
    {
      return false;
    }
  }

  return true;
}

class Object
{
  public:
    static Storage from_cpp(const cppValue& i);
    static Storage from_cpp_expression(const cppValues& i);
    static cppValue to_cpp(Storage i);
};

template<typename... Args>
Storage e(Args&&... values)
{
  const cppValues es{static_cast<cppValue>(std::forward<Args>(values))...};
  return Object::from_cpp_expression(es);
}

Storage c();

Storage test_error();
std::string error_to_string(const Storage &error);
std::string code_to_string(int code);

Storage eval(const mixed& e);
cppValue evalNoun(const cppValue& i);

cppValue evalExpression(const cppValues& values);

Storage evaluateExpression(const Storage& values);

namespace iota
{
  inline Storage i = Word::make(SymbolType::i, NounType::BUILTIN_SYMBOL);
  inline Storage x = Word::make(SymbolType::x, NounType::BUILTIN_SYMBOL);
  inline Storage y = Word::make(SymbolType::y, NounType::BUILTIN_SYMBOL);
  inline Storage z = Word::make(SymbolType::z, NounType::BUILTIN_SYMBOL);
  inline Storage f = Word::make(SymbolType::f, NounType::BUILTIN_SYMBOL);
  inline Storage causing = Word::make(SymbolType::causing, NounType::BUILTIN_SYMBOL);
  //inline Storage undefined = Word::make(SymbolType::undefined, NounType::BUILTIN_SYMBOL); // conflicts with the undefined verb
}

#endif