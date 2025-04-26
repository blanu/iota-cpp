//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("gradeDown integers", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({CppValues{0, 1, 0, 2}, gradeDown}) == CppValues{4, 2, 1, 3});
  REQUIRE(evalExpression({CppValues{0.0f, 1.0f, 0.0f, 2.0f}, gradeDown}) == CppValues{4, 2, 1, 3});
  REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, gradeDown}) == CppValues{4, 2, 1, 3});
}

TEST_CASE("gradeDown string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"abac", gradeDown}) == CppValues{4, 2, 1, 3});
}
