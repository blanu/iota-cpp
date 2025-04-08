//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects_register.h"

#include "effects.h"
#include "../error.h"

#include "../storage/word.h"

void EffectsRegister::initialize()
{
  Effects::initialize();
}

Storage EffectsRegister::eval(const Storage& s)
{
  if(s.o == NounType::SIGNAL)
  {
    if(std::holds_alternative<mixed>(s.i))
    {
      mixed ms = std::get<mixed>(s.i);

      if(ms.size() == 4 || ms.size() == 5)
      {
        Storage result = ms[0];

        Storage t = ms[1];
        Storage i = ms[2];

        if(ms.size() == 4)
        {
          Effects::dispatchMonadicEffect(t, i);
        }
        else
        {
          Storage x = ms[3];

          Effects::dispatchDyadicEffect(t, i, x);
        }

        return result;
      }
    }

    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
  else
  {
    return s;
  }
}
