//
// Created by Dr. Brandon Wiley on 4/11/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("cut integer list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({0, cut, ints{}}) == CppValues{ints{}});

  REQUIRE(evalExpression({0, cut, ints{1}}) == CppValues{ints{}, ints{1}});
  REQUIRE(evalExpression({1, cut, ints{1}}) == CppValues{ints{1}, ints{}});
  REQUIRE(evalExpression({1, cut, ints{2, 3}}) == CppValues{ints{2}, ints{3}});

  REQUIRE(evalExpression({0, cut, floats{1.0f}}) == CppValues{ints{}, floats{1.0f}});
  REQUIRE(evalExpression({1, cut, floats{1.0f}}) == CppValues{floats{1.0f}, floats{}});
  REQUIRE(evalExpression({1, cut, floats{2.0f, 3.0f}}) == CppValues{floats{2.0f}, floats{3.0f}});

  REQUIRE(evalExpression({0, cut, CppValues{1, 2.0f}}) == CppValues{ints{}, CppValues{1, 2.0f}});
  REQUIRE(evalExpression({1, cut, CppValues{1, 2.0f}}) == CppValues{ints{1}, floats{2.0f}});
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

  REQUIRE(evalExpression({ints{}, cut, 0}) == CppValues{ints{}});
  REQUIRE(evalExpression({ints{1}, cut, 0}) == CppValues{ints{}, ints{1}});
  REQUIRE(evalExpression({ints{1}, cut, 1}) == CppValues{ints{1}, ints{}});
  REQUIRE(evalExpression({ints{2, 3}, cut, 1}) == CppValues{ints{2}, ints{3}});

  REQUIRE(evalExpression({floats{1.0f}, cut, 0}) == CppValues{ints{}, floats{1.0f}});
  REQUIRE(evalExpression({floats{1.0f}, cut, 1}) == CppValues{floats{1.0f}, ints{}});
  REQUIRE(evalExpression({floats{2.0f, 3.0f}, cut, 1}) == CppValues{floats{2.0f}, floats{3.0f}});

  REQUIRE(evalExpression({CppValues{1, 2.0f}, cut, 0}) == CppValues{ints{}, CppValues{1, 2.0f}});
  REQUIRE(evalExpression({CppValues{1, 2.0f}, cut, 1}) == CppValues{ints{1}, floats{2.0f}});
}
