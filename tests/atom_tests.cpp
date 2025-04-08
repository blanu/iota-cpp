//
// Created by Dr. Brandon Wiley on 3/31/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("atom integer")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{1, atom}) == CppValue::t);
}

TEST_CASE("atom real")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{1.0f, atom}) == CppValue::t);
}

TEST_CASE("atom list")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{ints{}, atom}) == CppValue::t);

  REQUIRE(evalExpression(cppValues{ints{2, 3}, atom}) == CppValue::f);
  REQUIRE(evalExpression(cppValues{floats{2.0f, 3.0f}, atom}) == CppValue::f);
  REQUIRE(evalExpression(cppValues{CppValues{2, 3.0f}, atom}) == CppValue::f);
}

TEST_CASE("atom character")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{'a', atom}) == CppValue::t);
}

TEST_CASE("atom string")
{
  using namespace iota;

  REQUIRE(evalExpression(cppValues{"", atom}) == CppValue::t);
  REQUIRE(evalExpression(cppValues{"abc", atom}) == CppValue::f);
}

// TEST_CASE("atom dictionary")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression(cppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}, atom}) == CppValue::t);
// }
