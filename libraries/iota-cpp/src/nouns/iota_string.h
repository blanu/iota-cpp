//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef STRING_H
#define STRING_H

#include <vector>

#include <storage/storage.h>

#include <Connection.h>

class IotaString
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(ints i);
    static Storage makeEmpty();

    // Monads
    static Storage atom_impl(const Storage& i);
    static Storage first_impl(const Storage& i);
    static Storage gradeDown_impl(const Storage& i);
    static Storage gradeUp_impl(const Storage& i);
    static Storage group_impl(const Storage& i);
    static Storage not_impl(const Storage& i);
    static Storage reverse_impl(const Storage& i);
    static Storage size_impl(const Storage& i);

    // Dyads
    static Storage equal_impl(const Storage& i, const Storage& x);

    static Storage find_character(const Storage& i, const Storage& x);
    static Storage find_string(const Storage& i, const Storage& x);

    static Storage form_integer(const Storage& i, const Storage& x);
    static Storage form_real(const Storage& i, const Storage& x);
    static Storage form_list(const Storage& i, const Storage& x);
    static Storage form_character(const Storage& i, const Storage& x);
    static Storage form_quoted_symbol(const Storage& i, const Storage& x);

    static Storage index_impl(const Storage& i, const Storage& x);

    // Join
    static Storage append_character(const Storage& i, const Storage& x);
    static Storage join_string(const Storage& i, const Storage& x);

    static Storage match_impl(const Storage& i, const Storage& x);
    static Storage rotate_integer(const Storage& i, const Storage& x);

    static Storage split_integer(const Storage& i, const Storage& x);
    static Storage split_integers(const Storage& i, const Storage& x);
    static Storage take_integer(const Storage& i, const Storage& x);

    // Monadic Adverbs
    static Storage each_impl(const Storage& i, const Storage& f);

    // Dyadic Adverbs

    // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes& bs, int t);
    static void to_conn(Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(Connection& conn, int t);
};

#endif //STRING_H
