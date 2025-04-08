//
// Created by Dr. Brandon Wiley on 4/1/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("enclose integer")
{
  using namespace iota;

  REQUIRE(evalExpression({5, enclose}) == ints{5});
}

TEST_CASE("enclose real")
{
  using namespace iota;

  REQUIRE(evalExpression({5.0f, enclose}) == floats{5.0f});
}

TEST_CASE("enclose list")
{
  using namespace iota;

  REQUIRE(evalExpression({ints{0, 1, 2}, enclose}) == CppValues{ints{0, 1, 2}});
  REQUIRE(evalExpression({floats{0.0f, 1.0f, 2.0f}, enclose}) == CppValues{floats{0.0f, 1.0f, 2.0f}});
//  FIXME
//  REQUIRE(evalExpression({CppValues{0.0f, 1, 2.0f}, enclose}) == CppValues{CppValues{0.0f, 1, 2.0f}});
}

// FIXME
// TEST_CASE("enclose character")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression({'a', enclose}) == "a");
// }

// FIXME
// TEST_CASE("enclose string")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression({"a", enclose}) == cppValue(CppValues{cppValue("a")}));
// }

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
