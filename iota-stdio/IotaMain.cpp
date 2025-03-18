#include "IotaMain.h"

#include <iostream>

#include <eval_register.h>
#include <types.h>

IotaMain::IotaMain() : conn(IostreamStorageConnection::make()), eval_register(EvalRegister()), effects_register(EffectsRegister())
{
    EvalRegister::initialize();
    EffectsRegister::initialize();

    eval_register.setEffectsRegister(&effects_register);
    effects_register.setEvalRegister(&eval_register);
}

void IotaMain::loop()
{
    std::optional<Storage> storage = conn.read_storage();

    if(storage)
    {
        eval_register.store_i(*storage);
        eval_register.eval();
        maybe<Storage> result = eval_register.fetch_r();

        if(result)
        {
            conn.write_storage(*result);
        }
    }
}
