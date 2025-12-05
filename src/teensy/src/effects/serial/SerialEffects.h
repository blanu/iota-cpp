//
// Created by Dr. Brandon Wiley on 10/27/25.
//

#ifndef IOTA_CPP_SERIALEFFECTS_H
#define IOTA_CPP_SERIALEFFECTS_H

enum class SerialPorts : int
{
  USB = 0,
  UART1 = 1,
  UART2 = 2,
  UART3 = 3,
  UART4 = 4,
  UART5 = 5,
  UART6 = 6,
  UART7 = 7,
  UART8 = 8,
  USBDual = 9,
  USBTriple = 10,
};

class SerialEffects
{
  public:
    static Storage get(const Storage& i);
    static Storage wait(const Storage& i);
    static Storage waitUntil(const Storage& i, const Storage& o);
    static Storage begin(const Storage& i, const Storage& o);
    static Storage read(const Storage& i);
    static Storage write(const Storage& i, const Storage& o);
    static Storage availableForRead(const Storage& i);
    static Storage availableForWrite(const Storage& i);
    static Storage flush(const Storage& i);
    static Storage readTimeout(const Storage& i, const Storage& o);

    static Storage print_character(const Storage& i, const Storage& o);
    static Storage println_character(const Storage& i, const Storage& o);
    static Storage print_integer(const Storage& i, const Storage& o);
    static Storage println_integer(const Storage& i, const Storage& o);
    static Storage print_real(const Storage& i, const Storage& o);
    static Storage println_real(const Storage& i, const Storage& o);
    static Storage print_string(const Storage& i, const Storage& o);
    static Storage println_string(const Storage& i, const Storage& o);

};


#endif //IOTA_CPP_SERIALEFFECTS_H