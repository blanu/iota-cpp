#ifndef SYMBOLS_H_
#define SYMBOLS_H_

#include "nouns/symbol.h"

class Nilads
{
  public:
    static void initialize();

    inline static int symbols;
};

// Monads
class Monads
{
  public:
    static void initialize();

    inline static int atom;
    inline static int ichar;
    inline static int enclose;
    inline static int enumerate;
    inline static int expand;
    inline static int first;
    inline static int floor;
    inline static int format;
    inline static int gradeDown;
    inline static int gradeUp;
    inline static int group;
    inline static int negate;
    inline static int inot;
    inline static int reciprocal;
    inline static int reverse;
    inline static int shape;
    inline static int size;
    inline static int transpose;
    inline static int unique;
    inline static int count;
    inline static int undefined;

    inline static int evaluate;
    inline static int erase;
    inline static int truth;
    inline static int lift;
    inline static int occurs;
    inline static int range;
};

// Dyads
class Dyads
{
  public:
    static void initialize();

    inline static int amend;
    inline static int cut;
    inline static int divide;
    inline static int drop;
    inline static int equal;
    inline static int find;
    inline static int form;
    inline static int format2;
    inline static int index;
    inline static int indexInDepth;
    inline static int integerDivide;
    inline static int join;
    inline static int append;
    inline static int less;
    inline static int match;
    inline static int max;
    inline static int min;
    inline static int minus;
    inline static int more;
    inline static int plus;
    inline static int power;
    inline static int remainder;
    inline static int reshape;
    inline static int rotate;
    inline static int split;
    inline static int take;
    inline static int times;

    inline static int applyMonad;
    inline static int retype;
    inline static int causes;
    inline static int because;
    inline static int then;
    inline static int bind;
    inline static int retrieve;
    inline static int resolve;
};

// Triads
class Triads
{
  public:
    static void initialize();

    inline static int applyDyad;
    inline static int store;
    inline static int bind;
};

// MonadicAdverbs
class MonadicAdverbs
{
  public:
    static void initialize();

    inline static int converge;
    inline static int each;
    inline static int eachPair;
    inline static int over;
    inline static int scanConverging;
    inline static int scanOver;
};

// Dyadic Adverbs
class DyadicAdverbs
{
  public:
    static void initialize();

    inline static int each2;
    inline static int eachLeft;
    inline static int eachRight;
    inline static int overNeutral;
    inline static int whileOne;
    inline static int iterate;
    inline static int scanOverNeutral;
    inline static int scanWhileOne;
    inline static int scanIterating;
};

// Triadic Adverbs
class TriadicAdverbs
{
  public:
    static void initialize();

    inline static int till;
};

#endif