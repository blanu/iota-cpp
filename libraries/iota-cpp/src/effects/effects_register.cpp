//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "effects_register.h"

#include "iota_signal.h"
#include "../error.h"

#include "../storage/storage.h"
#include "../storage/word.h"

#include "../verbs.h"
#include "../storage/mixed_array.h"

EffectsRegister::EffectsRegister()
{
  Noun::registerDyad(StorageType::ANY, NounType::ANY, Dyads::causes, StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, cause_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, Dyads::because, StorageType::ANY, NounType::ANY, because_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::SIGNAL, Dyads::then, StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, then_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, Dyads::bind, StorageType::WORD, NounType::BUILTIN_MONAD, bind_monad);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::EFFECT_EXPRESSION, Dyads::bind, StorageType::MIXED_ARRAY, NounType::EXPRESSION, bind_expression);
}
void EffectsRegister::registerNiladicSourceEffect(Type f, Type e, const std::function<Storage()>& m)
{
  niladSources[Specialization2(f, e)] = m; // NOLINT
}

void EffectsRegister::registerMonadicSourceEffect(Type it, Type io, Type f, Type e, const std::function<Storage(const Storage&)>& m)
{
  monadSources[Specialization4(it, io, f, e)] = m; // NOLINT
}

void EffectsRegister::registerDyadicSourceEffect(Type it, Type io, Type f, Type e, Type xt, Type xo, const std::function<Storage (const Storage&, const Storage&)>& m)
{
  dyadSources[Specialization6(it, io, f, e, xt, xo)] = m;
}

void EffectsRegister::registerNiladicSinkEffect(Type f, Type e, const std::function<void()>& m)
{
  niladSinks[Specialization2(f, e)] = m; // NOLINT
}

void EffectsRegister::registerMonadicSinkEffect(Type it, Type io, Type f, Type e, const std::function<void(Storage)>& m)
{
  monadSinks[Specialization4(it, io, f, e)] = m; // NOLINT
}

void EffectsRegister::registerDyadicSinkEffect(Type it, Type io, Type f, Type e, Type xt, Type xo, const std::function<void(const Storage&, const Storage&)>& m)
{
  dyadSinks[Specialization6(it, io, f, e, xt, xo)] = m;
}

void EffectsRegister::dispatchMonadicSinkEffect(const Storage& i, const Storage& fe)
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
  if (monadSinks.find(specialization) == monadSinks.end()) {
    return;
  }

  std::function<void(Storage)> verb = monadSinks[specialization];
  return verb(i);
}

void EffectsRegister::dispatchDyadicSinkEffect(const Storage& i, const Storage& fe, const Storage& x)
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
  if (dyadSinks.find(specialization) == dyadSinks.end()) {
    return;
  }

  std::function<void(Storage,Storage)> verb = dyadSinks[specialization];
  verb(i, x);
}

Storage EffectsRegister::because_impl(const Storage& i, const Storage& x)
{
  const Storage& newI = x;
  const Storage& newX = i;
  return Signal::make(newI, newX);
}

Storage EffectsRegister::cause_impl(const Storage& i, const Storage& x)
{
  return Signal::make(i, x);
}

Storage EffectsRegister::then_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed is = std::get<mixed>(i.i);

    if(is.size() == 2)
    {
      const Storage& value = is[0];
      Storage effect = is[1];

      if(effect.o == NounType::EFFECT_EXPRESSION)
      {
        // There is just one effect in this Signal.
        // Make it into a list of multiple signals.
        mixed results = mixed{effect, x};
        return Signal::make(value, MixedArray::make(results));
      }
      else if(effect.o == NounType::LIST)
      {
        // There are multiple effects in this Signal.
        // Append the new effect to the list.
        if(std::holds_alternative<mixed>(effect.i))
        {
          mixed effects = std::get<mixed>(effect.i);
          mixed results = mixed(effects);
          results.push_back(x);

          return Signal::make(value, MixedArray::make(results));
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage EffectsRegister::bind_monad(const Storage& i, const Storage& x)
{
  return Contingency::make(i, x);
}

Storage EffectsRegister::bind_expression(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed is = std::get<mixed>(i.i);

    if(is.size() == 2)
    {
      const Storage& value = is[0];
      Storage effect = is[1];

      if(effect.o == NounType::EFFECT_EXPRESSION)
      {
        // There is just one effect in this Signal.
        // Make it into a list of multiple signals.
        mixed results = mixed{effect, x};
        return Signal::make(value, MixedArray::make(results));
      }
      else if(effect.o == NounType::LIST)
      {
        // There are multiple effects in this Signal.
        // Append the new effect to the list.
        if(std::holds_alternative<mixed>(effect.i))
        {
          mixed effects = std::get<mixed>(effect.i);
          mixed results = mixed(effects);
          results.push_back(x);

          return Signal::make(value, MixedArray::make(results));
        }
      }
    }
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
        const Storage& i = ms[0];
        const Storage& e = ms[1];

        eval_effect_expression(e);

        return i;
      }
    }
  }
  else if(s.o == NounType::CONTINGENCY)
  {
    if(std::holds_alternative<mixed>(s.i))
    {
      auto ms = std::get<mixed>(s.i);

      if(ms.size() == 2)
      {
        const Storage& i = ms[0];
        // Discard ms[1];

        eval_effect_expression(i);

        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

void EffectsRegister::eval_effect_expression(const Storage& e) // NOLINT
{
  if(e.o == NounType::EFFECT_EXPRESSION)
  {
    if(std::holds_alternative<mixed>(e.i))
    {
      auto mes = std::get<mixed>(e.i);
      if(mes.size() == 2)
      {
        const Storage& ei = mes[0];
        const Storage& ef = mes[1];

        dispatchMonadicSinkEffect(ei, ef);
      }
      else if(mes.size() == 3)
      {
        const Storage& ei = mes[0];
        const Storage& ef = mes[1];
        const Storage& ex = mes[2];

        dispatchDyadicSinkEffect(ei, ef, ex);
      }
    }
  }
  else if(e.o == NounType::LIST)
  {
    if(std::holds_alternative<mixed>(e.i))
    {
      auto mes  = std::get<mixed>(e.i);
      for(const auto& me : mes)
      {
        eval_effect_expression(me);
      }
    }
  }
}
