//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef LIST_H
#define LIST_H

#include "../storage/storage.h"

#include <Connection.h>

class List
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Monads
    static Storage atom_impl(const Storage& i);
    static Storage char_impl(const Storage& i);
    static Storage expand_impl(const Storage& i);
    static Storage first_impl(const Storage& i);
    static Storage floor_impl(const Storage& i);
    static Storage format_impl(const Storage& i);
    static Storage gradeDown_impl(const Storage& i);
    static Storage gradeUp_impl(const Storage& i);
    static Storage group_impl(const Storage& i);
    static Storage negate_impl(const Storage& i);
    static Storage not_impl(const Storage& i);
    static Storage reciprocal_impl(const Storage& i);
    static Storage reverse_impl(const Storage& i);
    static Storage shape_impl(const Storage& i);
    static Storage size_impl(const Storage& i);
    static Storage transpose_impl(const Storage& i);
    static Storage unique_impl(const Storage& i);

    // Dyads
    // static Storage amend_integers_integer(const Storage& i, const Storage& x);
    // static Storage amend_integers_mixed(const Storage& i, const Storage& x);
    // static Storage amend_floats_integer(const Storage& i, const Storage& x);
    // static Storage amend_floats_mixed(const Storage& i, const Storage& x);
    // static Storage amend_mixed_integer(const Storage& i, const Storage& x);
    // static Storage amend_mixed_mixed(const Storage& i, const Storage& x);

    static Storage cut_integer(const Storage& i, const Storage& x);
    static Storage cut_integers(const Storage& i, const Storage& x);

    static Storage divide_integer(const Storage& i, const Storage& x);
    static Storage divide_real(const Storage& i, const Storage& x);
    static Storage divide_integers(const Storage& i, const Storage& x);
    static Storage divide_reals(const Storage& i, const Storage& x);
    static Storage divide_mixed(const Storage& i, const Storage& x);

    static Storage drop_impl(const Storage& i, const Storage& x);
    static Storage equal_impl(const Storage& i, const Storage& x);

    static Storage find_integers_integer(const Storage& i, const Storage& x);
    static Storage find_integers_real(const Storage& i, const Storage& x);
    static Storage find_reals_integer(const Storage& i, const Storage& x);
    static Storage find_reals_real(const Storage& i, const Storage& x);
    static Storage find_mixed(const Storage& i, const Storage& x);

    static Storage format2_impl(const Storage& i, const Storage& x);
    static Storage index_impl(const Storage& i, const Storage& x);

    // Join
    static Storage append_integer(const Storage& i, const Storage& x);
    static Storage append_real(const Storage& i, const Storage& x);
    static Storage prepend_integer(const Storage& i, const Storage& x);
    static Storage prepend_real(const Storage& i, const Storage& x);
    static Storage join_integers(const Storage& i, const Storage& x);
    static Storage join_integers_reals(const Storage& i, const Storage& x);
    static Storage join_reals(const Storage& i, const Storage& x);
    static Storage join_reals_integers(const Storage& i, const Storage& x);
    static Storage join_mixed(const Storage& i, const Storage& x);

    static Storage less_integer(const Storage& i, const Storage& x);
    static Storage less_real(const Storage& i, const Storage& x);
    static Storage less_integers(const Storage& i, const Storage& x);
    static Storage less_reals(const Storage& i, const Storage& x);
    static Storage less_mixed(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage max_integer(const Storage& i, const Storage& x);
    static Storage max_real(const Storage& i, const Storage& x);
    static Storage max_integers(const Storage& i, const Storage& x);
    static Storage max_reals(const Storage& i, const Storage& x);
    static Storage max_mixed(const Storage& i, const Storage& x);
    static Storage min_integer(const Storage& i, const Storage& x);
    static Storage min_real(const Storage& i, const Storage& x);
    static Storage min_integers(const Storage& i, const Storage& x);
    static Storage min_reals(const Storage& i, const Storage& x);
    static Storage min_mixed(const Storage& i, const Storage& x);
    static Storage minus_integer(const Storage& i, const Storage& x);
    static Storage minus_real(const Storage& i, const Storage& x);
    static Storage minus_integers(const Storage& i, const Storage& x);
    static Storage minus_reals(const Storage& i, const Storage& x);
    static Storage minus_mixed(const Storage& i, const Storage& x);
    static Storage more_integer(const Storage& i, const Storage& x);
    static Storage more_real(const Storage& i, const Storage& x);
    static Storage more_integers(const Storage& i, const Storage& x);
    static Storage more_reals(const Storage& i, const Storage& x);
    static Storage more_mixed(const Storage& i, const Storage& x);
    static Storage plus_integer(const Storage& i, const Storage& x);
    static Storage plus_real(const Storage& i, const Storage& x);
    static Storage plus_integers(const Storage& i, const Storage& x);
    static Storage plus_reals(const Storage& i, const Storage& x);
    static Storage plus_mixed(const Storage& i, const Storage& x);
    static Storage power_integer(const Storage& i, const Storage& x);
    static Storage power_real(const Storage& i, const Storage& x);
    static Storage power_integers(const Storage& i, const Storage& x);
    static Storage power_reals(const Storage& i, const Storage& x);
    static Storage power_mixed(const Storage& i, const Storage& x);
    static Storage remainder_integer(const Storage& i, const Storage& x);
    static Storage remainder_integers(const Storage& i, const Storage& x);
    static Storage remainder_mixed(const Storage& i, const Storage& x);
    static Storage reshape_integer(const Storage& i, const Storage& x);
    static Storage reshape_integers(const Storage& i, const Storage& x);
    static Storage reshape_mixed(const Storage& i, const Storage& x);
    static Storage rotate_integer(const Storage& i, const Storage& x);
    static Storage split_integer(const Storage& i, const Storage& x);
    static Storage split_integers(const Storage& i, const Storage& x);
    static Storage take_integer(const Storage& i, const Storage& x);
    static Storage times_integer(const Storage& i, const Storage& x);
    static Storage times_real(const Storage& i, const Storage& x);
    static Storage times_integers(const Storage& i, const Storage& x);
    static Storage times_reals(const Storage& i, const Storage& x);
    static Storage times_mixed(const Storage& i, const Storage& x);

    // Monadic Adverbs
    static Storage each_integers(const Storage& i, const Storage& f);
    static Storage each_reals(const Storage& i, const Storage& f);
    static Storage each_mixed(const Storage& i, const Storage& f);
    static Storage eachPair_integers(const Storage& i, const Storage& f);
    static Storage eachPair_reals(const Storage& i, const Storage& f);
    static Storage eachPair_mixed(const Storage& i, const Storage& f);
    static Storage over_integers(const Storage& i, const Storage& f);
    static Storage over_reals(const Storage& i, const Storage& f);
    static Storage over_mixed(const Storage& i, const Storage& f);
    static Storage scanOver_integers(const Storage& i, const Storage& f);
    static Storage scanOver_reals(const Storage& i, const Storage& f);
    static Storage scanOver_mixed(const Storage& i, const Storage& f);

    // Dyadic Adverbs

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes &bs, int t);
    static void to_conn(Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(Connection& conn, int t);
};

#endif //LIST_H
