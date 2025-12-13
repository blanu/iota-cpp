//
// Created by Dr. Brandon Wiley on 12/9/25.
//

#ifndef IOTA_CPP_RANGE_H
#define IOTA_CPP_RANGE_H

#include "types.h"
#include "storage/storage.h"
#include <BigNumber.h>

class Range
{
  public:
    static void initialize();

    static Storage make(const ints& i);
    static Storage make(int x, int y);
    static Storage make(int x, BigNumber y);
    static Storage make(BigNumber x, int y);
    static Storage make(const mixed& i);
    static Storage make(BigNumber x, BigNumber y);
    static Storage make(const Storage& x, const Storage& y);

    static ints toIntegers(const Storage& i);
    static std::tuple<int, int> toIntegerTuple(const Storage& i);
    static Storage toMixedArray(const Storage& i);
    static std::tuple<BigNumber, BigNumber> toBigNumberTuple(const Storage& i);

    static Storage each_impl(const Storage& i, const Storage& f);
    // static Storage over_impl(const Storage& i, const Storage& f);
    // static Storage overNeutral_impl(const Storage& i, const Storage& f);
    // static Storage scanOver_impl(const Storage& i, const Storage& f);
};

#endif //IOTA_CPP_RANGE_H