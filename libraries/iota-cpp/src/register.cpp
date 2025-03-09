#include <optional>
#include <utility>
#include "register.h"
#include "storage/storage.h"
#include "symbols.h"
#include "nouns/noun.h"

void EvalRegister::initialize()
{
  Noun::initialize();
}

// Be careful with this function, it moves newI.
void EvalRegister::store_i(Storage newI)
{
  i = std::move(newI);
}

Storage EvalRegister::fetch_i()
{
  return i;
}

// Be careful with this function, it moves data.
void EvalRegister::load_i(bytes data)
{
  if(maybe<Storage> maybeResult = Noun::from_bytes(std::move(data)))
  {
    i = *maybeResult;
  }
}

maybe<Storage> EvalRegister::fetch_r()
{
  return r;
}

maybe<bytes> EvalRegister::retrieve_r() const
{
  if(r)
  {
    Storage value = *r;
    return {Noun::to_bytes(value)};
  }
  else
  {
    return std::nullopt;
  }
}

void EvalRegister::eval()
{
  r = Noun::dispatchMonad(i, Word::make(Monads::evaluate, NounType::BUILTIN_MONAD));
}

