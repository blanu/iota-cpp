//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "noun.h"
#include "symbols.h"
#include "verbs.h"

#include "expression.h"

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
