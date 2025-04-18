//
// Created by Dr. Brandon Wiley on 4/17/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("equal integer", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, equal, 0}) == 0);
  REQUIRE(evalExpression({1, equal, 2}) == 0);
  REQUIRE(evalExpression({1, equal, 1}) == 1);
  REQUIRE(evalExpression({1, equal, -1}) == 0);
}

TEST_CASE("equal real", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1.0f, equal, 0.0f}) == 0);
  REQUIRE(evalExpression({1.0f, equal, 2.0f}) == 0);
  REQUIRE(evalExpression({1.0f, equal, 1.0f}) == 1);
  REQUIRE(evalExpression({1.0f, equal, -1.0f}) == 0);
}

TEST_CASE("equal list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{}, equal, ints{}}) == ints{});
  REQUIRE(evalExpression({ints{1}, equal, ints{1}}) == ints{1});
  REQUIRE(evalExpression({ints{1}, equal, ints{2}}) == ints{0});

  REQUIRE(evalExpression({floats{1}, equal, floats{1}}) == ints{1});
  REQUIRE(evalExpression({floats{1}, equal, floats{2}}) == ints{0});

  REQUIRE(evalExpression({CppValues{1, 2.0f}, equal, CppValues{1, 2.0f}}) == ints{1, 1});
  REQUIRE(evalExpression({CppValues{1, 2.0f}, equal, CppValues{2, 1.0f}}) == ints{0, 0});
}

TEST_CASE("equal character", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', equal, 'a'}) == 1);
  REQUIRE(evalExpression({'a', equal, 'b'}) == 0);
}

TEST_CASE("equal string", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({"a", equal, "a"}) == 1);
  REQUIRE(evalExpression({"a", equal, "b"}) == 0);
  REQUIRE(evalExpression({"abc", equal, "abc"}) == 1);
  REQUIRE(evalExpression({"abc", equal, "abd"}) == 0);
}


