//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects_register.h"

#include "iota_signal.h"
#include "../error.h"

#include "../storage/storage.h"
#include "../storage/word.h"

#include "../verbs.h"

EffectsRegister::EffectsRegister()
{
  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::cause, StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, cause_impl);
}

void EffectsRegister::registerMonadicEffect(Type it, Type io, Type f, Type e, std::function<void(Storage)> m)
{
  monads[Specialization4(it, io, f, e)] = m;
}

void EffectsRegister::registerDyadicEffect(Type it, Type io, Type f, Type e, Type xt, Type xo, void (*d)(const Storage&, const Storage&))
{
  dyads[Specialization6(it, io, f, e, xt, xo)] = d;
}

void EffectsRegister::dispatchMonadicEffect(const Storage& i, const Storage& fe)
{
  if (i.o == NounType::ERROR)
  {
    return;
  }

  if (fe.t != StorageType::WORD_ARRAY)
  {
    return;
  }

  const auto fis = std::get<ints>(fe.i);
  if(fis.size() != 2)
  {
    return;
  }

  int f = fis[0];
  int e = fis[1];

  Specialization4 specialization = Specialization4(i.t, i.o, f, e);
  if (monads.find(specialization) == monads.end()) {
    return;
  }

  std::function<void(Storage)> verb = monads[specialization];
  return verb(i);
}

void EffectsRegister::dispatchDyadicEffect(const Storage& i, const Storage& fe, const Storage& x)
{
  if (i.o == NounType::ERROR) {
    return;
  }

  if (x.o == NounType::ERROR) {
    return;
  }

  const auto fis = std::get<ints>(fe.i);
  if(fis.size() != 2)
  {
    return;
  }

  int f = fis[0];
  int e = fis[1];

  Specialization6 specialization = Specialization6(i.t, i.o, f, e, x.t, x.o);
  if (dyads.find(specialization) == dyads.end()) {
    return;
  }

  std::function<void(Storage,Storage)> verb = dyads[specialization];
  verb(i, x);
}

void EffectsRegister::processEffects()
{

}

Storage EffectsRegister::cause_impl(const Storage& i, const Storage& x)
{
  if(x.o == NounType::EFFECT_EXPRESSION)
  {
    return Signal::make(i, x);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage EffectsRegister::eval(const Storage& s)
{
  if(s.o == NounType::SIGNAL)
  {
    if(std::holds_alternative<mixed>(s.i))
    {
      auto ms = std::get<mixed>(s.i);

      if(ms.size() == 2)
      {
        Storage i = ms[0];
        Storage e = ms[1];

        if(std::holds_alternative<mixed>(e.i))
        {
          auto mes = std::get<mixed>(e.i);
          if(mes.size() == 2)
          {
            Storage ei = mes[0];
            Storage ef = mes[1];

            dispatchMonadicEffect(ei, ef);
          }
          else if(mes.size() == 3)
          {
            Storage ei = mes[0];
            Storage ef = mes[1];
            Storage ex = mes[2];

            dispatchDyadicEffect(ei, ef, ex);
          }
        }

        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}
