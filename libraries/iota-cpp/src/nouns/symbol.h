//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <string>
#include <unordered_map>

#include "../types.h"

#include "../storage/storage.h"

class Symbol
{
  public:
    static std::unordered_map<int, ints> integerToString;
    static std::unordered_map<ints, int> stringToInteger;
    static std::unordered_map<int, Storage> values;

    // Initialize dispatch table and symbol tables
    static void initialize();

    static Storage evaluate_impl(const Storage& i);
    static Storage truth_impl(const Storage& i);

    static ints asciiToUTF32(const std::string& ascii);
};

#endif //SYMBOL_H
