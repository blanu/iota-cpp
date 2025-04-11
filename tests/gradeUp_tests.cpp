//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("gradeUp integers", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{0, 1, 0, 2}, gradeUp}) == cppValue(ints{1, 3, 2, 4}));
  REQUIRE(evalExpression(cppValues{floats{0.0f, 1.0f, 0.0f, 2.0f}, gradeUp}) == cppValue(ints{1, 3, 2, 4}));
  REQUIRE(evalExpression(cppValues{CppValues{0, 1.0f, 0, 2.0f}, gradeUp}) == cppValue(ints{1, 3, 2, 4}));
}

TEST_CASE("gradeUp string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"abac", gradeUp}) == cppValue(ints{1, 3, 2, 4}));
}
