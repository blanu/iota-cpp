//
// Created by Dr. Brandon Wiley on 3/29/25.
//

#include <catch2/catch_all.hpp>

#include <string>

#include "api.h"

TEST_CASE("small words", "[monad]")
{
  REQUIRE(evalNoun(0) == 0);
  REQUIRE(evalNoun(1) == 1);
  REQUIRE(evalNoun(-1) == -1);
  REQUIRE(evalNoun(256) == 256); // requires two bytes
  REQUIRE(evalNoun(-256) == -256);
  REQUIRE(evalNoun(2048) == 2048);
  REQUIRE(evalNoun(-2048) == -2048);
  REQUIRE(evalNoun(32768) == 32768); // requires two bytes
  REQUIRE(evalNoun(-32768) == -32768); // requires three bytes
  REQUIRE(evalNoun(8388608) == 8388608); // requires three bytes
  REQUIRE(evalNoun(-8388608) == -8388608); // requires three bytes
  REQUIRE(evalNoun(16777215) == 16777215); // three-byte maxint
  REQUIRE(evalNoun(-16777215) == -16777215);
}

// FIXME
// TEST_CASE("big words", "[monad]")
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

TEST_CASE("float", "[monad]")
{
  REQUIRE(evalNoun(0.0f) == 0.0f);
  REQUIRE(evalNoun(1.0f) == 1.0f);
  REQUIRE(evalNoun(-1.0f) == -1.0f);
  REQUIRE(evalNoun(100.0f) == 100.0f);
  REQUIRE(evalNoun(-100.0f) == -100.0f);
}

TEST_CASE("words", "[monad]")
{
  REQUIRE(evalNoun({0}) == 0);
  REQUIRE(evalNoun({1}) == 1);
  REQUIRE(evalNoun({-1}) == -1);
  REQUIRE(evalNoun({256}) == 256);
  REQUIRE(evalNoun({-256}) == -256);

  REQUIRE(evalNoun(CppValues{0, 1}) == CppValues{0, 1});
  REQUIRE(evalNoun(CppValues{1, 2}) == CppValues{1, 2});
  REQUIRE(evalNoun(CppValues{-1, 1}) == CppValues{-1, 1});
  REQUIRE(evalNoun(CppValues{256, 1024}) == CppValues{256, 1024});
  REQUIRE(evalNoun(CppValues{-256, -1024}) == CppValues{-256, -1024});
}

TEST_CASE("floats", "[monad]")
{
  REQUIRE(evalNoun({0.0f}) == 0.0f);
  REQUIRE(evalNoun({1.0f}) == 1.0f);
  REQUIRE(evalNoun({-1.0f}) == -1.0f);
  REQUIRE(evalNoun({256.0f}) == 256.0f);
  REQUIRE(evalNoun({-256.0f}) == -256.0f);

  REQUIRE(evalNoun(CppValues{0.0f, 1.0f}) == CppValues{0.0f, 1.0f});
  REQUIRE(evalNoun(CppValues{1.0f, 2.0f}) == CppValues{1.0f, 2.0f});
  REQUIRE(evalNoun(CppValues{-1.0f, 1.0f}) == CppValues{-1.0f, 1.0f});
  REQUIRE(evalNoun(CppValues{256.0f, 1024.0f}) == CppValues{256.0f, 1024.0f});
  REQUIRE(evalNoun(CppValues{-256.0f, -1024.0f}) == CppValues{-256.0f, -1024.0f});
}

TEST_CASE("mixed", "[monad]")
{
  REQUIRE(evalNoun(CppValues{0, 0.0f}) == CppValues{0, 0.0f});
  REQUIRE(evalNoun(CppValues{1.0f, 1}) == CppValues{1.0f, 1});
  REQUIRE(evalNoun(CppValues{0, {0}}) == CppValues{0, {0}});
  REQUIRE(evalNoun(CppValues{1.0f, {2.0f}}) == CppValues{1.0f, {2.0f}});
  REQUIRE(evalNoun(CppValues{{0}, {0}}) == CppValues{{0}, {0}});
  REQUIRE(evalNoun(CppValues{{1}, {2}}) == CppValues{{1}, {2}});
  REQUIRE(evalNoun(CppValues{{1.0f}, {2.0f}}) == CppValues{{1.0f}, {2.0f}});
}

TEST_CASE("character", "[monad]")
{
  REQUIRE(evalNoun('a') == 'a');
  REQUIRE(evalNoun('b') == 'b');
  REQUIRE(evalNoun('\x00') == '\x00');
}

TEST_CASE("string", "[monad]")
{
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalNoun("a"s) == "a"s);
  REQUIRE(evalNoun("b"s) == "b"s);
  REQUIRE(evalNoun("ab"s) == "ab"s);
  REQUIRE(evalNoun("😀"s) == "😀"s);
}

TEST_CASE("eval", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{0, negate}) == 0);
  REQUIRE(evalExpression(cppValues{1, negate}) == -1);
  REQUIRE(evalExpression(cppValues{2, negate}) == -2);
  REQUIRE(evalExpression(cppValues{-2, negate}) == 2);

  REQUIRE(evalExpression(cppValues{1, negate, negate}) == 1);
  REQUIRE(evalExpression(cppValues{1, negate, negate, negate}) == -1);
}