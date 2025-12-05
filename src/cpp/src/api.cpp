#include "api.h"

#include <utility>
#include <string>

#include "nouns/error.h"
#include <types.h>
#include "eval_register.h"

#include <storage/storage.h>
#include "storage/word_array.h"
#include <storage/float_array.h>

#include "storage/word.h"

#include "nouns/nouns.h"
#include "nouns/expression.h"
#include <storage/mixed_array.h>

cppValue CppValue::t = 1;
cppValue CppValue::f = 0;

bool CppValue::all_ints(const cppValues& values)
{
  for(const auto& value : values) // NOLINT
  {
    if(!std::holds_alternative<int>(value))
    {
      return false;
    }
  }

  return true;
}

bool CppValue::all_floats(const cppValues& values)
{
  for(const auto& value : values) // NOLINT
  {
    if(!std::holds_alternative<float>(value))
    {
      return false;
    }
  }

  return true;
}

Storage l(cppValues values)
{
  Storage list = Object::from_cpp(values);

  if(list.o != NounType::LIST)
  {
    return list;
  }

  return Lens::make(list);
}

Storage test_error()
{
  return Word::make(TEST_ERROR, NounType::ERROR);
}

std::string error_to_string(const Storage &error)
{
  if(error.o != NounType::ERROR)
  {
    return "Unknown error";
  }

  if(std::holds_alternative<int>(error.i))
  {
    return code_to_string(std::get<int>(error.i));
  }
  else if(std::holds_alternative<mixed>(error.i))
  {
    mixed ms = std::get<mixed>(error.i);
    if(ms.size() == 4)
    {
      int type = Integer::toInt(ms[0]);
      std::string file = IotaString::toString(ms[1]);
      int line = Integer::toInt(ms[2]);
      std::string func = IotaString::toString(ms[3]);

      return "Error: " + file + " (" + func + ":" + std::to_string(line) + "): " + code_to_string(type);
    }
  }

  return "Unknown error";
}

std::string code_to_string(const int code)
{
  switch(code)
  {
    case BAD_INDEX_TYPE:
      return "unsupported index type";

    case BAD_INITIALIZATION:
      return "bad initialization value";

    case BAD_STORAGE:
      return "this object type does not support this storage type";

    case BAD_OPERATION:
      return "this operation is not supported by this object type with this storage type";

    case EMPTY:
      return "empty";

    case INVALID_ARGUMENT:
      return "invalid argument type";

    case INVALID_ADVERB_ARGUMENT:
      return "invalid adverb argument";

    case OUT_OF_BOUNDS:
      return "out of bounds";

    case SHAPE_MISMATCH:
      return "mismatched shapes";

    case TEST_ERROR:
      return "test error";

    case UNSUPPORTED_OBJECT:
      return "operation is not supported by this object type";

    case UNSUPPORTED_SUBJECT:
      return "unsupported subject type";

    case UNKNOWN_KEY:
      return "unknown key";

    case UNEQUAL_ARRAY_LENGTHS:
      return "unequal array lengths";

    case DIVISION_BY_ZERO:
      return "division by zero";

    default:
      return "unknown error";
  }
}

std::string Error::string() const
{
  return code_to_string(code);
}

Storage eval(const mixed& e)
{
  if(maybe<Storage> result = EvalRegister::eval(Expression::make(e)))
  {
    return *result;
  }
  else
  {
    return makeError(UNSUPPORTED_OBJECT);
  }
}

cppValue evalExpression(const cppValues& values)
{
  const Storage se = Object::from_cpp_expression(values);
  if(const maybe<Storage> result = EvalRegister::eval(se))
  {
    return Object::to_cpp(*result);
  }
  else
  {
    return makeError(UNSUPPORTED_OBJECT);
  }
}

Storage evalExpressionCppToIota(const cppValues& values)
{
  const Storage se = Object::from_cpp_expression(values);
  if(const maybe<Storage> result = EvalRegister::eval(se))
  {
    return *result;
  }
  else
  {
    return makeError(UNSUPPORTED_OBJECT);
  }
}

Storage evalExpression(const Storage& values)
{
  if(maybe<Storage> result = EvalRegister::eval(values))
  {
    return *result;
  }
  else
  {
    return makeError(UNSUPPORTED_OBJECT);
  }
}

bool evalBool(const cppValue& i)
{
  cppValue result = evalNoun(i);
  if(std::holds_alternative<int>(result))
  {
    int integer = std::get<int>(result);
    return integer == 1;
  }

  return false;
}

cppValue evalNoun(const cppValue& i)
{
  const Storage se = Object::from_cpp(i);
  if(const maybe<Storage> result = EvalRegister::eval(se))
  {
    return Object::to_cpp(*result);
  }
  else
  {
    return Error::bad_operation;
  }
}

Storage Object::from_cpp_expression(const cppValues& i)
{
  auto results = mixed();

  for(const auto& y : i)
  {
    Storage result = Object::from_cpp(y);
    results.push_back(result);
  }

  return MixedArray::make(results, NounType::EXPRESSION);
}

Storage Object::from_cpp(const cppValue& i)
{
  if(std::holds_alternative<int>(i))
  {
    const int ii = std::get<int>(i);
    return Integer::make(ii);
  }
  else if(std::holds_alternative<float>(i))
  {
    const float fi = std::get<float>(i);
    return Real::make(fi);
  }
  else if(std::holds_alternative<BigNumber>(i))
  {
    const BigNumber& bn = std::get<BigNumber>(i);
    return Integer::make(bn);
  }
  else if(std::holds_alternative<cppValues>(i))
  {
    auto values = std::get<cppValues>(i); // NOLINT
    if(CppValue::all_ints(values))
    {
      ints results;
      results.reserve(values.size());
      for(const auto& value : values)
      {
        int result = std::get<int>(value);
        results.push_back(result);
      }
      return WordArray::make(results);
    }
    else if(CppValue::all_floats(values))
    {
      floats results;
      results.reserve(values.size());
      for(const auto& value : values)
      {
        float result = std::get<float>(value);
        results.push_back(result);
      }
      return FloatArray::make(results);
    }
    else
    {
      mixed results;
      results.reserve(values.size());
      for(const auto& value : values)
      {
        Storage result = Object::from_cpp(value);
        results.push_back(result);
      }
      return MixedArray::make(results);
    }
  }
  else if(std::holds_alternative<char>(i))
  {
    char ci = std::get<char>(i);
    return Character::make(ci);
  }
  else if(std::holds_alternative<std::string>(i))
  {
    std::string s = std::get<std::string>(i);
    auto integers = ints();
    for(const char c : s)
    {
      int integer = static_cast<unsigned char>(c);
      integers.push_back(integer);
    }
    return IotaString::make(integers);
  }
  else if(std::holds_alternative<Storage>(i))
  {
    auto s = std::get<Storage>(i);
    return s;
  }
  else
  {
    return makeError(UNSUPPORTED_OBJECT);
  }

  return WordArray::nil();
}

cppValue Object::to_cpp(Storage i) // NOLINT
{
  using namespace std::string_literals;

  switch(i.o)
  {
    case NounType::INTEGER:
    {
      if(std::holds_alternative<int>(i.i))
      {
        // Small integer - return as int
        return std::get<int>(i.i);
      }
      else if(std::holds_alternative<ints>(i.i))
      {
        // Big integer (WordArray) - convert to BigNumber
        const ints& bigint = std::get<ints>(i.i);

        if (bigint.empty())
        {
          return BigNumber(0);
        }

        bool negative = (bigint[0] == 1);

        // Check if all chunks are zero
        bool all_zero = true;
        for (size_t idx = 1; idx < bigint.size(); idx++)
        {
          if (bigint[idx] != 0)
          {
            all_zero = false;
            break;
          }
        }

        if (all_zero)
        {
          return BigNumber(0);
        }

        // Convert chunks back to BigNumber
        BigNumber::begin(); // Initialize if needed
        BigNumber result(0);
        BigNumber multiplier(1);

        // Build base = 2^(sizeof(int)*8)
        BigNumber base(1);
        const int BITS_PER_CHUNK = sizeof(int) * 8;
        for (int j = 0; j < BITS_PER_CHUNK; j++)
        {
          base = base + base; // Double for each bit
        }

        // Process chunks from least significant to most significant
        for (size_t idx = bigint.size() - 1; idx >= 1; idx--)
        {
          // Reinterpret bits as unsigned
          unsigned int chunk_unsigned = *reinterpret_cast<const unsigned int*>(&bigint[idx]);

          // Convert to string to avoid sign issues
          char chunk_str[32];
          snprintf(chunk_str, sizeof(chunk_str), "%u", chunk_unsigned);
          BigNumber chunk_bn(chunk_str);

          result = result + (chunk_bn * multiplier);
          multiplier = multiplier * base;

          if (idx == 1) break; // Avoid underflow
        }

        if (negative)
        {
          result = BigNumber(0) - result;
        }

        return result;
      }
      else
      {
        return makeError(UNSUPPORTED_OBJECT);
      }
    }

    case NounType::REAL:
    {
      if(std::holds_alternative<float>(i.i))
      {
        return std::get<float>(i.i);
      }
      else
      {
        return makeError(UNSUPPORTED_OBJECT);
      }
    }

    case NounType::LIST:
    {
      switch(i.t)
      {
        case StorageType::WORD_ARRAY:
        {
          if(std::holds_alternative<ints>(i.i))
          {
            auto integers = std::get<ints>(i.i);

            cppValues results;
            results.reserve(integers.size());
            for (const auto& result : integers)
            {
              results.emplace_back(result);  // Implicit conversion
            }

            return results;
          }
          else
          {
            return makeError(UNSUPPORTED_OBJECT);
          }
        }

        case StorageType::FLOAT_ARRAY:
        {
          if(std::holds_alternative<floats>(i.i))
          {
            auto fs = std::get<floats>(i.i);

            cppValues results;
            results.reserve(fs.size());
            for (const auto& result : fs)
            {
              results.emplace_back(result);  // Implicit conversion
            }

            return results;
          }
          else
          {
            return makeError(UNSUPPORTED_OBJECT);
          }
        }

        case StorageType::MIXED_ARRAY:
        {
          if(std::holds_alternative<mixed>(i.i))
          {
            auto ms = std::get<mixed>(i.i);

            auto vs = std::vector<cppValue>();

            for(const auto& y : ms)
            {
              cppValue v = to_cpp(y);
              vs.emplace_back(v);
            }

            return vs;
          }
          else
          {
            return makeError(UNSUPPORTED_OBJECT);
          }
        }

        default:
          return makeError(UNSUPPORTED_OBJECT);
      }
    }

    case NounType::CHARACTER:
    {
      // FIXME - This only works for ASCII, fix it to work with Unicode.
      if(std::holds_alternative<int>(i.i))
      {
        int ii = std::get<int>(i.i);

        return static_cast<char>(static_cast<unsigned char>(ii));
      }
      else
      {
        return makeError(UNSUPPORTED_OBJECT);
      }
    }

    case NounType::STRING:
    {
      // FIXME - This only works for ASCII, fix it to work with Unicode.
      if(std::holds_alternative<ints>(i.i))
      {
        auto iis = std::get<ints>(i.i);

        auto result = std::string();
        for(auto y : iis)
        {
          result += static_cast<char>(static_cast<unsigned char>(y));
        }

        return result;
      }
      else
      {
        return makeError(UNSUPPORTED_OBJECT);
      }
    }

    // case NounType::DICTIONARY:
    // {
    //   if(std::holds_alternative<mixed>(i.i))
    //   {
    //     mixed ms = std::get<mixed>(i.i);
    //
    //     if(ms.size() != 2)
    //     {
    //       return makeError(UNSUPPORTED_OBJECT);
    //     }
    //
    //     Storage keys = ms[0];
    //     Storage values = ms[1];
    //
    //     auto results = std::unordered_map<CppValue, CppValue>();
    //
    //     if(std::holds_alternative<mixed>(keys.i))
    //     {
    //       auto mkeys = std::get<mixed>(keys.i);
    //
    //       if(std::holds_alternative<mixed>(values.i))
    //       {
    //         auto mvalues = std::get<mixed>(values.i);
    //
    //         if(mkeys.size() != mvalues.size())
    //         {
    //           return makeError(UNSUPPORTED_OBJECT);
    //         }
    //
    //         for(int index = 0; index < mkeys.size(); index++)
    //         {
    //           cppValue key = to_cpp(mkeys[index]);
    //           cppValue value = to_cpp(mvalues[index]);
    //
    //           results[CppValue{key}] = CppValue{value};
    //         }
    //
    //         return {results};
    //       }
    //     }
    //   }
    //
    //   return makeError(UNSUPPORTED_OBJECT);
    // }

    case NounType::BUILTIN_SYMBOL:
    {
      if(std::holds_alternative<int>(i.i))
      {
        switch(std::get<int>(i.i))
        {
          case SymbolType::x:
            return ":x"s;
          case SymbolType::y:
            return ":y"s;
          case SymbolType::z:
            return ":z"s;
          case SymbolType::f:
            return ":f"s;
          case SymbolType::undefined:
            return ":undefined"s;

          default:
            return makeError(UNSUPPORTED_OBJECT);
        }
      }
      else
      {
        return makeError(UNSUPPORTED_OBJECT);
      }
    }

    case NounType::EXPRESSION:
    {
      if(std::holds_alternative<mixed>(i.i))
      {
        auto ms = std::get<mixed>(i.i);

        auto results = std::vector<cppValue>();

        for(const auto& y : ms)
        {
          cppValue result = to_cpp(y);
          results.emplace_back(result);
        }

        return results;
      }
    }

    case NounType::ERROR:
    {
      return error_to_string(i);
    }

    default:
      return makeError(UNSUPPORTED_OBJECT);
  }
}
