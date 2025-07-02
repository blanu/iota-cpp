#ifndef MAIN_H
#define MAIN_H

#include <eval_register.h>
#include <effects/effects_provider.h>

#include "IostreamStorageConnection.h"

class IotaMain
{
  public:
    IotaMain();

    void loop();

  private:
    IostreamStorageConnection conn;
    EvalRegister eval_register;
    EffectsProvider effects_register;
};

#endif //MAIN_H
