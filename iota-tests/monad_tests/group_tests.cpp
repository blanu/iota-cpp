//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("group list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{1, 2, 3, 4}, group}) == a{{1}, {2}, {3}, {4}});
  REQUIRE(evalExpression({{1.0f, 2.0f, 3.0f, 4.0f}, group}) == a{{1}, {2}, {3}, {4}});
  REQUIRE(evalExpression({{1.0f, 2, 3.0f, 4}, group}) == a{{1}, {2}, {3}, {4}});
}

TEST_CASE("group string", "[monad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"hello foo"s, group}) == a{{1}, {2}, {3, 4}, {5, 8, 9}, {6}, {7}});
}
