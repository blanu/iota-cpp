//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("find ref", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{1, 2, 3, 1, 2, 1}, find, 1}) == a{1, 4, 6});
  REQUIRE(evalExpression({{1, 2, 3}, find, 4}) == a{});
  REQUIRE(evalExpression({"hello", find, 'l'}) == a{3, 4});
  REQUIRE(evalExpression({"xyyyyz", find, "yy"}) == a{2, 3, 4});
  REQUIRE(evalExpression({"", find, ""}) == a{1});
  // FIXME - dictionaries
}

