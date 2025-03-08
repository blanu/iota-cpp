#ifndef REGISTER_H_
#define REGISTER_H_

#include "storage.h"

class EvalRegister;

class EvalRegister
{
  public:
    static void initialize();

    EvalRegister() : i(Word::make(0, NounType::INTEGER)), r(std::nullopt) {}
    explicit EvalRegister(Storage i) : i(i), r(std::nullopt) {}

    void store_i(Storage newI);
    Storage fetch_i();
    void load_i(bytes data);

    maybe<Storage> fetch_r();
    maybe<bytes> retrieve_r() const;

    void eval();

  private:
    Storage i;
    maybe<Storage> r;
};

#endif