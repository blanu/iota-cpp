#ifndef _RELIABLE_CONNECTION_H_
#define _RELIABLE_CONNECTION_H_

#include <Arduino.h>

#include <types.h>
#include <Connection.h>

class ReliableConnection : public Connection
{
  public:
    ReliableConnection(SerialUSB serial) : serial(serial) {}
    ~ReliableConnection() {}

    char readOne() const;
    bytes read(int size) const;
    void write(bytes bs) const;

  private:
    SerialUSB serial;
};

#endif