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

  REQUIRE(evalExpression({nil, equal, nil}) == nil);
  REQUIRE(evalExpression({{1}, equal, {1}}) == a{1});
  REQUIRE(evalExpression({{1}, equal, {2}}) == a{0});

  REQUIRE(evalExpression({{1}, equal, {1}}) == a{1});
  REQUIRE(evalExpression({{1}, equal, {2}}) == a{0});

  REQUIRE(evalExpression({{1, 2.0f}, equal, {1, 2.0f}}) == a{1, 1});
  REQUIRE(evalExpression({{1, 2.0f}, equal, {2, 1.0f}}) == a{0, 0});
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
  using namespace std::string_literals;

  REQUIRE(evalExpression({"a"s, equal, "a"s}) == 1);
  REQUIRE(evalExpression({"a"s, equal, "b"s}) == 0);
  REQUIRE(evalExpression({"abc"s, equal, "abc"s}) == 1);
  REQUIRE(evalExpression({"abc"s, equal, "abd"s}) == 0);
}