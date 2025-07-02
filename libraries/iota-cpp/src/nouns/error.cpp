//
// Created by Dr. Brandon Wiley on 5/27/25.
//

#include "error.h"

#include "../storage/storage.h"
#include "../storage/word.h"

Storage Error::make(int i)
{
  return Word::make(i, NounType::ERROR);
}
