//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("state get", "[effect]")
{
  using namespace iota;

  auto result = evalExpression({get});
  REQUIRE(result == a{});
}

TEST_CASE("state put get", "[effect]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, put, then, get}) == 1);
}
