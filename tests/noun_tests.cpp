//
// Created by Dr. Brandon Wiley on 3/29/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("small words")
{
  REQUIRE(evalNoun(0) == cppValue(0));
  REQUIRE(evalNoun(1) == cppValue(1));
  REQUIRE(evalNoun(-1) == cppValue(-1));
  REQUIRE(evalNoun(256) == cppValue(256)); // requires two bytes
  REQUIRE(evalNoun(-256) == cppValue(-256));
  REQUIRE(evalNoun(2048) == cppValue(2048));
  REQUIRE(evalNoun(-2048) == cppValue(-2048));
  REQUIRE(evalNoun(32768) == cppValue(32768)); // requires two bytes
  REQUIRE(evalNoun(-32768) == cppValue(-32768)); // requires three bytes
  REQUIRE(evalNoun(8388608) == cppValue(8388608)); // requires three bytes
  REQUIRE(evalNoun(-8388608) == cppValue(-8388608)); // requires three bytes
  REQUIRE(evalNoun(16777215) == cppValue(16777215)); // three-byte maxint
  REQUIRE(evalNoun(-16777215) == cppValue(-16777215));
}

// FIXME
// TEST_CASE("big words")
// {
//   REQUIRE(evalNoun(2147483648) == 2147483648);  // requires 4 bytes
//   REQUIRE(evalNoun(-2147483648) == -2147483648);  // requires 4 bytes
//   REQUIRE(evalNoun(4294967295) == 4294967295); // unsigned 32-bit maxint
//   REQUIRE(evalNoun(-4294967295) == -4294967295);
//   REQUIRE(evalNoun(549755813888) == 549755813888); // requires 5 bytes
//   REQUIRE(evalNoun(-549755813888) == -549755813888); // requires 5 bytes
//   REQUIRE(evalNoun(10000000000) == 10000000000); // too big for 32-bit
//   REQUIRE(evalNoun(-10000000000) == -10000000000);
//   REQUIRE(evalNoun(9223372036854775807) == 9223372036854775807); // signed 64-bit max
//   REQUIRE(evalNoun(-9223372036854775807) == -9223372036854775807); // signed 64-bit max
// }

TEST_CASE("float")
{
  REQUIRE(evalNoun(0.0f) == cppValue(0.0f));
  REQUIRE(evalNoun(1.0f) == cppValue(1.0f));
  REQUIRE(evalNoun(-1.0f) == cppValue(-1.0f));
  REQUIRE(evalNoun(100.0f) == cppValue(100.0f));
  REQUIRE(evalNoun(-100.0f) == cppValue(-100.0f));
}

TEST_CASE("words")
{
  REQUIRE(evalNoun(ints{0}) == cppValue(ints{0}));
  REQUIRE(evalNoun(ints{1}) == cppValue(ints{1}));
  REQUIRE(evalNoun(ints{-1}) == cppValue(ints{-1}));
  REQUIRE(evalNoun(ints{256}) == cppValue(ints{256}));
  REQUIRE(evalNoun(ints{-256}) == cppValue(ints{-256}));

  REQUIRE(evalNoun(ints{0, 1}) == cppValue(ints{0, 1}));
  REQUIRE(evalNoun(ints{1, 2}) == cppValue(ints{1, 2}));
  REQUIRE(evalNoun(ints{-1, 1}) == cppValue(ints{-1, 1}));
  REQUIRE(evalNoun(ints{256, 1024}) == cppValue(ints{256, 1024}));
  REQUIRE(evalNoun(ints{-256, -1024}) == cppValue(ints{-256, -1024}));
}

TEST_CASE("floats")
{
  REQUIRE(evalNoun(floats{0.0f}) == cppValue(floats{0.0f}));
  REQUIRE(evalNoun(floats{1.0f}) == cppValue(floats{1.0f}));
  REQUIRE(evalNoun(floats{-1.0f}) == cppValue(floats{-1.0f}));
  REQUIRE(evalNoun(floats{256.0f}) == cppValue(floats{256.0f}));
  REQUIRE(evalNoun(floats{-256.0f}) == cppValue(floats{-256.0f}));

  REQUIRE(evalNoun(floats{0.0f, 1.0f}) == cppValue(floats{0.0f, 1.0f}));
  REQUIRE(evalNoun(floats{1.0f, 2.0f}) == cppValue(floats{1.0f, 2.0f}));
  REQUIRE(evalNoun(floats{-1.0f, 1.0f}) == cppValue(floats{-1.0f, 1.0f}));
  REQUIRE(evalNoun(floats{256.0f, 1024.0f}) == cppValue(floats{256.0f, 1024.0f}));
  REQUIRE(evalNoun(floats{-256.0f, -1024.0f}) == cppValue(floats{-256.0f, -1024.0f}));
}

TEST_CASE("mixed")
{
  REQUIRE(evalNoun(CppValues{0, 0.0f}) == cppValue(CppValues{0, 0.0f}));
  REQUIRE(evalNoun(CppValues{1.0f, 1}) == cppValue(CppValues{1.0f, 1}));
  REQUIRE(evalNoun(CppValues{0, ints{0}}) == cppValue(CppValues{0, ints{0}}));
  REQUIRE(evalNoun(CppValues{1.0f, floats{2.0f}}) == cppValue(CppValues{1.0f, floats{2.0f}}));
  REQUIRE(evalNoun(CppValues{ints{0}, ints{0}}) == cppValue(CppValues{ints{0}, ints{0}}));
  REQUIRE(evalNoun(CppValues{ints{1}, ints{2}}) == cppValue(CppValues{ints{1}, ints{2}}));
  REQUIRE(evalNoun(CppValues{floats{1.0f}, floats{2.0f}}) == cppValue(CppValues{floats{1.0f}, floats{2.0f}}));
}

TEST_CASE("character")
{
  REQUIRE(evalNoun('a') == cppValue('a'));
  REQUIRE(evalNoun('b') == cppValue('b'));
  REQUIRE(evalNoun('\x00') == cppValue('\x00'));
}

TEST_CASE("string")
{
  REQUIRE(evalNoun("a") == cppValue("a"));
  REQUIRE(evalNoun("b") == cppValue("b"));
  REQUIRE(evalNoun("ab") == cppValue("ab"));
  REQUIRE(evalNoun("😀") == cppValue("😀"));
}

TEST_CASE("eval")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{0, negate}) == cppValue(0));
  REQUIRE(evalExpression(cppValues{1, negate}) == cppValue(-1));
  REQUIRE(evalExpression(cppValues{2, negate}) == cppValue(-2));
  REQUIRE(evalExpression(cppValues{-2, negate}) == cppValue(2));

  REQUIRE(evalExpression(cppValues{1, negate, negate}) == cppValue(1));
  REQUIRE(evalExpression(cppValues{1, negate, negate, negate}) == cppValue(-1));
}