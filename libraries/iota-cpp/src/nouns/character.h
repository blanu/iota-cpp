//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include <storage/storage.h>

#include <Connection.h>

class Character
{
public:
  // Initialize dispatch table
  static void initialize();

  static Storage make(int i);

  // Monads
  static Storage enclose_impl(const Storage& i);
  static Storage format_impl(const Storage& i);
  static Storage reverse_impl(const Storage& i);
  static Storage size_impl(const Storage& i);

  // Dyads
  static Storage equal_impl(const Storage& i, const Storage& x);

  // Join
  static Storage join_scalar(const Storage& i, const Storage& x);
  static Storage join_character(const Storage& i, const Storage& x);
  static Storage join_list(const Storage& i, const Storage& x);
  static Storage prepend_string(const Storage& i, const Storage& x);

  static Storage less_character(const Storage& i, const Storage& x);
  static Storage match_impl(const Storage& i, const Storage& x);
  static Storage more_character(const Storage& i, const Storage& x);

  // Serialization
  static maybe<bytes> to_bytes(const Storage& i);
  static maybe<Storage> from_bytes(const bytes& bs, int t);
  static void to_conn(Connection& conn, const Storage& i);
  static maybe<Storage> from_conn(Connection& conn, int t);
};

#endif //CHARACTER_H
