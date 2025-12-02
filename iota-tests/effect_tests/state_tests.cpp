//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("state get", "[effect]")
{
  using namespace iota;

  auto result = evalExpression({get});
  REQUIRE(result == a{});
}

TEST_CASE("state put get", "[effect]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, put, then, get}) == 1);
}

TEST_CASE("state modify", "[effect]")
{
  using namespace iota;

  auto result = evalExpression({1, put, then, negate, modify});
  REQUIRE(result == -1);
}

TEST_CASE("state pull", "[effect]")
{
  using namespace  iota;

  auto lens = l({1});
  auto result = evalExpression({{3, 4, 5}, put, then, lens, pull});
  REQUIRE(result == 3);
}

TEST_CASE("state push", "[effect]")
{
  using namespace iota;

  auto lens = l({1});
  auto result = evalExpression({{3, 4, 5}, put, then, 2, push, lens});
  REQUIRE(result == a{2, 4, 5});
}