//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>

#include <storage/storage.h>

#include <Connection.h>

class Dictionary
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(const mixed &i);
    static Storage makeEmpty();

    // Monads

    // // Dyads
    // static Storage drop_impl(const Storage& i, const Storage& x);
    // static Storage equal_impl(const Storage& i, const Storage& x);
    static Storage find_impl(const Storage& i, const Storage& x);
    // static Storage join_impl(const Storage& i, const Storage& x);
    static Storage match_impl(const Storage& i, const Storage& x);

    // // Monadic Adverbs
    // static Storage each_impl(const Storage& i, const Storage& f);

    // // Dyadic Adverbs

    // // Serialization
    static maybe<bytes> to_bytes(const Storage& i);
    static maybe<Storage> from_bytes(const bytes& bs, int t);
    static void to_conn(Connection& conn, const Storage& i);
    static maybe<Storage> from_conn(Connection& conn, int t);
};

#endif //DICTIONARY_H
