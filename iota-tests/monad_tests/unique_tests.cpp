//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("unique list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{0, 1, 0, 2}, unique}) == a{0, 1, 2});
  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, unique}) == a{0.0f, 1.0f, 2.0f});
  auto result = evalExpression({{0, 1.0f, 0, 2.0f}, unique});
  auto correct = a{0, 1.0f, 2.0f};
  REQUIRE(result == correct);
  // REQUIRE(evalExpression({CppValues{0, 1.0f, 0, 2.0f}, unique}) == CppValues{0, 1.0f, 2.0f});
  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, unique}) == a{0, 1.0f, 2.0f});
}
