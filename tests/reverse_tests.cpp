//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("reverse integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({2, reverse}) == 2);
}

TEST_CASE("reverse real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({2.0f, reverse}) == 2.0f);
}

TEST_CASE("reverse list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{}, reverse}) == ints{});
  REQUIRE(evalExpression({ints{2, 3}, reverse}) == ints{3, 2});
  REQUIRE(evalExpression({floats{2.0f, 3.0f}, reverse}) == floats{3.0f, 2.0f});
  REQUIRE(evalExpression({CppValues{2, 3.0f}, reverse}) == CppValues{3.0f, 2});
}

TEST_CASE("reverse character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', reverse}) == 'a');
}

// FIXME
// TEST_CASE("reverse string", "[monad]")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression({"abac", reverse}) == "caba");
// }
