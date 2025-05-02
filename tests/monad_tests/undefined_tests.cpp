//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("undefined ref", "[monad]")
{
// Examples:        :_1%0  -->  1
//           :_:{[1 2]}?3  -->  1
//               :_:valid  -->  0

  using namespace iota;

  REQUIRE(evalExpression({1, divide, 0, undefined}) == 1);
  // FIXME - undefined dictionary
  // FIXME - quoted symbol
}

TEST_CASE("undefined integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0, undefined}) == 0);
}

TEST_CASE("undefined real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0.0f, undefined}) == 0);
}

TEST_CASE("undefined list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, undefined}) == 0);
  REQUIRE(evalExpression({{0}, undefined}) == 0);
  REQUIRE(evalExpression({{0.0f}, undefined}) == 0);
  REQUIRE(evalExpression({{0.0f, 1}, undefined}) == 0);
}

TEST_CASE("undefined character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', undefined}) == 0);
}

TEST_CASE("undefined string", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({"abc", undefined}) == 0);
}

// FIXME - first dictionary
// FIXME - quoted symbol