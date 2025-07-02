#include "IotaMain.h"

#include <iostream>

#include <eval_register.h>
#include <types.h>

IotaMain::IotaMain() : conn(IostreamStorageConnection::make()), eval_register(EvalRegister()), effects_register(EffectsProvider())
{
    EvalRegister::initialize();
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
