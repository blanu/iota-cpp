//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include "noun.h"

#include "conditional.h"
#include "expression.h"

#include "../symbols.h"
#include "../error.h"
#include "../verbs.h"
#include "../api.h"

#include "../storage/word.h"
#include "../storage/mixed_array.h"

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
  using namespace iota;

  if(std::holds_alternative<mixed>(e.i))
  {
    mixed mis = std::get<mixed>(e.i);

    if(mis.size() != 3)
    {
      return Word::make(SHAPE_MISMATCH, NounType::ERROR);
    }

    const Storage& a = mis[0];
    const Storage& b = mis[1];
    const Storage& c = mis[2];

    if(a.truth())
    {
      return eval({b, evaluate});
    }
    else
    {
      return eval({c, evaluate});
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Conditional::truth_impl(const Storage& i)
{
  using namespace iota;

  return eval({i, evaluate, truth});
}
