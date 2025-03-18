//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef EFFECTS_REGISTER_H
#define EFFECTS_REGISTER_H

#include <queue>

#include "eval_register.h"

#include "effects/effect.h"

class EvalRegister;

class EffectsRegister
{
  public:
    static void initialize();

    void setEvalRegister(EvalRegister* reg);

    void handleEffects();

  private:
    EvalRegister* eval_register = nullptr;
    std::queue<Effect> effects;
};

#endif //EFFECTS_REGISTER_H
