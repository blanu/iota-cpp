#ifndef _SERIAL_CONNECTION_H_
#define _SERIAL_CONNECTION_H_

#include <Arduino.h>

#include "storage/storage.h"
#include "StorageConnection.h"

#include <ReliableConnectionUsbCdc.h>

class SerialConnection : public StorageConnection
{
  public:
    static SerialConnection make();

    explicit SerialConnection(const ReliableConnectionUsbCdc &reliable) : reliable(reliable) {}

    ~SerialConnection() {}

    maybe<Storage> read_storage();
    void write_storage(Storage x);

  private:
    ReliableConnectionUsbCdc reliable;
};

#endif