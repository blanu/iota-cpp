//
// Created by Dr. Brandon Wiley on 10/27/25.
//

#include "SerialEffects.h"

#include <Arduino.h>
#include <variant>
#include <string>

#include <storage/storage.h>
#include <storage/word_array.h>

#include "nouns/character.h"
#include "nouns/integer.h"
#include "nouns/error.h"

Storage SerialEffects::wait(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    switch(static_cast<SerialPorts>(port))
    {
      case SerialPorts::USB:
        while(!Serial)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART1:
        while(!Serial1)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART2:
        while(!Serial2)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART3:
        while(!Serial3)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART4:
        while(!Serial4)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART5:
        while(!Serial5)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART6:
        while(!Serial6)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART7:
        while(!Serial7)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::UART8:
        while(!Serial8)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::USBDual:
        while(!SerialUSB1)
        {
          delay(1);
        }

        return Integer::make(port); // FIXME - should be a SerialPort NounType

      case SerialPorts::USBTriple:
        while(!SerialUSB2)
        {
          delay(1);
        }

      default:
        return WordArray::nil();
    }
  }
}

Storage SerialEffects::waitUntil(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    if(std::holds_alternative<int>(o.i))
    {
      int timeout = std::get<int>(o.i);

      int now = millis();
      int start = now;
      int elapsed = now - start;

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          while(elapsed > timeout)
          {
            if(Serial)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART1:
          while(elapsed > timeout)
          {
            if(Serial1)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART2:
          while(elapsed > timeout)
          {
            if(Serial2)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART3:
          while(elapsed > timeout)
          {
            if(Serial3)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART4:
          while(elapsed > timeout)
          {
            if(Serial4)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART5:
          while(elapsed > timeout)
          {
            if(Serial5)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART6:
          while(elapsed > timeout)
          {
            if(Serial6)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART7:
          while(elapsed > timeout)
          {
            if(Serial7)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::UART8:
          while(elapsed > timeout)
          {
            if(Serial8)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::USBDual:
          while(elapsed > timeout)
          {
            if(SerialUSB1)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        case SerialPorts::USBTriple:
          while(elapsed > timeout)
          {
            if(SerialUSB2)
            {
              return Integer::make(port); // FIXME - should be a SerialPort NounType
            }

            now = millis();
            elapsed = now - start;
          }

          return WordArray::nil();

        default:
          return WordArray::nil();
      }
    }
  }
}

Storage SerialEffects::get(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i);

    if(ii >= 0 && ii <= 10)
    {
      return Integer::make(ii); // FIXME - should be custom SerialPort type
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::begin(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    if(std::holds_alternative<int>(o.i))
    {
      unsigned long baud = static_cast<unsigned long>(std::get<int>(o.i));

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.begin(baud);

          return i;

        case SerialPorts::UART1:
          Serial1.begin(baud);

          return i;

        case SerialPorts::UART2:
          Serial2.begin(baud);
          return i;

        case SerialPorts::UART3:
          Serial3.begin(baud);
          return i;

        case SerialPorts::UART4:
          Serial4.begin(baud);
          return i;

        case SerialPorts::UART5:
          Serial5.begin(baud);
          return i;

        case SerialPorts::UART6:
          Serial6.begin(baud);
          return i;

        case SerialPorts::UART7:
          Serial7.begin(baud);
          return i;

        case SerialPorts::UART8:
          Serial8.begin(baud);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.begin(baud);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.begin(baud);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::read(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    switch(static_cast<SerialPorts>(port))
    {
      case SerialPorts::USB:
        int result = Serial.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART1:
        int result = Serial1.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART2:
        int result = Serial2.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART3:
        int result = Serial3.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART4:
        int result = Serial4.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART5:
        int result = Serial5.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART6:
        int result = Serial6.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART7:
        int result = Serial7.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::UART8:
        int result = Serial8.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::USBDual:
        int result = SerialUSB1.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      case SerialPorts::USBTriple:
        int result = SerialUSB2.read();
        if(result == -1)
        {
          return WordArray::nil();
        }

        return Character::make(result);

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::write(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o);
      uint8_t b = static_cast<uint8_t>(oi);

    switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.write(b);

          return i;

        case SerialPorts::UART1:
          Serial1.write(b);

          return i;

        case SerialPorts::UART2:
          Serial2.write(b);

          return i;

        case SerialPorts::UART3:
          Serial3.write(b);

          return i;

        case SerialPorts::UART4:
          Serial4.write(b);

          return i;

        case SerialPorts::UART5:
          Serial5.write(b);

          return i;

        case SerialPorts::UART6:
          Serial6.write(b);

          return i;

        case SerialPorts::UART7:
          Serial7.write(b);

          return i;

        case SerialPorts::UART8:
          Serial8.write(b);

          return i;

        case SerialPorts::USBDual:
          Serial9.write(b);

          return i;

        case SerialPorts::USBTriple:
          Serial10.write(b);

          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::availableForRead(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    switch(static_cast<SerialPorts>(port))
    {
      case SerialPorts::USB:
        int result = Serial.available();
        return Integer::make(result);

      case SerialPorts::UART1:
        int result = Serial1.available();
        return Integer::make(result);

      case SerialPorts::UART2:
        int result = Serial2.available();
        return Integer::make(result);

      case SerialPorts::UART3:
        int result = Serial3.available();
        return Integer::make(result);

      case SerialPorts::UART4:
        int result = Serial4.available();
        return Integer::make(result);

      case SerialPorts::UART5:
        int result = Serial5.available();
        return Integer::make(result);

      case SerialPorts::UART6:
        int result = Serial6.available();
        return Integer::make(result);

      case SerialPorts::UART7:
        int result = Serial7.available();
        return Integer::make(result);

      case SerialPorts::UART8:
        int result = Serial8.available();
        return Integer::make(result);

      case SerialPorts::USBDual:
        int result = SerialUSB1.available();
        return Integer::make(result);

      case SerialPorts::USBTriple:
        int result = SerialUSB2.available();
        return Integer::make(result);

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::availableForWrite(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    switch(static_cast<SerialPorts>(port))
    {
      case SerialPorts::USB:
        int result = Serial.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART1:
        int result = Serial1.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART2:
        int result = Serial2.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART3:
        int result = Serial3.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART4:
        int result = Serial4.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART5:
        int result = Serial5.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART6:
        int result = Serial6.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART7:
        int result = Serial7.availableForWrite();
        return Integer::make(result);

      case SerialPorts::UART8:
        int result = Serial8.availableForWrite();
        return Integer::make(result);

      case SerialPorts::USBDual:
        int result = SerialUSB1.availableForWrite();
        return Integer::make(result);

      case SerialPorts::USBTriple:
        int result = SerialUSB2.availableForWrite();
        return Integer::make(result);

      default:
        return WordArray::nil();
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::write(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    if(std::holds_alternative<int>(o.i))
    {
      int oi = std::get<int>(o);
      uint8_t b = static_cast<uint8_t>(oi);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.write(b);

          return i;

        case SerialPorts::UART1:
          Serial1.write(b);

          return i;

        case SerialPorts::UART2:
          Serial2.write(b);

          return i;

        case SerialPorts::UART3:
          Serial3.write(b);

          return i;

        case SerialPorts::UART4:
          Serial4.write(b);

          return i;

        case SerialPorts::UART5:
          Serial5.write(b);

          return i;

        case SerialPorts::UART6:
          Serial6.write(b);

          return i;

        case SerialPorts::UART7:
          Serial7.write(b);

          return i;

        case SerialPorts::UART8:
          Serial8.write(b);

          return i;

        case SerialPorts::USBDual:
          Serial9.write(b);

          return i;

        case SerialPorts::USBTriple:
          Serial10.write(b);

          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::print_character(const Storage& i, const Storage& o)Storage SerialEffects::print_character(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    if(std::holds_alternative<int>(o.i)) // Single-argument print, works with both C-char characters and Unicode characters
    {
      maybe<char> maybeChar = Character::to_char(o);
      if(maybeChar)
      {
        char c = *maybeChar;
        switch(static_cast<SerialPorts>(port))
        {
          case SerialPorts::USB:
            Serial.print(c);

            return i;

          case SerialPorts::UART1:
            Serial2.print(c);

            return i;

          case SerialPorts::UART2:
            Serial3.print(c);

            return i;

          case SerialPorts::UART3:
            Serial3.print(c);

            return i;

          case SerialPorts::UART4:
            Serial4.print(c);

            return i;

          case SerialPorts::UART5:
            Serial5.print(c);

            return i;

          case SerialPorts::UART6:
            Serial6.print(c);

            return i;

          case SerialPorts::UART7:
            Serial7.print(c);

            return i;

          case SerialPorts::UART8:
            Serial8.print(c);

            return i;

          case SerialPorts::USBDual:
            Serial9.print(c);

            return i;

          case SerialPorts::USBTriple:
            Serial10.print(c);

            return i;

          default:
            return WordArray::nil();
        }
      }
      else
      {
        maybe<std::string> maybeString = Character::to_string(o);
        if(maybeString)
        {
          std::string s = *maybeString;

          switch(static_cast<SerialPorts>(port))
          {
            case SerialPorts::USB:
              for(uint8_t b : s)
              {
                Serial.print(b);
              }

              return i;

            case SerialPorts::UART1:
              for(uint8_t b : s)
              {
                Serial1.print(b);
              }

              return i;

            case SerialPorts::UART2:
              for(uint8_t b : s)
              {
                Serial2.print(b);
              }

              return i;

            case SerialPorts::UART3:
              for(uint8_t b : s)
              {
                Serial3.print(b);
              }

              return i;

            case SerialPorts::UART4:
              for(uint8_t b : s)
              {
                Serial4.print(b);
              }

              return i;

            case SerialPorts::UART5:
              for(uint8_t b : s)
              {
                Serial5.print(b);
              }

              return i;

            case SerialPorts::UART6:
              for(uint8_t b : s)
              {
                Serial6.print(b);
              }

              return i;

            case SerialPorts::UART7:
              for(uint8_t b : s)
              {
                Serial7.print(b);
              }

              return i;

            case SerialPorts::UART8:
              for(uint8_t b : s)
              {
                Serial8.print(b);
              }

              return i;

            case SerialPorts::USBDual:
              for(uint8_t b : s)
              {
                Serial9.print(b);
              }

              return i;

            case SerialPorts::USBTriple:
              for(uint8_t b : s)
              {
                Serial10.print(b);
              }

              return i;

            default:
              return WordArray::nil();
          }
        }
      }
    }
    else if(std::holds_alternative<mixed>(o.i)) // Two-argument print, second argument is format. Works only with C-char characters.
    {
      mixed mos = std::get<ints>(o.i);

      if(mos.size() == 2)
      {
        Storage valueS = mos[0];
        Storage formatS = mos[1];

        if(std::holds_alternative<int>(value.i))
        {
          maybe<char> maybeChar = Character::to_char(value.i);
          if(maybeChar)
          {
            char value = *maybeChar;

            if(std::holds_alternative<int>(formatS.i))
            {
              int format = std::get<int>(formatS.i);

              switch(static_cast<SerialPorts>(port))
              {
                case SerialPorts::USB:
                  Serial.print(value, format);

                  return i;

                case SerialPorts::UART1:
                  Serial1.print(value, format);

                  return i;

                case SerialPorts::UART2:
                  Serial2.print(value, format);

                  return i;

                case SerialPorts::UART3:
                  Serial3.print(value, format);

                  return i;

                case SerialPorts::UART4:
                  Serial4.print(value, format);

                  return i;

                case SerialPorts::UART5:
                  Serial5.print(value, format);

                  return i;

                case SerialPorts::UART6:
                  Serial6.print(value, format);

                  return i;

                case SerialPorts::UART7:
                  Serial7.print(value, format);

                  return i;

                case SerialPorts::UART8:
                  Serial8.print(value, format);

                  return i;

                case SerialPorts::USBDual:
                  Serial9.print(value, format);

                  return i;

                case SerialPorts::USBTriple:
                  Serial10.print(value, format);

                  return i;

                default:
                  return WordArray::nil();
              }
            }
          }
        }
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::println_character(const Storage& i, const Storage& o)Storage SerialEffects::print_character(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i);

    if(std::holds_alternative<int>(o.i)) // Single-argument println, works with both C-char characters and Unicode characters
    {
      maybe<char> maybeChar = Character::to_char(o);
      if(maybeChar)
      {
        char c = *maybeChar;
        switch(static_cast<SerialPorts>(port))
        {
          case SerialPorts::USB:
            Serial.println(c);

            return i;

          case SerialPorts::UART1:
            Serial2.println(c);

            return i;

          case SerialPorts::UART2:
            Serial3.println(c);

            return i;

          case SerialPorts::UART3:
            Serial3.println(c);

            return i;

          case SerialPorts::UART4:
            Serial4.println(c);

            return i;

          case SerialPorts::UART5:
            Serial5.println(c);

            return i;

          case SerialPorts::UART6:
            Serial6.println(c);

            return i;

          case SerialPorts::UART7:
            Serial7.println(c);

            return i;

          case SerialPorts::UART8:
            Serial8.println(c);

            return i;

          case SerialPorts::USBDual:
            Serial9.println(c);

            return i;

          case SerialPorts::USBTriple:
            Serial10.println(c);

            return i;

          default:
            return WordArray::nil();
        }
      }
      else
      {
        maybe<std::string> maybeString = Character::to_string(o);
        if(maybeString)
        {
          std::string s = *maybeString;

          switch(static_cast<SerialPorts>(port))
          {
            case SerialPorts::USB:
              for(uint8_t b : s)
              {
                Serial.println(b);
              }

              return i;

            case SerialPorts::UART1:
              for(uint8_t b : s)
              {
                Serial1.println(b);
              }

              return i;

            case SerialPorts::UART2:
              for(uint8_t b : s)
              {
                Serial2.println(b);
              }

              return i;

            case SerialPorts::UART3:
              for(uint8_t b : s)
              {
                Serial3.println(b);
              }

              return i;

            case SerialPorts::UART4:
              for(uint8_t b : s)
              {
                Serial4.println(b);
              }

              return i;

            case SerialPorts::UART5:
              for(uint8_t b : s)
              {
                Serial5.println(b);
              }

              return i;

            case SerialPorts::UART6:
              for(uint8_t b : s)
              {
                Serial6.println(b);
              }

              return i;

            case SerialPorts::UART7:
              for(uint8_t b : s)
              {
                Serial7.println(b);
              }

              return i;

            case SerialPorts::UART8:
              for(uint8_t b : s)
              {
                Serial8.println(b);
              }

              return i;

            case SerialPorts::USBDual:
              for(uint8_t b : s)
              {
                Serial9.println(b);
              }

              return i;

            case SerialPorts::USBTriple:
              for(uint8_t b : s)
              {
                Serial10.println(b);
              }

              return i;

            default:
              return WordArray::nil();
          }
        }
      }
    }
    else if(std::holds_alternative<mixed>(o.i)) // Two-argument println, second argument is format. Works only with C-char characters.
    {
      mixed mos = std::get<ints>(o.i);

      if(mos.size() == 2)
      {
        Storage valueS = mos[0];
        Storage formatS = mos[1];

        if(std::holds_alternative<int>(value.i))
        {
          maybe<char> maybeChar = Character::to_char(value.i);
          if(maybeChar)
          {
            char value = *maybeChar;

            if(std::holds_alternative<int>(formatS.i))
            {
              int format = std::get<int>(formatS.i);

              switch(static_cast<SerialPorts>(port))
              {
                case SerialPorts::USB:
                  Serial.println(value, format);

                  return i;

                case SerialPorts::UART1:
                  Serial1.println(value, format);

                  return i;

                case SerialPorts::UART2:
                  Serial2.println(value, format);

                  return i;

                case SerialPorts::UART3:
                  Serial3.println(value, format);

                  return i;

                case SerialPorts::UART4:
                  Serial4.println(value, format);

                  return i;

                case SerialPorts::UART5:
                  Serial5.println(value, format);

                  return i;

                case SerialPorts::UART6:
                  Serial6.println(value, format);

                  return i;

                case SerialPorts::UART7:
                  Serial7.println(value, format);

                  return i;

                case SerialPorts::UART8:
                  Serial8.println(value, format);

                  return i;

                case SerialPorts::USBDual:
                  Serial9.println(value, format);

                  return i;

                case SerialPorts::USBTriple:
                  Serial10.println(value, format);

                  return i;

                default:
                  return WordArray::nil();
              }
            }
          }
        }
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::print_integer(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i)) // Single Word integer
    {
      int integer = std::get<int>(o.i);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.print(integer);
          return i;

        case SerialPorts::UART1:
          Serial1.print(integer);
          return i;

        case SerialPorts::UART2:
          Serial2.print(integer);
          return i;

        case SerialPorts::UART3:
          Serial3.print(integer);
          return i;

        case SerialPorts::UART4:
          Serial4.print(integer);
          return i;

        case SerialPorts::UART5:
          Serial5.print(integer);
          return i;

        case SerialPorts::UART6:
          Serial6.print(integer);
          return i;

        case SerialPorts::UART7:
          Serial7.print(integer);
          return i;

        case SerialPorts::UART8:
          Serial8.print(integer);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.print(integer);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.print(integer);
          return i;

        default:
          return WordArray::nil();
      }
    }
    else if(std::holds_alternative<ints>(o.i)) // WordArray bigint
    {
      const ints& bigint = std::get<ints>(o.i);

      if(bigint.empty())
      {
        return WordArray::nil();
      }

      // Convert WordArray to BigNumber
      BigNumber::begin();

      // First element is sign bit
      bool negative = (bigint[0] == 1);

      // Calculate BASE = 2^(sizeof(int)*8)
      BigNumber base = BigNumber(2);
      for(size_t bit = 1; bit < sizeof(int) * 8; bit++)
      {
        base = base * BigNumber(2);
      }

      // Reconstruct number from chunks in big-endian order
      BigNumber result = BigNumber(0);
      typedef unsigned int uint_t;

      for(size_t idx = 1; idx < bigint.size(); idx++)
      {
        uint_t chunk = static_cast<uint_t>(bigint[idx]);

        // Convert chunk to string for BigNumber constructor
        char chunk_str[32];
        snprintf(chunk_str, sizeof(chunk_str), "%u", chunk);
        BigNumber chunk_bn = BigNumber(chunk_str);

        result = result * base + chunk_bn;
      }

      if(negative)
      {
        result = result * BigNumber(-1);
      }

      // Wrap in PrintableBigNumber for printing
      PrintableBigNumber printable(result);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.print(printable);
          return i;

        case SerialPorts::UART1:
          Serial1.print(printable);
          return i;

        case SerialPorts::UART2:
          Serial2.print(printable);
          return i;

        case SerialPorts::UART3:
          Serial3.print(printable);
          return i;

        case SerialPorts::UART4:
          Serial4.print(printable);
          return i;

        case SerialPorts::UART5:
          Serial5.print(printable);
          return i;

        case SerialPorts::UART6:
          Serial6.print(printable);
          return i;

        case SerialPorts::UART7:
          Serial7.print(printable);
          return i;

        case SerialPorts::UART8:
          Serial8.print(printable);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.print(printable);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.print(printable);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::println_integer(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i.i);

    if(std::holds_alternative<int>(o.i)) // Single Word integer
    {
      int integer = std::get<int>(o.i);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.println(integer);
          return i;

        case SerialPorts::UART1:
          Serial1.println(integer);
          return i;

        case SerialPorts::UART2:
          Serial2.println(integer);
          return i;

        case SerialPorts::UART3:
          Serial3.println(integer);
          return i;

        case SerialPorts::UART4:
          Serial4.println(integer);
          return i;

        case SerialPorts::UART5:
          Serial5.println(integer);
          return i;

        case SerialPorts::UART6:
          Serial6.println(integer);
          return i;

        case SerialPorts::UART7:
          Serial7.println(integer);
          return i;

        case SerialPorts::UART8:
          Serial8.println(integer);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.println(integer);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.println(integer);
          return i;

        default:
          return WordArray::nil();
      }
    }
    else if(std::holds_alternative<ints>(o.i)) // WordArray bigint
    {
      const ints& bigint = std::get<ints>(o.i);

      if(bigint.empty())
      {
        return WordArray::nil();
      }

      // Convert WordArray to BigNumber
      BigNumber::begin();

      // First element is sign bit
      bool negative = (bigint[0] == 1);

      // Calculate BASE = 2^(sizeof(int)*8)
      BigNumber base = BigNumber(2);
      for(size_t bit = 1; bit < sizeof(int) * 8; bit++)
      {
        base = base * BigNumber(2);
      }

      // Reconstruct number from chunks in big-endian order
      BigNumber result = BigNumber(0);
      typedef unsigned int uint_t;

      for(size_t idx = 1; idx < bigint.size(); idx++)
      {
        uint_t chunk = static_cast<uint_t>(bigint[idx]);

        // Convert chunk to string for BigNumber constructor
        char chunk_str[32];
        snprintf(chunk_str, sizeof(chunk_str), "%u", chunk);
        BigNumber chunk_bn = BigNumber(chunk_str);

        result = result * base + chunk_bn;
      }

      if(negative)
      {
        result = result * BigNumber(-1);
      }

      // Wrap in PrintableBigNumber for printing
      PrintableBigNumber printable(result);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.println(printable);
          return i;

        case SerialPorts::UART1:
          Serial1.println(printable);
          return i;

        case SerialPorts::UART2:
          Serial2.println(printable);
          return i;

        case SerialPorts::UART3:
          Serial3.println(printable);
          return i;

        case SerialPorts::UART4:
          Serial4.println(printable);
          return i;

        case SerialPorts::UART5:
          Serial5.println(printable);
          return i;

        case SerialPorts::UART6:
          Serial6.println(printable);
          return i;

        case SerialPorts::UART7:
          Serial7.println(printable);
          return i;

        case SerialPorts::UART8:
          Serial8.println(printable);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.println(printable);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.println(printable);
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::print_real(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i.i);

    if(std::holds_alternative<float>(o.i)) // Single float
    {
      float value = std::get<float>(o.i);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.print(value);
          return i;

        case SerialPorts::UART1:
          Serial1.print(value);
          return i;

        case SerialPorts::UART2:
          Serial2.print(value);
          return i;

        case SerialPorts::UART3:
          Serial3.print(value);
          return i;

        case SerialPorts::UART4:
          Serial4.print(value);
          return i;

        case SerialPorts::UART5:
          Serial5.print(value);
          return i;

        case SerialPorts::UART6:
          Serial6.print(value);
          return i;

        case SerialPorts::UART7:
          Serial7.print(value);
          return i;

        case SerialPorts::UART8:
          Serial8.print(value);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.print(value);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.print(value);
          return i;

        default:
          return WordArray::nil();
      }
    }
    else if(std::holds_alternative<mixed>(o.i)) // Two-argument print with decimal places
    {
      mixed mos = std::get<mixed>(o.i);

      if(mos.size() == 2)
      {
        Storage valueS = mos[0];
        Storage digitsS = mos[1];

        if(std::holds_alternative<float>(valueS.i) && std::holds_alternative<int>(digitsS.i))
        {
          float value = std::get<float>(valueS.i);
          int digits = std::get<int>(digitsS.i);

          switch(static_cast<SerialPorts>(port))
          {
            case SerialPorts::USB:
              Serial.print(value, digits);
              return i;

            case SerialPorts::UART1:
              Serial1.print(value, digits);
              return i;

            case SerialPorts::UART2:
              Serial2.print(value, digits);
              return i;

            case SerialPorts::UART3:
              Serial3.print(value, digits);
              return i;

            case SerialPorts::UART4:
              Serial4.print(value, digits);
              return i;

            case SerialPorts::UART5:
              Serial5.print(value, digits);
              return i;

            case SerialPorts::UART6:
              Serial6.print(value, digits);
              return i;

            case SerialPorts::UART7:
              Serial7.print(value, digits);
              return i;

            case SerialPorts::UART8:
              Serial8.print(value, digits);
              return i;

            case SerialPorts::USBDual:
              SerialUSB1.print(value, digits);
              return i;

            case SerialPorts::USBTriple:
              SerialUSB2.print(value, digits);
              return i;

            default:
              return WordArray::nil();
          }
        }
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::println_real(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i.i);

    if(std::holds_alternative<float>(o.i)) // Single float
    {
      float value = std::get<float>(o.i);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          Serial.println(value);
          return i;

        case SerialPorts::UART1:
          Serial1.println(value);
          return i;

        case SerialPorts::UART2:
          Serial2.println(value);
          return i;

        case SerialPorts::UART3:
          Serial3.println(value);
          return i;

        case SerialPorts::UART4:
          Serial4.println(value);
          return i;

        case SerialPorts::UART5:
          Serial5.println(value);
          return i;

        case SerialPorts::UART6:
          Serial6.println(value);
          return i;

        case SerialPorts::UART7:
          Serial7.println(value);
          return i;

        case SerialPorts::UART8:
          Serial8.println(value);
          return i;

        case SerialPorts::USBDual:
          SerialUSB1.println(value);
          return i;

        case SerialPorts::USBTriple:
          SerialUSB2.println(value);
          return i;

        default:
          return WordArray::nil();
      }
    }
    else if(std::holds_alternative<mixed>(o.i)) // Two-argument print with decimal places
    {
      mixed mos = std::get<mixed>(o.i);

      if(mos.size() == 2)
      {
        Storage valueS = mos[0];
        Storage digitsS = mos[1];

        if(std::holds_alternative<float>(valueS.i) && std::holds_alternative<int>(digitsS.i))
        {
          float value = std::get<float>(valueS.i);
          int digits = std::get<int>(digitsS.i);

          switch(static_cast<SerialPorts>(port))
          {
            case SerialPorts::USB:
              Serial.println(value, digits);
              return i;

            case SerialPorts::UART1:
              Serial1.println(value, digits);
              return i;

            case SerialPorts::UART2:
              Serial2.println(value, digits);
              return i;

            case SerialPorts::UART3:
              Serial3.println(value, digits);
              return i;

            case SerialPorts::UART4:
              Serial4.println(value, digits);
              return i;

            case SerialPorts::UART5:
              Serial5.println(value, digits);
              return i;

            case SerialPorts::UART6:
              Serial6.println(value, digits);
              return i;

            case SerialPorts::UART7:
              Serial7.println(value, digits);
              return i;

            case SerialPorts::UART8:
              Serial8.println(value, digits);
              return i;

            case SerialPorts::USBDual:
              SerialUSB1.println(value, digits);
              return i;

            case SerialPorts::USBTriple:
              SerialUSB2.println(value, digits);
              return i;

            default:
              return WordArray::nil();
          }
        }
      }
    }
  }

  return WordArray::nil();
}

Storage SerialEffects::print_string(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i.i);

    if(std::holds_alternative<ints>(o.i))
    {
      std::string s = IotaString::toString(o);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          for(char c : s)
          {
            Serial.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART1:
          for(char c : s)
          {
            Serial1.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART2:
          for(char c : s)
          {
            Serial2.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART3:
          for(char c : s)
          {
            Serial3.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART4:
          for(char c : s)
          {
            Serial4.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART5:
          for(char c : s)
          {
            Serial5.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART6:
          for(char c : s)
          {
            Serial6.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART7:
          for(char c : s)
          {
            Serial7.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART8:
          for(char c : s)
          {
            Serial8.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::USBDual:
          for(char c : s)
          {
            SerialUSB1.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::USBTriple:
          for(char c : s)
          {
            SerialUSB2.write(static_cast<uint8_t>(c));
          }
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}}

Storage SerialEffects::println_string(const Storage& i, const Storage& o)
{
  if(std::holds_alternative<int>(i.i))
  {
    int port = std::get<int>(i.i);

    if(std::holds_alternative<ints>(o.i))
    {
      std::string s = IotaString::toString(o);

      switch(static_cast<SerialPorts>(port))
      {
        case SerialPorts::USB:
          for(char c : s)
          {
            Serial.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART1:
          for(char c : s)
          {
            Serial1.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART2:
          for(char c : s)
          {
            Serial2.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART3:
          for(char c : s)
          {
            Serial3.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART4:
          for(char c : s)
          {
            Serial4.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART5:
          for(char c : s)
          {
            Serial5.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART6:
          for(char c : s)
          {
            Serial6.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART7:
          for(char c : s)
          {
            Serial7.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::UART8:
          for(char c : s)
          {
            Serial8.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::USBDual:
          for(char c : s)
          {
            SerialUSB1.write(static_cast<uint8_t>(c));
          }
          return i;

        case SerialPorts::USBTriple:
          for(char c : s)
          {
            SerialUSB2.write(static_cast<uint8_t>(c));
          }
          return i;

        default:
          return WordArray::nil();
      }
    }
  }

  return WordArray::nil();
}}