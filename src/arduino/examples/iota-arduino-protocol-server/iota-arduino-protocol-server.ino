#include <Arduino.h>

#include <eval_register.h>
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
  std::optional<Storage> storage = conn.read_storage();

  if(storage)
  {
    maybe<Storage> result = EvalRegister::eval(*storage);

    conn.write_storage(*result);
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