#ifndef REGISTER_H_
#define REGISTER_H_

#include <string>
#include <map>
#include <vector>
#include <tuple>

#include <types.h>

#include <ion-cpp.h>

#include "effects/effects_provider.h"

class EvalRegister;
class EffectsProvider;

class EvalRegister
{
  public:
    static void initialize();
    static maybe<Storage> eval(const Storage& i);
    static void registerEffectsProvider(EffectsProvider& reg);

    EvalRegister() : i(Word::make(0, NounType::INTEGER)), r(std::nullopt) {}
    EvalRegister(const EvalRegister& other) = default;
    explicit EvalRegister(const Storage& i) : i(i), r(std::nullopt) {}

    void store_i(const Storage& newI);
    Storage fetch_i();
    void load_i(bytes data);

    maybe<Storage> fetch_r();
    [[nodiscard]] maybe<bytes> retrieve_r() const;

    void eval();

    std::vector<std::tuple<Storage, Storage>> getLogs();
    void printLogs();

    static void printLog(Storage li, Storage lr);

  private:
    static maybe<EvalRegister> instance;

    Storage i;
    maybe<Storage> r;
    EffectsProvider* effects_register = nullptr;

    std::vector<std::tuple<Storage, Storage>> logs = std::vector<std::tuple<Storage, Storage>>();
};

#endif