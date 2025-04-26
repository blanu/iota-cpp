//
// Created by Dr. Brandon Wiley on 4/1/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("enclose integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5, enclose}) == CppValues{5});
}

TEST_CASE("enclose real", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5.0f, enclose}) == CppValues{5.0f});
}

// FIXME
TEST_CASE("enclose list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({CppValues{0, 1, 2}, enclose}) == cppValue{CppValues{cppValue{CppValues{0, 1, 2}}}});
  REQUIRE(evalExpression({CppValues{0.0f, 1.0f, 2.0f}, enclose}) == cppValue{CppValues{cppValue{CppValues{0.0f, 1.0f, 2.0f}}}});
//  FIXME
//  REQUIRE(evalExpression({CppValues{0.0f, 1, 2.0f}, enclose}) == CppValues{CppValues{0.0f, 1, 2.0f}});
}

// FIXME
// TEST_CASE("enclose character", "[monad]")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression({'a', enclose}) == "a");
// }

// FIXME
// TEST_CASE("enclose string", "[monad]")
// {
//   using namespace iota;
//
//   REQUIRE(evalExpression({"a", enclose}) == cppValue(CppValues{cppValue("a")}));
// }

// FIXME
// TEST_CASE("enclose dictionary", "[monad]")
// {
//   using namespace iota;
//
//   cppValues input = cppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}, enclose};
//   CppValue result = evalExpression(input);
//   CppValue correct = cppValue(CppValues{std::unordered_map<CppValue, CppValue>{{1, 2}}});
//   REQUIRE(result == correct);
// }
