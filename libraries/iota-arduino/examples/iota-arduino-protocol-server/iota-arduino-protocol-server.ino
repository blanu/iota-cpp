#include <Arduino.h>

#include <eval_register.h>
#include <effects/effects_register.h>
#include <types.h>

#include "debug.h"
#include "SerialConnection.h"

SerialConnection conn = SerialConnection::make();

void setup()
{
  pinMode(D13, OUTPUT);
  while(!Serial)
  {
    blink(255, 255, 255, 1, 200, 200);
  }

  EvalRegister::initialize();
}

void loop()
{
  EffectsRegister effects_register = EffectsRegister();

  std::optional<Storage> storage = conn.read_storage();

  if(storage)
  {
    maybe<Storage> result = EvalRegister::eval(*storage);

    if(result)
    {
      if((*result).o == NounType::SIGNAL)
      {
        Storage signalResult = effects_register.eval(*result);

        while(signalResult.o == NounType::SIGNAL)
        {
          signalResult = effects_register.eval(signalResult);
        }

        conn.write_storage(signalResult);
      }
    }
    else
    {
      conn.write_storage(*result);
    }
  }
}

void blink(byte r, byte g, byte b, int count, int onTime, int offTime)
{
  for(int x=0; x<count; x++)
  {
    digitalWrite(D13, HIGH);
    delay(onTime);

    digitalWrite(D13, LOW);
    delay(offTime);
  }
}