//
// Created by Dr. Brandon Wiley on 12/3/25.
//

#include <catch2/catch_all.hpp>

#include <string>

#include "api.h"

TEST_CASE("remainder", "[dyad]")
{
  using namespace iota;
  using iota::remainder;

  auto result1 = evalExpression({101, remainder, 100});
  REQUIRE(result1 == 1);

  auto result2 = evalExpression({-1, remainder, 100});
  REQUIRE(result2 == 99);
}