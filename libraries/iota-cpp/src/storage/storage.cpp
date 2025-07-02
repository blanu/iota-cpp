#include <utility>
#include <vector>
#include <variant>
#include <tuple>
#include <cstdio> // NOLINT, required for printf

#include "../types.h"
#include "storage.h"

bool Storage::operator==(const Storage& other) const // NOLINT
{
  if(o != other.o)
  {
    return false;
  }

  if(t != other.t)
  {
    return false;
  }

  if(std::holds_alternative<int>(i))
  {
    if(std::holds_alternative<int>(other.i))
    {
      const int x = std::get<int>(i);
      const int y = std::get<int>(other.i);

      return x == y;
    }
    else
    {
      return false;
    }
  }
  else if (std::holds_alternative<float>(i))
  {
    if(std::holds_alternative<float>(other.i))
    {
      const float x = std::get<float>(i);
      const float y = std::get<float>(other.i);

      return x == y;
    }
    else
    {
      return false;
    }
  }
  else if(std::holds_alternative<ints>(i))
  {
    if(std::holds_alternative<ints>(other.i))
    {
      const ints xs = std::get<ints>(i);
      const ints ys = std::get<ints>(other.i);

      if(xs.size() != ys.size())
      {
        return false;
      }

      for(int index = 0; index < xs.size(); index++)
      {
        if(xs[index] != ys[index])
        {
          return false;
        }
      }

      return true;
    }
    else
    {
      return false;
    }
  }
  else if(std::holds_alternative<floats>(i))
  {
    if(std::holds_alternative<floats>(other.i))
    {
      const floats xs = std::get<floats>(i);
      const floats ys = std::get<floats>(other.i);

      if(xs.size() != ys.size())
      {
        return false;
      }

      for(int index = 0; index < xs.size(); index++)
      {
        if(xs[index] != ys[index])
        {
          return false;
        }
      }

      return true;
    }
    else
    {
      return false;
    }
  }
  else if(std::holds_alternative<mixed>(i))
  {
    if(std::holds_alternative<mixed>(other.i))
    {
      const mixed xs = std::get<mixed>(i);
      const mixed ys = std::get<mixed>(other.i);

      if(xs.size() != ys.size())
      {
        return false;
      }

      for(int index = 0; index < xs.size(); index++)
      {
        if(xs[index] == ys[index])
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
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

Storage Storage::identity(const Storage& i)
{
  return i;
}

int Storage::truth() const
{
  switch(o)
  {
    case NounType::INTEGER:
      switch(t)
      {
        case StorageType::WORD:
          if(std::holds_alternative<int>(i))
          {
            const int integer = std::get<int>(i);

            return integer != 0;
          }
          else
          {
            return 0;
          }

        // FIXME - support bigints

        default:
          return 0;
      }

    default:
      return 0;
  }
}

void Storage::print() // NOLINT
{
  switch(t)
  {
    case StorageType::WORD:
      printf("WORD:");
      printf("%d:", t);
      printf("%d", std::get<int>(i));
      break;

    case StorageType::FLOAT:
      printf("FLOAT:");
      printf("%d:", t);
      printf("%.1f", std::get<float>(i));
      break;

    case StorageType::WORD_ARRAY:
      printf("WORDS:");
      printf("%d:[", t);

      for(int index = 0; index < std::get<ints>(i).size(); index++)
      {
        const int integer = std::get<ints>(i)[index];
        printf("%d", integer);
        if(index < std::get<ints>(i).size() - 1)
        {
          printf(", ");
        }
      }

      printf("]");
      break;

    case StorageType::FLOAT_ARRAY:
      printf("FLOATS:");
      printf("%d:[", t);

      for(int index = 0; index < std::get<floats>(i).size(); index++)
      {
        const float f = std::get<floats>(i)[index];
        printf("%.1f", f);
        if(index < std::get<floats>(i).size() - 1)
        {
          printf(", ");
        }
      }

      printf("]");
      break;

    case StorageType::MIXED_ARRAY:
      printf("MIXED:");
      printf("%d:[", t);

      for(int index = 0; index < std::get<mixed>(i).size(); index++)
      {
        Storage s = std::get<mixed>(i)[index];
        s.print();
        if(index < std::get<mixed>(i).size() - 1)
        {
          printf(", ");
        }
      }

      printf("]");
      break;

    default:
      return;
  }
}