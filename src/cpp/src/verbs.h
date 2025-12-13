//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef VERBS_H
#define VERBS_H

#include <storage/storage.h>
#include <storage/word_array.h>

int getInteger(const Storage& i);

class Nilad
{
  public:
    static Storage make(int i);
    static void print(const Storage &);

    static void initialize();
};

class Monad
{
  public:
    static Storage make(int i);

    static void initialize();
};

class Dyad
{
  public:
    static Storage make(int i);
    static void print(const Storage &);

    static void initialize();
};

class Triad
{
  public:
    static Storage make(int i);
    static void print(const Storage &);

    static void initialize();
};

// Monads
namespace iota
{
  inline Storage atom = WordArray::nil();
  inline Storage ichar = WordArray::nil();
  inline Storage enclose = WordArray::nil();
  inline Storage enumerate = WordArray::nil();
  inline Storage expand = WordArray::nil();
  inline Storage first = WordArray::nil();
  inline Storage floor = WordArray::nil();
  inline Storage format = WordArray::nil();
  inline Storage gradeDown = WordArray::nil();
  inline Storage gradeUp = WordArray::nil();
  inline Storage group = WordArray::nil();
  inline Storage negate = WordArray::nil();
  inline Storage inot = WordArray::nil();
  inline Storage reciprocal = WordArray::nil();
  inline Storage reverse = WordArray::nil();
  inline Storage shape = WordArray::nil();
  inline Storage size = WordArray::nil();
  inline Storage transpose = WordArray::nil();
  inline Storage unique = WordArray::nil();
  inline Storage undefined = WordArray::nil();

  // Extension Monads
  inline Storage evaluate = WordArray::nil();
  inline Storage erase = WordArray::nil();
  inline Storage truth = WordArray::nil();
  inline Storage lift = WordArray::nil();
  inline Storage occurs = WordArray::nil();
  inline Storage range = WordArray::nil();

  // Dyads
  inline Storage amend = WordArray::nil();
  inline Storage cut = WordArray::nil();
  inline Storage divide = WordArray::nil();
  inline Storage drop = WordArray::nil();
  inline Storage equal = WordArray::nil();
  inline Storage find = WordArray::nil();
  inline Storage form = WordArray::nil();
  inline Storage format2 = WordArray::nil();
  inline Storage index = WordArray::nil();
  inline Storage integerDivide = WordArray::nil();
  inline Storage join = WordArray::nil();
  inline Storage append = WordArray::nil();
  inline Storage less = WordArray::nil();
  inline Storage match = WordArray::nil();
  inline Storage max = WordArray::nil();
  inline Storage min = WordArray::nil();
  inline Storage minus = WordArray::nil();
  inline Storage more = WordArray::nil();
  inline Storage plus = WordArray::nil();
  inline Storage power = WordArray::nil();
  inline Storage remainder = WordArray::nil();
  inline Storage reshape = WordArray::nil();
  inline Storage rotate = WordArray::nil();
  inline Storage split = WordArray::nil();
  inline Storage take = WordArray::nil();
  inline Storage times = WordArray::nil();
  inline Storage resolve = WordArray::nil();

  // Lens
  inline Storage retrieve = WordArray::nil();

  // Triads
  inline Storage store = WordArray::nil();
  inline Storage bind = WordArray::nil();
}

#endif //VERBS_H
