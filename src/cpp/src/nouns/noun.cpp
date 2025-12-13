#include <vector>
#include <variant>
#include <algorithm>

#include "noun.h"
#include "nouns.h"

#include <squeeze.h>
#include "../verbs.h"
#include "error.h"
#include "../api.h"
#include "../adverbs.h"

#include <storage/word.h>
#include <storage/word_array.h>
#include <storage/ion_float.h>
#include <storage/float_array.h>
#include <storage/mixed_array.h>

#include "../conjunctions/conjunctions.h"

std::map<Specialization1, NiladicSourceFunction> Noun::niladSources;
std::map<Specialization3, MonadicSourceFunction> Noun::monadSources;
std::map<Specialization5, DyadicSourceFunction> Noun::dyadSources;
std::map<Specialization7, TriadicSourceFunction> Noun::triadSources;
std::map<Specialization3, MonadicAdverbFunction> Noun::monadicAdverbs;
std::map<Specialization5, DyadicAdverbFunction> Noun::dyadicAdverbs;
std::map<Specialization1, ConjunctionFunction> Noun::conjunctions;

Logger* Noun::logger;

void Noun::initialize()
{
  Integer::initialize();
  Real::initialize();
  List::initialize();
  Character::initialize();
  IotaString::initialize();
  Dictionary::initialize();
  Expression::initialize();
  Conditional::initialize();
  Symbol::initialize();
  QuotedSymbol::initialize();
  Lens::initialize();
  Conjunctions::initialize();
  Range::initialize();
  Bindings::initialize();
  SymbolDefinition::initialize();
  UserSymbol::initialize();
}

// Dispatch
Storage Noun::dispatchNilad(const Storage& f)
{
  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const auto& specialization = Specialization1(fi);
  const auto verb = niladSources.find(specialization);
  if(verb != niladSources.end())
  {
    return verb->second();
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchMonad(const Storage& i, const Storage& f)
{
  if (i.o == NounType::ERROR) {
    return i;
  }

  if(f.o == NounType::EXPRESSION)
  {
    if(std::holds_alternative<mixed>(f.i))
    {
      mixed ms = std::get<mixed>(f.i);
      mixed next_e = mixed();
      next_e.reserve(ms.size() + 1);

      next_e.push_back(i);
      for(auto& m : ms)
      {
        next_e.push_back(m);
      }

      Storage result = evaluate_expression(Expression::make(next_e));
      if(result.o == NounType::ERROR)
      {
        return result;
      }

      return result;
    }
  }
  else if(f.o == NounType::USER_MONAD)
  {
    if(std::holds_alternative<mixed>(f.i))
    {
      mixed ms = std::get<mixed>(f.i);
      mixed next_e = mixed();
      next_e.reserve(ms.size() + 1);

      next_e.push_back(i);
      for(auto& m : ms)
      {
        next_e.push_back(m);
      }

      Storage result = evaluate_expression(Expression::make(next_e));
      if(result.o == NounType::ERROR)
      {
        return result;
      }

      return result;
    }
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const std::vector specializations = {
    Specialization3(i.t, i.o, fi),
    Specialization3(NounType::ANY, i.o, fi),
    Specialization3(i.t, NounType::ANY, fi),
    Specialization3(NounType::ANY, NounType::ANY, fi),
  };

  for(const auto& specialization : specializations)
  {
    const auto verb = monadSources.find(specialization);
    if(verb != monadSources.end())
    {
      return verb->second(i);
    }
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchDyad(const Storage& i, const Storage& f, const Storage& x) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if(f.o == NounType::EXPRESSION)
  {
    if(std::holds_alternative<mixed>(f.i))
    {
      mixed ms = std::get<mixed>(f.i);
      mixed next_e = mixed();
      next_e.reserve(ms.size() + 1);

      if(i.o == NounType::BUILTIN_SYMBOL)
      {
        if(std::holds_alternative<int>(i.i))
        {
          int mi = std::get<int>(i.i);
          switch(mi)
          {
            case SymbolType::i:
              next_e.push_back(i);
              break;

            case SymbolType::x:
              next_e.push_back(x);
              break;

            case SymbolType::f:
              next_e.push_back(f);
              break;

            default:
              return makeError(UNSUPPORTED_OBJECT);
          }
        }
        else
        {
          return makeError(UNSUPPORTED_OBJECT);
        }
      }
      else
      {
        next_e.push_back(i);
      }

      for(auto& m : ms)
      {
        if(m.o == NounType::BUILTIN_SYMBOL)
        {
          if(std::holds_alternative<int>(m.i))
          {
            int mi = std::get<int>(m.i);
            switch(mi)
            {
              case SymbolType::i:
                next_e.push_back(i);
                break;

              case SymbolType::x:
                next_e.push_back(x);
                break;

              case SymbolType::f:
                next_e.push_back(f);
                break;

              default:
                return makeError(UNSUPPORTED_OBJECT);
            }
          }
          else
          {
            return makeError(UNSUPPORTED_OBJECT);
          }
        }
        else
        {
          next_e.push_back(m);
        }
      }

      return evaluate_expression(Expression::make(next_e));
    }
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const std::vector<Specialization5> specializations = {
    Specialization5(i.t, i.o, fi, x.t, x.o),
    Specialization5(i.t, i.o, fi, x.t, NounType::ANY),
    Specialization5(i.t, i.o, fi, NounType::ANY, x.o),
    Specialization5(i.t, i.o, fi, NounType::ANY, NounType::ANY),

    Specialization5(i.t, NounType::ANY, fi, x.t, x.o),
    Specialization5(i.t, NounType::ANY, fi, x.t, NounType::ANY),
    Specialization5(i.t, NounType::ANY, fi, NounType::ANY, x.o),
    Specialization5(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY),

    Specialization5(NounType::ANY, i.o, fi, x.t, x.o),
    Specialization5(NounType::ANY, i.o, fi, x.t, NounType::ANY),
    Specialization5(NounType::ANY, i.o, fi, NounType::ANY, x.o),
    Specialization5(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY),

    Specialization5(NounType::ANY, NounType::ANY, fi, x.t, x.o),
    Specialization5(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY),
    Specialization5(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o),
    Specialization5(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY)
  };

  //auto sources = dyadSources;
  for(const auto& specialization : specializations)
  {
    auto verb = dyadSources.find(specialization);
    if (verb != dyadSources.end())
    {
      return verb->second(i, x);
    }
  }

  //printDyad(i, f, x);
  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchTriad(const Storage& i, const Storage& f, const Storage& x, const Storage& y)
{
  if(i.o == NounType::ERROR)
  {
    return i;
  }

  if(x.o == NounType::ERROR)
  {
    return x;
  }

  if(y.o == NounType::ERROR)
  {
    return y;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const std::vector specializations = {
    Specialization7(i.t, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, i.o, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(i.t, i.o, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(i.t, i.o, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, NounType::ANY),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, NounType::ANY, NounType::ANY),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, NounType::ANY),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),
  };

  //auto sources = triadSources;
  for(const auto& specialization : specializations)
  {
    auto verb = triadSources.find(specialization);
    if(verb != triadSources.end())
    {
      return verb->second(i, x, y);
    }
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchMonadicAdverb(const Storage& i, const Storage& f, const Storage& g)
{
  if (i.o == NounType::ERROR)
  {
    return i;
  }

  if (f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const auto specialization = Specialization3(i.t, i.o, fi);
  const auto adverb = monadicAdverbs.find(specialization);
  if(adverb != monadicAdverbs.end())
  {
    return adverb->second(i, g);
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchDyadicAdverb(const Storage& i, const Storage& f, const Storage& g, const Storage& x)
{
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const auto specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  const auto adverb = dyadicAdverbs.find(specialization);
  if(adverb != dyadicAdverbs.end())
  {
    return adverb->second(i, g, x);
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, g);
}

Storage Noun::dispatchNiladicEffect(const Storage& f)
{
  if(f.o != NounType::NILADIC_EFFECT)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  if (f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const auto specialization = Specialization1(fi);
  const auto verb = niladSources.find(specialization);
  if(verb != niladSources.end())
  {
    return verb->second();
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchMonadicEffect(const Storage& i, const Storage& f)
{
  if (i.o == NounType::ERROR)
  {
    return i;
  }

  if(f.o != NounType::MONADIC_EFFECT)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  if (f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const std::vector specializations = {
    Specialization3(i.t, i.o, fi),
    Specialization3(i.t, NounType::ANY, fi),
    Specialization3(NounType::ANY, i.o, fi),
    Specialization3(NounType::ANY, NounType::ANY, fi),
  };

  //auto sources = monadSources;
  for(const auto& specialization : specializations)
  {
    const auto verb = monadSources.find(specialization);
    if(verb != monadSources.end())
    {
      return verb->second(i);
    }
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchDyadicEffect(const Storage& i, const Storage& f, const Storage& x)
{
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if(f.o != NounType::DYADIC_EFFECT)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const std::vector<Specialization5> specializations = {
    Specialization5(i.t, i.o, fi, x.t, x.o),
    Specialization5(i.t, i.o, fi, x.t, NounType::ANY),
    Specialization5(i.t, i.o, fi, NounType::ANY, x.o),
    Specialization5(i.t, i.o, fi, NounType::ANY, NounType::ANY),

    Specialization5(i.t, NounType::ANY, fi, x.t, x.o),
    Specialization5(i.t, NounType::ANY, fi, x.t, NounType::ANY),
    Specialization5(i.t, NounType::ANY, fi, NounType::ANY, x.o),
    Specialization5(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY),

    Specialization5(NounType::ANY, i.o, fi, x.t, x.o),
    Specialization5(NounType::ANY, i.o, fi, x.t, NounType::ANY),
    Specialization5(NounType::ANY, i.o, fi, NounType::ANY, x.o),
    Specialization5(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY),

    Specialization5(NounType::ANY, NounType::ANY, fi, x.t, x.o),
    Specialization5(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY),
    Specialization5(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o),
    Specialization5(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY)
  };

  for(const auto& specialization : specializations)
  {
    const auto verb = dyadSources.find(specialization);
    if(verb != dyadSources.end())
    {
      return verb->second(i, x);
    }
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchTriadicEffect(const Storage& i, const Storage& f, const Storage& x, const Storage& y)
{
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (y.o == NounType::ERROR) {
    return y;
  }

  if(f.o != NounType::TRIADIC_EFFECT)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const std::vector<Specialization7> specializations = {
    Specialization7(i.t, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, y.t, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, y.o),

    Specialization7(i.t, i.o, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, y.o),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, NounType::ANY, y.o),

    Specialization7(i.t, i.o, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, y.t, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, y.t, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),

    Specialization7(i.t, i.o, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, i.o, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, NounType::ANY),

    Specialization7(i.t, NounType::ANY, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(i.t, NounType::ANY, fi, NounType::ANY, NounType::ANY, NounType::ANY, NounType::ANY),

    Specialization7(NounType::ANY, i.o, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, i.o, fi, NounType::ANY, NounType::ANY, NounType::ANY, NounType::ANY),

    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, x.t, NounType::ANY, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, x.o, NounType::ANY, NounType::ANY),
    Specialization7(NounType::ANY, NounType::ANY, fi, NounType::ANY, NounType::ANY, y.t, NounType::ANY),
  };

  for(const auto& specialization : specializations)
  {
    const auto verb = triadSources.find(specialization);
    if(verb != triadSources.end())
    {
      return verb->second(i, x, y);
    }
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

Storage Noun::dispatchConjunction(const Storage& i, const Storage& f, const Storage& x)
{
  if (f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  const auto specialization = Specialization1(fi);
  const auto verb = conjunctions.find(specialization);
  if(verb != conjunctions.end())
  {
    return verb->second(i, x);
  }

  return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
}

// Registration
void Noun::registerNilad(Type f, Storage (*m)())
{
  Noun::niladSources[Specialization1(f)] = m;
}

void Noun::registerMonad(Type it, Type io, Type f, Storage (*m)(const Storage&))
{
  Noun::monadSources[Specialization3(it, io, f)] = m;
}

void Noun::registerDyad(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&)) {
  Noun::dyadSources[Specialization5(it, io, f, xt, xo)] = d;
}

void Noun::registerTriad(Type it, Type io, Type f, Type xt, Type xo, Type yt, Type yo, Storage (*t)(const Storage&, const Storage&, const Storage&)) {
  Noun::triadSources[Specialization7(it, io, f, xt, xo, yt, yo)] = t;
}

void Noun::registerMonadicAdverb(Type it, Type io, Type f, Storage (*a)(const Storage&, const Storage&)) {
  Noun::monadicAdverbs[Specialization3(it, io, f)] = a;
}

void Noun::registerDyadicAdverb(Type it, Type io, Type f, Type xt, Type xo, Storage (*a)(const Storage&, const Storage&, const Storage&)) {
  Noun::dyadicAdverbs[Specialization5(it, io, f, xt, xo)] = a;
}

void Noun::registerConjunction(Type f, Storage (*c)(const Storage&, const Storage&))
{
  Noun::conjunctions[Specialization1(f)] = c;
}

void Noun::printDyad(const Storage& i, const Storage& f, const Storage& x)
{
  printf("Dyad:");
  i.print();
  printf(" ");
  Dyad::print(f);
  printf(" ");
  x.print();
  printf("\n");
}


Storage Noun::true0() {
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::true1(const Storage& i) {
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::true2(const Storage& i, const Storage& x) {
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::false0() {
  return Word::make(0, NounType::INTEGER);
}

Storage Noun::false1(const Storage& i) {
  return Word::make(0, NounType::INTEGER);
}

Storage Noun::false2(const Storage& i, const Storage& x) {
  return Word::make(0, NounType::INTEGER);
}

Storage Noun::identity1(const Storage& i)
{
  return i;
}

// Extension Monads - Implementations
Storage Noun::evaluate_expression(const Storage& e) // NOLINT
{
  using namespace iota;
  using iota::bind;

  if (std::holds_alternative<mixed>(e.i))
  {
    mixed items = std::get<mixed>(e.i);

    if (items.empty())
    {
      return e;
    }

    Storage i = items[0];

    if(i.o == NounType::ERROR)
    {
      return i;
    }

    // The first item might be a nilad effect
    if(i.o == NounType::NILADIC_EFFECT)
    {
      Storage result = dispatchNiladicEffect(i);
      if(items.size() == 1)
      {
        return result;
      }
      else
      {
        mixed rest(items.begin() + 1, items.end());

        rest.insert(rest.begin(), result);

        Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
        Storage result = evaluate_expression(next_e);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        return result;
      }
    }

    // If there is only one item, and it's not a nilad effect, then it must be a value.
    if (items.size() == 1) {
      return i;
    }

    // If there is more than one item, and the first item is not a nilad effect, then
    // - the first item is a value
    // - the second item is a function or non-nilad effect
    Storage f = items[1];

    mixed rest(items.begin() + 2, items.end());

    switch (f.o)
    {
      case NounType::BUILTIN_MONAD:
      {
        Storage result = dispatchMonad(i, f);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::USER_MONAD:
      {
        mixed ms = std::get<mixed>(f.i);
        ms.insert(ms.begin(), i);

        Storage result = evaluate_expression(MixedArray::make(ms, NounType::EXPRESSION));
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::BUILTIN_DYAD:
      {
        Storage x = items[2];

        if(x.o == NounType::ERROR)
        {
          return x;
        }

        if(x.o == NounType::BUILTIN_SYMBOL)
        {
          if(std::holds_alternative<int>(x.i))
          {
            int xi = std::get<int>(x.i);

            switch(xi)
            {
              case SymbolType::i:
                x = i;
                break;

              case SymbolType::x:
                break;

              case SymbolType::f:
                x = f;
                break;

              default:
                break;
            }
          }
        }

        rest = mixed(items.begin() + 3, items.end());

        if(x.o == NounType::EXPRESSION)
        {
          x = evaluate_expression(x);
        }

        if(x.o == NounType::ERROR)
        {
          return x;
        }

        Storage result = dispatchDyad(i, f, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::BUILTIN_TRIAD:
      {
        Storage x = items[2];
        Storage y = items[3];
        rest = mixed(items.begin() + 4, items.end());

        if(x.o == NounType::EXPRESSION)
        {
          x = evaluate_expression(x);
        }

        if(x.o == NounType::ERROR)
        {
          return x;
        }

        if(y.o == NounType::EXPRESSION)
        {
          y = evaluate_expression(y);
        }

        if(y.o == NounType::ERROR)
        {
          return y;
        }

        Storage result = dispatchTriad(i, f, x, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if (rest.empty())
        {
          return result;
        }

        rest.insert(rest.begin(), result);

        Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
        result = evaluate_expression(next_e);

        if(result.o == NounType::ERROR)
        {
          return result;
        }

        return result;
      }

      case NounType::MONADIC_ADVERB:
      {
        Storage g = items[2];
        rest = mixed(items.begin() + 3, items.end());

        Storage result = dispatchMonadicAdverb(i, f, g);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::DYADIC_ADVERB:
      {
        Storage g = items[2];
        Storage x = items[3];
        rest = mixed(items.begin() + 4, items.end());

        Storage result = Noun::dispatchDyadicAdverb(i, f, g, x);
        if(rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::MONADIC_EFFECT:
      {
        Storage result = dispatchMonadicEffect(i, f);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::DYADIC_EFFECT:
      {
        Storage x = items[2];
        rest = mixed(items.begin() + 3, items.end());

        if(x.o == NounType::EXPRESSION)
        {
          x = evaluate_expression(x);
        }

        if(x.o == NounType::ERROR)
        {
          return x;
        }

        Storage result = dispatchDyadicEffect(i, f, x);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::TRIADIC_EFFECT:
      {
        Storage x = items[2];
        Storage y = items[3];
        rest = mixed(items.begin() + 4, items.end());

        if(x.o == NounType::EXPRESSION)
        {
          x = evaluate_expression(x);
        }

        if(x.o == NounType::ERROR)
        {
          return x;
        }

        if(y.o == NounType::EXPRESSION)
        {
          y = evaluate_expression(y);
        }

        if(y.o == NounType::ERROR)
        {
          return y;
        }

        Storage result = dispatchTriadicEffect(i, f, x, y);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          if(result.o == NounType::ERROR)
          {
            return result;
          }

          return result;
        }
      }

      case NounType::CONJUNCTION:
      {
        rest = mixed(items.begin() + 2, items.end());
        Storage x = MixedArray::make(rest, NounType::EXPRESSION);

        Storage next_e = dispatchConjunction(i, f, x);
        auto result = evaluate_expression(next_e);

        if(result.o == NounType::ERROR)
        {
          return result;
        }

        return result;
      }

      default:
        return makeUnknownSymbolError(UNSUPPORTED_OBJECT, f);
    }
  }

  return makeError(UNSUPPORTED_OBJECT);
}

Storage Noun::mix(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();

    for(int y : iis)
    {
      results.push_back(Word::make(y, NounType::INTEGER));
    }

    return MixedArray::make(results, NounType::LIST);
  }  
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    mixed results = mixed();

    for(float y : iis)
    {
      results.push_back(Float::make(y, NounType::REAL));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return i;
  }
}

Storage Noun::simplify(const Storage& i) // NOLINT
{
  if(std::holds_alternative<int>(i.i) || std::holds_alternative<float>(i.i))
  {
    return i;
  }

  if(std::holds_alternative<ints>(i.i) || std::holds_alternative<floats>(i.i))
  {
    return i;
  }

  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    // You can't get any more simplified than an empty list.
    if(iis.empty())
    {
      return WordArray::nil();
    }

    // We can only simplify Lists of Integer, Real, or Character.
    for(const Storage& y : iis)
    {
      if((y.o != NounType::INTEGER) && (y.o != NounType::REAL) && (y.o != NounType::CHARACTER))
      {
        return i;
      }
    }

    int all_integers = 1;
    int all_reals = 1;
    int all_characters = 1;
    for(const Storage& y : iis)
    {
      if((y.t == StorageType::WORD) && (y.o == NounType::INTEGER))
      {
        all_reals = 0;
        all_characters = 0;

        if(!all_integers)
        {
          break;
        }
      }
      else if((y.t == StorageType::FLOAT) && (y.o == NounType::REAL))
      {
        all_integers = 0;
        all_characters = 0;

        if(!all_reals)
        {
          break;
        }
      }
      else if((y.t == StorageType::WORD) && (y.o == NounType::CHARACTER))
      {
        all_integers = 0;
        all_reals = 0;

        if(!all_characters)
        {
          break;
        }
      }
      else
      {
        all_reals = 0;
        all_integers = 0;
        all_characters = 0;
        break;
      }
    }

    if(all_integers)
    {
      // A simplified all-integer List is a WordArray
      ints results = ints();
      for(Storage y : iis)
      {
        int result = std::get<int>(y.i);

        results.push_back(result);
      }

      return WordArray::make(results);
    }    
    else if(all_reals)
    {
      // A simplified all-float List is a FloatArray
      floats results = floats();
      for(Storage y : iis)
      {
        float result = std::get<float>(y.i);

        results.push_back(result);
      }

      return FloatArray::make(results);
    }
    else if(all_characters)
    {
      // A simplified all-character List is a String
      ints results = ints();
      for(Storage y : iis)
      {
        int result = std::get<int>(y.i);

        results.push_back(result);
      }

      return WordArray::make(results, NounType::STRING);
    }    
    else
    {
      // We can recursively simplify sub-lists.
      mixed results = mixed();
      for(const Storage& y : iis)
      {
        results.push_back(simplify(y));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return makeError(UNSUPPORTED_OBJECT);
}

int getInteger(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    return ii;
  }

  return 0;
}

float getReal(const Storage& i)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);
    return ii;
  }

  return 0.0;
}

ints getIntegers(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    return integers;
  }

  return {};
}

floats getReals(const Storage& i)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    return fs;
  }

  return {};
}

mixed getMixed(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    return ms;
  }

  return {};
}

int isNil(const Storage& i)
{
  using namespace iota;

  return getInteger(eval({i, match, WordArray::nil()}));
}

int isAtom(const Storage& i)
{
  using namespace iota;

  return getInteger(eval({i, atom}));
}

int getSize(const Storage& i)
{
  using namespace iota;

  return getInteger(eval({i, size}));
}

// Extension Dyads - Implementations
Storage Noun::join_scalar(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({eval({i, enclose}), join, eval({x, enclose})});
}

Storage Noun::prepend(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({eval({i, enclose}), join, x});
}

Storage Noun::append(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({i, join, eval({x, enclose})});
}

Storage Noun::join_mixed(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({Noun::mix(i), join, Noun::mix(x)});
}

Storage Noun::join_mix_left(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({Noun::mix(i), join, x});
}

Storage Noun::join_mix_right(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({i, join, Noun::mix(x)});
}

Storage Noun::join_enclose_mix(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({eval({i, enclose}), join, Noun::mix(x)});
}

Storage Noun::join_mix_enclose(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({Noun::mix(i), join, eval({x, enclose})});
}

Storage Noun::identity2(const Storage& i, const Storage& x)
{
  return i;
}

Storage Noun::enclose2(const Storage& i, const Storage& x)
{
  using namespace iota;

  return eval({i, enclose});
}

// Monadic Adverbs
// FIXME - previous may escape
Storage Noun::converge_impl(const Storage& i, const Storage& f)
{
  using namespace iota;

  Storage previous = i;
  Storage equivalence = Noun::false0();

  for(int iterations = 0; iterations < Noun::maximumConvergeIterations; iterations++)
  {
    Storage next = dispatchMonad(previous, f);
    if(next.o == NounType::ERROR)
    {
      return next; // FIXME, clang-tidy warning about address escaping function
    }

    equivalence = eval({next, match, previous});
    previous = next;

    if(equivalence.truth())
    {
      return next; // FIXME, also here
    }
  }

  return Word::make(MAXIMUM_ITERATIONS, NounType::ERROR);
}

Storage Noun::scanConverging_impl(const Storage& i, const Storage& f)
{
  using namespace iota;

  Storage previous = i;
  Storage equivalence = Noun::false0();

  mixed results = mixed({i});

  for(int iterations = 0; iterations < Noun::maximumConvergeIterations; iterations++)
  {
    Storage next = dispatchMonad(previous, f);
    if(next.o == NounType::ERROR)
    {
      return next; // FIXME - also here
    }

    equivalence = eval({next, match, previous});
    previous = next;

    if(equivalence.truth())
    {
      return Noun::simplify(MixedArray::make(results));
    }
    else
    {
      results.push_back(next);
    }
  }

  return Word::make(MAXIMUM_ITERATIONS, NounType::ERROR);
}

// Dyadic Adverbs
Storage Noun::each2_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(isNil(i))
  {
    return i;
  }

  if(isNil(x))
  {
    return x;
  }

  if(isAtom(i) || isAtom(x))
  {
    return dispatchDyad(i, f, x);
  }

  int is = getSize(i);
  int xs = getSize(x);

  int max = std::min(is, xs);

  mixed results = mixed();
  for(int offset = 1; offset <= max; offset++)
  {
    Storage y = eval({i, iota::index, Word::make(offset)});
    Storage z = eval({x, iota::index, Word::make(offset)});
    Storage result = Noun::dispatchDyad(y, f, z);

    if(result.o == NounType::ERROR)
    {
      return result;
    }

    results.push_back(result);
  }

  return Noun::simplify(MixedArray::make(results));
}

Storage Noun::eachLeft_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(isNil(i))
  {
    return i;
  }

  if(isAtom(i))
  {
    return dispatchDyad(i, f, x);
  }

  int is = getSize(i);

  mixed results = mixed();
  for(int offset = 1; offset <= is; offset++)
  {
    Storage y = eval({i, iota::index, Word::make(offset)});

    Storage result = Noun::dispatchDyad(y, f, x);

    if(result.o == NounType::ERROR)
    {
      return result;
    }

    results.push_back(result);
  }

  return Noun::simplify(MixedArray::make(results));
}

Storage Noun::eachRight_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(isNil(i))
  {
    return i;
  }

  if(isAtom(i))
  {
    return dispatchDyad(i, f, x);
  }

  int is = getSize(i);

  mixed results = mixed();
  for(int offset = 1; offset <= is; offset++)
  {
    Storage y = eval({i, iota::index, Word::make(offset)});

    Storage result = Noun::dispatchDyad(x, f, y);

    if(result.o == NounType::ERROR)
    {
      return result;
    }

    results.push_back(result);
  }

  return Noun::simplify(MixedArray::make(results));
}

Storage Noun::overNeutral_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(isNil(i))
  {
    return x;
  }

  if(isAtom(i) && isAtom(x))
  {
    return dispatchDyad(i, f, x);
  }

  // The next two lines are to dispel the perception that we accidentally swapped the order of the arguments i and x.
  const Storage& swapI = x;
  const Storage& swapX = i;
  return eval({prepend(swapI, swapX), over, f});
}

Storage Noun::iterate_integer(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(x.o == NounType::INTEGER)
  {
    Storage current = i;
    Storage countdown = x;
    while(eval({countdown, more, Integer::zero()}).truth())
    {
      current = dispatchMonad(current, f);
      if(current.o == NounType::ERROR)
      {
        return current;
      }

      countdown = eval({countdown, minus, Integer::one()});
      if(countdown.o == NounType::ERROR)
      {
        return countdown;
      }
    }

    return current;
  }

  return makeError(UNSUPPORTED_OBJECT);
}

Storage Noun::scanIterating_integer(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(x.o == NounType::INTEGER)
  {
    mixed results = mixed({i});

    Storage current = i;
    Storage countdown = x;
    while(eval({countdown, more, Integer::zero()}).truth())
    {
      current = dispatchMonad(current, f);
      if(current.o == NounType::ERROR)
      {
        return current;
      }

      countdown = eval({countdown, minus, Integer::one()});
      if(countdown.o == NounType::ERROR)
      {
        return countdown;
      }

      results.push_back(current);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return makeError(UNSUPPORTED_OBJECT);
}

Storage Noun::scanOverNeutral_impl(const Storage& i, const Storage& f, const Storage& x)
{
  using namespace iota;

  if(isNil(i))
  {
    return x;
  }

  if(isAtom(i) && isAtom(x))
  {
    return prepend(i, dispatchDyad(i, f, x));
  }

  return eval({prepend(x, i), scanOver, f});
}

// FIXME - address leak
Storage Noun::scanWhileOne_impl(const Storage& i, const Storage& f, const Storage& g)
{
  mixed results = mixed();

  Storage current = i;
  Storage t = Noun::dispatchMonad(current, f);

  if(t.o == NounType::ERROR)
  {
    return t; // FIXME - also here
  }

  while(t.truth())
  {
    results.push_back(current);

    current = dispatchMonad(current, g);
    if(current.o == NounType::ERROR)
    {
      return t; // FIXME - also here
    }

    t = dispatchMonad(current, f);
    if(t.o == NounType::ERROR)
    {
      return t; // FIXME - also here
    }
  }

  return Noun::simplify(MixedArray::make(results));
}

Storage Noun::whileOne_impl(const Storage& i, const Storage& f, const Storage& g)
{
  Storage current = i;
  Storage t = Noun::dispatchMonad(current, f);

  if(t.o == NounType::ERROR)
  {
    return t; // FIXME - also here
  }

  while(t.truth())
  {
    current = dispatchMonad(current, g);
    if(current.o == NounType::ERROR)
    {
      return t; // FIXME - also here
    }


    t = dispatchMonad(current, f);
    if(t.o == NounType::ERROR)
    {
      return t; // FIXME - also here
    }
  }

  return current;
}

// Serialization
// Noun::from_bytes decodes a byte array into a Storage object by delegating to each Storage subclass's decoder
maybe<Storage> Noun::from_bytes(bytes x) {
  int t = static_cast<unsigned char>(x.at(0));
  int o = static_cast<unsigned char>(x.at(1));
  bytes untypedData(x.begin() + 2, x.end());

  switch (o) {
    case NounType::INTEGER:
      {
        return maybe<Storage>(Integer::from_bytes(untypedData, t));
      }

    case NounType::REAL:
      {
        return maybe<Storage>(Real::from_bytes(untypedData, t));
      }

    case NounType::LIST:
      {
        return maybe<Storage>(List::from_bytes(untypedData, t));
      }

    case NounType::CHARACTER:
      {
        return maybe<Storage>(Character::from_bytes(untypedData, t));
      }

    case NounType::STRING:
      {
        return maybe<Storage>(IotaString::from_bytes(untypedData, t));
      }

    default:
      switch (t) {
        case StorageType::WORD:
          {
            return maybe<Storage>(Word::from_bytes(untypedData, o));
          }

        case StorageType::FLOAT:
          {
            return maybe<Storage>(Float::from_bytes(untypedData, o));
          }

        case StorageType::WORD_ARRAY:
          {
            return maybe<Storage>(WordArray::from_bytes(untypedData, o));
          }

        case StorageType::FLOAT_ARRAY:
          {
            return maybe<Storage>(FloatArray::from_bytes(untypedData, o));
          }

        case StorageType::MIXED_ARRAY:
          {
            return maybe<Storage>(MixedArray::from_bytes(untypedData, o));
          }

        default:
          return std::nullopt;
      }
  }
}

// Encodes a Storage into a byte array by delegating to each subclass
// Format: byte:t byte:o [byte]:subclass.from_bytes(i)
bytes Noun::to_bytes(const Storage& x) {
  // Noun::to_bytes includes type, never include type in any other to_bytes
  bytes typeBytes = { static_cast<char>(x.t), static_cast<char>(x.o) };

  bytes valueBytes = bytes();
  switch (x.o) {
    case NounType::INTEGER:
      {
        if (maybe<bytes> maybeValueBytes = Integer::to_bytes(x)) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return {};
        }
      }

    case NounType::REAL:
      {
        if (maybe<bytes> maybeValueBytes = Real::to_bytes(x)) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return {};
        }
      }

    case NounType::LIST:
      {
        if (maybe<bytes> maybeValueBytes = List::to_bytes(x)) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return {};
        }
      }

    case NounType::CHARACTER:
      {
        if (maybe<bytes> maybeValueBytes = Character::to_bytes(x)) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return {};
        }
      }

    case NounType::STRING:
      {
        if (maybe<bytes> maybeValueBytes = IotaString::to_bytes(x)) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return {};
        }
      }

    default:
      return {};
  }

  bytes result(typeBytes.begin(), typeBytes.end());
  result.insert(result.end(), valueBytes.begin(), valueBytes.end());
  return result;
}

maybe<Storage> Noun::from_conn(Connection& conn, Logger* logger) {
  int storageType = static_cast<unsigned char>(conn.readOne());

  int objectType = static_cast<unsigned char>(conn.readOne());

  switch (objectType)
  {
    case NounType::INTEGER:
      return maybe<Storage>(Integer::from_conn(conn, storageType, logger));

    case NounType::REAL:
      return maybe<Storage>(Real::from_conn(conn, storageType));

    case NounType::LIST:
      return maybe<Storage>(List::from_conn(conn, storageType));

    case NounType::CHARACTER:
      return maybe<Storage>(Character::from_conn(conn, storageType));

    case NounType::STRING:
      return maybe<Storage>(IotaString::from_conn(conn, storageType));

    default:
      switch (storageType) {
        case StorageType::WORD:
          {
            return maybe<Storage>(Word::from_conn(conn, objectType, nullptr));
          }

        case StorageType::FLOAT:
          {
            return maybe<Storage>(Float::from_conn(conn, objectType));
          }

        case StorageType::WORD_ARRAY:
          {
            return maybe<Storage>(WordArray::from_conn(conn, objectType));
          }

        case StorageType::FLOAT_ARRAY:
          {
            return maybe<Storage>(FloatArray::from_conn(conn, objectType));
          }

        case StorageType::MIXED_ARRAY:
          {
            return maybe<Storage>(MixedArray::from_conn(conn, objectType, nullptr));
          }

        default:
          return std::nullopt;
      }
  }
}

void Noun::to_conn(Connection& conn, const Storage& x) {
  // Storage.to_conn does not include type information, always include it in the specific to_conn implementation
  switch (x.o) {
    case NounType::INTEGER:
      {
        Integer::to_conn(conn, x);
        return;
      }

    case NounType::REAL:
      {
        Real::to_conn(conn, x);
        return;
      }

    case NounType::LIST:
      {
        List::to_conn(conn, x);
        return;
      }

    case NounType::CHARACTER:
      {
        Character::to_conn(conn, x);
        return;
      }

    case NounType::STRING:
      {
        IotaString::to_conn(conn, x);
        return;
      }

    default:
      switch (x.t) {
        case StorageType::WORD:
          Word::to_conn(conn, x);
          return;

        case StorageType::FLOAT:
          Float::to_conn(conn, x);
          return;

        case StorageType::WORD_ARRAY:
          WordArray::to_conn(conn, x);
          return;

        case StorageType::FLOAT_ARRAY:
          FloatArray::to_conn(conn, x);
          return;

        case StorageType::MIXED_ARRAY:
          MixedArray::to_conn(conn, x);
          return;

        default:
          Word::to_conn(conn, Word::make(UNSUPPORTED_OBJECT, NounType::ERROR));
          return; 
      }
  }
}

// Monads
Storage Noun::enclose_impl(const Storage& i) {
  return MixedArray::make(mixed({ i }), NounType::LIST);
}

Storage Noun::shape_scalar(const Storage& i)
{
  return Word::make(0, NounType::INTEGER);
}

void Noun::setLogger(Logger* newLogger)
{
  logger = newLogger;
  List::logger = logger;
  WordArray::logger = logger;
}
