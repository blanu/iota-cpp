//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef INTEGER_H
#define INTEGER_H

#include <storage/storage.h>

#include <Connection.h>
#include <BigNumber.h>

class Integer
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(int i);
    static Storage make(uint64_t i);
    static Storage make(unsigned long i);
    static Storage makeHex(std::string i);
    static Storage makeDecimal(std::string i);
    static Storage make(const BigNumber& bn);

    static uint64_t* toUInt64(const Storage& i);
    static unsigned long* toUnsignedLong(const Storage& i);
    static std::string toHexString(const Storage &i);
    static std::string toDecimalString(const Storage &i);
    static BigNumber toBigNumber(const Storage &i);
    static int toInt(const Storage& i);

    static Storage zero();
    static Storage one();

    // Monads
    static Storage char_impl(const Storage& i);
    static Storage enclose_impl(const Storage& i);
    static Storage enumerate_impl(const Storage& i);
    static Storage expand_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage negate_impl(const Storage& i);
    static Storage not_impl(const Storage& i);
    static Storage reciprocal_impl(const Storage& i);
    static Storage size_impl(const Storage& i);

    // Dyads
    static Storage cut_integers(const Storage& i, const Storage& x);
    static Storage cut_reals(const Storage& i, const Storage& x);
    static Storage cut_mixed(const Storage& i, const Storage& x);
    static Storage divide_integer(const Storage& i, const Storage& x);
    static Storage divide_real(const Storage& i, const Storage& x);
    static Storage divide_integers(const Storage& i, const Storage& x);
    static Storage divide_reals(const Storage& i, const Storage& x);
    static Storage divide_mixed(const Storage& i, const Storage& x);
    static Storage equal_impl(const Storage& i, const Storage& x);
    static Storage format2_impl(const Storage& i, const Storage& x);
    static Storage integerDivide_impl(const Storage& i, const Storage& x);
    static Storage join_integer(const Storage& i, const Storage& x);
    static Storage prepend_to_integers(const Storage& i, const Storage& x);
    static Storage less_integer(const Storage& i, const Storage& x);
    static Storage less_real(const Storage& i, const Storage& x);
    static Storage less_list(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage max_integer(const Storage& i, const Storage& x);
    static Storage max_real(const Storage& i, const Storage& x);
    static Storage max_list(const Storage& i, const Storage& x);
    static Storage min_integer(const Storage& i, const Storage& x);
    static Storage min_real(const Storage& i, const Storage& x);
    static Storage min_list(const Storage& i, const Storage& x);
    static Storage minus_integer(const Storage& i, const Storage& x);
    static Storage minus_real(const Storage& i, const Storage& x);
    static Storage minus_list(const Storage& i, const Storage& x);
    static Storage more_integer(const Storage& i, const Storage& x);
    static Storage more_real(const Storage& i, const Storage& x);
    static Storage more_list(const Storage& i, const Storage& x);
    static Storage plus_integer(const Storage& i, const Storage& x);
    static Storage plus_real(const Storage& i, const Storage& x);
    static Storage plus_list(const Storage& i, const Storage& x);
    static Storage power_integer(const Storage& i, const Storage& x);
    static Storage power_real(const Storage& i, const Storage& x);
    static Storage power_list(const Storage& i, const Storage& x);
    static Storage remainder_integer(const Storage& i, const Storage& x);
    static Storage remainder_integers(const Storage& i, const Storage& x);
    static Storage remainder_mixed(const Storage& i, const Storage& x);
    static Storage reshape_integer(const Storage& i, const Storage& x);
    static Storage reshape_integers(const Storage& i, const Storage& x);
    static Storage reshape_mixed(const Storage& i, const Storage& x);
    static Storage times_integer(const Storage& i, const Storage& x);
    static Storage times_real(const Storage& i, const Storage& x);
    static Storage times_list(const Storage& i, const Storage& x);

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes& bs, int t);
    static void to_conn(Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(Connection& conn, int t);
};

#endif //INTEGER_H
