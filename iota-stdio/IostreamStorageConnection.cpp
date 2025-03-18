//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "IostreamStorageConnection.h"

#include "IostreamConnection.h"

#include "types.h"

#include "storage/storage.h"
#include "nouns/noun.h"

IostreamStorageConnection IostreamStorageConnection::make()
{
  return IostreamStorageConnection(IostreamConnection());
}

maybe<Storage> IostreamStorageConnection::read_storage()
{
  return Noun::from_conn(reliable);
}

void IostreamStorageConnection::write_storage(Storage x)
{
  Noun::to_conn(reliable, x);
}
