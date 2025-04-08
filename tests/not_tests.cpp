//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("not integer")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{0, inot}) == cppValue(1));
  REQUIRE(evalExpression(cppValues{5, inot}) == cppValue(0));
}

TEST_CASE("not real")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{0.0f, inot}) == cppValue(1));
  REQUIRE(evalExpression(cppValues{5.0f, inot}) == cppValue(0));
}

TEST_CASE("not list")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{}, inot}) == cppValue(1));
  REQUIRE(evalExpression(cppValues{ints{0, 1, 2}, inot}) == cppValue(ints{1, 0, 0}));
  REQUIRE(evalExpression(cppValues{floats{0.0f, 1.0f, 2.0f}, inot}) == cppValue(ints{1, 0, 0}));
  REQUIRE(evalExpression(cppValues{CppValues{0, 1.0f, 2}, inot}) == cppValue(ints{1, 0, 0}));
}

TEST_CASE("not character")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{'a', inot}) == cppValue{0});
}

TEST_CASE("not string")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"", inot}) == cppValue{1});
  REQUIRE(evalExpression(cppValues{"a", inot}) == cppValue{0});
}

// FIXME
// TEST_CASE("not dictionary")
// {
//   using namespace iota;
//
//   cppValues input = cppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}, enclose};
//   CppValue result = evalExpression(input);
//   CppValue correct = cppValue(CppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}});
//   REQUIRE(result == correct);
// }
