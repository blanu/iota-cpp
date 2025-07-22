//
// Created by Dr. Brandon Wiley on 4/11/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("cut list integer", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({nil, cut, 0}) == a{nil});
  REQUIRE(evalExpression({{1}, cut, 0}) == a{nil, {1}});
  REQUIRE(evalExpression({{1}, cut, 1}) == a{{1}, nil});
  REQUIRE(evalExpression({{2, 3}, cut, 1}) == a{{2}, {3}});

  REQUIRE(evalExpression({{1.0f}, cut, 0}) == a{nil, {1.0f}});
  REQUIRE(evalExpression({{1.0f}, cut, 1}) == a{{1.0f}, nil});
  REQUIRE(evalExpression({{2.0f, 3.0f}, cut, 1}) == a{{2.0f}, {3.0f}});

  REQUIRE(evalExpression({{1, 2.0f}, cut, 0}) == a{nil, {1, 2.0f}});
  REQUIRE(evalExpression({{1, 2.0f}, cut, 1}) == a{{1}, {2.0f}});
}

TEST_CASE("cut list integers", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({nil, cut, nil}) == a{nil});

  // FIXME - these should be errors
  //REQUIRE(evalExpression({nil, cut, {0}}) == a{{0}});
  //REQUIRE(evalExpression({nil, cut, {1}}) == a{{1}});
}
