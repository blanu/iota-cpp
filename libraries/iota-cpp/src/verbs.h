//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef VERBS_H
#define VERBS_H

#include "storage/storage.h"

int getInteger(const Storage& i);

// Monads
Storage atom(const Storage& i);
Storage ichar(const Storage& i);
Storage enclose(const Storage& i);
Storage enumerate(const Storage& i);
Storage expand(const Storage& i);
Storage first(const Storage& i);
Storage floor(const Storage& i);
Storage format(const Storage& i);
Storage gradeDown(const Storage& i);
Storage gradeUp(const Storage& i);
Storage group(const Storage& i);
Storage negate(const Storage& i);
Storage reciprocal(const Storage& i);
Storage reverse(const Storage& i);
Storage shape(const Storage& i);
Storage size(const Storage& i);
Storage transpose(const Storage& i);
Storage unique(const Storage& i);
Storage inot(const Storage& i);
Storage undefined(const Storage& i);

// Extension Monads

Storage evaluate(const Storage& i);
Storage erase(const Storage& i);
Storage truth(const Storage& i);

// Dyads
Storage amend(const Storage& i, const Storage& x);
Storage cut(const Storage& i, const Storage& x);
Storage divide(const Storage& i, const Storage& x);
Storage drop(const Storage& i, const Storage& x);
Storage equal(const Storage& i, const Storage& x);
Storage find(const Storage& i, const Storage& x);
Storage form(const Storage& i, const Storage& x);
Storage format2(const Storage& i, const Storage& x);
Storage index(const Storage& i, const Storage& x);
Storage integerDivide(const Storage& i, const Storage& x);
Storage join(const Storage& i, const Storage& x);
Storage less(const Storage& i, const Storage& x);
Storage match(const Storage& i, const Storage& x);
Storage max(const Storage& i, const Storage& x);
Storage min(const Storage& i, const Storage& x);
Storage minus(const Storage& i, const Storage& x);
Storage more(const Storage& i, const Storage& x);
Storage plus(const Storage& i, const Storage& x);
Storage power(const Storage& i, const Storage& x);
Storage remainder(const Storage& i, const Storage& x);
Storage reshape(const Storage& i, const Storage& x);
Storage rotate(const Storage& i, const Storage& x);
Storage split(const Storage& i, const Storage& x);
Storage take(const Storage& i, const Storage& x);
Storage times(const Storage& i, const Storage& x);

// Monadic Adverbs
Storage converge(const Storage& i, const Storage& f);
Storage each(const Storage& i, const Storage& f);
Storage eachPair(const Storage& i, const Storage& f);
Storage over(const Storage& i, const Storage& f);
Storage scanConverging(const Storage& i, const Storage& f);
Storage scanOver(const Storage& i, const Storage& f);

// Dyadic Adverbs
Storage each2(const Storage& i, const Storage& f, const Storage& x);
Storage eachLeft(const Storage& i, const Storage& f, const Storage& x);
Storage eachRight(const Storage& i, const Storage& f, const Storage& x);
Storage overNeutral(const Storage& i, const Storage& f, const Storage& x);
Storage iterate(const Storage& i, const Storage& f, const Storage& x);
Storage scanIterating(const Storage& i, const Storage& f, const Storage& x);
Storage scanOverNeutral(const Storage& i, const Storage& f, const Storage& x);
Storage scanWhileOne(const Storage& i, const Storage& f, const Storage& x);
Storage whileOne(const Storage& i, const Storage& f, const Storage& x);

#endif //VERBS_H
