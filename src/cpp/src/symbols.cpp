//
// Created by Dr. Brandon Wiley on 11/16/25.
//

#include <symbols.h>

void Nilads::initialize()
{
  INTERN_INT(symbols);
}

void Monads::initialize()
{
  INTERN_INT(atom);
  INTERN_INT_AS(char, ichar);
  INTERN_INT(enclose);
  INTERN_INT(enumerate);
  INTERN_INT(expand);
  INTERN_INT(first);
  INTERN_INT(floor);
  INTERN_INT(format);
  INTERN_INT(gradeDown);
  INTERN_INT(gradeUp);
  INTERN_INT(group);
  INTERN_INT(negate);
  INTERN_INT_AS(not, inot);
  INTERN_INT(reciprocal);
  INTERN_INT(reverse);
  INTERN_INT(shape);
  INTERN_INT(size);
  INTERN_INT(transpose);
  INTERN_INT(unique);
  INTERN_INT(count);
  INTERN_INT(undefined);

  INTERN_INT(evaluate);
  INTERN_INT(erase);
  INTERN_INT(truth);
  INTERN_INT(lift);
  INTERN_INT(occurs);
  INTERN_INT(range);
}

void Dyads::initialize()
{
    INTERN_INT(amend);
    INTERN_INT(cut);
    INTERN_INT(divide);
    INTERN_INT(drop);
    INTERN_INT(equal);
    INTERN_INT(find);
    INTERN_INT(form);
    INTERN_INT(format2);
    INTERN_INT(index);
    INTERN_INT(indexInDepth);
    INTERN_INT(integerDivide);
    INTERN_INT(join);
    INTERN_INT(append);
    INTERN_INT(less);
    INTERN_INT(match);
    INTERN_INT(max);
    INTERN_INT(min);
    INTERN_INT(minus);
    INTERN_INT(more);
    INTERN_INT(plus);
    INTERN_INT(power);
    INTERN_INT(remainder);
    INTERN_INT(reshape);
    INTERN_INT(rotate);
    INTERN_INT(split);
    INTERN_INT(take);
    INTERN_INT(times);

    INTERN_INT(applyMonad);
    INTERN_INT(retype);
    INTERN_INT(causes);
    INTERN_INT(because);
    INTERN_INT(then);
    INTERN_INT(bind);
    INTERN_INT(retrieve);
    INTERN_INT(resolve);
}

void Triads::initialize()
{
  INTERN_INT(applyDyad);
  INTERN_INT(store);
  INTERN_INT(bind);
}

void MonadicAdverbs::initialize()
{
  INTERN_INT(converge);
  INTERN_INT(each);
  INTERN_INT(eachPair);
  INTERN_INT(over);
  INTERN_INT(scanConverging);
  INTERN_INT(scanOver);
}

void DyadicAdverbs::initialize()
{
  INTERN_INT(each2);
  INTERN_INT(eachLeft);
  INTERN_INT(eachRight);
  INTERN_INT(overNeutral);
  INTERN_INT(whileOne);
  INTERN_INT(iterate);
  INTERN_INT(scanOverNeutral);
  INTERN_INT(scanWhileOne);
  INTERN_INT(scanIterating);
}

void TriadicAdverbs::initialize()
{
  INTERN_INT(till);
}
