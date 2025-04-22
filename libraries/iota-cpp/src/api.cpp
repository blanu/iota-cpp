#include "api.h"

#include <utility>
#include "error.h"
#include "types.h"
#include "eval_register.h"
#include "effects/iota_signal.h"

#include "storage/storage.h"
#include "storage/word_array.h"
#include "storage/float_array.h"

#include "storage/word.h"

#include "nouns/nouns.h"
#include "nouns/expression.h"
#include "storage/mixed_array.h"

cppValue CppValue::t = 1;
cppValue CppValue::f = 0;

// bool CppValue::operator==(const CppValue& i) const
// {
//   if(std::holds_alternative<int>(i.value) && std::holds_alternative<int>(value))
//   {
//     return std::get<int>(i.value) == std::get<int>(value);
//   }
//   else if(std::holds_alternative<float>(i.value) && std::holds_alternative<float>(value))
//   {
//     return std::get<float>(i.value) == std::get<float>(value);
//   }
//   else if(std::holds_alternative<std::string>(i.value) && std::holds_alternative<std::string>(value))
//   {
//     return std::get<std::string>(i.value) == std::get<std::string>(value);
//   }
//   else if(std::holds_alternative<std::vector<int>>(i.value) && std::holds_alternative<std::vector<int>>(value))
//   {
//     return std::get<std::vector<int>>(i.value) == std::get<std::vector<int>>(value);
//   }
//   else if(std::holds_alternative<std::vector<float>>(i.value) && std::holds_alternative<std::vector<float>>(value))
//   {
//     return std::get<std::vector<float>>(i.value) == std::get<std::vector<float>>(value);
//   }
//   // FIXME
//   // else if(std::holds_alternative<std::unordered_map<CppValue, CppValue>>(i.value))
//   // {
//   //   const auto map = std::get<std::unordered_map<CppValue, CppValue>>(i.value);
//   //
//   //   std::size_t hash = 0;
//   //
//   //   for (const auto& pair : map)
//   //   {
//   //     hash ^= std::hash<CppValue>()(pair.first) ^ (std::hash<CppValue>()(pair.second) << 1) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//   //   }
//   //
//   //   return hash;
//   // }
//   // FIXME
//   // else if(std::holds_alternative<std::vector<CppValue>>(i.value) && std::holds_alternative<std::vector<CppValue>>(value))
//   // {
//   //   const std::vector<CppValue> vs = std::get<std::vector<CppValue>>(i.value);
//   //
//   //   std::size_t hash = 0;
//   //
//   //   for (const CppValue& v : vs)
//   //   {
//   //     hash ^= std::hash<CppValue>()(v) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//   //   }
//   //
//   //   return hash;
//   // }
//   else if(std::holds_alternative<Error>(i.value) && std::holds_alternative<Error>(value))
//   {
//     return std::get<Error>(i.value) == std::get<Error>(value);
//   }
//   else if(std::holds_alternative<Storage>(i.value) && std::holds_alternative<Storage>(value))
//   {
//     return std::get<Storage>(i.value) == std::get<Storage>(value);
//   }
//   else
//   {
//     return false;
//   }
// }

bool CppValue::operator==(const CppValue& i) const
{
  return value == i.value;
}

// template<>
// struct std::hash<CppValue>
// {
//   std::size_t operator()(const CppValue& i) const noexcept
//   {
//     if(std::holds_alternative<int>(i.value))
//     {
//       return std::hash<int>()(std::get<int>(i.value));
//     }
//     else if(std::holds_alternative<float>(i.value))
//     {
//       return std::hash<float>()(std::get<float>(i.value));
//     }
//     else if(std::holds_alternative<std::string>(i.value))
//     {
//       return std::hash<std::string>()(std::get<std::string>(i.value));
//     }
//     else if(std::holds_alternative<std::vector<int>>(i.value))
//     {
//       return std::hash<std::vector<int>>()(std::get<std::vector<int>>(i.value));
//     }
//     else if(std::holds_alternative<std::vector<float>>(i.value))
//     {
//       return std::hash<std::vector<float>>()(std::get<std::vector<float>>(i.value));
//     }
//     // FIXME
//     // else if(std::holds_alternative<std::unordered_map<CppValue, CppValue>>(i.value))
//     // {
//     //   const auto map = std::get<std::unordered_map<CppValue, CppValue>>(i.value);
//     //
//     //   std::size_t hash = 0;
//     //
//     //   for (const auto& pair : map)
//     //   {
//     //     hash ^= std::hash<CppValue>()(pair.first) ^ (std::hash<CppValue>()(pair.second) << 1) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//     //   }
//     //
//     //   return hash;
//     // }
//     // FIXME
//     // else if(std::holds_alternative<std::vector<CppValue>>(i.value))
//     // {
//     //   const std::vector<CppValue> vs = std::get<std::vector<CppValue>>(i.value);
//     //
//     //   std::size_t hash = 0;
//     //
//     //   for (const CppValue& v : vs)
//     //   {
//     //     hash ^= std::hash<CppValue>()(v) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//     //   }
//     //
//     //   return hash;
//     // }
//     else if(std::holds_alternative<Error>(i.value))
//     {
//       return std::hash<Error>()(std::get<Error>(i.value));
//     }
//     else if(std::holds_alternative<Storage>(i.value))
//     {
//       return std::hash<Storage>()(std::get<Storage>(i.value));
//     }
//     else
//     {
//       return 0;
//     }
//   }
// };

Storage test_error()
{
  return Word::make(TEST_ERROR, NounType::ERROR);
}

std::string error_to_string(const Storage &e)
{
  if(e.o != NounType::ERROR)
  {
    return "Unknown error";
  }

  if(e.t != StorageType::WORD)
  {
    return "Unknown error";
  }

  if(std::holds_alternative<int>(e.i))
  {
    return code_to_string(std::get<int>(e.i));
  }
  else
  {
    return "Unknown error";
  }
}

std::string code_to_string(int code)
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
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

cppValue evalExpression(const cppValues& values)
{
  Storage se = Object::from_cpp_expression(values);
  if(maybe<Storage> result = EvalRegister::eval(se))
  {
    return Object::to_cpp(*result);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

void evalExpressionForEffects(const cppValues& values, EffectsRegister* effects_register)
{
  Storage se = Object::from_cpp_expression(values);
  if(const maybe<Storage> result = EvalRegister::eval(se))
  {
    if(result)
    {
      if((*result).o == NounType::SIGNAL)
      {
        effects_register->eval(*result);
      }
    }
  }
}

cppValue evalNoun(const cppValue& i)
{
  Storage se = Object::from_cpp(i);
  if(maybe<Storage> result = EvalRegister::eval(se))
  {
    return Object::to_cpp(*result);
  }
  else
  {
    return "Error: unsupported object";
  }
}

Storage Object::from_cpp_expression(const cppValues& i)
{
  mixed results = mixed();

  bool effective = false;
  for(const auto& y : i)
  {
    Storage result = Object::from_cpp(y);
    if(result.o == NounType::EFFECT_TYPE)
    {
      effective = true;
    }

    results.push_back(result);
  }

  if(effective)
  {
    return MixedArray::make(results, NounType::EFFECT_EXPRESSION);
  }
  else
  {
    return MixedArray::make(results, NounType::EXPRESSION);
  }
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
  else if(std::holds_alternative<std::vector<int>>(i))
  {
    std::vector<int> iis = std::get<std::vector<int>>(i);
    return WordArray::make(iis);
  }
  else if(std::holds_alternative<std::vector<float>>(i))
  {
    std::vector<float> fis = std::get<std::vector<float>>(i);
    return FloatArray::make(fis);
  }
  else if(std::holds_alternative<char>(i))
  {
    // FIXME - This only works for ASCII, fix it to work with Unicode.
    char ci = std::get<char>(i);
    return Character::make(ci);
  }
  else if(std::holds_alternative<std::string>(i))
  {
    // FIXME - This only works for ASCII, fix it to work with Unicode.
    std::string s = std::get<std::string>(i);

    auto integers = ints();
    for(const char c : s)
    {
      int integer = static_cast<unsigned char>(c);
      integers.push_back(integer);
    }

    return IotaString::make(integers);
  }
  else if(std::holds_alternative<std::vector<CppValue>>(i))
  {
    std::vector<CppValue> vs = std::get<std::vector<CppValue>>(i);

    mixed results = mixed();

    bool effective = false;
    for(const auto& y : vs)
    {
      Storage sy = from_cpp(y.value);
      if(sy.o == NounType::EFFECT_TYPE)
      {
        effective = true;
      }

      results.push_back(sy);
    }

    if(effective)
    {
      return MixedArray::make(results, NounType::EFFECT_EXPRESSION);
    }
    else
    {
      return MixedArray::make(results);
    }
  }
  // else if(std::holds_alternative<std::unordered_map<CppValue, CppValue>>(i))
  // {
  //   auto map = std::get<std::unordered_map<CppValue, CppValue>>(i);
  //
  //   auto keys = mixed();
  //   auto values = mixed();
  //
  //   for(const auto& [fst, snd] : map)
  //   {
  //     Storage key = from_cpp(fst.value);
  //     keys.push_back(key);
  //
  //     Storage value = from_cpp(snd.value);
  //     values.push_back(value);
  //   }
  //
  //   mixed results = {MixedArray::make(keys), MixedArray::make(values)};
  //   return Dictionary::make(results);
  // }
  else if(std::holds_alternative<Storage>(i))
  {
    Storage s = std::get<Storage>(i);
    return s;
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

cppValue Object::to_cpp(Storage i)
{
  switch(i.o)
  {
    case NounType::INTEGER:
    {
      if(std::holds_alternative<int>(i.i))
      {
        return std::get<int>(i.i);
      }
      else
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
            return std::get<ints>(i.i);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }

        case StorageType::FLOAT_ARRAY:
        {
          if(std::holds_alternative<floats>(i.i))
          {
            return std::get<floats>(i.i);
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }

        case StorageType::MIXED_ARRAY:
        {
          if(std::holds_alternative<mixed>(i.i))
          {
            mixed ms = std::get<mixed>(i.i);

            std::vector<CppValue> vs = std::vector<CppValue>();

            for(const auto& y : ms)
            {
              cppValue v = to_cpp(y);
              vs.emplace_back(v);
            }

            return vs;
          }
          else
          {
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
          }
        }

        default:
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
      }
    }

    case NounType::STRING:
    {
      // FIXME - This only works for ASCII, fix it to work with Unicode.
      if(std::holds_alternative<ints>(i.i))
      {
        ints iis = std::get<ints>(i.i);

        std::string result = std::string();
        for(auto y : iis)
        {
          result += static_cast<char>(static_cast<unsigned char>(y));
        }

        return result;
      }
      else
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
    //       return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
    //           return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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
    //   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    // }

    case NounType::BUILTIN_SYMBOL:
    {
      if(std::holds_alternative<int>(i.i))
      {
        switch(std::get<int>(i.i))
        {
          case SymbolType::x:
            return ":x";
          case SymbolType::y:
            return ":y";
          case SymbolType::z:
            return ":z";
          case SymbolType::f:
            return ":f";
          case SymbolType::undefined:
            return ":undefined";

          default:
            return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }
      else
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
      }
    }

    case NounType::EXPRESSION:
    {
      if(std::holds_alternative<mixed>(i.i))
      {
        mixed ms = std::get<mixed>(i.i);

        std::vector<CppValue> results = std::vector<CppValue>();

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
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}
