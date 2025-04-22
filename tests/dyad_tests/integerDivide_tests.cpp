//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("integerDivide integer integer", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, integerDivide, 1}) == 1);
  REQUIRE(evalExpression({2, integerDivide, 1}) == 2);
  REQUIRE(evalExpression({1, integerDivide, 2}) == 0);
}
