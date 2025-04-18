//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("find ref", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{1, 2, 3, 1, 2, 1}, find, 1}) == ints{1, 4, 6});
  REQUIRE(evalExpression({ints{1, 2, 3}, find, 4}) == ints{});
  REQUIRE(evalExpression({"hello", find, 'l'}) == ints{3, 4});
  REQUIRE(evalExpression({"xyyyyz", find, "yy"}) == ints{2, 3, 4});
  REQUIRE(evalExpression({"", find, ""}) == ints{1});
  // FIXME - dictionaries
}

