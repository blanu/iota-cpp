//
// Created by Dr. Brandon Wiley on 12/12/25.
//

#include "symbol_definition.h"

#include "api.h"
#include "iota_string.h"
#include "symbol.h"
#include "iota_string.h"

void SymbolDefinition::initialize()
{

}

Storage SymbolDefinition::make(const std::string& s)
{
  Storage symbol = IotaString::makeString(s);
  symbol.o = NounType::SYMBOL_DEFINITION;

  return symbol;
}

std::string SymbolDefinition::toString(const Storage& i)
{
  Storage result = IotaString::makeEmpty();
  result.i = i.i;

  return IotaString::toString(result);
}