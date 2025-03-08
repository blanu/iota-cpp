#include "ReliableConnection.h"

char ReliableConnection::readOne() const
{
  // Wait for serial port to be ready
  while(!Serial || !Serial.available())
  {
    delay(0.01);
  }

  int b = -1;
  while(b == -1)
  {
    b = Serial.read();
  }

  return (byte)b;
}

bytes ReliableConnection::read(int size) const
{
  bytes r = bytes();

  while(r.size() < size)
  {
    byte b = readOne();
    r.push_back(b);
  }

  return r;
}

void ReliableConnection::write(bytes bs) const
{
  for (byte b : bs)
  {
    Serial.write(b); // Send each byte
  }
}

