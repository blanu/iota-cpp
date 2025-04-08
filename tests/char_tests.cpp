//
// Created by Dr. Brandon Wiley on 4/1/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("char integer")
{
  using namespace iota;

  REQUIRE(evalExpression({1, ichar}) == '\x01');
}

TEST_CASE("char list")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{}, ichar}) == ints{});

  REQUIRE(evalExpression({ints{2, 3}, ichar}) == CppValues{'\x02', '\x03'});
}

TEST_CASE("char character")
{
  using namespace iota;

  REQUIRE(evalExpression({'a', ichar}) == 'a');
}
