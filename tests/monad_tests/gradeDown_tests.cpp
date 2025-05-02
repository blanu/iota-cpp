//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("gradeDown integers", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{0, 1, 0, 2}, gradeDown}) == a{4, 2, 1, 3});
  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, gradeDown}) == a{4, 2, 1, 3});
  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, gradeDown}) == a{4, 2, 1, 3});
}

TEST_CASE("gradeDown string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({"abac", gradeDown}) == a{4, 2, 1, 3});
}
