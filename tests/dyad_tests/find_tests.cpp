//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("find ref", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({CppValues{1, 2, 3, 1, 2, 1}, find, 1}) == CppValues{1, 4, 6});
  REQUIRE(evalExpression({CppValues{1, 2, 3}, find, 4}) == CppValues{});
  REQUIRE(evalExpression({"hello", find, 'l'}) == CppValues{3, 4});
  REQUIRE(evalExpression({"xyyyyz", find, "yy"}) == CppValues{2, 3, 4});
  REQUIRE(evalExpression({"", find, ""}) == CppValues{1});
  // FIXME - dictionaries
}

