//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef VERBS_H
#define VERBS_H

#include "symbols.h"

#include <storage/storage.h>

int getInteger(const Storage& i);

class Monad
{
  public:
    static Storage make(int i);
};

class Dyad
{
  public:
    static Storage make(int i);
};

// Monads
namespace iota
{
  inline Storage atom = Monad::make(Monads::atom);
  inline Storage ichar = Monad::make(Monads::ichar);
  inline Storage enclose = Monad::make(Monads::enclose);
  inline Storage enumerate = Monad::make(Monads::enumerate);
  inline Storage expand = Monad::make(Monads::expand);
  inline Storage first = Monad::make(Monads::first);
  inline Storage floor = Monad::make(Monads::floor);
  inline Storage format = Monad::make(Monads::format);
  inline Storage gradeDown = Monad::make(Monads::gradeDown);
  inline Storage gradeUp = Monad::make(Monads::gradeUp);
  inline Storage group = Monad::make(Monads::group);
  inline Storage negate = Monad::make(Monads::negate);
  inline Storage inot = Monad::make(Monads::inot);
  inline Storage reciprocal = Monad::make(Monads::reciprocal);
  inline Storage reverse = Monad::make(Monads::reverse);
  inline Storage shape = Monad::make(Monads::shape);
  inline Storage size = Monad::make(Monads::size);
  inline Storage transpose = Monad::make(Monads::transpose);
  inline Storage unique = Monad::make(Monads::unique);
  inline Storage undefined = Monad::make(Monads::undefined);

  // Extension Monads
  inline Storage evaluate = Monad::make(Monads::evaluate);
  inline Storage erase = Monad::make(Monads::erase);
  inline Storage truth = Monad::make(Monads::truth);
  inline Storage lift = Monad::make(Monads::lift);
  inline Storage occurs = Monad::make(Monads::occurs);

  // Dyads
  inline Storage amend = Dyad::make(Dyads::amend);
  inline Storage cut = Dyad::make(Dyads::cut);
  inline Storage divide = Dyad::make(Dyads::divide);
  inline Storage drop = Dyad::make(Dyads::drop);
  inline Storage equal = Dyad::make(Dyads::equal);
  inline Storage find = Dyad::make(Dyads::find);
  inline Storage form = Dyad::make(Dyads::form);
  inline Storage format2 = Dyad::make(Dyads::format2);
  inline Storage index = Dyad::make(Dyads::index);
  inline Storage integerDivide = Dyad::make(Dyads::integerDivide);
  inline Storage join = Dyad::make(Dyads::join);
  inline Storage less = Dyad::make(Dyads::less);
  inline Storage match = Dyad::make(Dyads::match);
  inline Storage max = Dyad::make(Dyads::max);
  inline Storage min = Dyad::make(Dyads::min);
  inline Storage minus = Dyad::make(Dyads::minus);
  inline Storage more = Dyad::make(Dyads::more);
  inline Storage plus = Dyad::make(Dyads::plus);
  inline Storage power = Dyad::make(Dyads::power);
  inline Storage remainder = Dyad::make(Dyads::remainder);
  inline Storage reshape = Dyad::make(Dyads::reshape);
  inline Storage rotate = Dyad::make(Dyads::rotate);
  inline Storage split = Dyad::make(Dyads::split);
  inline Storage take = Dyad::make(Dyads::take);
  inline Storage times = Dyad::make(Dyads::times);
}

#endif //VERBS_H
