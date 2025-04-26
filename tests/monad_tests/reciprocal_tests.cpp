//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("reciprocal integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({2, reciprocal}) == (1.0f / 2.0f));
}

TEST_CASE("reciprocal real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({2.0f, reciprocal}) == (1.0f / 2.0f));
}


TEST_CASE("reciprocal list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({CppValues{}, reciprocal}) == CppValues{});
  REQUIRE(evalExpression({CppValues{2, 3}, reciprocal}) == CppValues{1.0f/2.0f, 1.0f/3.0f});
  REQUIRE(evalExpression({CppValues{2.0f, 3.0f}, reciprocal}) == CppValues{1.0f/2.0f, 1.0f/3.0f});
  REQUIRE(evalExpression({CppValues{2, 4.0f}, reciprocal}) == CppValues{1.0f/2.0f, 1.0f/4.0f});
}
