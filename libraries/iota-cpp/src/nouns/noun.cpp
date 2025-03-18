#include <vector>
#include <variant>
#include <algorithm>

#include "noun.h"
#include "nouns.h"

#include "../squeeze.h"
#include "../verbs.h"
#include "../error.h"

#include "../storage/word.h"
#include "../storage/word_array.h"
#include "../storage/iota_float.h"
#include "../storage/float_array.h"
#include "../storage/mixed_array.h"

std::map<Specialization3, Monad> Noun::monads;
std::map<Specialization5, Dyad> Noun::dyads;
std::map<Specialization5, Triad> Noun::triads;
std::map<Specialization3, MonadicAdverb> Noun::monadicAdverbs;
std::map<Specialization5, DyadicAdverb> Noun::dyadicAdverbs;

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
  if(std::holds_alternative<ints>(i.i) || std::holds_alternative<floats>(i.i))
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

    equivalence = match(next, previous);
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

    equivalence = match(next, previous);
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

  // The next two lines are to dispel the perception that we accidentally swapped the order of the arguments i and x.
  const Storage& swapX = i;
  const Storage& swapI = x;
  return over(prepend(swapI, swapX), f);
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

// FIXME - address leak
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

maybe<Storage> Noun::from_conn(const Connection& conn) {
  int storageType = static_cast<unsigned char>(conn.readOne());

  switch (int objectType = static_cast<unsigned char>(conn.readOne())) {
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

