#ifndef API_H_
#define API_H_

#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

#include "storage/storage.h"
#include "verbs.h" // NOLINT, included for convenience for users of api.h
#include "adverbs.h" // NOLINT, included for convenience for users of api.h
#include "types.h"

class CppValue;

class Error
{
  public:
    int code;

    bool operator==(const Error& rhs) const
    {
      return code == rhs.code; // Compare member variables
    }

    [[nodiscard]] std::string string() const;
};

template<>
struct std::hash<Error>
{
  std::size_t operator()(const Error& i) const noexcept
  {
    return std::hash<int>()(i.code);
  }
};

using cppValue = std::variant<int, float, char, std::string, std::vector<int>, std::vector<float>, std::vector<CppValue>, Error, Storage>;
using cppValues = std::vector<cppValue>;
using CppValues = std::vector<CppValue>;
class CppValue
{
  public:
    static cppValue t;
    static cppValue f;

    bool operator==(const CppValue& i) const;
    std::size_t operator()(const CppValue& i) const noexcept;

    cppValue value;

    CppValue(const CppValue& other) = default; // copy constructor
    CppValue(const cppValue& value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(int value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(float value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(char value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(std::string value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(ints value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(floats value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(CppValues value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    // CppValue(std::unordered_map<CppValue, CppValue> value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(Error value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
    CppValue(Storage value) : value(value) {} // NOLINT, don't mark as explicit because we want an implicit conversion even if clang-tidy doesn't like that
};

class Object
{
  public:
    static Storage from_cpp(const cppValue& i);
    static Storage from_cpp_expression(const std::vector<cppValue>& i);
    static cppValue to_cpp(Storage i);
};

Storage e();
Storage c();

Storage test_error();
std::string error_to_string(const Storage &error);
std::string code_to_string(int code);

Storage eval(const mixed& e);
cppValue evalNoun(const cppValue& i);

cppValue evalExpression(const cppValues& values);

#endif