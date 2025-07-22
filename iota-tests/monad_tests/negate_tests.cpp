//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("negate integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, negate}) == -1);
}

TEST_CASE("negate real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1.0f, negate}) == -1.0f);
}

TEST_CASE("negate list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{2, 3}, negate}) == a{-2, -3});
  REQUIRE(evalExpression({{2.0f, 3.0f}, negate}) == a{-2.0f, -3.0f});
  REQUIRE(evalExpression({{2, 3.0f}, negate}) == a{-2, -3.0f});
}
