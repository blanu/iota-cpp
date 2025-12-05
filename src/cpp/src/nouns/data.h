//
// Created by Dr. Brandon Wiley on 10/29/25.
//

#ifndef IOTA_CPP_DATA_H
#define IOTA_CPP_DATA_H

#include <vector>
#include <tuple>

#include <storage/storage.h>
#include <Connection.h>

#include <types.h>

class Data
{
  public:
    static void initialize();

    static Storage make(std::vector<uint8_t> i);

    static maybe<std::vector<uint8_t>> toBytes(const Storage& i);

    // FIXME - serialization
};


#endif //IOTA_CPP_DATA_H