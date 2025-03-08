#include <cmath>
#include <vector>
#include <variant>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <limits>
#include <numeric>

#include "noun.h"
#include "squeeze.h"
#include "symbols.h"
#include "error.h"

// Verbs
// Monads
Storage atom(const Storage& i)  // @a
{
  return Noun::dispatchMonad(i, Word::make(Monads::atom, NounType::BUILTIN_MONAD));
}

Storage ichar(const Storage& i)  // :#a
{
  return Noun::dispatchMonad(i, Word::make(Monads::ichar, NounType::BUILTIN_MONAD));
}

Storage enclose(const Storage& i)  // ,a
{
  return Noun::dispatchMonad(i, Word::make(Monads::enclose, NounType::BUILTIN_MONAD));
}

Storage enumerate(const Storage& i)  // !a
{
  return Noun::dispatchMonad(i, Word::make(Monads::enumerate, NounType::BUILTIN_MONAD));
}

Storage expand(const Storage& i, const Storage& x) // &b
{
  return Noun::dispatchDyad(i, Word::make(Monads::expand, NounType::BUILTIN_MONAD), x);
}

Storage first(const Storage& i)  // *a
{
  return Noun::dispatchMonad(i, Word::make(Monads::first, NounType::BUILTIN_MONAD));
}

Storage floor(const Storage& i)  // _a
{
  return Noun::dispatchMonad(i, Word::make(Monads::floor, NounType::BUILTIN_MONAD));
}

Storage format(const Storage& i)  // $a
{
  return Noun::dispatchMonad(i, Word::make(Monads::format, NounType::BUILTIN_MONAD));
}

Storage gradeDown(const Storage& i)  // >a
{
  return Noun::dispatchMonad(i, Word::make(Monads::gradeDown, NounType::BUILTIN_MONAD));
}

Storage gradeUp(const Storage& i)  // <a
{
  return Noun::dispatchMonad(i, Word::make(Monads::gradeUp, NounType::BUILTIN_MONAD));
}

Storage group(const Storage& i)  // =a
{
  return Noun::dispatchMonad(i, Word::make(Monads::group, NounType::BUILTIN_MONAD));
}

Storage negate(const Storage& i) // -a
{
  return Noun::dispatchMonad(i, Word::make(Monads::negate, NounType::BUILTIN_MONAD));
}

Storage inot(const Storage& i)  // ~a
{
  return Noun::dispatchMonad(i, Word::make(Monads::inot, NounType::BUILTIN_MONAD));
}

Storage reciprocal(const Storage& i) // %a
{
  return Noun::dispatchMonad(i, Word::make(Monads::reciprocal, NounType::BUILTIN_MONAD));
}

Storage reverse(const Storage& i) // |a
{
  return Noun::dispatchMonad(i, Word::make(Monads::reciprocal, NounType::BUILTIN_MONAD));
}

Storage shape(const Storage& i) // ^a
{
  return Noun::dispatchMonad(i, Word::make(Monads::shape, NounType::BUILTIN_MONAD));
}

Storage size(const Storage& i) // #a
{
  return Noun::dispatchMonad(i, Word::make(Monads::size, NounType::BUILTIN_MONAD));
}

Storage transpose(const Storage& i) // +a
{
  return Noun::dispatchMonad(i, Word::make(Monads::transpose, NounType::BUILTIN_MONAD));
}

Storage unique(const Storage& i) // ?a
{
  return Noun::dispatchMonad(i, Word::make(Monads::unique, NounType::BUILTIN_MONAD));
}

Storage undefined(const Storage& i) // ?a
{
  return Noun::dispatchMonad(i, Word::make(Monads::undefined, NounType::BUILTIN_MONAD));
}

// Extension Monads
Storage evaluate(const Storage& i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::evaluate, NounType::BUILTIN_MONAD));
}

Storage erase(const Storage& i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::erase, NounType::BUILTIN_MONAD));
}

Storage truth(const Storage& i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::truth, NounType::BUILTIN_MONAD));
}

// Dyads
Storage amend(const Storage& i, const Storage& x) // a:_b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::amend, NounType::BUILTIN_DYAD), x);
}

Storage cut(const Storage& i, const Storage& x) // a:_b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::cut, NounType::BUILTIN_DYAD), x);
}

Storage divide(const Storage& i, const Storage& x) // a%b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::divide, NounType::BUILTIN_DYAD), x);
}

Storage drop(const Storage& i, const Storage& x) // a_b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::drop, NounType::BUILTIN_DYAD), x);
}

Storage equal(const Storage& i, const Storage& x) // a=b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::equal, NounType::BUILTIN_DYAD), x);
}

Storage find(const Storage& i, const Storage& x) // a?b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::find, NounType::BUILTIN_DYAD), x);
}

Storage form(const Storage& i, const Storage& x) // a:$b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::form, NounType::BUILTIN_DYAD), x);
}

Storage format2(const Storage& i, const Storage& x) // a$b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::format2, NounType::BUILTIN_DYAD), x);
}

Storage index(const Storage& i, const Storage& x) // a@b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::index, NounType::BUILTIN_DYAD), x);
}

Storage integerDivide(const Storage& i, const Storage& x) // a%b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::integerDivide, NounType::BUILTIN_DYAD), x);
}

Storage join(const Storage& i, const Storage& x) // a,b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::join, NounType::BUILTIN_DYAD), x);
}

Storage less(const Storage& i, const Storage& x) // a<b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::less, NounType::BUILTIN_DYAD), x);
}

Storage match(const Storage& i, const Storage& x) // a~b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::match, NounType::BUILTIN_DYAD), x);
}

Storage max(const Storage& i, const Storage& x) // a|b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::max, NounType::BUILTIN_DYAD), x);
}

Storage min(const Storage& i, const Storage& x) // a&b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::min, NounType::BUILTIN_DYAD), x);
}

Storage minus(const Storage& i, const Storage& x) // a-b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::minus, NounType::BUILTIN_DYAD), x);
}

Storage more(const Storage& i, const Storage& x) // a>b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::more, NounType::BUILTIN_DYAD), x);
}

Storage plus(const Storage& i, const Storage& x) // a+b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::plus, NounType::BUILTIN_DYAD), x);
}

Storage power(const Storage& i, const Storage& x) // a^b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::power, NounType::BUILTIN_DYAD), x);
}

Storage remainder(const Storage& i, const Storage& x) // a!b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::remainder, NounType::BUILTIN_DYAD), x);
}

Storage reshape(const Storage& i, const Storage& x) // a:^b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::reshape, NounType::BUILTIN_DYAD), x);
}

Storage rotate(const Storage& i, const Storage& x) // a:+b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::rotate, NounType::BUILTIN_DYAD), x);
}

Storage split(const Storage& i, const Storage& x) // a:#b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::split, NounType::BUILTIN_DYAD), x);
}

Storage take(const Storage& i, const Storage& x) // a#b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::take, NounType::BUILTIN_DYAD), x);
}

Storage times(const Storage& i, const Storage& x) // a*b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::times, NounType::BUILTIN_DYAD), x);
}

// Monadic Adverbs
Storage converge(const Storage& i, const Storage& f) // f:~a
{
  return Noun::dispatchMonadicAdverb(i, Word::make(MonadicAdverbs::converge, NounType::MONADIC_ADVERB), f);
}

Storage each(const Storage& i, const Storage& f) // f'a
{
  return Noun::dispatchMonadicAdverb(i, Word::make(MonadicAdverbs::each, NounType::MONADIC_ADVERB), f);
}

Storage eachPair(const Storage& i, const Storage& f) // f:'a
{
  return Noun::dispatchMonadicAdverb(i, Word::make(MonadicAdverbs::eachPair, NounType::MONADIC_ADVERB), f);
}

Storage over(const Storage& i, const Storage& f) // f/a
{
  return Noun::dispatchMonadicAdverb(i, Word::make(MonadicAdverbs::over, NounType::MONADIC_ADVERB), f);
}

Storage scanConverging(const Storage& i, const Storage& f) // f:~a
{
  return Noun::dispatchMonadicAdverb(i, Word::make(MonadicAdverbs::scanConverging, NounType::MONADIC_ADVERB), f);
}

Storage scanOver(const Storage& i, const Storage& f) // f\a
{
  return Noun::dispatchMonadicAdverb(i, Word::make(MonadicAdverbs::scanOver, NounType::MONADIC_ADVERB), f);
}

// Dyadic Adverbs
Storage each2(const Storage& i, const Storage& f, const Storage& x) // a f'b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::each2, NounType::MONADIC_ADVERB), f, x);
}

Storage eachLeft(const Storage& i, const Storage& f, const Storage& x) // a f'b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::eachLeft, NounType::MONADIC_ADVERB), f, x);
}

Storage eachRight(const Storage& i, const Storage& f, const Storage& x) // a f'b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::eachRight, NounType::MONADIC_ADVERB), f, x);
}

Storage overNeutral(const Storage& i, const Storage& f, const Storage& x) // a f'b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::overNeutral, NounType::MONADIC_ADVERB), f, x);
}

Storage iterate(const Storage& i, const Storage& f, const Storage& x) // a f:*b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::iterate, NounType::MONADIC_ADVERB), f, x);
}

Storage scanIterating(const Storage& i, const Storage& f, const Storage& x) // a f\*b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::scanIterating, NounType::MONADIC_ADVERB), f, x);
}

Storage scanOverNeutral(const Storage& i, const Storage& f, const Storage& x) // a f\b 
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::scanOverNeutral, NounType::MONADIC_ADVERB), f, x);
}

Storage whileOne(const Storage& i, const Storage& f, const Storage& x) // a f\b 
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::whileOne, NounType::MONADIC_ADVERB), f, x);
}

Storage scanWhileOne(const Storage& i, const Storage& f, const Storage& x) // a f\b
{
  return Noun::dispatchDyadicAdverb(i, Word::make(DyadicAdverbs::scanWhileOne, NounType::MONADIC_ADVERB), f, x);
}

std::map<Specialization3, Monad> Noun::monads;
std::map<Specialization5, Dyad> Noun::dyads;
std::map<Specialization5, Triad> Noun::triads;
std::map<Specialization3, MonadicAdverb> Noun::monadicAdverbs;
std::map<Specialization5, DyadicAdverb> Noun::dyadicAdverbs;

void Noun::initialize() {
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
}

// Dispatch
Storage Noun::dispatchMonad(const Storage& i, const Storage& f) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monads.find(specialization) == monads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Monad verb = monads[specialization];
  return verb(i);
}

Storage Noun::dispatchDyad(const Storage& i, const Storage& f, const Storage& x) {
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

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyads.find(specialization) == dyads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Dyad verb = dyads[specialization];
  return verb(i, x);
}

Storage Noun::dispatchTriad(const Storage& i, const Storage& f, const Storage& x, const Storage& y)
{
  if (i.o == NounType::ERROR)
  {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (triads.find(specialization) == triads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Triad verb = triads[specialization];
  return verb(i, x, y);
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

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monadicAdverbs.find(specialization) == monadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  MonadicAdverb adverb = monadicAdverbs[specialization];
  return adverb(i, g);
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

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyadicAdverbs.find(specialization) == dyadicAdverbs.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  DyadicAdverb adverb = dyadicAdverbs[specialization];
  return adverb(i, g, x);
}

// Registration

void Noun::registerMonad(Type it, Type io, Type f, Storage (*m)(const Storage&))
{
  Noun::monads[Specialization3(it, io, f)] = m;
}

void Noun::registerDyad(Type it, Type io, Type f, Type xt, Type xo, Storage (*d)(const Storage&, const Storage&)) {
  Noun::dyads[Specialization5(it, io, f, xt, xo)] = d;
}

void Noun::registerTriad(Type it, Type io, Type f, Type xt, Type xo, Storage (*t)(const Storage&, const Storage&, const Storage&)) {
  Noun::triads[Specialization5(it, io, f, xt, xo)] = t;
}

void Noun::registerMonadicAdverb(Type it, Type io, Type f, Storage (*a)(const Storage&, const Storage&)) {
  Noun::monadicAdverbs[Specialization3(it, io, f)] = a;
}

void Noun::registerDyadicAdverb(Type it, Type io, Type f, Type xt, Type xo, Storage (*a)(const Storage&, const Storage&, const Storage&)) {
  Noun::dyadicAdverbs[Specialization5(it, io, f, xt, xo)] = a;
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
Storage Noun::evaluate_expression(const Storage& e)
{
  if (std::holds_alternative<mixed>(e.i))
  {
    mixed items = std::get<mixed>(e.i);

    if (items.empty())
    {
      return e;
    }

    Storage i = items[0];

    if (items.size() == 1) {
      return i;
    }

    Storage f = items[1];

    mixed rest(items.begin() + 2, items.end());

    switch (f.o)
    {
      case NounType::BUILTIN_MONAD:
      {
        Storage result = Noun::dispatchMonad(i, f);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          return result;
        }
      }

      case NounType::BUILTIN_DYAD:
      {
        Storage x = items[2];
        rest = mixed(items.begin() + 3, items.end());

        Storage result = Noun::dispatchDyad(i, f, x);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          return result;
        }
      }

      case NounType::MONADIC_ADVERB:
      {
        Storage g = items[2];
        rest = mixed(items.begin() + 3, items.end());

        Storage result = Noun::dispatchMonadicAdverb(i, f, g);
        if(rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

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

          return result;
        }
      }

      // FIXME - add case for BUILTIN_TRIAD

      default:
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
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

Storage Noun::simplify(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    return i;
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    return i;
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return WordArray::nil();
    }

    int all_integers = 1;
    int all_reals = 1;
    int all_characters = 1;
    for(Storage y : iis)
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
      return i;
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
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

  return ints();
}

floats getReals(const Storage& i)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    return fs;
  }

  return floats();
}

mixed getMixed(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    return ms;
  }

  return mixed();
}

int isNil(const Storage& i)
{
  return getInteger(match(i, WordArray::nil()));
}

int isAtom(const Storage& i)
{
  return getInteger(atom(i));
}

int getSize(const Storage& i)
{
  return getInteger(size(i));
}

// Extension Dyads - Implementations
Storage Noun::join_scalar(const Storage& i, const Storage& x)
{
  return join(enclose(i), enclose(x));
}

Storage Noun::prepend(const Storage& i, const Storage& x)
{
  return join(enclose(i), x);
}

Storage Noun::append(const Storage& i, const Storage& x)
{
  return join(i, enclose(x));
}

Storage Noun::join_mixed(const Storage& i, const Storage& x)
{
  return join(Noun::mix(i), Noun::mix(x));
}

Storage Noun::join_mix_left(const Storage& i, const Storage& x)
{
  return join(Noun::mix(i), x);
}

Storage Noun::join_mix_right(const Storage& i, const Storage& x)
{
  return join(i, Noun::mix(x));
}

Storage Noun::join_enclose_mix(const Storage& i, const Storage& x)
{
  return join(enclose(i), mix(x));
}

Storage Noun::join_mix_enclose(const Storage& i, const Storage& x)
{
  return join(mix(i), enclose(x));
}

Storage Noun::identity2(const Storage& i, const Storage& x)
{
  return i;
}

Storage Noun::enclose2(const Storage& i, const Storage& x)
{
  return enclose(i);
}

// Monadic Adverbs
Storage Noun::converge_impl(const Storage& i, const Storage& f)
{
  Storage previous = i;
  Storage equivalence = Noun::false0();

  for(int iterations = 0; iterations < Noun::maximumConvergeIterations; iterations++)
  {
    Storage next = dispatchMonad(previous, f);
    if(next.o == NounType::ERROR)
    {
      return next;
    }

    Storage equivalence = match(next, previous);
    previous = next;

    if(equivalence.truth())
    {
      return next;
    }
  }

  return Word::make(MAXIMUM_ITERATIONS, NounType::ERROR);
}

Storage Noun::scanConverging_impl(const Storage& i, const Storage& f)
{
  Storage previous = i;
  Storage equivalence = Noun::false0();

  mixed results = mixed({i});

  for(int iterations = 0; iterations < Noun::maximumConvergeIterations; iterations++)
  {
    Storage next = dispatchMonad(previous, f);
    if(next.o == NounType::ERROR)
    {
      return next;
    }

    Storage equivalence = match(next, previous);
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
    Storage y = index(i, Word::make(offset));
    Storage z = index(x, Word::make(offset));
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
    Storage y = index(i, Word::make(offset));

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
    Storage y = index(i, Word::make(offset));

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
  if(isNil(i))
  {
    return x;
  }

  if(isAtom(i) && isAtom(x))
  {
    return dispatchDyad(i, f, x);
  }

  return over(prepend(x, i), f);
}

Storage Noun::iterate_integer(const Storage& i, const Storage& f, const Storage& x)
{
  if(x.o == NounType::INTEGER)
  {
    Storage current = i;
    Storage countdown = x;
    while(more(countdown, Word::make(0)).truth())
    {
      current = dispatchMonad(current, f);
      if(current.o == NounType::ERROR)
      {
        return current;
      }

      countdown = minus(countdown, Word::make(1));
      if(countdown.o == NounType::ERROR)
      {
        return countdown;
      }
    }

    return current;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Noun::scanIterating_integer(const Storage& i, const Storage& f, const Storage& x)
{
  if(x.o == NounType::INTEGER)
  {
    mixed results = mixed({i});

    Storage current = i;
    Storage countdown = x;
    while(more(countdown, Word::make(0)).truth())
    {
      current = dispatchMonad(current, f);
      if(current.o == NounType::ERROR)
      {
        return current;
      }

      countdown = minus(countdown, Word::make(1));
      if(countdown.o == NounType::ERROR)
      {
        return countdown;
      }

      results.push_back(current);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Noun::scanOverNeutral_impl(const Storage& i, const Storage& f, const Storage& x)
{
  if(isNil(i))
  {
    return x;
  }

  if(isAtom(i) && isAtom(x))
  {
    return prepend(i, dispatchDyad(i, f, x));
  }

  return scanOver(prepend(x, i), f);
}

Storage Noun::scanWhileOne_impl(const Storage& i, const Storage& f, const Storage& g)
{
  mixed results = mixed();

  Storage current = i;
  Storage t = Noun::dispatchMonad(current, f);

  if(t.o == NounType::ERROR)
  {
    return t;
  }

  while(t.truth())
  {
    results.push_back(current);

    current = dispatchMonad(current, g);
    if(current.o == NounType::ERROR)
    {
      return t;
    }


    t = dispatchMonad(current, f);
    if(t.o == NounType::ERROR)
    {
      return t;
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
    return t;
  }

  while(t.truth())
  {
    current = dispatchMonad(current, g);
    if(current.o == NounType::ERROR)
    {
      return t;
    }


    t = dispatchMonad(current, f);
    if(t.o == NounType::ERROR)
    {
      return t;
    }
  }

  return current;
}

// Serialization
// Noun::from_bytes decodes a byte array into a Storage object by delegating to each Storage subclass's decoder
maybe<Storage> Noun::from_bytes(bytes x) {
  int t = (int)x.at(0);
  int o = (int)x.at(1);
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
      }

      return std::nullopt;
  }
}

// Encodes a Storage into a byte array by delegating to each subclass
// Format: byte:t byte:o [byte]:subclass.from_bytes(i)
bytes Noun::to_bytes(const Storage& x) {
  // Noun::to_bytes includes type, never include type in any other to_bytes
  bytes typeBytes = { (char)x.t, (char)x.o };

  bytes valueBytes = bytes();
  switch (x.o) {
    case NounType::INTEGER:
      {
        maybe<bytes> maybeValueBytes = Integer::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::REAL:
      {
        maybe<bytes> maybeValueBytes = Real::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::LIST:
      {
        maybe<bytes> maybeValueBytes = List::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::CHARACTER:
      {
        maybe<bytes> maybeValueBytes = Character::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::STRING:
      {
        maybe<bytes> maybeValueBytes = IotaString::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    default:
      return bytes();
  }

  bytes result(typeBytes.begin(), typeBytes.end());
  result.insert(result.end(), valueBytes.begin(), valueBytes.end());
  return result;
}

maybe<Storage> Noun::from_conn(const Connection& conn) {
  int storageType = (int)conn.readOne();
  int objectType = (int)conn.readOne();

  switch (objectType) {
    case NounType::INTEGER:
      return maybe<Storage>(Integer::from_conn(conn, storageType));

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
            return maybe<Storage>(Word::from_conn(conn, objectType));
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
            return maybe<Storage>(MixedArray::from_conn(conn, objectType));
          }

        default:
          return std::nullopt;
      }
  }
}

void Noun::to_conn(const Connection& conn, const Storage& x) {
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

// Integer
void Integer::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::ichar, Integer::char_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enclose, Integer::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::expand, Integer::expand_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enumerate, Integer::enumerate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::format, Integer::format_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::floor, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::negate, Integer::negate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::inot, Integer::not_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::reciprocal, Integer::reciprocal_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::size, Integer::size_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::evaluate, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::INTEGER, Monads::evaluate, Noun::identity1);

  // Dyads
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, Integer::cut_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::cut_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::MIXED_ARRAY, NounType::LIST, Integer::cut_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD, NounType::INTEGER, Integer::divide_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT, NounType::REAL, Integer::divide_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Integer::divide_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::divide_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Integer::divide_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::equal, StorageType::WORD, NounType::INTEGER, Integer::equal_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD, NounType::INTEGER, Integer::integerDivide_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::INTEGER, Integer::join_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::prepend_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD, NounType::INTEGER, Integer::less_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::FLOAT, NounType::REAL, Integer::less_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, Integer::less_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::less_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, Integer::less_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD, NounType::INTEGER, Integer::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::FLOAT, NounType::REAL, Integer::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD, NounType::INTEGER, Integer::max_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT, NounType::REAL, Integer::max_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Integer::max_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT, NounType::REAL, Integer::min_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Integer::min_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT, NounType::REAL, Integer::minus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::minus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT, NounType::REAL, Integer::more_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Integer::more_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD, NounType::INTEGER, Integer::plus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::FLOAT, NounType::REAL, Integer::plus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, Integer::plus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::plus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::plus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::WORD, NounType::INTEGER, Integer::power_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::FLOAT, NounType::REAL, Integer::power_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, Integer::power_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::power_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, Integer::power_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::WORD, NounType::INTEGER, Integer::remainder_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, Integer::remainder_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, Integer::remainder_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::WORD, NounType::INTEGER, Integer::reshape_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, Integer::reshape_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, Integer::reshape_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::WORD, NounType::INTEGER, Integer::times_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::FLOAT, NounType::REAL, Integer::times_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, Integer::times_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::times_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, Integer::times_list);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::each, Noun::dispatchMonad);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::eachPair, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::over, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::INTEGER, MonadicAdverbs::scanOver, Noun::enclose2);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::dispatchDyad);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::dispatchDyad);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::INTEGER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage Integer::make(int i)
{
  return Word::make(i, NounType::INTEGER);
}

Storage Integer::zero()
{
  return Integer::make(0);
}

Storage Integer::one()
{
  return Integer::make(1);
}

// Monads
Storage Integer::char_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(integer, NounType::CHARACTER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::enclose_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return WordArray::make(ints({ integer }), NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::enumerate_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);

    ints results(integer);
    std::iota(results.begin(), results.end(), 1);  // iota here refers to the C++/STL version of enumerate

    return WordArray::make(results, NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::expand_impl(const Storage& i)
{
  if (std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    ints results = ints();
    for(int index = 0; index < integer; index++)
    {
      results.push_back(0);
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::format_impl(const Storage& i)
{
  int unicode_minus = static_cast<int>('-');
  int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.

  if (std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(integer == 0)
    {
      return IotaString::make({unicode_zero});      
    }

    ints results = ints();

    int negative = 0;
    if(integer < 0)
    {
      integer = -integer;
      negative = 1;
    }

    while(integer > 0)
    {
      int digit = integer % 10;
      // Unicode value is located at x + 45 for all x '0' to '9'
      results.insert(results.begin(), digit + unicode_zero);
      integer = integer / 10;
    }      

    if(negative)
    {
      results.insert(results.begin(), unicode_minus);
    }

    return IotaString::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::negate_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(-integer, NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::not_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(integer == 0)
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::reciprocal_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Float::make(1.0 / static_cast<float>(integer), NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::size_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(abs(integer), NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
Storage Integer::cut_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints integers = std::get<ints>(x.i);

      if(integer == 0)
      {
        if(integers.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= integers.size())
      {
        ints left = ints(integers.begin(), integers.begin() + integer);
        ints right = ints(integers.begin() + integer, integers.end());

        mixed results = mixed();
        results.insert(results.end(), WordArray::make(left, NounType::LIST));
        results.insert(results.end(), WordArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::cut_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats list = std::get<floats>(x.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= list.size())
      {
        floats left = floats(list.begin(), list.begin() + integer);
        floats right = floats(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), FloatArray::make(left, NounType::LIST));
        results.insert(results.end(), FloatArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::cut_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed list = std::get<mixed>(x.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= list.size())
      {
        mixed left = mixed(list.begin(), list.begin() + integer);
        mixed right = mixed(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), MixedArray::make(left, NounType::LIST));
        results.insert(results.end(), MixedArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with two integer arguments
Storage Integer::divide_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      float fx = static_cast<float>(xi);

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with an integer and a float
Storage Integer::divide_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fx < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if(y == 0)
        {
        return QuotedSymbol::undefined();
        }

        results.insert(results.end(), fi / fy);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<floats>(x.i))
    {
      floats fis = std::get<floats>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(float fy : fis)
      {
        if(fy < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float result = fi / fy;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(Storage y : xis)
      {
        Storage result = divide(Float::make(fi, NounType::REAL), y);

        if(result.o == NounType::ERROR)
        {
          return result;
        }
        else if(result.o == NounType::QUOTED_SYMBOL) // :undefined
        {
          mixedResults.push_back(result);
        }
        else if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.push_back(fr);
          mixedResults.push_back(Real::make(fr));
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      return Word::make(ii == xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::format2_impl(const Storage& i, const Storage& x)
{
  int xi = 0;
  if(std::holds_alternative<int>(x.i))
  {
    xi = std::get<int>(x.i);
  }
  else if(std::holds_alternative<float>(x.i))
  {
    float fi = std::get<float>(x.i);
    xi = static_cast<int>(fi);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Storage formatted = format(i);
  if(formatted.o == NounType::ERROR)
  {
    return formatted;
  }

  if(xi == 0)
  {
    return formatted;
  }
  else if(xi > 0)
  {
    if(std::holds_alternative<ints>(formatted.i))
    {
      ints characters = std::get<ints>(formatted.i);

      if(xi <= characters.size())
      {
        return formatted;
      }
      else
      {
        int difference = xi - characters.size();
        for(int index = 0; index < difference; index++)
        {
          characters.push_back(static_cast<int>(' '));
        }

        return IotaString::make(characters);
      }
    }
  }
  else if(xi < 0)
  {
    xi = -xi;

    if(std::holds_alternative<ints>(formatted.i))
    {
      ints characters = std::get<ints>(formatted.i);

      if(xi <= characters.size())
      {
        return formatted;
      }
      else
      {
        int difference = xi - characters.size();
        for(int index = 0; index < difference; index++)
        {
          characters.insert(characters.begin(), static_cast<int>(' '));
        }

        return IotaString::make(characters);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::integerDivide_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      return Word::make(ii / xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage Integer::join_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints({ii, xi});

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::prepend_to_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xi = std::get<ints>(x.i);

      ints results(xi);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::less_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii < xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::less_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false0();
}

Storage Integer::less_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii < y)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii == xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);
      float fi = static_cast<float>(ii);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::max_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii < xi)
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::max_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false0();
}

Storage Integer::max_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii < y)
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(Float::make(fy));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::min_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii > xi)
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::min_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false0();
}

Storage Integer::min_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii > y)
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(Float::make(fy));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::minus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii - xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::minus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi - fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::minus_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii - y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = minus(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::more_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii > xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::more_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false0();
}

Storage Integer::more_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii > y)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::plus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii + xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::plus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi + fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::plus_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii + y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = plus(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::power_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      float fi = static_cast<float>(ii);
      float fx = static_cast<float>(xi);

      float result = powf(fi, fx);
      return Float::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::power_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = powf(fi, fx);
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::power_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      float fi = static_cast<float>(ii);

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = power(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::remainder_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      return Word::make(ii % xi);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::remainder_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii % y);
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::remainder_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = remainder(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::reshape_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi == -1)
      {
        xi = getInteger(integerDivide(size(i), Word::make(2)));
      }

      if(xi > 0)
      {
        ints results = ints();

        for(int index = 0; index < xi; index++)
        {
          results.push_back(ii);
        }

        return WordArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::reshape_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    int halfSize = getInteger(integerDivide(size(i), Word::make(2)));

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }

      ints lengths = ints();
      for(int xi : xis)
      {
        if(xi == 0 || xi < -1)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        if(xi == -1)
        {
          lengths.push_back(halfSize);
        }

        // else xi > 0
        lengths.push_back(xi);
      }

      if(lengths.size() == 1)
      {
        int xi = lengths[0];
        Storage sx = Word::make(xi);

        return reshape(i, sx);
      }
      else // xi.size() > 1
      {
        Storage total = over(WordArray::make(lengths), Word::make(Dyads::times, NounType::BUILTIN_DYAD));
        ints rest(lengths.begin(), lengths.end() - 1);

        Storage working = reshape(i, total);

        for(int index = rest.size() - 1; index >= 0; index--)
        {
          int y = rest[index];
          working = split(working, Word::make(y));
        }

        return working;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::reshape_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      if(xis.size() > 0)
      {
        if(xis.size() == 1)
        {
          Storage xi = xis[0];

          return reshape(i, xi);
        }
        else // xi.size() > 1
        {
          Storage first = xis.front();
          mixed rest(xis.begin() + 1, xis.end());

          Storage result = reshape(i, MixedArray::make(rest));
          return reshape(first, result);
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::times_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii * xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::times_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi * fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::times_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii * y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi * fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = times(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> Integer::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::WORD:
      return Word::from_bytes(bs, NounType::INTEGER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Integer::to_bytes(const Storage& i) {
  if (i.o != NounType::INTEGER) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if (std::holds_alternative<ints>(i.i)) {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      } else {
        return std::nullopt;
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Integer::from_conn(const Connection& conn, int t) {
  switch (t) {
    case NounType::INTEGER:
      return Word::from_conn(conn, NounType::INTEGER);

    default:
      return std::nullopt;
  }
}

void Integer::to_conn(const Connection& conn, const Storage& i) {
  if (i.o != NounType::INTEGER) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD:
      {
        // No need to include type here because it is provided by Word::to_conn
        return Word::to_conn(conn, i);
      }

    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          bytes intBytes = squeeze_bigint(integers);

          // Note that we always send NounType::INTEGER and StorageType::WORD, even if we internally represent them as StorageType::WORD_ARRAYs.
          conn.write({ (char)StorageType::WORD, (char)i.o });
          conn.write(intBytes);
        } else {
          return;
        }
      }

    default:
      return;
  }
}

// Real
// Registration
void Real::initialize() {
  // Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::enclose, Real::enclose_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::floor, Real::floor_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::format, Real::format_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::negate, Real::negate_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::inot, Real::not_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::reciprocal, Real::reciprocal_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::size, Real::size_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::evaluate, Noun::identity1);

  // Dyads
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::WORD, NounType::INTEGER, Real::divide_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::FLOAT, NounType::REAL, Real::divide_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Real::divide_integers);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Real::divide_reals);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Real::divide_mixed);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_scalar);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::FLOAT, NounType::REAL, Real::join_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Real::prepend_to_reals);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::format2, StorageType::WORD, NounType::INTEGER, Real::format2_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::format2, StorageType::FLOAT, NounType::REAL, Real::format2_impl);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::WORD, NounType::INTEGER, Real::less_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::FLOAT, NounType::REAL, Real::less_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, Real::less_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, Real::less_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, Real::less_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD, NounType::INTEGER, Real::match_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::FLOAT, NounType::REAL, Real::match_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::WORD, NounType::INTEGER, Real::max_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::FLOAT, NounType::REAL, Real::max_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Real::max_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Real::max_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Real::max_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::WORD, NounType::INTEGER, Real::min_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::FLOAT, NounType::REAL, Real::min_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Real::min_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Real::min_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Real::min_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::WORD, NounType::INTEGER, Real::minus_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::FLOAT, NounType::REAL, Real::minus_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Real::minus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Real::minus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Real::minus_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::WORD, NounType::INTEGER, Real::more_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::FLOAT, NounType::REAL, Real::more_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Real::more_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Real::more_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Real::more_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::WORD, NounType::INTEGER, Real::plus_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::FLOAT, NounType::REAL, Real::plus_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, Real::plus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, Real::plus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, Real::plus_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::WORD, NounType::INTEGER, Real::power_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::FLOAT, NounType::REAL, Real::power_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, Real::power_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, Real::power_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, Real::power_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::WORD, NounType::INTEGER, Real::times_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::FLOAT, NounType::REAL, Real::times_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, Real::times_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, Real::times_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, Real::times_list);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::each, Noun::dispatchMonad);
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::eachPair, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::over, Noun::identity2);
  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::scanOver, Noun::enclose2);

  Noun::registerMonadicAdverb(StorageType::FLOAT, NounType::REAL, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT, NounType::REAL, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage Real::make(float i)
{
  return Float::make(i, NounType::REAL);
}

Storage Real::zero()
{
  return Real::make(0.0);
}

Storage Real::one()
{
  return Real::make(1.0);
}

Storage Real::enclose_impl(const Storage& i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);
    return FloatArray::make(floats({ f }), NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::floor_impl(const Storage& i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);
    int result = (int)std::floor(f);

    return Word::make(result, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::format_impl(const Storage& i)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    // This code prints a float with the minimum number of digits necessary to not lose precision
    std::vector<char> buffer = std::vector<char>(256);
    int formattedLength = std::snprintf(buffer.data(), buffer.size(), "%.*g", std::numeric_limits<double>::max_digits10, fi);
    std::string s = std::string(buffer.data());

    ints results = ints();
    int needDecimal = 1;
    for(char c : s)
    {
      results.push_back(static_cast<int>(c));
      if(c == '.')
      {
        needDecimal = 0;
      }
    }

    if(needDecimal)
    {
      results.push_back(static_cast<int>('.'));
      results.push_back(static_cast<int>('0'));
    }

    return IotaString::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::negate_impl(const Storage& i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(-f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::not_impl(const Storage& i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);

    if(abs(f) < Float::tolerance)
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::reciprocal_impl(const Storage& i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(1.0 / f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::size_impl(const Storage& i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(abs(f), NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
// Floating-point division with a float and an integer
Storage Real::divide_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      float fx = static_cast<float>(xi);

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with two floats
Storage Real::divide_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fx < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::divide_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(int y : xis)
      {
        if(y == 0)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fy = static_cast<float>(y);
          float result = fi / fy;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::divide_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats fis = std::get<floats>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(float fy : fis)
      {
        if(fy < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float result = fi / fy;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::divide_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      floats results = floats();
      mixed mixedResults = mixed();

      for(Storage y : xis)
      {
        Storage result = divide(Float::make(fi, NounType::REAL), y);

        if(result.o == NounType::ERROR)
        {
          return result;
        }
        else if(result.o == NounType::QUOTED_SYMBOL) // :undefined
        {
          mixedResults.push_back(result);
        }
        else if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.push_back(fr);
          mixedResults.push_back(Real::make(fr));
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::format2_impl(const Storage& i, const Storage& x)
{
  Storage formatted = format(i);
  if(formatted.o == NounType::ERROR)
  {
    return formatted;
  }

  if(std::holds_alternative<int>(x.i))
  {  
    int xi = std::get<int>(x.i);

    if(xi == 0)
    {
      return formatted;
    }
    else if(xi > 0)
    {
      if(std::holds_alternative<ints>(formatted.i))
      {
        ints characters = std::get<ints>(formatted.i);

        if(xi <= characters.size())
        {
          return formatted;
        }
        else
        {
          int difference = xi - characters.size();
          for(int index = 0; index < difference; index++)
          {
            characters.push_back((int)' ');
          }

          return IotaString::make(characters);
        }
      }
    }
    else if(xi < 0)
    {
      xi = -xi;

      if(std::holds_alternative<ints>(formatted.i))
      {
        ints characters = std::get<ints>(formatted.i);

        if(xi <= characters.size())
        {
          return formatted;
        }
        else
        {
          int difference = xi - characters.size();
          for(int index = 0; index < difference; index++)
          {
            characters.insert(characters.begin(), (int)' ');
          }

          return IotaString::make(characters);
        }
      }
    }
  }
  else if(std::holds_alternative<float>(x.i))
  {
    float fi = std::get<float>(x.i);

    // We can ignore the sign on float format parameters
    int negative = 0;
    if(fi < 0)
    {
      fi = -fi;
      negative = 1;
    }

    int integerPartTarget = static_cast<int>(fi);
    int fractionalPartTarget = static_cast<int>((fi - integerPartTarget) * powf(10, Float::precision));
    while((fractionalPartTarget != 0) && (fractionalPartTarget % 10 == 0))
    {
      fractionalPartTarget = fractionalPartTarget / 10;
    }

    if((integerPartTarget == 0) && (fractionalPartTarget == 0))
    {
      return formatted;
    }
    else if(fractionalPartTarget == 0)
    {
      if(negative)
      {
        return format2(i, Integer::make(-integerPartTarget));
      }
      else
      {
        return format2(i, Integer::make(integerPartTarget));
      }
    }
  
    if(std::holds_alternative<ints>(formatted.i))
    {
      ints characters = std::get<ints>(formatted.i);

      int decimalIndex = -1;
      for(int index = 0; index < characters.size(); index++)
      {
        int character = characters[index];
        if(character == static_cast<int>('.'))
        {
          decimalIndex = index;
          break;
        }
      }

      if(decimalIndex == -1)
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
      }

      ints integerPart = ints(characters.begin(), characters.begin() + decimalIndex);
      ints fractionalPart = ints(characters.begin() + decimalIndex + 1, characters.end());

      if(integerPart.size() < integerPartTarget)
      {
        int difference = integerPartTarget - integerPart.size();
        for(int index = 0; index < difference; index++)
        {
          integerPart.insert(integerPart.begin(), static_cast<int>(' '));
        }
      }

      if(fractionalPart.size() < fractionalPartTarget)
      {
        int difference = fractionalPartTarget - fractionalPart.size();
        for(int index = 0; index < difference; index++)
        {
          fractionalPart.push_back(static_cast<int>('0'));
        }
      }

      ints results = ints();
      results.insert(results.end(), integerPart.begin(), integerPart.end());
      results.insert(results.end(), static_cast<int>('.'));
      results.insert(results.end(), fractionalPart.begin(), fractionalPart.end());

      return IotaString::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage Real::join_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results = floats({ii, xi});

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::prepend_to_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xi = std::get<floats>(x.i);

      floats results(xi);
      results.insert(results.begin(), ii);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::less_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::less_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::less_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::max_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::max_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::max_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(Word::make(y));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(fy);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::min_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::min_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::min_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(Word::make(y));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(fy);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::minus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi - fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::minus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi - fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::minus_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = minus(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::more_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::more_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::more_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::plus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi + fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::plus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi + fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::plus_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = plus(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::power_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(powf(fi, fx));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::power_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(powf(fi, fx));
    }
  }

  return Noun::false1(i);
}

Storage Real::power_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = power(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::times_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi * fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::times_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi * fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::times_list(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi * fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi * fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = times(si, y);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> Real::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::FLOAT:
      return Float::from_bytes(bs, NounType::REAL);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Real::to_bytes(const Storage& i) {
  if (i.o != NounType::REAL) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::FLOAT:
      return Float::to_bytes(i);

    default:
      return std::nullopt;
  }
}

maybe<Storage> Real::from_conn(const Connection& conn, int t) {
  switch (t) {
    case StorageType::FLOAT:
      return Float::from_conn(conn, NounType::REAL);

    default:
      return std::nullopt;
  }
}

void Real::to_conn(const Connection& conn, const Storage& i) {
  if (i.o != NounType::REAL) {
    return;
  }

  switch (i.t) {
    case StorageType::FLOAT:
      {
        // No need to include type here because it is provided by Float::to_conn
        return Float::to_conn(conn, i);
      }

    default:
      return;
  }
}

// List
void List::initialize() {
  // WordArray
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::expand, List::expand_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::floor, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::format, List::format_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::group, List::group_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::undefined, Noun::false1);
  
  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::amend, StorageType::WORD_ARRAY, NounType::LIST, List::amend_integers_integers);
  // Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, List::amend_integers_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::equal, StorageType::WORD_ARRAY, NounType::LIST, List::equal_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_integers_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_integers_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, WordArray::nil2);  
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::CHARACTER, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, WordArray::nil2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, WordArray::nil2);
  
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::format2, StorageType::WORD, NounType::INTEGER, List::format2_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::format2, StorageType::FLOAT, NounType::REAL, List::format2_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, List::append_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, List::join_integers_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::join_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_mixed);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_mix_left);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_enclose);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);  

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD, NounType::INTEGER, List::remainder_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, List::remainder_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, List::remainder_mixed);  

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD, NounType::INTEGER, List::reshape_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, List::reshape_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, List::reshape_mixed);  

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::rotate, StorageType::WORD, NounType::INTEGER, List::rotate_integer);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD, NounType::INTEGER, List::split_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, List::split_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::take, StorageType::WORD, NounType::INTEGER, List::take_integer);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD, NounType::INTEGER, List::times_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT, NounType::REAL, List::times_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, List::times_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, List::times_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, List::times_mixed);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::converge, Noun::converge_impl);  

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::each, List::each_integers);
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::eachPair, List::eachPair_integers);
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::over, List::over_integers);

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);  

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, MonadicAdverbs::scanOver, List::scanOver_integers);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);  

  // FloatArray
  // Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::floor, List::floor_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::format, List::format_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::group, List::group_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::amend, StorageType::WORD_ARRAY, NounType::LIST, List::amend_floats_integers);
  // Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, List::amend_floats_mixed);
  
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_reals_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_reals_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, WordArray::nil2);  
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::CHARACTER, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, WordArray::nil2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, WordArray::nil2);
  
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::format2, StorageType::WORD, NounType::INTEGER, List::format2_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::format2, StorageType::FLOAT, NounType::REAL, List::format2_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, List::append_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mixed);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, List::join_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_mix_left);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_enclose);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);  

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::rotate, StorageType::WORD, NounType::INTEGER, List::rotate_integer);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD, NounType::INTEGER, List::split_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, List::split_integers);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::take, StorageType::WORD, NounType::INTEGER, List::take_integer);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD, NounType::INTEGER, List::times_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT, NounType::REAL, List::times_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, List::times_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, List::times_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, List::times_mixed);  

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::converge, Noun::converge_impl);   

  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::each, List::each_reals);
  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::eachPair, List::eachPair_reals);
  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::over, List::over_reals);

  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);   

  Noun::registerMonadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, MonadicAdverbs::scanOver, List::scanOver_reals);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);  

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);  

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);  

  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::FLOAT_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);  

  // MixedArray
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::floor, List::floor_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::format, List::format_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::group, List::group_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::transpose, List::transpose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, List::amend_floats);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, List::find_mixed);  
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::CHARACTER, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, List::find_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, List::find_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::format2, StorageType::WORD, NounType::INTEGER, List::format2_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::format2, StorageType::FLOAT, NounType::REAL, List::format2_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, List::join_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_right);
  
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);  

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD, NounType::INTEGER, List::remainder_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::remainder, StorageType::WORD_ARRAY, NounType::LIST, List::remainder_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::remainder, StorageType::MIXED_ARRAY, NounType::LIST, List::remainder_mixed);  

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD, NounType::INTEGER, List::reshape_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::reshape, StorageType::WORD_ARRAY, NounType::LIST, List::reshape_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::reshape, StorageType::MIXED_ARRAY, NounType::LIST, List::reshape_mixed);  

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::rotate, StorageType::WORD, NounType::INTEGER, List::rotate_integer);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD, NounType::INTEGER, List::split_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, List::split_integers);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::take, StorageType::WORD, NounType::INTEGER, List::take_integer);  

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD, NounType::INTEGER, List::times_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT, NounType::REAL, List::times_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::WORD_ARRAY, NounType::LIST, List::times_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::FLOAT_ARRAY, NounType::LIST, List::times_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::times, StorageType::MIXED_ARRAY, NounType::LIST, List::times_mixed);   

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::converge, Noun::converge_impl);

  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::each, List::each_mixed);
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::eachPair, List::eachPair_mixed);
  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::over, List::over_mixed);

  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);

  Noun::registerMonadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, MonadicAdverbs::scanOver, List::scanOver_mixed);

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::INTEGER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT, NounType::REAL, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::MIXED_ARRAY, NounType::LIST, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD, NounType::CHARACTER, Noun::each2_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::each2, StorageType::WORD_ARRAY, NounType::STRING, Noun::each2_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::INTEGER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT, NounType::REAL, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD, NounType::CHARACTER, Noun::eachLeft_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachLeft, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachLeft_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::INTEGER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT, NounType::REAL, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD, NounType::CHARACTER, Noun::overNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::overNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::overNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::INTEGER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT, NounType::REAL, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::MIXED_ARRAY, NounType::LIST, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD, NounType::CHARACTER, Noun::eachRight_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::eachRight, StorageType::WORD_ARRAY, NounType::STRING, Noun::eachRight_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::INTEGER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT, NounType::REAL, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::MIXED_ARRAY, NounType::LIST, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::CHARACTER, Noun::scanOverNeutral_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanOverNeutral, StorageType::WORD_ARRAY, NounType::STRING, Noun::scanOverNeutral_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);

  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);
  Noun::registerDyadicAdverb(StorageType::MIXED_ARRAY, NounType::LIST, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);
}

Storage List::atom_impl(const Storage& i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);
    if (integers.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);
    if (fs.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);
    if (ms.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else {
    return Noun::false0();
  }
}

Storage List::char_impl(const Storage& i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);

    if (integers.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed ms = mixed();
    for (int y : integers) {
      ms.insert(ms.end(), Word::make(y, NounType::CHARACTER));
    }
    return MixedArray::make(ms, NounType::LIST);
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);

    if (fs.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    } else {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);

    if (ms.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    } else {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::expand_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return WordArray::nil();
    }

    ints results = ints();

    for(int index = 0; index < integers.size(); index++)
    {
      int count = integers[index];

      for(int y = 0; y < count; y++)
      {
        results.push_back(index);
      }
    }

    return WordArray::make(results);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::first_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    int integer = integers.front();

    return Word::make(integer, NounType::INTEGER);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    float f = fs.front();

    return Float::make(f, NounType::REAL);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    Storage result = ms.front();

    return result;
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::floor_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    return i;
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    ints results = ints();
    for(float y : fs)
    {
      results.insert(results.end(), (int)std::floor(y));
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed results = mixed();
    for(Storage y : ms)
    {
      results.insert(results.end(), floor(y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::format_impl(const Storage& i)
{
  Storage mi = Noun::mix(i);
  if(std::holds_alternative<mixed>(mi.i))
  {
    mixed ms = std::get<mixed>(mi.i);

    if(ms.empty())
    {
      return IotaString::make(ints({(int)'[', (int)']'}));
    }

    mixed results = mixed();

    for(Storage y : ms)
    {
      results.push_back(format(y));
    }

    return MixedArray::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::gradeDown_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
        return integers[x] > integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return i;
    }

    ints results(fs.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&fs](int x, int y)
    {
        if(fs[x] > fs[y])
        {
          float difference = fs[x] - fs[y];
          if(difference > Float::tolerance)
          {
            return 1; // x > y
          }
          else
          {
            return 0; // x ~= y
          }
        }
        else
        {
          return 0; // x <= y
        }
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return i;
    }

    ints results(ms.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&ms](int x, int y)
    {
        Storage result = more(ms[x], ms[y]);
        switch(result.t)
        {
          case NounType::INTEGER:
            if(std::holds_alternative<int>(result.i))
            {
              return std::get<int>(result.i);
            }
        }

        return 0;
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::gradeUp_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
        return integers[x] < integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return i;
    }

    ints results(fs.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&fs](int x, int y)
    {
        if(fs[x] < fs[y])
        {
          float difference = fs[y] - fs[x];
          if(difference > Float::tolerance)
          {
            return 1; // y < x
          }
          else
          {
            return 0; // y ~= x
          }
        }
        else
        {
          return 0; // y >= x
        }
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return i;
    }

    ints results(ms.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&ms](int x, int y)
    {
        Storage result = less(ms[x], ms[y]);
        switch(result.t)
        {
          case NounType::INTEGER:
            if(std::holds_alternative<int>(result.i))
            {
              int integer = std::get<int>(result.i);
              return integer;
            }
        }

        return 0;
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::group_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints items = std::get<ints>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<int, int> firsts=std::unordered_map<int, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();
    
    for (int index = 0; index < items.size(); index++)
    {
      // Get each item in the list
      int item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto pair = groups.begin(); pair != groups.end(); pair++)
    {
      ints group = pair->second;
      results.push_back(WordArray::make(group));
    }  

    return MixedArray::make(results);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats items = std::get<floats>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<float, int> firsts=std::unordered_map<float, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();
    
    for (int index = 0; index < items.size(); index++)
    {
      // Get each item in the list
      float item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto pair = groups.begin(); pair != groups.end(); pair++)
    {
      ints group = pair->second;
      results.push_back(WordArray::make(group));
    }  

    return MixedArray::make(results);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed items = std::get<mixed>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<Storage, int> firsts=std::unordered_map<Storage, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();
    
    for (int index = 0; index < items.size(); index++)
    {
      // Get each item in the list
      Storage item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto pair = groups.begin(); pair != groups.end(); pair++)
    {
      ints group = pair->second;
      results.push_back(WordArray::make(group));
    }  

    return MixedArray::make(results);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::negate_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    ints results = ints();
    for(int y : integers)
    {
      results.insert(results.end(), -y);
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats();
    for(float y : fs)
    {
      results.insert(results.end(), -y);
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed();
    for(Storage y : ms)
    {
      results.insert(results.end(), negate(y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::not_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if (integers.empty())
    {
      return Noun::true0();
    }

    ints results = ints();
    for (int y : integers)
    {
      if(y == 0)
      {
        results.push_back(1);
      }
      else
      {
        results.push_back(0);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if (std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if (fs.empty())
    {
      return Noun::true0();
    }

    floats results = floats();
    for (float y : fs)
    {
      if(abs(y) < Float::tolerance)
      {
        results.push_back(1);
      }
      else
      {
        results.push_back(0);
      }
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if (std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if (ms.empty())
    {
      return Noun::true0();
    }

    mixed results = mixed();
    for (Storage y : ms)
    {
      results.push_back(inot(y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::reciprocal_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    floats results = floats();
    for(int y : integers)
    {
      results.insert(results.end(), 1.0 / static_cast<float>(y));
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats();
    for(float y : fs)
    {
      results.insert(results.end(), 1.0 / y);
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed();
    for(Storage y : ms)
    {
      results.insert(results.end(), divide(Float::make(1.0, NounType::REAL), y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::reverse_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    ints results = ints(integers);
    std::reverse(results.begin(), results.end());

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats(fs);
    std::reverse(results.begin(), results.end());

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed(ms);
    std::reverse(results.begin(), results.end());

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::shape_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    ints results = ints({static_cast<int>(integers.size())});
    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    ints results = ints({static_cast<int>(fs.size())});
    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    mixed shapes = mixed();
    for(Storage y : ms)
    {
      Storage result = shape(y);
      shapes.insert(shapes.end(), result);
    }

    Storage firstShape = shapes.front();
    if(firstShape.o == NounType::LIST && firstShape.t == StorageType::WORD_ARRAY && std::holds_alternative<ints>(firstShape.i))
    {
      ints firstShapeIntegers = std::get<ints>(firstShape.i);

      for(Storage y : shapes)
      {
        Storage nextShape = shape(y);
        if(nextShape.o == NounType::LIST && nextShape.t == StorageType::WORD_ARRAY && std::holds_alternative<ints>(nextShape.i))
        {
          ints nextShapeIntegers = std::get<ints>(nextShape.i);

          if(firstShapeIntegers != nextShapeIntegers)
          {
            return WordArray::make(ints({static_cast<int>(shapes.size())}), NounType::LIST);
          }
        }
      }

      ints results = ints(firstShapeIntegers);
      results.insert(results.begin(), shapes.size());

      return WordArray::make(results, NounType::LIST);
    }
    else
    {
      return WordArray::make(ints({static_cast<int>(ms.size())}), NounType::LIST);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::size_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    return Word::make(static_cast<int>(integers.size()), NounType::INTEGER);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    return Word::make(static_cast<int>(fs.size()), NounType::INTEGER);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    return Word::make(static_cast<int>(ms.size()), NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// We can only transpose 2D arrays, which means a mixed array of either all words or all floats, where all subarrays are the same size
// FIXME - support 2D arrays of mixed words and floats
// FIXME - support 2D arrays of bigints
Storage List::transpose_impl(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }
    else
    {
      int all_word_arrays = 1;
      int all_float_arrays = 1;
      for(Storage y : ms)
      {
        if(y.t == StorageType::WORD_ARRAY)
        {
          all_float_arrays = 0;
        }
        else if(y.t == StorageType::FLOAT_ARRAY)
        {
          all_word_arrays = 0;
        }
        else
        {
          all_word_arrays = 0;
          all_float_arrays = 0;
          break;
        }
      }

      if(all_word_arrays)
      {
        Storage first = ms.front();
        if(std::holds_alternative<ints>(first.i))
        {
          ints firstIntegers = std::get<ints>(first.i);

          int rows = ms.size();
          int columns = firstIntegers.size();

          std::vector<ints> source(rows);
          for (int j = 0; j < rows; ++j)
          {
            Storage subarray = ms[j];
            if(std::holds_alternative<ints>(subarray.i))
            {
              source[j] = std::get<ints>(subarray.i);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
          }

          std::vector<ints> transposed(columns, ints(rows));
          for (int j = 0; j < rows; ++j)
          {
            for (int k = 0; k < columns; ++k)
            {
                transposed[k][j] = source[j][k];  // Swap row and column indices
            }
          }

          mixed results = mixed();
          for (int k = 0; k < columns; ++k)
          {
            results.insert(results.end(), WordArray::make(transposed[k], NounType::LIST));
          }

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(all_float_arrays)
      {
        Storage first = ms.front();
        if(std::holds_alternative<floats>(first.i))
        {
          floats firstFloats = std::get<floats>(first.i);

          int rows = ms.size();
          int columns = firstFloats.size();

          std::vector<floats> source(rows);
          for (int j = 0; j < rows; ++j)
          {
            Storage subarray = ms[j];
            if(std::holds_alternative<floats>(subarray.i))
            {
              source[j] = std::get<floats>(subarray.i);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
          }

          std::vector<floats> transposed(columns, floats(rows));
          for (int j = 0; j < rows; ++j)
          {
            for (int k = 0; k < columns; ++k)
            {
                transposed[k][j] = source[j][k];  // Swap row and column indices
            }
          }

          mixed results = mixed();
          for (int k = 0; k < columns; ++k)
          {
            results.insert(results.end(), FloatArray::make(transposed[k], NounType::LIST));
          }

          return MixedArray::make(results, NounType::LIST);
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::unique_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    std::unordered_set<int> set = std::unordered_set<int>();
    ints results = ints();

    for(int y : integers)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    std::unordered_set<float> set = std::unordered_set<float>();
    floats results = floats();

    for(float y : fs)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    // FIXME - implement unique for mixed
    // mixed ms = std::get<mixed>(i.i);

    // std::unordered_set<Storage> set = std::unordered_set<Storage>();
    // mixed results = mixed();

    // for(Storage y : ms)
    // {
    //   if(set.find(y) == set.end())
    //   {
    //     set.insert(y);
    //     results.insert(results.end(), y);
    //   }
    // }

    // return MixedArray::make(results, NounType::LIST);
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// List Dyads
// Storage List::amend_integers_integer(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<ints>(i.i))
//   {
//     ints integers = std::get<ints>(i.i);
//
//     if(integers.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<ints>(x.i))
//     {
//       ints indices = std::get<ints>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       ints results = ints(integers);
//
//       int replacement = indices.front();
//       for(int offset = 1; offset < indices.size(); offset++)
//       {
//         int index = indices[offset] - 1;
//         if(index < 0)
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//
//         if(index < results.size())
//         {
//           results[index] = replacement;
//         }
//         else if(index == results.size())
//         {
//           results.push_back(replacement);
//         }
//         else
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//       }
//
//       return WordArray::make(results);
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_integers_mixed(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<ints>(i.i))
//   {
//     ints integers = std::get<ints>(i.i);
//
//     if(integers.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<mixed>(x.i))
//     {
//       mixed mixedIndices = std::get<mixed>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       ints results = ints(integers);
//
//       Storage replacement = mixedIndices.front();
//       Storage simplifiedIndices = simplify(drop(x, Integer::one()));
//
//       for(int offset = 1; offset < indices.size(); offset++)
//       {
//         int index = indices[offset] - 1;
//         if(index < 0)
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//
//         if(index < results.size())
//         {
//           results[index] = replacement;
//         }
//         else if(index == results.size())
//         {
//           results.push_back(replacement);
//         }
//         else
//         {
//           return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//         }
//       }
//
//       return WordArray::make(results);
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_floats_integer(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<floats>(i.i))
//   {
//     floats iis = std::get<floats>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<ints>(x.i))
//     {
//       ints indices = std::get<ints>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = Integer::make(indices.front());
//
//       if(std::holds_alternative<float>(mixedReplacement))
//       {
//         float replacement = std::get<float>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < results.size())
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < results.size())
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_floats_mixed(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<floats>(i.i))
//   {
//     floats iis = std::get<floats>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<mixed>(x.i))
//     {
//       mixed indices = std::get<mixed>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = indices.front();
//
//       if(std::holds_alternative<float>(mixedReplacement))
//       {
//         float replacement = std::get<float>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < results.size())
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < results.size())
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_mixed_integer(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<mixed>(i.i))
//   {
//     mixed iis = std::get<mixed>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<ints>(x.i))
//     {
//       ints indices = std::get<ints>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = Integer::make(indices.front());
//
//       if(std::holds_alternative<float>(mixedReplacement))
//       {
//         float replacement = std::get<float>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < results.size())
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < results.size())
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }
//
// Storage List::amend_mixed(const Storage& i, const Storage& x)
// {
//   if(std::holds_alternative<mixed>(i.i))
//   {
//     mixed iis = std::get<mixed>(i.i);
//
//     if(iis.empty())
//     {
//       return Word::make(INVALID_ARGUMENT, NounType::ERROR);
//     }
//
//     if(std::holds_alternative<mixed>(x.i))
//     {
//       mixed indices = std::get<mixed>(x.i);
//
//       if(indices.size() < 2)
//       {
//         return i;
//       }
//
//       Storage mixedReplacement = indices.front();
//
//       if(std::holds_alternative<int>(mixedReplacement))
//       {
//         int replacement = std::get<int>(mixedReplacement);
//         floats results = floats(iis);
//
//         for(int offset = 1; offset < indices.size(); offset++)
//         {
//           int index = indices[offset] - 1;
//           if(index < 0)
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//
//           if(index < results.size())
//           {
//             results[index] = replacement;
//           }
//           else if(index == results.size())
//           {
//             results.push_back(replacement);
//           }
//           else
//           {
//             return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//           }
//         }
//
//         return FloatArray::make(results);
//       }
//       else
//       {
//           mixed results = mix(iis);
//
//           for(int offset = 1; offset < indices.size(); offset++)
//           {
//             int index = indices[offset] - 1;
//             if(index < 0)
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//
//             if(index < results.size())
//             {
//               results[index] = mixedReplacement;
//             }
//             else if(index == results.size())
//             {
//               results.push_back(mixedReplacement);
//             }
//             else
//             {
//               return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
//             }
//           }
//
//           return MixedArray::make(results);
//       }
//     }
//   }
//
//   return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
// }

Storage List::cut_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int integer = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints list = std::get<ints>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == list.size())
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < list.size())
      {
        ints left = ints(list.begin(), list.begin() + integer);
        ints right = ints(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), WordArray::make(left, NounType::LIST));
        results.insert(results.end(), WordArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats list = std::get<floats>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == list.size())
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < list.size())
      {
        floats left = floats(list.begin(), list.begin() + integer);
        floats right = floats(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), FloatArray::make(left, NounType::LIST));
        results.insert(results.end(), FloatArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed list = std::get<mixed>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == list.size())
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < list.size())
      {
        mixed left = mixed(list.begin(), list.begin() + integer);
        mixed right = mixed(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), MixedArray::make(left, NounType::LIST));
        results.insert(results.end(), MixedArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::cut_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints integers = std::get<ints>(x.i);

    // If no indices where specified, we always return [i]
    if(integers.empty())
    {
      mixed results = mixed({i});
      return MixedArray::make(results, NounType::LIST);
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints list = std::get<ints>(i.i);

      // Indices are non-empty, so source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > list.size())
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonicaly increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == list.size())
            {
              // Capture the rest of the list that wasn't in any previous slice
              ints slice = ints(list.begin() + last, list.end());
              results.insert(results.end(), WordArray::make(slice, NounType::LIST));

              // Also insert a nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              ints slice = ints(list.begin() + last, list.begin() + y);
              results.insert(results.end(), WordArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < list.size())
        {
          ints slice = ints(list.begin() + last, list.end());
          results.insert(results.end(), WordArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats list = std::get<floats>(i.i);

      // Indices are non-empty, so source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > list.size())
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonicaly increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == list.size())
            {
              // Capture the rest of the list that wasn't in any previous slice
              floats slice = floats(list.begin() + last, list.end());
              results.insert(results.end(), FloatArray::make(slice, NounType::LIST));

              // Also insert a nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              floats slice = floats(list.begin() + last, list.begin() + y);
              results.insert(results.end(), FloatArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < list.size())
        {
          ints slice = ints(list.begin() + last, list.end());
          results.insert(results.end(), WordArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed list = std::get<mixed>(i.i);

      // Indices are non-empty, so source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > list.size())
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonicaly increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == list.size())
            {
              // Capture the rest of the list that wasn't in any previous slice
              mixed slice = mixed(list.begin() + last, list.end());
              results.insert(results.end(), MixedArray::make(slice, NounType::LIST));

              // Also insert a nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              mixed slice = mixed(list.begin() + last, list.begin() + y);
              results.insert(results.end(), MixedArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < list.size())
        {
          mixed slice = mixed(list.begin() + last, list.end());
          results.insert(results.end(), MixedArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      floats results = floats();
      for(int y : iis)
      {
        float fy = static_cast<float>(y);
        float fxi = static_cast<float>(xi);
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      float fxi = static_cast<float>(xi);

      floats results = floats();
      for(float fy : fis)
      {
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }    
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed mis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return QuotedSymbol::undefined();
      }

      float fxi = static_cast<float>(xi);

      floats results = floats();
      mixed mixedResults = mixed();

      for(Storage y : mis)
      {
        Storage result = divide(y, Float::make(fxi, NounType::REAL));
        if(result.o == NounType::QUOTED_SYMBOL)
        {
          mixedResults.push_back(result);
        }
        else if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.push_back(fr);
          mixedResults.push_back(result);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }       
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      if(xi < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      floats results = floats();
      for(int y : iis)
      {
        float fy = static_cast<float>(y);
        float fxi = static_cast<float>(xi);
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fxi = std::get<float>(x.i);

      if(fxi < Float::tolerance)
      {
        return QuotedSymbol::undefined();
      }

      floats results = floats();
      for(float fy : fis)
      {
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed mis = std::get<mixed>(i.i);

    mixed results = mixed();

    for(Storage y : mis)
    {
      Storage result = divide(y, x);
      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return MixedArray::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] == 0)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fi = static_cast<float>(iis[index]);
          float fx = static_cast<float>(xis[index]);

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] == 0)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fi = iis[index];
          float fx = static_cast<float>(xis[index]);

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Word::make(xis[index], NounType::INTEGER);

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fi = static_cast<float>(iis[index]);
          float fx = xis[index];

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      mixed mixedResults = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          mixedResults.push_back(QuotedSymbol::undefined());
        }
        else
        {
          float fi = iis[index];
          float fx = xis[index];

          float result = fi / fx;
          results.push_back(result);
          mixedResults.push_back(Real::make(result));
        }
      }

      if(mixedResults.size() == results.size())
      {
        return FloatArray::make(results);
      }
      else
      {
        return MixedArray::make(mixedResults);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Float::make(xis[index], NounType::REAL);

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = xis[index];

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = xis[index];

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// FIXME - drop for strings
Storage List::drop_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        ints results(iis.begin() + xi, iis.end());
        return WordArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        ints results(iis.begin(), iis.end() - xi);
        return WordArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        floats results(iis.begin() + xi, iis.end());
        return FloatArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        floats results(iis.begin(), iis.end() - xi);
        return FloatArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        mixed results(iis.begin() + xi, iis.end());
        return MixedArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        mixed results(iis.begin(), iis.end() - xi);
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        results.insert(results.end(), iis[index] == xis[index]);
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_integers_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Word::make(xi, NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_integers_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Float::make(fx, NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_reals_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      Storage sx = Word::make(xi, NounType::INTEGER);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);

        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_reals_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = Float::make(xi, NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    ints results = ints();

    for(int index = 0; index < iis.size(); index++)
    {
      Storage si = iis[index];
      Storage matched = match(si, x);
      if(matched.o == NounType::ERROR)
      {
        return matched;
      }

      if(matched.truth())
      {
        results.push_back(index + 1);
      }
    }
    
    return WordArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::format2_impl(const Storage& i, const Storage& x)
{
  Storage mi = Noun::mix(i);
  if(std::holds_alternative<mixed>(mi.i))
  {
    mixed ms = std::get<mixed>(mi.i);

    if(ms.empty())
    {
      return QuotedSymbol::undefined();
    }

    mixed results = mixed();

    for(Storage y : ms)
    {
      results.push_back(format2(y, x));
    }

    return MixedArray::make(results);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::index_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        int result = iis[xi - 1];
        return Word::make(result, NounType::INTEGER);
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          int result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        float result = iis[xi - 1];
        return Float::make(result, NounType::REAL);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          float result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        return iis[xi - 1];
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          results.push_back(iis[xi - 1]);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage List::append_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results(iis);
      results.push_back(xi);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::append_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results(iis);
      results.push_back(xi);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::prepend_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(xis);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::prepend_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results(iis);
      results.insert(results.begin(), xi);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(iis);

      for(int y : xis)
      {
        results.push_back(y);
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_integers_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(int y : iis)
      {
        results.push_back(Word::make(y, NounType::INTEGER));
      }

      for(float y : xis)
      {
        results.push_back(Float::make(y, NounType::REAL));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results(iis);

      for(float y : xis)
      {
        results.push_back(y);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_reals_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(float y : iis)
      {
        results.push_back(Float::make(y, NounType::REAL));
      }

      for(int y : xis)
      {
        results.push_back(Word::make(y, NounType::INTEGER));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : iis)
      {
        results.push_back(y);
      }

      for(Storage y : xis)
      {
        results.push_back(y);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y < xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      ints results = ints();

      for(int fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy < fx) && ((fx - fy ) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      ints results = ints();

      for(float fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii < xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y > xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      ints results = ints();

      for(int fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      ints results = ints();

      for(float fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii > xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        if(iis[index] != xis[index])
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        float fi = static_cast<float>(iis[index]);
        float fx = xis[index];
        if(abs(fi - fx) >= Float::tolerance)
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = xis[index];
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = Word::make(xis[index], NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Float::make(xis[index], NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = xis[index];
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Word::make(xis[index], NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Float::make(xis[index], NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y < xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(y);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      mixed results = mixed();

      for(int fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(fy));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy < fx) && ((fx - fy ) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(y));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fy);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii < xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(Word::make(xi));
        }
        else
        {
          results.push_back(Float::make(fi));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(Float::make(fx));
        }
        else
        {
          results.push_back(Word::make(ii));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          if(int ri = std::get<int>(result.i))
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y > xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(y);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      mixed results = mixed();

      for(int fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(fy));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(y));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fy);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii > xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(Word::make(xi));
        }
        else
        {
          results.push_back(Float::make(fi));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(Float::make(fx));
        }
        else
        {
          results.push_back(Word::make(ii));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y - xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = minus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = minus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii - xi);       
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = minus(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi - fx);       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = minus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = minus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = minus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y + xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = plus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = plus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii + xi);       
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = plus(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi + fx);       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = plus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = plus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = plus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);
    float fx = static_cast<float>(xi);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = power(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = power(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        int xi = xis[index];

        float fi = static_cast<float>(ii);
        float fx = static_cast<float>(xi);

        results.push_back(powf(fi, fx));       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fi = iis[index];

        int xi = xis[index];
        float fx = static_cast<float>(xi);

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = power(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(powf(fi, fx));       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = power(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = power(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = power(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = power(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::remainder_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y % xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = remainder(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::remainder_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        int xi = xis[index];

        results.push_back(ii % xi);       
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = remainder(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::remainder_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = remainder(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = remainder(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::reshape_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(xi == 0)
    {
      return i;
    }

    if(xi < -1)
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    if(xi == -1)
    {
      xi = getInteger(divide(size(i), Word::make(2)));
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int index = 0; index < xi; index++)
      {
        int cyclingIndex = index % iis.size();
        results.push_back(iis[cyclingIndex]);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(int index = 0; index < xi; index++)
      {
        int cyclingIndex = index % iis.size();
        results.push_back(iis[cyclingIndex]);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(int index = 0; index < xi; index++)
      {
        int cyclingIndex = index % iis.size();
        results.push_back(iis[cyclingIndex]);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::reshape_integers(const Storage& i, const Storage& x)
{
  int halfSize = getInteger(integerDivide(size(i), Word::make(2)));

  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(xis.empty())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    ints lengths = ints();
    for(int xi : xis)
    {
      if(xi == 0 || xi < -1)
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
      else if(xi == -1)
      {
        lengths.push_back(halfSize);
      }
      else
      {
        // else xi > 0
        lengths.push_back(xi);
      }
    }

    if(lengths.size() == 1)
    {
      int xi = lengths[0];
      Storage sx = Word::make(xi);

      return reshape(i, sx);
    }
    else // lengths.size() > 1
    {
      Storage totals = reverse(scanOver(WordArray::make(lengths), Word::make(Dyads::times, NounType::BUILTIN_DYAD)));

      Storage working = reshape(i, index(totals, Integer::make(0)));

      return overNeutral(working, Word::make(Dyads::split, NounType::BUILTIN_DYAD), totals);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::reshape_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = reshape(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = reshape(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::rotate_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = iis.size() - (xi % iis.size());

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return WordArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % iis.size();

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return WordArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = iis.size() - (xi % iis.size());

        floats results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return FloatArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % iis.size();

        floats results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return FloatArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = iis.size() - (xi % iis.size());

        mixed results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return MixedArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % iis.size();

        mixed results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::split_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        ints result = ints();
        for(int index = 0; index < iis.size(); index++)
        {
          result.push_back(iis[index]);

          if(result.size() == xi)
          {
            results.push_back(WordArray::make(result));
            result = ints();
          }
        }

        if(result.size() > 0)
        {
          results.push_back(WordArray::make(result));
        }

        return MixedArray::make(results);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        floats result = floats();
        for(int index = 0; index < iis.size(); index++)
        {
          result.push_back(iis[index]);

          if(result.size() == xi)
          {
            results.push_back(FloatArray::make(result));
            result = floats();
          }
        }

        if(result.size() > 0)
        {
          results.push_back(FloatArray::make(result));
        }

        return MixedArray::make(results);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        mixed result = mixed();
        for(int index = 0; index < iis.size(); index++)
        {
          result.push_back(iis[index]);

          if(result.size() == xi)
          {
            results.push_back(MixedArray::make(result));
            result = mixed();
          }
        }

        if(result.size() > 0)
        {
          results.push_back(MixedArray::make(result));
        }

        return MixedArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::split_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(xis.empty())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < iis.size())
      {
        int y = xis[index++ % xis.size()]; // cycle

        if(count + y > iis.size())
        {
          ints result(iis.begin() + count, iis.end());
          results.push_back(WordArray::make(result));
          break;
        }
        else
        {
          ints result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(WordArray::make(result));
        }

        count = count + y;
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < iis.size())
      {
        int y = xis[index++ % xis.size()]; // cycle

        if(count + y > iis.size())
        {
          floats result(iis.begin(), iis.end());
          results.push_back(FloatArray::make(result));
          break;
        }
        else
        {
          floats result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(FloatArray::make(result));
        }

        count = count + y;
      }

      if(count < iis.size())
      {
          floats result(iis.begin() + count, iis.end());
          results.push_back(FloatArray::make(result));
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);
      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < iis.size())
      {
        int y = xis[index++ % xis.size()]; // cycle
        
        if(count + y > iis.size())
        {
          mixed result(iis.begin(), iis.end());
          results.push_back(MixedArray::make(result));
          break;
        }
        else
        {
          mixed result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(MixedArray::make(result));
        }

        count = count + y;
      }

      if(count < iis.size())
      {
          mixed result(iis.begin() + count, iis.end());
          results.push_back(MixedArray::make(result));
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::take_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return WordArray::nil();
      }
      else if(xi > 0)
      {
        ints results = ints();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % iis.size()]); // cycle through iis
        }

        return WordArray::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = iis.size() - (xi % iis.size());

        ints results = ints();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % iis.size();
          results.push_back(iis[index]);
        }

        return WordArray::make(results);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return WordArray::nil();
      }

      if(xi > 0)
      {
        floats results = floats();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % iis.size()]); // cycle through iis
        }

        return FloatArray::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = iis.size() - (xi % iis.size());

        floats results = floats();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % iis.size();
          results.push_back(iis[index]);
        }

        return FloatArray::make(results);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return WordArray::nil();
      }

      if(xi > 0)
      {
        mixed results = mixed();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % iis.size()]); // cycle through iis
        }

        return MixedArray::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = iis.size() - (xi % iis.size());

        mixed results = mixed();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % iis.size();
          results.push_back(iis[index]);
        }

        return MixedArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y * xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(fy * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = times(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_real(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fy * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = times(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii * xi);       
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = times(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_reals(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi * fx);       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi * fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = times(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::times_mixed(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = times(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = times(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = times(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Monadic Adverbs
Storage List::each_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();
    for(int y : iis)
    {
      Storage result = Noun::dispatchMonad(Integer::make(y), f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::each_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    mixed results = mixed();
    for(int y : iis)
    {
      Storage result = Noun::dispatchMonad(Real::make(y), f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::each_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    mixed results = mixed();
    for(Storage y : iis)
    {
      Storage result = Noun::dispatchMonad(y, f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::eachPair_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();
    for(int index = 0; index < iis.size() - 1; index++)
    {
      int y = iis[index];
      int z = iis[index+1];
      Storage result = Noun::dispatchDyad(Word::make(y), f, Word::make(z));

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::eachPair_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    mixed results = mixed();
    for(int index = 0; index < iis.size() - 1; index++)
    {
      float y = iis[index];
      float z = iis[index+1];
      Storage result = Noun::dispatchDyad(Float::make(y), f, Float::make(z));

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::eachPair_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    mixed results = mixed();
    for(int index = 0; index < iis.size() - 1; index++)
    {
      Storage y = iis[index];
      Storage z = iis[index+1];
      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::over_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(iis.size() == 1)
    {
      int result = iis[0];
      return Word::make(result);
    }

    // else iis.size() > 1

    Storage y = Word::make(iis[0]);

    for(int index = 1; index < iis.size(); index++)
    {
      Storage z = Word::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;
    }

    return y;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::over_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(iis.size() == 1)
    {
      float result = iis[0];
      return Float::make(result);
    }

    // else iis.size() > 1

    Storage y = Float::make(iis[0]);

    for(int index = 1; index < iis.size(); index++)
    {
      Storage z = Float::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;
    }

    return y;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::over_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(iis.size() == 1)
    {
      return iis[0];
    }

    // else iis.size() > 1

    Storage y = iis[0];

    for(int index = 1; index < iis.size(); index++)
    {
      Storage z = iis[index];

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;
    }

    return y;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::scanOver_integers(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(iis.size() == 1)
    {
      return i;
    }

    // else iis.size() > 1

    Storage y = Word::make(iis[0]);
    mixed results = mixed({y});

    for(int index = 1; index < iis.size(); index++)
    {
      Storage z = Word::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;

      results.push_back(y);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::scanOver_reals(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(iis.size() == 1)
    {
      return i;
    }

    // else iis.size() > 1

    Storage y = Float::make(iis[0]);
    mixed results = mixed({y});

    for(int index = 1; index < iis.size(); index++)
    {
      Storage z = Float::make(iis[index]);

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;

      results.push_back(y);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::scanOver_mixed(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(iis.size() == 1)
    {
      return i;
    }

    // else iis.size() > 1

    Storage y = iis[0];
    mixed results = mixed({y});

    for(int index = 1; index < iis.size(); index++)
    {
      Storage z = iis[index];

      Storage result = Noun::dispatchDyad(y, f, z);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      y = result;

      results.push_back(y);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

maybe<Storage> List::from_bytes(const bytes &bs, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_bytes(bs, NounType::LIST);

    case StorageType::FLOAT_ARRAY:
      return FloatArray::from_bytes(bs, NounType::LIST);

    case StorageType::MIXED_ARRAY:
      return MixedArray::from_bytes(bs, NounType::LIST);

    default:
      return std::nullopt;
  }
}

maybe<bytes> List::to_bytes(const Storage& i) {
  // Don't include type, that is handled by Noun::to_bytes

  if (i.o != NounType::LIST) {
    return std::nullopt;
  }

  bytes result = bytes();

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          return squeeze_ints(integers);
        } else {
          return std::nullopt;
        }
      }

    case StorageType::FLOAT_ARRAY:
      {
        if (std::holds_alternative<floats>(i.i)) {
          floats fs = std::get<floats>(i.i);
          return squeeze_floats(fs);
        } else {
          return std::nullopt;
        }
      }

    case StorageType::MIXED_ARRAY:
      {
        return MixedArray::to_bytes(i);
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> List::from_conn(const Connection& conn, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_conn(conn, NounType::LIST);

    case StorageType::FLOAT_ARRAY:
      return FloatArray::from_conn(conn, NounType::LIST);

    case StorageType::MIXED_ARRAY:
      return MixedArray::from_conn(conn, NounType::LIST);

    default:
      return std::nullopt;
  }
}

void List::to_conn(const Connection& conn, const Storage& i) {
  if (i.o != NounType::LIST) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          // Always include type in to_conn implementation
          conn.write({ static_cast<char>(i.t), static_cast<char>(i.o) });

          ints integers = std::get<ints>(i.i);
          bytes bs = squeeze_ints(integers);

          conn.write(bs);
        }
        return;
      }

    case StorageType::FLOAT_ARRAY:
      {
        // Always include type in to_conn implementation
        conn.write({ static_cast<char>(i.t), static_cast<char>(i.o) });

        floats fs = std::get<floats>(i.i);
        bytes bs = squeeze_floats(fs);

        conn.write(bs);
      }

    case StorageType::MIXED_ARRAY:
      {
        // No need to include type here, because it is provided by MixedArray::to_conn
        MixedArray::to_conn(conn, i);
      }

    default:
      return;
  }
}

// Character
void Character::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::ichar, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::enclose, Character::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::format, Character::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::inot, Noun::false1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::size, Character::size_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::evaluate, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::CHARACTER, Monads::evaluate, Noun::identity1);

  // Dyads
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::equal, StorageType::WORD, NounType::CHARACTER, Character::equal_impl);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD, NounType::INTEGER, Character::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::FLOAT, NounType::REAL, Character::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Character::join_character);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Character::prepend_string);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD, NounType::CHARACTER, Character::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::CHARACTER, MonadicAdverbs::converge, Noun::converge_impl);  
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::CHARACTER, MonadicAdverbs::each, Noun::dispatchMonad);  
  Noun::registerMonadicAdverb(StorageType::WORD, NounType::CHARACTER, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);  

  // Dyadic Adverbs
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);  
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);  

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanOverNeutral_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::USER_MONAD, Noun::scanOverNeutral_impl);  

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);  

  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD, NounType::CHARACTER, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);  
}

Storage Character::make(int i)
{
  return Word::make(i, NounType::CHARACTER);
}

Storage Character::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      return Word::make(ii == xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::enclose_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return WordArray::make({ integer }, NounType::STRING);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Character::size_impl(const Storage& i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(abs(integer), NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads


// Join
Storage Character::join_scalar(const Storage& i, const Storage& x)
{
  mixed results = mixed({i, x});

  return MixedArray::make(results, NounType::LIST);
}

Storage Character::join_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints({ii, xi});

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::join_list(const Storage& i, const Storage& x)
{
  Storage mx = Noun::mix(x);
  if(std::holds_alternative<mixed>(mx.i))
  {
    mixed results = std::get<mixed>(mx.i);
    results.insert(results.begin(), i);

    return MixedArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::prepend_string(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(xis);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii == xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> Character::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::WORD:
      return Word::from_bytes(bs, NounType::CHARACTER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Character::to_bytes(const Storage& i) {
  if (i.o != NounType::CHARACTER) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if (std::holds_alternative<ints>(i.i)) {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      } else {
        return std::nullopt;
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Character::from_conn(const Connection& conn, int t) {
  switch (t) {
    case StorageType::WORD:
      return Word::from_conn(conn, NounType::CHARACTER);

      // FIXME - add support for StorageType::WORD_ARRAY to represent grapheme clusters

    default:
      return std::nullopt;
  }
}

void Character::to_conn(const Connection& conn, const Storage& i) {
  if (i.o != NounType::CHARACTER) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD:
      {
        // No need to include type here because it is provided by Word::to_conn
        return Word::to_conn(conn, i);
      }

    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          bytes intBytes = squeeze_bigint(integers);

          // Note that we always send NounType::INTEGER and StorageType::WORD, even if we internally represent them as StorageType::WORD_ARRAYs.
          conn.write({ static_cast<char>(StorageType::WORD), static_cast<char>(i.o) });
          conn.write(intBytes);
        } else {
          return;
        }
      }

    default:
      return;
  }
}

// String
void IotaString::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::atom, IotaString::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::first, IotaString::first_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::format, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::gradeDown, IotaString::gradeDown_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::gradeUp, IotaString::gradeUp_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::group, IotaString::group_impl);  
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::inot, IotaString::not_impl);  
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::reverse, IotaString::reverse_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::size, IotaString::size_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::undefined, Noun::false1);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::evaluate, Noun::identity1);

  // Dyads
  // Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::amend, StorageType::MIXED_ARRAY, NounType::LIST, IotaString::amend_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::equal, StorageType::WORD_ARRAY, NounType::STRING, IotaString::equal_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::find, StorageType::WORD, NounType::CHARACTER, IotaString::find_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, IotaString::find_string);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD, NounType::INTEGER, IotaString::form_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::FLOAT, NounType::REAL, IotaString::form_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD_ARRAY, NounType::LIST, IotaString::form_list);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::FLOAT_ARRAY, NounType::LIST, IotaString::form_list);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::MIXED_ARRAY, NounType::LIST, IotaString::form_list);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD, NounType::CHARACTER, IotaString::form_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD_ARRAY, NounType::STRING, Noun::identity2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::form, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, IotaString::form_quoted_symbol);
  
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::index, StorageType::WORD, NounType::INTEGER, IotaString::index_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, IotaString::index_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD, NounType::CHARACTER, IotaString::append_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, IotaString::join_string);  

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, IotaString::match_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::rotate, StorageType::WORD, NounType::INTEGER, IotaString::rotate_integer);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::split, StorageType::WORD, NounType::INTEGER, IotaString::split_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::split, StorageType::WORD_ARRAY, NounType::LIST, IotaString::split_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::take, StorageType::WORD, NounType::INTEGER, IotaString::take_integer);  

  // Monadic Adverbs
  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, MonadicAdverbs::converge, Noun::converge_impl);  

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, MonadicAdverbs::each, IotaString::each_impl);  

  Noun::registerMonadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, MonadicAdverbs::scanConverging, Noun::scanConverging_impl);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::iterate, StorageType::WORD, NounType::INTEGER, Noun::iterate_integer);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanIterating, StorageType::WORD, NounType::INTEGER, Noun::scanIterating_integer);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanOverNeutral_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanOverNeutral, StorageType::WORD, NounType::USER_MONAD, Noun::scanOverNeutral_impl);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::scanWhileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::scanWhileOne, StorageType::WORD, NounType::USER_MONAD, Noun::scanWhileOne_impl);  

  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::whileOne, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::whileOne_impl);  
  Noun::registerDyadicAdverb(StorageType::WORD_ARRAY, NounType::STRING, DyadicAdverbs::whileOne, StorageType::WORD, NounType::USER_MONAD, Noun::whileOne_impl);  
}

Storage IotaString::make(ints i)
{
  return WordArray::make(i, NounType::STRING);
}

Storage IotaString::makeEmpty()
{
  return WordArray::make(ints(), NounType::STRING);
}

Storage IotaString::atom_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints chars = std::get<ints>(i.i);

    if (chars.empty())
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::first_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints chars = std::get<ints>(i.i);

    if (chars.empty())
    {
      return Word::make(EMPTY, NounType::ERROR);
    }

    int c = chars.front();

    return Word::make(c, NounType::CHARACTER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::gradeDown_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
      results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
      return integers[x] > integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::gradeUp_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
      results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
      return integers[x] > integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::not_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if (integers.empty())
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::reverse_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers);
    std::reverse(results.begin(), results.end());
    
    return WordArray::make(results, NounType::STRING);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::size_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    int result = static_cast<int>(integers.size());
    
    return Word::make(result, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::group_impl(const Storage& i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints items = std::get<ints>(i.i);
    if(items.empty())
    {
      return WordArray::nil();
    }

    // Map from the item to the first index in the group
    std::unordered_map<int, int> firsts=std::unordered_map<int, int>();

    // Groups sorted by the first index in each group
    std::map<int, ints> groups=std::map<int, ints>();
    
    for (int index = 0; index < items.size(); index++)
    {
      // Get each item in the list
      int item = items[index];

      // Have we seen this item before?
      if(firsts.find(item) == firsts.end())
      {
        // This is a new item

        // Remember that this index was the first seen for this item
        firsts.insert({item, index});

        // Create a new group with this index in it
        ints group = ints({index + 1});

        // Store the group sorted by first index in the group
        groups[index] = group;
      }
      else
      {
        // This is a repeated item

        // Find the first index for this group
        int first = firsts[item];

        // Get the group by the first index
        ints group = groups[first];

        // Add the item to the group
        group.push_back(index + 1);

        // Store the group sorted by first index in the group
        groups[first] = group;
      }
    }

    mixed results = mixed();
    for (auto pair = groups.begin(); pair != groups.end(); ++pair)
    {
      ints group = pair->second;
      results.push_back(WordArray::make(group));
    }  

    return MixedArray::make(results);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
Storage IotaString::equal_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        if(iis[index] != xis[index])
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::find_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    ints results = ints();

    for(int index = 0; index < iis.size(); index++)
    {
      Storage si = Character::make(iis[index]);
      Storage matched = match(si, x);
      if(matched.o == NounType::ERROR)
      {
        return matched;
      }

      if(matched.truth())
      {
        results.push_back(index + 1);
      }
    }
    
    return WordArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::find_string(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(xis.empty())
      {
        return enumerate(Integer::make(iis.size() + 1));
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Character::make(iis[offset]);
          Storage sx = Character::make(xis[xindex]);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::form_integer(const Storage& i, const Storage& x)
{
  int unicode_minus = static_cast<int>('-');
  int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    int first = 1;
    int negative = 0;
    int result = 0;
    for(int y : iis)
    {
      if(first)
      {        
        first = 0;

        if(y == unicode_minus)
        {
          negative = 1;
          continue;
        }
      }

      int digit = y - unicode_zero;
      if((digit >= 0) && (digit <= 9))
      {
        result = result * 10;
        result = result + digit;
      }
      else
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
    }

    if(negative)
    {
      return Integer::make(-result);
    }
    else
    {
      return Integer::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::form_real(const Storage& i, const Storage& x)
{
  int unicode_minus = static_cast<int>('-');
  int unicode_zero = static_cast<int>('0'); // '0' is 48 (decimal) in Unicode, '1' is 49, etc.
  int unicode_period = static_cast<int>('.');

  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    int first = 1;
    int negative = 0;
    int decimalFound = 0;
    int integerPart = 0;
    int fractionalPart = 0;
    float fractionalPower = 1;
    for(int y : iis)
    {
      if(first)
      {        
        first = 0;

        if(y == unicode_minus)
        {
          negative = 1;
          continue;
        }
      }

      if(y == unicode_period)
      {
        if(decimalFound)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }
        else
        {        
          decimalFound = 1;
          continue;
        }
      }

      int digit = y - unicode_zero;
      if((digit >= 0) && (digit <= 9))
      {
        if(decimalFound)
        {
          fractionalPart = fractionalPart * 10;
          fractionalPart = fractionalPart + digit;

          fractionalPower = fractionalPower * 10.0;
        }
        else
        {
          integerPart = integerPart * 10;
          integerPart = integerPart + digit;
        }
      }
      else
      {
        return Word::make(INVALID_ARGUMENT, NounType::ERROR);
      }
    }

    float integerFloat = static_cast<float>(integerPart);
    float fractionalFloat = static_cast<float>(fractionalPart);
    float result = integerFloat + (fractionalFloat / fractionalPower);

    if(negative)
    {
      result = -result;
    }

    return Float::make(result);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}


Storage IotaString::form_list(const Storage& i, const Storage& x)
{
  return eachRight(Noun::mix(x), Word::make(Dyads::form, NounType::BUILTIN_DYAD), i);
}

Storage IotaString::form_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.size() == 1)
    {
      int result = iis[0];
      return Character::make(result);
    }
    else
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::form_quoted_symbol(const Storage& i, const Storage& x)
{
  int unicode_colon = static_cast<int>(':');

  if(std::holds_alternative<ints>(i.i))
  {
    ints result = ints(std::get<ints>(i.i));
    if(result.front() == unicode_colon)
    {
      result.erase(result.begin());
    }

    return QuotedSymbol::make(result);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::index_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        int result = iis[xi - 1];
        return Word::make(result, NounType::CHARACTER);
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          int result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage IotaString::append_character(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results(iis);
      results.insert(results.end(), xi);

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::join_string(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(iis);
      results.insert(results.end(), xis.begin(), xis.end());

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        if(iis[index] != xis[index])
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::rotate_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(iis.empty())
    {
      return i;
    }

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        int offset = iis.size() - (xi % iis.size());

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return IotaString::make(results);
      }
      else // x < 0
      {
        xi = -xi;

        int offset = xi % iis.size();

        ints results(iis.begin() + offset, iis.end());
        results.insert(results.end(), iis.begin(), iis.begin() + offset);
        return IotaString::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::split_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          mixed results = mixed();
          results.push_back(i);

          return MixedArray::make(results);
        }

        mixed results = mixed();

        ints result = ints();
        for(int index = 0; index < iis.size(); index++)
        {
          result.push_back(iis[index]);

          if(result.size() == xi)
          {
            results.push_back(IotaString::make(result));
            result = ints();
          }
        }

        if(result.size() > 0)
        {
          results.push_back(IotaString::make(result));
        }

        return MixedArray::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::split_integers(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      int count = 0;
      int index = 0;
      while(count < iis.size())
      {
        int y = xis[index++ % xis.size()]; // cycle
        
        if(count + y > iis.size())
        {
          ints result(iis.begin(), iis.end());
          results.push_back(IotaString::make(result));
          break;
        }
        else
        {
          ints result(iis.begin() + count, iis.begin() + count + y);
          results.push_back(IotaString::make(result));
        }

        count = count + y;
      }

      if(count < iis.size())
      {
        ints result(iis.begin() + count, iis.end());
        results.push_back(IotaString::make(result));
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::take_integer(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.empty())
      {
        return i;
      }

      if(xi == 0)
      {
        return IotaString::makeEmpty();
      }

      if(xi > 0)
      {
        ints results = ints();
        for(int index = 0; index < xi; index++)
        {
          results.push_back(iis[index % iis.size()]); // cycle through iis
        }

        return IotaString::make(results);
      }
      else if(xi < 0)
      {
        xi = -xi;
        int start = iis.size() - (xi % iis.size());

        ints results = ints();
        for(int offset = 0; offset < xi; offset++)
        {
          int index = (start + offset) % iis.size();
          results.push_back(iis[index]);
        }

        return IotaString::make(results);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Monadic Adverbs
Storage IotaString::each_impl(const Storage& i, const Storage& f)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();
    for(int y : iis)
    {
      Storage result = Noun::dispatchMonad(Character::make(y), f);

      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return Noun::simplify(MixedArray::make(results));
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> IotaString::from_bytes(const bytes& bs, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_bytes(bs, NounType::STRING);

    default:
      return std::nullopt;
  }
}

maybe<bytes> IotaString::to_bytes(const Storage& i) {
  if (i.o != NounType::STRING) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      return WordArray::to_bytes(i);

    default:
      return std::nullopt;
  }
}

maybe<Storage> IotaString::from_conn(const Connection& conn, int t) {
  switch (t)
  {
    case StorageType::WORD_ARRAY:
      return WordArray::from_conn(conn, NounType::STRING);

    default:
      return std::nullopt;
  }
}

void IotaString::to_conn(const Connection& conn, const Storage& i) {
  if (i.o != NounType::STRING) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        // No need to include type here because it is provided by Word::to_conn
        return WordArray::to_conn(conn, i);
      }

    default:
      return;
  }
}

// Dictionary
void Dictionary::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::first, Noun::identity1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::inot, Noun::false1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::reverse, Noun::identity1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::shape, Noun::false1);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Monads::undefined, Noun::false1);

  // Dyads
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD, NounType::INTEGER, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::FLOAT, NounType::REAL, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD, NounType::CHARACTER, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dictionary::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::find, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dictionary::find_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dictionary::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::match, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Noun::false2);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::DICTIONARY, Dyads::rotate, StorageType::WORD, NounType::INTEGER, Noun::identity2);
}

Storage Dictionary::make(const mixed &i)
{
  return MixedArray::make(i, NounType::DICTIONARY);
}

Storage Dictionary::makeEmpty()
{
  return MixedArray::make(mixed(), NounType::DICTIONARY);
}

Storage Dictionary::find_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.size() == 2)
    {
      Storage keys = ms[0];
      Storage values = ms[1];

      Storage indices = find(keys, x);

      if(std::holds_alternative<ints>(indices.i))
      {
        ints integerIndices = std::get<ints>(indices.i);

        if(integerIndices.size() == 0)
        {
          return QuotedSymbol::undefined();
        }
        else if(integerIndices.size() == 1)
        {
          int valueIndex = integerIndices.front();

          Storage result = index(values, Integer::make(valueIndex));

          if(result.o == NounType::ERROR)
          {
            return QuotedSymbol::undefined();
          }

          return result;
        }        
      }
    }        
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Dictionary::match_impl(const Storage& i, const Storage& x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage matched = match(iis[index], xis[index]);
        if(matched.truth())
        {
          continue;
        }
        else
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

maybe<Storage> Dictionary::from_bytes(bytes bs, int t)
{
  switch (t)
  {
    case StorageType::MIXED_ARRAY:
      return MixedArray::from_bytes(bs, NounType::DICTIONARY);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Dictionary::to_bytes(const Storage& i)
{
  // Don't include type, that is handled by Noun::to_bytes

  if (i.o != NounType::LIST)
  {
    return std::nullopt;
  }

  bytes result = bytes();

  switch (i.t)
  {
    case StorageType::MIXED_ARRAY:
    {
      return MixedArray::to_bytes(i);
    }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Dictionary::from_conn(const Connection& conn, int t)
{
  switch (t)
  {
    case StorageType::MIXED_ARRAY:
      return MixedArray::from_conn(conn, NounType::DICTIONARY);

    default:
      return std::nullopt;
  }
}

void Dictionary::to_conn(const Connection& conn, const Storage& i)
{
  if (i.o != NounType::LIST)
  {
    return;
  }

  switch (i.t)
  {
    case StorageType::MIXED_ARRAY:
    {
      // No need to include type here, because it is provided by MixedArray::to_conn
      MixedArray::to_conn(conn, i);
    }

    default:
      return;
  }
}

// Expression
void Expression::initialize() {
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::EXPRESSION, Monads::evaluate, Noun::evaluate_expression);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::EXPRESSION, Monads::truth, Expression::truth);

  /* FIXME
  Dyads.applyMonad: {
      (NounType.BUILTIN_MONAD, StorageType.StorageType::WORD): Storage.applyMonad_expression,
      (NounType.USER_MONAD, StorageType.StorageType::MIXED_ARRAY): Storage.applyMonad_expression,
  },

  Triads.applyDyad: {
      (NounType.BUILTIN_DYAD, StorageType.StorageType::WORD): Storage.applyDyad_expression,
      (NounType.USER_DYAD, StorageType.StorageType::MIXED_ARRAY): Storage.applyDyad_expression,
  },
  */
}

Storage Expression::truth(const Storage& i) {
  return truth(evaluate(i));
}

// Conditional
void Conditional::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::evaluate, Noun::evaluate_expression);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::truth, Expression::truth);

  // Extension Monads
  // Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::erase, MixedArray::erase_impl);

  // Extension Dyads
  // Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::retype, StorageType::WORD, NounType::TYPE, MixedArray::retype_impl);  

  // Dyads
  // Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::applyMonad, StorageType::WORD, NounType::BUILTIN_MONAD, Noun::applyMonad_expression);
  // Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::applyMonad, StorageType::MIXED_ARRAY, NounType::USER_MONAD, Noun::applyDyad_expression);

  // Triads
  // Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::applyDyad, StorageType::WORD, NounType::BUILTIN_DYAD, Noun::applyMonad_expression);
  // Noun::registerTriad(StorageType::MIXED_ARRAY, NounType::CONDITIONAL, Monads::applyDyad, StorageType::MIXED_ARRAY, NounType::USER_DYAD, Noun::applyDyad_expression);
}

Storage Conditional::make(const mixed &i)
{
  return MixedArray::make(i, NounType::CONDITIONAL);
}

Storage Conditional::evaluate_impl(const Storage& e)
{
  if(std::holds_alternative<mixed>(e.i))
  {
    mixed mis = std::get<mixed>(e.i);

    if(mis.size() != 3)
    {
      return Word::make(SHAPE_MISMATCH, NounType::ERROR);
    }

    Storage a = mis[0];
    Storage b = mis[1];
    Storage c = mis[2];

    if(a.truth())
    {
      return evaluate(b);
    }
    else
    {
      return evaluate(c);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Conditional::truth_impl(const Storage& i)
{
  return truth(evaluate(i));
}

// Symbol
std::unordered_map<int, ints> Symbol::integerToString;
std::unordered_map<ints, int, IntsHash> Symbol::stringToInteger;
std::unordered_map<int, Storage> Symbol::values;

void Symbol::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::BUILTIN_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::BUILTIN_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::USER_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::USER_SYMBOL, Monads::evaluate, Symbol::evaluate_impl);

  Noun::registerMonad(StorageType::WORD, NounType::BUILTIN_SYMBOL, Monads::truth, Symbol::truth_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::BUILTIN_SYMBOL, Monads::truth, Symbol::truth_impl);
  Noun::registerMonad(StorageType::WORD, NounType::USER_SYMBOL, Monads::truth, Symbol::truth_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::USER_SYMBOL, Monads::truth, Symbol::truth_impl);

  // Symbol tables
  integerToString[SymbolType::x] = asciiToUTF32("x");
  stringToInteger[asciiToUTF32("x")] = SymbolType::x;

  integerToString[SymbolType::y]=asciiToUTF32("y");
  stringToInteger[asciiToUTF32("y")] = SymbolType::y;

  integerToString[SymbolType::z]=asciiToUTF32("z");
  stringToInteger[asciiToUTF32("z")] = SymbolType::z;

  integerToString[SymbolType::f]=asciiToUTF32("f");
  stringToInteger[asciiToUTF32("f")] = SymbolType::f;

  integerToString[SymbolType::undefined]=asciiToUTF32("undefined");
  stringToInteger[asciiToUTF32("undefined")] = SymbolType::undefined;
}

Storage Symbol::evaluate_impl(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    auto pair = values.find(ii);
    if(pair == values.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    return pair->second;
  }
  else if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(stringToInteger.find(iis) == stringToInteger.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    int integer = stringToInteger[iis];

    auto pair = values.find(integer);
    if(pair == values.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }

    return pair->second;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Symbol::truth_impl(const Storage& i)
{
  return truth(evaluate(i));
}

ints Symbol::asciiToUTF32(const std::string& ascii)
{
  ints results = ints();

  for(char y : ascii)
  {
    results.push_back(static_cast<int>(y));
  }

  return results;
}

void QuotedSymbol::initialize()
{
  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::evaluate, Noun::identity1);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::format, QuotedSymbol::format_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::undefined, QuotedSymbol::undefined_impl);

  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Monads::truth, Noun::true1);

  // Dyads
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::format2, StorageType::WORD, NounType::INTEGER, Integer::format2_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::format2, StorageType::FLOAT, NounType::REAL, Integer::format2_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::MIXED_ARRAY, NounType::DICTIONARY, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, Dyads::match, StorageType::WORD_ARRAY, NounType::QUOTED_SYMBOL, IotaString::match_impl);
}

Storage QuotedSymbol::make(const ints &i)
{
  return WordArray::make(i, NounType::QUOTED_SYMBOL);
}

Storage QuotedSymbol::undefined()
{
  ints name = Symbol::integerToString[SymbolType::undefined];
  return QuotedSymbol::make(name);
}

Storage QuotedSymbol::format_impl(const Storage& i)
{
  int unicode_colon = static_cast<int>(':');

  if(std::holds_alternative<ints>(i.i))
  {
    ints result = ints(std::get<ints>(i.i));
    result.insert(result.begin(), unicode_colon);
    return IotaString::make(result);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage QuotedSymbol::undefined_impl(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    ints name = Symbol::integerToString[SymbolType::undefined];

    if(integers == name)
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// MixedArray
// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(bytes x, int o)
{
  return maybe<Storage>(Storage(0, StorageType::WORD, 0));
}

// Encodes a MixedArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x to_bytes} over join)
maybe<bytes> MixedArray::to_bytes(const Storage& i) {
  if (std::holds_alternative<mixed>(i.i)) {
    mixed ii = std::get<mixed>(i.i);

    bytes r = bytes();

    int size = ii.size();
    bytes sizeBytes = squeeze_int(size);

    r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

    for (Storage y : ii) {
      bytes valueBytes = Noun::to_bytes(y);
      r.insert(r.end(), valueBytes.begin(), valueBytes.end());
    }

    return maybe<bytes>(r);
  } else {
    return std::nullopt;
  }
}

maybe<Storage> MixedArray::from_conn(const Connection& conn, int o) {
  varint varsize = expand_conn(conn);
  if (std::holds_alternative<int>(varsize)) {
    int size = std::get<int>(varsize);

    mixed i = mixed();

    for (int y = 0; y < size; y++) {
      if (maybe<Storage> maybeStorage = Noun::from_conn(conn)) {
        i.push_back(*maybeStorage);
      } else {
        return std::nullopt;
      }
    }

    return MixedArray::make(i, o);
  } else {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void MixedArray::to_conn(const Connection& conn, const Storage& x) {
  if (std::holds_alternative<mixed>(x.i)) {
    mixed i = std::get<mixed>(x.i);

    // Always include type in to_conn implementation
    conn.write({ static_cast<char>(x.t), static_cast<char>(x.o) });

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for (Storage y : i) {
      Noun::to_conn(conn, y);
    }
  }
}

Storage MixedArray::make(mixed x, int o) {
  return Storage(o, StorageType::MIXED_ARRAY, x);
}
