//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "verbs.h"
#include "symbols.h"

#include "nouns/noun.h"
#include "storage/word.h"

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
