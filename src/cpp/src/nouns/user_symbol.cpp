//
// Created by Dr. Brandon Wiley on 12/12/25.
//

#include "user_symbol.h"

#include "symbol.h"

void UserSymbol::initialize()
{

}

Storage UserSymbol::make(const std::string& s)
{
  Storage symbol = Symbol::make(s);
  symbol.o = NounType::USER_SYMBOL;

  return symbol;
}