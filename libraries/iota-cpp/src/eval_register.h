#ifndef REGISTER_H_
#define REGISTER_H_

#include "types.h"

#include "effects/effects_register.h"
#include "storage/storage.h"
#include "storage/word.h"

class EvalRegister;
class EffectsRegister;

class EvalRegister
{
  public:
    static EvalRegister defaultInstance();

    static void initialize();
    static maybe<Storage> eval(const Storage& i);

    EvalRegister() : i(Word::make(0, NounType::INTEGER)), r(std::nullopt) {}
    EvalRegister(const EvalRegister& other) = default;
    explicit EvalRegister(const Storage& i) : i(i), r(std::nullopt) {}

    void setEffectsRegister(EffectsRegister* reg);

    void store_i(const Storage& newI);
    Storage fetch_i();
    void load_i(bytes data);

    maybe<Storage> fetch_r();
    [[nodiscard]] maybe<bytes> retrieve_r() const;

    void eval();

  private:
    static maybe<EvalRegister> instance;

    Storage i;
    maybe<Storage> r;
    EffectsRegister* effects_register = nullptr;
};

#endif