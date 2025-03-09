#include "SerialConnection.h"

#include "squeeze.h"
#include "types.h"

#include "storage/storage.h"

#include "nouns/noun.h"

#include "ReliableConnection.h"

SerialConnection SerialConnection::make()
{
  Serial.begin(115200);
  return SerialConnection(ReliableConnection(Serial));
}

maybe<Storage> SerialConnection::read_storage()
{
  return Noun::from_conn(reliable);
}

void SerialConnection::write_storage(Storage x)
{
  Noun::to_conn(reliable, x);
}
