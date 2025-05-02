//
// Created by Dr. Brandon Wiley on 3/31/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("atom integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, atom}) == 1);
}

TEST_CASE("atom real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1.0f, atom}) == 1);
}

TEST_CASE("atom list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, atom}) == 1);

  REQUIRE(evalExpression({{2, 3}, atom}) == 0);
  REQUIRE(evalExpression({{2.0f, 3.0f}, atom}) == 0);
  REQUIRE(evalExpression({{2, 3.0f}, atom}) == 0);
}

TEST_CASE("atom character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', atom}) == 1);
}

TEST_CASE("atom string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({"", atom}) == 1);
  REQUIRE(evalExpression({"abc", atom}) == 0);
}

// TEST_CASE("atom dictionary", "[monad]")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression({std::unordered_map<CppValue, CppValue>{{1, 2}}, atom}) == 1);
// }
