//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("shape integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5, shape}) == 0);
}

TEST_CASE("shape real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5.5f, shape}) == 0);
}

TEST_CASE("shape list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{}, shape}) == 0);
  REQUIRE(evalExpression({ints{0, 1, 2}, shape}) == ints{3});
  REQUIRE(evalExpression({floats{0.1f, 1.5f, 2.9f}, shape}) == ints{3});
  REQUIRE(evalExpression({floats{0, 1.0f, 2}, shape}) == ints{3});
  REQUIRE(evalExpression({CppValues{0, 1, ints{1, 2, 3}}, shape}) == ints{3});
  REQUIRE(evalExpression({CppValues{ints{0}, ints{1}, ints{0}}, shape}) == ints{3, 1});
}
