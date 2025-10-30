//
// Created by Dr. Brandon Wiley on 10/29/25.
//

#ifndef IOTA_CPP_I2CEFFECTS_H
#define IOTA_CPP_I2CEFFECTS_H

#include <storage/storage.h>

enum class I2CPorts : int
{
  I2C0 = 0,
  I2C1 = 1,
  I2C2 = 2
}

class I2CEffects
{
  static void initialize();
  static Storage get(const Storage& i);
  static Storage begin(const Storage& i);
  static Storage beginWithAddress(const Storage& i, const Storage& o);
  static Storage setClock(const Storage& i, const Storage& o);
  static Storage end(const Storage& i);
  static Storage beginTransmission(const Storage& i, const Storage& o);
  static Storage endTransmission(const Storage& i);
  static Storage endTransmissionSendStop(const Storage& i);
  static Storage writeByte(const Storage& i, const Storage& o);
  static Storage write(const Storage& i, const Storage& o);
  static Storage request(const Storage& i, const Storage& o);
  static Storage available(const Storage& i);
  static Storage read(const Storage& i);
  static Storage peek(const Storage& i);
  // FIXME onReceive and onRequest callbacks
  // Inherit Stream class functions
};

#endif //IOTA_CPP_I2CEFFECTS_H