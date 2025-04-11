//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("group list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{1, 2, 3, 4}, group}) == CppValues{ints{1}, ints{2}, ints{3}, ints{4}});
  REQUIRE(evalExpression({floats{1.0f, 2.0f, 3.0f, 4.0f}, group}) == CppValues{ints{1}, ints{2}, ints{3}, ints{4}});
  REQUIRE(evalExpression({CppValues{1.0f, 2, 3.0f, 4}, group}) == CppValues{ints{1}, ints{2}, ints{3}, ints{4}});
}

TEST_CASE("group string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({"hello foo", group}) == CppValues{ints{1}, ints{2}, ints{3, 4}, ints{5, 8, 9}, ints{6}, ints{7}});
}
