//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("index list integer", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{2, 3}, iota::index, 1}) == 2);
  REQUIRE(evalExpression({floats{2.0f, 3.0f}, iota::index, 1}) == 2.0f);
  REQUIRE(evalExpression({CppValues{2, 3.0f}, iota::index, 1}) == 2);
}

TEST_CASE("index list list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{2, 3}, iota::index, ints{1, 2}}) == ints{2, 3});
  REQUIRE(evalExpression({floats{2.0f, 3.0f}, iota::index, ints{1, 2}}) == floats{2.0f, 3.0f});
  REQUIRE(evalExpression({CppValues{2, 3.0f}, iota::index, ints{1, 2}}) == CppValues{2, 3.0f});
}

TEST_CASE("index string list", "[dyad]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"abc"s, iota::index, ints{2, 3}}) == "bc"s);
}