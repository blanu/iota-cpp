//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef SYMBOL_H
#define SYMBOL_H

#include <functional>
#include <vector>
#include <string>

#include "../storage/storage.h"

class Symbol
{
  public:
    static std::unordered_map<int, ints> integerToString;
    static std::unordered_map<ints, int, IntsHash> stringToInteger;
    static std::unordered_map<int, Storage> values;

    // Initialize dispatch table and symbol tables
    static void initialize();

    static Storage match_impl(const Storage& i, const Storage& x);

    static Storage evaluate_impl(const Storage& i);
    static Storage truth_impl(const Storage& i);

    static ints asciiToUTF32(const std::string& ascii);
};

#endif //SYMBOL_H
