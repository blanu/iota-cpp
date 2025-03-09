#include <utility>
#include <vector>
#include <variant>
#include <tuple>

#include "../types.h"
#include "storage.h"

bool Storage::operator==(const Storage& other) const
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
      int x = std::get<int>(i);
      int y = std::get<int>(other.i);

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
      float x = std::get<float>(i);
      float y = std::get<float>(other.i);

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
      ints xs = std::get<ints>(i);
      ints ys = std::get<ints>(other.i);

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
      floats xs = std::get<floats>(i);
      floats ys = std::get<floats>(other.i);

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
      mixed xs = std::get<mixed>(i);
      mixed ys = std::get<mixed>(other.i);

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
            int integer = std::get<int>(i);

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