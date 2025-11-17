#ifndef SYMBOLS_H_
#define SYMBOLS_H_

#include "nouns/symbol.h"

class Nilads
{
  public:
    static void initialize();

    static int symbols;
};

// Monads
class Monads
{
  public:
    static void initialize();

    static int atom;
    static int ichar;
    static int enclose;
    static int enumerate;
    static int expand;
    static int first;
    static int floor;
    static int format;
    static int gradeDown;
    static int gradeUp;
    static int group;
    static int negate;
    static int inot;
    static int reciprocal;
    static int reverse;
    static int shape;
    static int size;
    static int transpose;
    static int unique;
    static int count;
    static int undefined;

    static int evaluate;
    static int erase;
    static int truth;
    static int lift;
    static int occurs;
};

// Dyads
class Dyads
{
  public:
    static void initialize();

    static int amend;
    static int cut;
    static int divide;
    static int drop;
    static int equal;
    static int find;
    static int form;
    static int format2;
    static int index;
    static int indexInDepth;
    static int integerDivide;
    static int join;
    static int less;
    static int match;
    static int max;
    static int min;
    static int minus;
    static int more;
    static int plus;
    static int power;
    static int remainder;
    static int reshape;
    static int rotate;
    static int split;
    static int take;
    static int times;

    static int applyMonad;
    static int retype;
    static int causes;
    static int because;
    static int then;
    static int bind;
    static int retrieve;
    static int mutate;
};

// Triads
class Triads
{
  public:
    static void initialize();

    static int applyDyad;
};

// MonadicAdverbs
class MonadicAdverbs
{
  public:
    static void initialize();

    static int converge;
    static int each;
    static int eachPair;
    static int over;
    static int scanConverging;
    static int scanOver;
};

// Dyadic Adverbs
class DyadicAdverbs
{
  public:
    static void initialize();

    static int each2;
    static int eachLeft;
    static int eachRight;
    static int overNeutral;
    static int whileOne;
    static int iterate;
    static int scanOverNeutral;
    static int scanWhileOne;
    static int scanIterating;
};

#endif