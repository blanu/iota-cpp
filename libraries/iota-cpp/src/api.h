#ifndef API_H_
#define API_H_

#include "storage.h"
#include "types.h"

// const int i = SymbolType::i;
// const int x = SymbolType::x;
// const int y = SymbolType::y;
// const int z = SymbolType::z;
// const int f = SymbolType::f;
// const int undefined = SymbolType::undefined; // This is conflicting with Noun::undefined()

Storage e();
Storage c();

Storage test_error();
const char *error_to_string(const Storage &error);

maybe<Storage> eval(Storage x);

#endif