//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "IotaMain.h"

int main()
{
  IotaMain iota_main = IotaMain();
  while(true)
  {
    iota_main.loop();
  }
}
