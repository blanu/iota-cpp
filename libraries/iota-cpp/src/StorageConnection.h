#ifndef SERIAL_CONNECTION_H_
#define SERIAL_CONNECTION_H_

#include "types.h"
#include "storage/storage.h"

#define EXPORT

class EXPORT StorageConnection
{
  public:
    virtual ~StorageConnection() = default;

    virtual maybe<Storage> read_storage() = 0;
    virtual void write_storage(Storage x) = 0;
};

#endif