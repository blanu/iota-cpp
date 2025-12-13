//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <string>
#include <unordered_map>

#include <types.h>

#include <storage/storage.h>

// Simple case: field name matches symbol name
#define INTERN(name) name = Symbol::make(#name)

// Complex case: field name differs from symbol string
#define INTERN_AS(symbolName, field) field = Symbol::make(#symbolName)

// Simple case: field name matches symbol name
#define INTERN_INT(name) name = Symbol::toInteger(Symbol::make(#name))

// Complex case: field name differs from symbol string
#define INTERN_INT_AS(symbolName, field) field = Symbol::toInteger(Symbol::make(#symbolName))

#define INTERN_VERB(space, type, name) space::name = type::make(Symbol::toInteger(Symbol::make(#name)))
#define INTERN_EFFECT(space, type, name) space::name = type##icEffect::make(Symbol::toInteger(Symbol::make(#name)))

class Symbol
{
  public:
    static std::unordered_map<int, ints> integerToString;
    static std::unordered_map<ints, int> stringToInteger;
    static std::unordered_map<int, Storage> values;

    // Initialize dispatch table and symbol tables
    static void initialize();

    static Storage make(int i);
    static Storage make(std::string s);
    static Storage make(const Storage& i);

    static int toInteger(const Storage& s);
    static std::string toString(const Storage& s);

    static Storage symbols_impl();
    static Storage evaluate_impl(const Storage& i);
    static Storage truth_impl(const Storage& i);
};

#endif //SYMBOL_H
