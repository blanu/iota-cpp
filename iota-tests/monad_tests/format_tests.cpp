//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("format integer", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression(cppValues{0, format}) == cppValue("0"s));
  REQUIRE(evalExpression(cppValues{1, format}) == cppValue("1"s));
  REQUIRE(evalExpression(cppValues{-1, format}) == cppValue("-1"s));
  REQUIRE(evalExpression(cppValues{10, format}) == cppValue("10"s));
  REQUIRE(evalExpression(cppValues{-10, format}) == cppValue("-10"s));
  REQUIRE(evalExpression(cppValues{38473, format}) == cppValue("38473"s));
  REQUIRE(evalExpression(cppValues{-38473, format}) == cppValue("-38473"s));
}

TEST_CASE("format real", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression(cppValues{0.0f, format}) == cppValue("0.0"s));
  REQUIRE(evalExpression(cppValues{1.0f, format}) == cppValue("1.0"s));
  REQUIRE(evalExpression(cppValues{-1.0f, format}) == cppValue("-1.0"s));
  REQUIRE(evalExpression(cppValues{10.0f, format}) == cppValue("10.0"s));
  REQUIRE(evalExpression(cppValues{-10.0f, format}) == cppValue("-10.0"s));
  REQUIRE(evalExpression(cppValues{38473.0f, format}) == cppValue("38473.0"s));
  REQUIRE(evalExpression(cppValues{-38473.0f, format}) == cppValue("-38473.0"s));
}

TEST_CASE("format list", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({{}, format}) == "[]"s);
  REQUIRE(evalExpression({{0}, format}) == a{"0"s});
  REQUIRE(evalExpression({{0.0f}, format}) == a{"0.0"s});
  REQUIRE(evalExpression({{0, 1.0f}, format}) == a{"0"s, "1.0"s});
}

TEST_CASE("format character", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression(cppValues{'a', format}) == "a"s);
}

TEST_CASE("format string", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression(cppValues{"abc"s, format}) == "abc"s);
}

// FIXME - quoted symbol
// TEST_CASE("format quoted symbol", "[monad]")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression(cppValues{QuotedSymbol::make("x"), format}) == cppValue(":x"));
// }
