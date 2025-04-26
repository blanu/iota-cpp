//
// Created by Dr. Brandon Wiley on 4/11/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("cut integer list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0, cut, CppValues{}}) == cppValue{CppValues{cppValue{CppValues{}}}});

  REQUIRE(evalExpression({0, cut, CppValues{1}}) == CppValues{CppValues{}, CppValues{1}});
  REQUIRE(evalExpression({1, cut, CppValues{1}}) == CppValues{CppValues{1}, CppValues{}});
  REQUIRE(evalExpression({1, cut, CppValues{2, 3}}) == CppValues{CppValues{2}, CppValues{3}});

  REQUIRE(evalExpression({0, cut, CppValues{1.0f}}) == CppValues{CppValues{}, CppValues{1.0f}});
  REQUIRE(evalExpression({1, cut, CppValues{1.0f}}) == CppValues{CppValues{1.0f}, CppValues{}});
  REQUIRE(evalExpression({1, cut, CppValues{2.0f, 3.0f}}) == CppValues{CppValues{2.0f}, CppValues{3.0f}});

  REQUIRE(evalExpression({0, cut, CppValues{1, 2.0f}}) == CppValues{CppValues{}, CppValues{1, 2.0f}});
  REQUIRE(evalExpression({1, cut, CppValues{1, 2.0f}}) == CppValues{CppValues{1}, CppValues{2.0f}});
}

//         assert_equal(eval([], cut, 0), [[]])
//
//         assert_equal(eval([1], cut, 0), [[], [1]])
//         assert_equal(eval([1], cut, 1), [[1], []])
//         assert_equal(eval([2, 3], cut, 1), [[2], [3]])
//
//         assert_equal(eval([1.0], cut, 0), [[], [1.0]])
//         assert_equal(eval([1.0], cut, 1), [[1.0], []])
//         assert_equal(eval([2.0, 3.0], cut, 1), [[2.0], [3.0]])
//
//         assert_equal(eval([1, 2.0], cut, 0), [[], [1, 2.0]])
//         assert_equal(eval([1, 2.0], cut, 1), [[1], [2.0]])
TEST_CASE("cut list integers", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({CppValues{}, cut, 0}) == cppValue{CppValues{cppValue{CppValues{}}}});
  REQUIRE(evalExpression({CppValues{1}, cut, 0}) == CppValues{CppValues{}, CppValues{1}});
  REQUIRE(evalExpression({CppValues{1}, cut, 1}) == CppValues{CppValues{1}, CppValues{}});
  REQUIRE(evalExpression({CppValues{2, 3}, cut, 1}) == CppValues{CppValues{2}, CppValues{3}});

  REQUIRE(evalExpression({CppValues{1.0f}, cut, 0}) == CppValues{CppValues{}, CppValues{1.0f}});
  REQUIRE(evalExpression({CppValues{1.0f}, cut, 1}) == CppValues{CppValues{1.0f}, CppValues{}});
  REQUIRE(evalExpression({CppValues{2.0f, 3.0f}, cut, 1}) == CppValues{CppValues{2.0f}, CppValues{3.0f}});

  REQUIRE(evalExpression({CppValues{1, 2.0f}, cut, 0}) == CppValues{CppValues{}, CppValues{1, 2.0f}});
  REQUIRE(evalExpression({CppValues{1, 2.0f}, cut, 1}) == CppValues{CppValues{1}, CppValues{2.0f}});
}
