#ifndef SYMBOLS_H_
#define SYMBOLS_H_

// Monads
class Monads
{
  public:
    static constexpr int atom = 0;
    static constexpr int ichar = 1;
    static constexpr int enclose = 3;
    static constexpr int enumerate = 4;
    static constexpr int expand = 27;
    static constexpr int first = 5;
    static constexpr int floor = 6;
    static constexpr int format = 7;
    static constexpr int gradeDown = 8;
    static constexpr int gradeUp = 9;
    static constexpr int group = 10;
    static constexpr int negate = 11;
    static constexpr int inot = 2;
    static constexpr int reciprocal = 12;
    static constexpr int reverse = 13;
    static constexpr int shape = 14;
    static constexpr int size = 15;
    static constexpr int transpose = 16;
    static constexpr int unique = 17;
    static constexpr int count = 18;
    static constexpr int undefined = 67;

    static constexpr int evaluate = 19;
    static constexpr int erase = 20;
    static constexpr int truth = 21;
};

// Dyads
class Dyads
{
  public:
    static constexpr int amend = 22;
    static constexpr int cut = 23;
    static constexpr int divide = 24;
    static constexpr int drop = 25;
    static constexpr int equal = 26;
    static constexpr int find = 28;
    static constexpr int form = 29;
    static constexpr int format2 = 30;
    static constexpr int index = 31;
    static constexpr int indexInDepth = 32;
    static constexpr int integerDivide = 33;
    static constexpr int join = 34;
    static constexpr int less = 35;
    static constexpr int match = 36;
    static constexpr int max = 37;
    static constexpr int min = 38;
    static constexpr int minus = 39;
    static constexpr int more = 40;
    static constexpr int plus = 41;
    static constexpr int power = 42;
    static constexpr int remainder = 43;
    static constexpr int reshape = 44;
    static constexpr int rotate = 45;
    static constexpr int split = 46;
    static constexpr int take = 47;
    static constexpr int times = 48;

    static constexpr int applyMonad = 49;
    static constexpr int retype = 50;

    static constexpr int cause = 67; // FIXME - renumber sequentially
};

// Triads
class Triads
{
  public:
    static constexpr int applyDyad = 51;
};

// MonadicAdverbs
class MonadicAdverbs
{
  public:
    static constexpr int converge = 52;
    static constexpr int each = 53;
    static constexpr int eachPair = 54;
    static constexpr int over = 55;
    static constexpr int scanConverging = 56;
    static constexpr int scanOver = 57;
};

// Dyadic Adverbs
class DyadicAdverbs
{
  public:
    static constexpr int each2 = 58;
    static constexpr int eachLeft = 59;
    static constexpr int eachRight = 60;
    static constexpr int overNeutral = 61;
    static constexpr int whileOne = 62;
    static constexpr int iterate = 63;
    static constexpr int scanOverNeutral = 64;
    static constexpr int scanWhileOne = 65;
    static constexpr int scanIterating = 66;
};

#endif