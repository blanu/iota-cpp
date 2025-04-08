//
// Created by Dr. Brandon Wiley on 4/1/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("char integer")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{1, ichar}) == cppValue('\x01'));
}

TEST_CASE("char list")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{}, ichar}) == cppValue(ints{}));

  REQUIRE(evalExpression(cppValues{ints{2, 3}, ichar}) == cppValue(CppValues{'\x02', '\x03'}));
}

TEST_CASE("char character")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{'a', ichar}) == cppValue('a'));
}
