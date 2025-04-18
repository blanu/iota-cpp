//
// Created by Dr. Brandon Wiley on 4/17/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("drop list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{}, drop, 0}) == ints{});
  REQUIRE(evalExpression({ints{}, drop, 1}) == ints{});
  REQUIRE(evalExpression({ints{}, drop, -1}) == ints{});
  REQUIRE(evalExpression({ints{}, drop, 10}) == ints{});
  REQUIRE(evalExpression({ints{}, drop, -10}) == ints{});

  REQUIRE(evalExpression({ints{0, 1, 0, 2}, drop, 0}) == ints{0, 1, 0, 2});
  REQUIRE(evalExpression({ints{0, 1, 0, 2}, drop, 2}) == ints{0, 2});
  REQUIRE(evalExpression({ints{0, 1, 0, 2}, drop, -2}) == ints{0, 1});
  REQUIRE(evalExpression({ints{0, 1, 0, 2}, drop, 100}) == ints{});
  REQUIRE(evalExpression({ints{0, 1, 0, 2}, drop, -100}) == ints{});

  REQUIRE(evalExpression({floats{0.0f, 1.0f, 0.0f, 2.0f}, drop, 0}) == floats{0.0f, 1.0f, 0.0f, 2.0f});
  REQUIRE(evalExpression({floats{0.0f, 1.0f, 0.0f, 2.0f}, drop, 2}) == floats{0.0f, 2.0f});
  REQUIRE(evalExpression({floats{0.0f, 1.0f, 0.0f, 2.0f}, drop, -2}) == floats{0.0f, 1.0f});
  REQUIRE(evalExpression({floats{0.0f, 1.0f, 0.0f, 2.0f}, drop, 100}) == ints{});
  REQUIRE(evalExpression({floats{0.0f, 1.0f, 0.0f, 2.0f}, drop, -100}) == ints{});

  REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, drop, 0}) == CppValues{0, 1.0f, 0, 2.0f});
  REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, drop, 2}) == CppValues{0, 2.0f});
  REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, drop, -2}) == CppValues{0, 1.0f});
  REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, drop, 100}) == ints{});
  REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, drop, -100}) == ints{});
}
