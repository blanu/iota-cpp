//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("size integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0, size}) == 0);
  REQUIRE(evalExpression({1, size}) == 1);
  REQUIRE(evalExpression({-1, size}) == 1);
}

TEST_CASE("size real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0.0f, size}) == 0.0f);
  REQUIRE(evalExpression({1.0f, size}) == 1.0f);
  REQUIRE(evalExpression({-1.0f, size}) == 1.0f);
}

TEST_CASE("size list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, size}) == 0);
  REQUIRE(evalExpression({{0, 1, 2}, size}) == 3);
  REQUIRE(evalExpression({{0.1f, 1.5f, 2.9f}, size}) == 3);
  REQUIRE(evalExpression({{0, 1.0f, 2}, size}) == 3);
  REQUIRE(evalExpression({{0, 1, {1, 2, 3}}, size}) == 3);
  REQUIRE(evalExpression({{{0}, {1}, {0}}, size}) == 3);
}

TEST_CASE("size character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', size}) == 97);
}

TEST_CASE("size string", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({""s, size}) == 0);
  REQUIRE(evalExpression({"a"s, size}) == 1);
  REQUIRE(evalExpression({"abc"s, size}) == 3);
}
