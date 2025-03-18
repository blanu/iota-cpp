//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "IostreamConnection.h"

#include <iostream>

char IostreamConnection::readOne() const
{
  char result;
  std::cin.get(result);
  if(std::cin)
  {
    return result;
  }
  else
  {
    return 0;
  }
}

bytes IostreamConnection::read(int size) const
{
  bytes r = bytes();

  while(r.size() < size)
  {
    char b = readOne();
    r.push_back(b);
  }

  return r;
}

void IostreamConnection::write(bytes bs) const
{
  for (char b : bs)
  {
    std::cout.put(b);
  }
}
