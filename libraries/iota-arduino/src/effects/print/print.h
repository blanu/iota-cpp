//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef PRINT_H
#define PRINT_H

#include <types.h>

#include <storage/storage.h>

class PrintEffect
{
  public:
    PrintEffect(Storage message, maybe<Storage>completionHandler = nullptr) : message(message), completionHandler(completionHandler) {};

  private:
    Storage message;
    maybe<Storage> completionHandler;
};

#endif //PRINT_H
