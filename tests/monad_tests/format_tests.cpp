//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("format integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{0, format}) == cppValue("0"));
  REQUIRE(evalExpression(cppValues{1, format}) == cppValue("1"));
  REQUIRE(evalExpression(cppValues{-1, format}) == cppValue("-1"));
  REQUIRE(evalExpression(cppValues{10, format}) == cppValue("10"));
  REQUIRE(evalExpression(cppValues{-10, format}) == cppValue("-10"));
  REQUIRE(evalExpression(cppValues{38473, format}) == cppValue("38473"));
  REQUIRE(evalExpression(cppValues{-38473, format}) == cppValue("-38473"));
}

TEST_CASE("format real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{0.0f, format}) == cppValue("0.0"));
  REQUIRE(evalExpression(cppValues{1.0f, format}) == cppValue("1.0"));
  REQUIRE(evalExpression(cppValues{-1.0f, format}) == cppValue("-1.0"));
  REQUIRE(evalExpression(cppValues{10.0f, format}) == cppValue("10.0"));
  REQUIRE(evalExpression(cppValues{-10.0f, format}) == cppValue("-10.0"));
  REQUIRE(evalExpression(cppValues{38473.0f, format}) == cppValue("38473.0"));
  REQUIRE(evalExpression(cppValues{-38473.0f, format}) == cppValue("-38473.0"));
}

TEST_CASE("format list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{}, format}) == cppValue("[]"));
  REQUIRE(evalExpression(cppValues{ints{0}, format}) == cppValue(CppValues{cppValue("0")}));
  REQUIRE(evalExpression(cppValues{floats{0.0f}, format}) == cppValue(CppValues{cppValue("0.0")}));
  REQUIRE(evalExpression(cppValues{CppValues{0, 1.0f}, format}) == cppValue(CppValues{cppValue("0"), cppValue("1.0")}));
}

TEST_CASE("format character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{'a', format}) == cppValue("a"));
}

TEST_CASE("format string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"abc", format}) == cppValue("abc"));
}

// FIXME - quoted symbol
// TEST_CASE("format quoted symbol", "[monad]")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression(cppValues{QuotedSymbol::make("x"), format}) == cppValue(":x"));
// }
