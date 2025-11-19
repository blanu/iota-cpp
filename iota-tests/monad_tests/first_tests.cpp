//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("first integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5, first}) == 5);
}

TEST_CASE("first real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5.0f, first}) == 5.0f);
}

TEST_CASE("first list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, first}) == a{});
  REQUIRE(evalExpression({{0, 1, 2}, first}) == 0);
  REQUIRE(evalExpression({{0.0f, 1.0f, 2.0f}, first}) == 0.0f);
  REQUIRE(evalExpression({{0, 1.0f, 2}, first}) == 0);
}

TEST_CASE("first character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', first}) == 'a');
}

TEST_CASE("first string", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"abc"s, first}) == 'a');
}

// FIXME - first dictionary