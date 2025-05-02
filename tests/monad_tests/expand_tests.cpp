//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("expand ref", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0, expand}) == a{});
  REQUIRE(evalExpression({5, expand}) == a{0, 0, 0, 0, 0});
  REQUIRE(evalExpression({{1, 2, 3}, expand}) == a{0, 1, 1, 2, 2, 2});
  REQUIRE(evalExpression({{0, 1, 0, 1, 0}, expand}) == a{1, 3});
}