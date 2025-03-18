//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef IOSTREAMSTORAGECONNECTION_H
#define IOSTREAMSTORAGECONNECTION_H

#include "storage/storage.h"
#include "StorageConnection.h"

#include "IostreamConnection.h"

class IostreamStorageConnection : public IostreamConnection
{
  public:
    static IostreamStorageConnection make();

    explicit IostreamStorageConnection(const IostreamConnection &reliable) : reliable(reliable) {}

    ~IostreamStorageConnection() {}

    maybe<Storage> read_storage();
    void write_storage(Storage x);

  private:
    IostreamConnection reliable;
};

#endif //IOSTREAMSTORAGECONNECTION_H
