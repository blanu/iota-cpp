//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef REAL_H
#define REAL_H

#include <vector>

#include "../Connection.h"

#include "../storage/storage.h"

class Real
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(float i);
    static Storage zero();
    static Storage one();

    static Storage enclose_impl(const Storage& i);
    static Storage floor_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage negate_impl(const Storage& i);
    static Storage not_impl(const Storage& i);
    static Storage reciprocal_impl(const Storage& i);
    static Storage size_impl(const Storage& i);

    // Dyads
    static Storage divide_integer(const Storage& i, const Storage& x);
    static Storage divide_real(const Storage& i, const Storage& x);
    static Storage divide_integers(const Storage& i, const Storage& x);
    static Storage divide_reals(const Storage& i, const Storage& x);
    static Storage divide_mixed(const Storage& i, const Storage& x);
    static Storage equal_impl(const Storage& i, const Storage& x);
    static Storage format2_impl(const Storage& i, const Storage& x);
    static Storage join_real(const Storage& i, const Storage& x);
    static Storage prepend_to_reals(const Storage& i, const Storage& x);
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
    static Storage times_integer(const Storage& i, const Storage& x);
    static Storage times_real(const Storage& i, const Storage& x);
    static Storage times_list(const Storage& i, const Storage& x);

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes &bs, int t);
    static void to_conn(const Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(const Connection& conn, int t);
};

#endif //REAL_H
