//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("expand ref", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0, expand}) == ints{});
  REQUIRE(evalExpression({5, expand}) == ints{0, 0, 0, 0, 0});
  REQUIRE(evalExpression({ints{1, 2, 3}, expand}) == ints{0, 1, 1, 2, 2, 2});
  REQUIRE(evalExpression({ints{0, 1, 0, 1, 0}, expand}) == ints{1, 3});
}