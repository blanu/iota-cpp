#include <optional>
#include <utility>

#include "eval_register.h"

#include "symbols.h"
#include "storage/storage.h"
#include "nouns/noun.h"

maybe<EvalRegister> EvalRegister::instance = std::nullopt;

void EvalRegister::initialize()
{
  Noun::initialize();
}

maybe<Storage> EvalRegister::eval(const Storage& i)
{
  auto evalRegister = EvalRegister();
  evalRegister.store_i(i);
  evalRegister.eval();
  return evalRegister.fetch_r();
}

void EvalRegister::store_i(const Storage& newI)
{
  i = newI;
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
