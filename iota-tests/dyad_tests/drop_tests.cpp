//
// Created by Dr. Brandon Wiley on 4/17/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("drop list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{}, drop, 0}) == a{});
  REQUIRE(evalExpression({{}, drop, 1}) == a{});
  REQUIRE(evalExpression({{}, drop, -1}) == a{});
  REQUIRE(evalExpression({{}, drop, 10}) == a{});
  REQUIRE(evalExpression({{}, drop, -10}) == a{});

  REQUIRE(evalExpression({{0, 1, 0, 2}, drop, 0}) == a{0, 1, 0, 2});
  REQUIRE(evalExpression({{0, 1, 0, 2}, drop, 2}) == a{0, 2});
  REQUIRE(evalExpression({{0, 1, 0, 2}, drop, -2}) == a{0, 1});
  REQUIRE(evalExpression({{0, 1, 0, 2}, drop, 100}) == a{});
  REQUIRE(evalExpression({{0, 1, 0, 2}, drop, -100}) == a{});

  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, drop, 0}) == a{0.0f, 1.0f, 0.0f, 2.0f});
  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, drop, 2}) == a{0.0f, 2.0f});
  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, drop, -2}) == a{0.0f, 1.0f});
  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, drop, 100}) == a{});
  REQUIRE(evalExpression({{0.0f, 1.0f, 0.0f, 2.0f}, drop, -100}) == a{});

  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, drop, 0}) == a{0, 1.0f, 0, 2.0f});
  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, drop, 2}) == a{0, 2.0f});
  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, drop, -2}) == a{0, 1.0f});
  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, drop, 100}) == a{});
  REQUIRE(evalExpression({{0, 1.0f, 0, 2.0f}, drop, -100}) == a{});
}
