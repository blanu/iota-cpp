//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef IOSTREAMCONNECTION_H
#define IOSTREAMCONNECTION_H

#include <types.h>
#include <Connection.h>

class IostreamConnection : public Connection
{
  public:
    IostreamConnection() {}
    ~IostreamConnection() {}

    char readOne() const;
    bytes read(int size) const;
    void write(bytes bs) const;
};

#endif //IOSTREAMCONNECTION_H
