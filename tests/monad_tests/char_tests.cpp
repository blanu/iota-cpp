//
// Created by Dr. Brandon Wiley on 4/1/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("char integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, ichar}) == '\x01');
}

TEST_CASE("char list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, ichar}) == a{});

  REQUIRE(evalExpression({{2, 3}, ichar}) == a{'\x02', '\x03'});
}

TEST_CASE("char character", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', ichar}) == 'a');
}
