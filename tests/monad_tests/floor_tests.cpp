//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("floor integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{5, iota::floor}) == 5);
}

TEST_CASE("floor real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{5.0f, iota::floor}) == 5);
}

TEST_CASE("floor list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, iota::floor}) == a{});
  REQUIRE(evalExpression({{0, 1, 2}, iota::floor}) == a{0, 1, 2});
  REQUIRE(evalExpression({{0.1f, 1.5f, 2.9f}, iota::floor}) == a{0, 1, 2});
  REQUIRE(evalExpression({{1, 2.0f, 3, 4, 5}, iota::floor}) == a{1, 2, 3, 4, 5});
}

// FIXME - first dictionary