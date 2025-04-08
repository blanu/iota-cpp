//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("gradeDown integers")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{0, 1, 0, 2}, gradeDown}) == cppValue(ints{4, 2, 1, 3}));
  REQUIRE(evalExpression(cppValues{floats{0.0f, 1.0f, 0.0f, 2.0f}, gradeDown}) == cppValue(ints{4, 2, 1, 3}));
  REQUIRE(evalExpression(cppValues{CppValues{0, 1.0f, 0, 2.0f}, gradeDown}) == cppValue(ints{4, 2, 1, 3}));
}

TEST_CASE("gradeDown string")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"abac", gradeDown}) == cppValue(ints{4, 2, 1, 3}));
}
