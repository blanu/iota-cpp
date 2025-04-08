//
// Created by Dr. Brandon Wiley on 4/1/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("enclose integer")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{5, enclose}) == cppValue(ints{5}));
}

TEST_CASE("enclose real")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{5.0f, enclose}) == cppValue(floats{5.0f}));
}

TEST_CASE("enclose list")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{0, 1, 2}, enclose}) == cppValue(CppValues{ints{0, 1, 2}}));
  REQUIRE(evalExpression(cppValues{floats{0.0f, 1.0f, 2.0f}, enclose}) == cppValue(CppValues{floats{0.0f, 1.0f, 2.0f}}));
  REQUIRE(evalExpression(cppValues{CppValues{0.0f, 1, 2.0f}, enclose}) == cppValue(CppValues{cppValue{CppValues{0.0f, 1, 2.0f}}}));
}

TEST_CASE("enclose character")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{'a', enclose}) == cppValue{"a"});
}

TEST_CASE("enclose string")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"a", enclose}) == cppValue(CppValues{cppValue("a")}));
}

// FIXME
// TEST_CASE("enclose dictionary")
// {
//   using namespace iota;
//
//   cppValues input = cppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}, enclose};
//   CppValue result = evalExpression(input);
//   CppValue correct = cppValue(CppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}});
//   REQUIRE(result == correct);
// }
